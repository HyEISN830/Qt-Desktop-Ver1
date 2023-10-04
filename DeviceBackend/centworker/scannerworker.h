#ifndef SCANNERWORKER_H
#define SCANNERWORKER_H

#include <QThread>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>

#include "devicescanner.h"


// @brief Scanner logic process
class ScannerWorker : public QObject
{
    Q_OBJECT
public:
    explicit ScannerWorker(QObject *parent = nullptr);

    ScannerWorker(DeviceScanner *scanner) : scanner(scanner)
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

    ~ScannerWorker()
    {
    }

signals:

public slots:
    void querydone(bool error, QJsonObject result);
    void analysis(DeviceScanner *scanner, QString barcode);

private:
    QNetworkAccessManager *manager = nullptr;
    DeviceScanner *scanner = nullptr;
};

#endif // SCANNERWORKER_H
