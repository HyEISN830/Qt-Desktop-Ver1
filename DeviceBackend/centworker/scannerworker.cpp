#include "scannerworker.h"

ScannerWorker::ScannerWorker(QObject *parent)
    : QObject{parent}
{

}

void ScannerWorker::init()
{
    manager = new QNetworkAccessManager;
    connect(manager, &QNetworkAccessManager::finished, this, [=] (QNetworkReply *reply) {
        if (reply->error() == QNetworkReply::NoError)
        {
            QJsonDocument jdoc = QJsonDocument::fromJson(reply->readAll());
            querydone(false, jdoc.object());
        }
        else
        {
            querydone(true, QJsonObject());
        }
    });
}

void ScannerWorker::querydone(bool error, QJsonObject result)
{
    if (error)
    {
        emit queryFailed(scanner, barcode, result);
    }
    else
    {
        emit querySuccess(scanner, barcode, result);

        // TODO: 成功后业务流程
    }
}

void ScannerWorker::analysis(DeviceScanner *scanner, QString barcode)
{
    QUrl url(settings.value("barcodeInfoURL").toString());
    QUrlQuery query;
    QNetworkRequest request;

    this->barcode = barcode;
    query.addQueryItem("barcode", barcode);
    url.setQuery(query);
    request.setUrl(url);
    manager->get(request);
}
