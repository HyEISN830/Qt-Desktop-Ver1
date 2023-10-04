#include "scannerworker.h"

ScannerWorker::ScannerWorker(QObject *parent)
    : QObject{parent}
{

}

void ScannerWorker::querydone(bool error, QJsonObject result)
{
    // TODO: query barcode info and upload barcode in stackboard
    qDebug() << error << result;
}

void ScannerWorker::analysis(DeviceScanner *scanner, QString barcode)
{
//    manager->get(QNetworkRequest(QUrl("https://httpbin.org/get")));
//    manager->get(QNetworkRequest(QUrl("https://hyeisn.cn/get")));
    QUrl url(settings.value("barcodeInfoURL").toString());
    QUrlQuery query;
    QNetworkRequest request;

    query.addQueryItem("barcode", barcode);
    url.setQuery(query);
    request.setUrl(url);
    manager->get(request);
}
