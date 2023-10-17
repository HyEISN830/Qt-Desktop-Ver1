#include "scannerworker.h"

ScannerWorker::ScannerWorker(DeviceScanner *scanner) : scanner(scanner)
{
    keepaliveTimmer = new QTimer;
    keepaliveTimmer->setInterval(5000);
    connect(keepaliveTimmer, &QTimer::timeout, this, [=] { emit sendKeepalive(keepaliveCmd); emit sendedKeep(scanner, keepaliveCmd); });
    keepaliveTimmer->start();
}

ScannerWorker::~ScannerWorker()
{
    if (keepaliveTimmer)
        keepaliveTimmer->stop();

    delete keepaliveTimmer;
}

void ScannerWorker::init()
{
    manager = new QNetworkAccessManager;
    connect(manager, &QNetworkAccessManager::finished, this, [=] (QNetworkReply *reply) {
        if (reply->error() == QNetworkReply::NoError)
        {
            QJsonDocument jdoc = QJsonDocument::fromJson(reply->readAll());
            querydone(false, reply->url(), jdoc.object());
        }
        else
        {
            querydone(true, QUrl(), QJsonObject());
        }
    });
}

void ScannerWorker::querydone(bool error, QUrl url, QJsonObject result)
{
    if (error)
    {
        emit queryFailed(scanner, barcode.trimmed().length() ? barcode : url.toString(), result);
    }
    else
    {
        QString barcodeInfoURL = settings.value("barcodeInfoURL").toString();   // 条码信息接口
        QString uploadMatlURL = settings.value("uploadMatlURL").toString();     // 上传物料到栈接口
        QString pullUpMatlURL = settings.value("pullUpMatlURL").toString();     // 指定线体机器人已码好一个物料
        QString robotParamsURL = settings.value("robotParamsURL").toString();   // 机器人参数接口
        QString commitStacksURL = settings.value("commitStacksURL").toString();   // 上转线体码垛接口

        QUrl surl = url.toString();
        surl.setQuery(QUrlQuery());
        QString u = surl.toString();

        if (u == barcodeInfoURL)
        {
            if (result["IsSucess"].toString() != "true" || !(result.contains("ModelData") && result.value("ModelData").isObject()) && result.value("ModelData").toObject().contains("isWmsSuccess"))
            {
                emit queryFailed(scanner, barcode, result);
                emit gotoError(scanner, scanner->getLine(), barcode);
            }
            else
            {
                barcodeInfoResult = result;
                emit querySuccess(scanner, barcode, result);

                QJsonObject modelData = result["ModelData"].toObject();
                if (modelData["isWmsSuccess"] == "Y")
                {
                    QStringList size = modelData["box"].toString().split("*");

                    if (size.size() == 3)
                    {
                        emit gotoNormal(scanner, scanner->getLine(), barcode);
                        requestUploadMatl(scanner->getLine(), modelData["OrderNo"].toString(), barcode, size[0].toInt(), size[1].toInt(), size[2].toInt());
                    }
                    else
                    {
                        emit gotoNormal(scanner, scanner->getLine(), barcode);
                    }
                }
                else
                {
                    emit gotoError(scanner, scanner->getLine(), barcode);
                }
            }
        }
        else if (u == uploadMatlURL)
        {
            QJsonObject rr = result["result"].toObject();
            QJsonObject rrnew = rr["newstack"].toObject();
            QUrlQuery query(url.query());

            emit uploaded(scanner, scanner->getLine(), query.queryItemValue("SN").trimmed());
            if (rr["change"].toBool())
            {
                emit gotoChange(scanner, scanner->getLine(), rrnew["orderNo"].toString(), rrnew["len"].toInt(), rrnew["wide"].toInt(), rrnew["height"].toInt());
                requestRobotParams(scanner->getLine(), rrnew["len"].toInt(), rrnew["wide"].toInt(), rrnew["height"].toInt());
            }
        }
        else if (u == pullUpMatlURL)
        {
            QJsonObject rr = result["result"].toObject();

            emit querySuccess(scanner, "API:/PullUpMatlURL", result);
            if (rr["curstack"].isObject())
            {
                emit pullUped(scanner, scanner->getLine(), rr["curstack"].toObject()["sn"].toString());
                if (rr["change"].toBool() && rr["nextstack"].isObject())
                {
                    QJsonObject next = rr["nextstack"].toObject();
                    emit gotoChange(scanner, scanner->getLine(), rr["curstack"].toObject()["orderNo"].toString(), next["len"].toInt(), next["wide"].toInt(), next["height"].toInt());
                    requestRobotParams(scanner->getLine(), next["len"].toInt(), next["wide"].toInt(), next["height"].toInt());
                }
            }
            else
            {
                emit noAvailableStack(scanner);
            }
        }
        else if (u == robotParamsURL)
        {
            QJsonObject rr = result["result"].toObject();

            emit querySuccess(scanner, "API:/RobotParamsURL", result);
            emit txRobotParams(rr["len"].toInt(), rr["wide"].toInt(), rr["height"].toInt(), rr["row"].toInt(), rr["col"].toInt(), rr["layer"].toInt());
        }
        else if (u == commitStacksURL)
        {
            QJsonObject curStack = result["result"].toObject()["curStack"].toObject();
            QJsonObject response = result["result"].toObject()["wmsresp"].toObject()["response"].toObject();
            bool offline = result["result"].toObject()["offline"].toBool();

            emit querySuccess(scanner, "API:/CommitStacksURL", result);
            if (offline || response["return"].toObject()["returnFlag"].toString() == "1")
                emit approveOut(scanner, scanner->getLine());
            else
                emit rejectOut(scanner, scanner->getLine());
        }
    }
}

void ScannerWorker::analysis(DeviceScanner *scanner, QString barcode)
{
    QUrl url(settings.value("barcodeInfoURL").toString());
    QUrlQuery query;
    QNetworkRequest request;

    // HACK: 托管开关设置
    if ((settings.value(DC::DC_TOSTRING(scanner->getLine()) + "Auto").toString()) != "true") return;

    // 扫码枪心跳
    if (barcode.length() && !barcode.indexOf("OK,KEYENCE")) return;

    barcode = barcode.trimmed().replace("\r\n", "");
    if (barcode == "NG")
    {
        emit gotoError(scanner, scanner->getLine(), barcode);
        return;
    }

    this->barcode = barcode;
    query.addQueryItem("barcode", barcode);
    url.setQuery(query);
    request.setUrl(url);
    manager->get(request);
}


void ScannerWorker::requestUploadMatl(DeviceLineNo line, QString order, QString barcode, int len, int wide, int height)
{
    QUrl url(settings.value("uploadMatlURL").toString());

    if (url.toString().trimmed().length())
    {
        QUrlQuery query;

        query.addQueryItem("OrderNo", order);
        query.addQueryItem("SN", barcode);
        query.addQueryItem("Line", QString::number((int)line));
        query.addQueryItem("Len", QString::number((int)len));
        query.addQueryItem("Wide", QString::number((int)wide));
        query.addQueryItem("Height", QString::number((int)height));
        url.setQuery(query);
        manager->get(QNetworkRequest(url));
    }
}

void ScannerWorker::requestPullUpMatl(DeviceLineNo line)
{
    // HACK: 托管开关设置
    if ((settings.value(DC::DC_TOSTRING(line) + "Auto").toString()) != "true") return;

    QUrl url(settings.value("pullUpMatlURL").toString());

    if (url.toString().trimmed().length())
    {
        QUrlQuery query;

        query.addQueryItem("line", QString::number((int)line));
        url.setQuery(query);
        manager->get(QNetworkRequest(url));
    }
}

void ScannerWorker::requestRobotParams(DeviceLineNo line, int len, int wide, int height)
{
    QUrl url(settings.value("robotParamsURL").toString());

    if (url.toString().trimmed().length())
    {
        QUrlQuery query;

        query.addQueryItem("line", QString::number((int)line));
        query.addQueryItem("len", QString::number((int)len));
        query.addQueryItem("wide", QString::number((int)wide));
        query.addQueryItem("height", QString::number((int)height));
        url.setQuery(query);
        manager->get(QNetworkRequest(url));
    }
}

void ScannerWorker::requestCommitStack(DeviceLineNo line)
{
    // HACK: 交收开关设置
    bool uncommit = (settings.value(DC::DC_TOSTRING(line) + "Commit").toString()) != "true";
    QUrl url(settings.value("commitStacksURL").toString());

    if (url.toString().trimmed().length())
    {
        QUrlQuery query;
        query.addQueryItem("url",  uncommit ? "API:/CommitLocal" : settings.value("stackUploadURL").toString());
        query.addQueryItem("line", QString::number((int)line));
        url.setQuery(query);
        manager->get(QNetworkRequest(url));
    }
}

void ScannerWorker::pullUp(DevicePLC *plc, DeviceLineNo line)
{
    if (line == scanner->getLine())
        requestPullUpMatl(line);
}

void ScannerWorker::commitReq(DevicePLC *plc, DeviceLineNo line)
{
    if (line == scanner->getLine())
        requestCommitStack(line);
}
