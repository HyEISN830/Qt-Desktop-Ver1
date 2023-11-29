#include "scannerworker.h"

ScannerWorker::ScannerWorker(DeviceScanner *scanner) : scanner(scanner)
{
    keepaliveTimmer = new QTimer;
    keepaliveTimmer->setInterval(5000);
    connect(keepaliveTimmer, &QTimer::timeout, this, [=] { emit sendKeepalive(keepaliveCmd); emit sendedKeep(scanner, keepaliveCmd); });
    connect(this, &ScannerWorker::deleteTimer, keepaliveTimmer, &QTimer::deleteLater);
    keepaliveTimmer->start();
}

ScannerWorker::~ScannerWorker()
{

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

        if (reply)
            reply->deleteLater();
    });
}

void ScannerWorker::timerDeleteLater()
{
    emit deleteTimer();
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
        QString cstackURL = settings.value("cstackURL").toString();    // 根据工单获取工单下首个物料信息以及机器人参数
        QString fbarcodeURL = settings.value("fbarcodeURL").toString();    // 为了防止未知错误, 在堡垒机上发送https延迟的问题, 因此由server代理请求
        QString startUpParamsURL = settings.value("startUpParamsURL").toString();    // 根据线体获取机器人开机启动产品参数

        QUrl surl = url.toString();
        surl.setQuery(QUrlQuery());
        QString u = surl.toString();

        if (u == fbarcodeURL)
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
//                        emit gotoNormal(scanner, scanner->getLine(), barcode);
                        requestUploadMatl(scanner->getLine(), modelData["OrderNo"].toString(), barcode, size[0].toInt(), size[1].toInt(), size[2].toInt());
                    }
                    else
                    {
//                        emit gotoNormal(scanner, scanner->getLine(), barcode);
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
                emit gotoChangeReady(scanner, scanner->getLine());
                QThread::msleep(1000);  // 发送新工单时, 保证先写入新工单, 在写入扫码ok
            }

            // 扫码处不发送判断, 扫码成功一定上传, 因此上传后可以控制产品流入正常线; 否则异常在扫码结果后直接拦截
            emit gotoNormal(scanner, scanner->getLine(), rrnew["sn"].toString());
        }
        else if (u == pullUpMatlURL)
        {
            QJsonObject rr = result["result"].toObject();

            emit querySuccess(scanner, "API:/PullUpMatlURL", result);
            if (rr["curstack"].isObject())
            {
                emit pullUped(scanner, scanner->getLine(), rr["curstack"].toObject()["sn"].toString());
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
            emit txRobotParams(rr);
        }
        else if (u == commitStacksURL)
        {
            QJsonObject response = result["result"].toObject()["wmsresp"].toObject()["response"].toObject();
            bool offline = result["result"].toObject()["offline"].toBool();

            emit querySuccess(scanner, "API:/CommitStacksURL", result);

            if (!result["result"].toObject()["children"].toArray().size())    // 出空板默认允许
            {
                emit approveOut(scanner, scanner->getLine());
            }
            else
            {
//                if (offline || response["return"].toObject()["returnFlag"].toString() == "1")
//                    emit approveOut(scanner, scanner->getLine());
//                else
//                    emit rejectOut(scanner, scanner->getLine());

                // TODO: 发送为何wms出板错误
//                if (!(offline || response["return"].toObject()["returnFlag"].toString() == "1"))

                // 不管怎样, 准许出板
                emit approveOut(scanner, scanner->getLine());
            }
        }
        else if (u == cstackURL)
        {
            QJsonObject rr = result["result"].toObject();
            QJsonObject curstack = rr["curstack"].toObject();
            QJsonObject robotparams = rr["robotparams"].toObject();

            emit querySuccess(scanner, "API:/CStackURL", result);
            emit gotoChange(scanner, scanner->getLine(), curstack["orderNo"].toString(), curstack["len"].toInt(), curstack["wide"].toInt(), curstack["height"].toInt(), robotparams["bottom"].toBool());
            emit txRobotParams(robotparams);
        }
        else if (u == startUpParamsURL)
        {
            QJsonObject rr = result["result"].toObject();
            QJsonObject curstack = rr["curstack"].toObject();
            QJsonObject robotparams = rr["robotparams"].toObject();

            emit querySuccess(scanner, "API:/StartUpParamsURL", result);
            emit txRobotParams(robotparams);
        }
    }
}

void ScannerWorker::analysis(DeviceScanner *scanner, QString barcode)
{
    QUrl url(settings.value("barcodeInfoURL").toString());
    QUrl furl(settings.value("fbarcodeURL").toString());
    QUrlQuery query;
    QNetworkRequest request;

    // HACK: 托管开关设置
    if ((settings.value(DC::DC_TOSTRING(scanner->getLine()) + "Auto").toString()) != "true") return;

    // 扫码枪心跳
    if (barcode.length() && !barcode.indexOf("OK,KEYENCE")) return;
//    if (barcode.contains("OK,KEYENCE")) return;

    barcode = barcode.trimmed().replace("\r\n", "");
    if (barcode == "NG")
    {
        emit gotoError(scanner, scanner->getLine(), barcode);
        return;
    }

    this->barcode = barcode;
    query.addQueryItem("url", url.toString());
    query.addQueryItem("barcode", barcode);
    furl.setQuery(query);
    request.setUrl(furl);
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

void ScannerWorker::requestCStack(DeviceLineNo line)
{
    QUrl url(settings.value("cstackURL").toString());

    if (url.toString().trimmed().length())
    {
        QUrlQuery query;
        query.addQueryItem("line", QString::number((int)line));
        url.setQuery(query);
        manager->get(QNetworkRequest(url));
    }
}

void ScannerWorker::requestStartUpParams(DeviceLineNo line)
{
    QUrl url(settings.value("startUpParamsURL").toString());

    if (url.toString().trimmed().length())
    {
        QUrlQuery query;
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
    QThread::msleep(300);
    if (line == scanner->getLine())
        requestCommitStack(line);
}

void ScannerWorker::cleanReq(DevicePLC *plc, DeviceLineNo line)
{
    QThread::msleep(300);
    if (line == scanner->getLine())
        requestCStack(line);
}

void ScannerWorker::requestLog(QUrl url)
{
    apiCostLog[url] = QDateTime::currentMSecsSinceEpoch();
}

long ScannerWorker::requestCost(QUrl url)
{
    if (apiCostLog.contains(url))
        return QDateTime::currentMSecsSinceEpoch() - apiCostLog[url];

    return 0;
}
