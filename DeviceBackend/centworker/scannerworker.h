#ifndef SCANNERWORKER_H
#define SCANNERWORKER_H

#include <QThread>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QSettings>
#include <QUrlQuery>

#include "devicescanner.h"


// @brief Scanner logic process
class ScannerWorker : public QObject
{
    Q_OBJECT
public:
    explicit ScannerWorker(QObject *parent = nullptr);

    ScannerWorker(DeviceScanner *scanner) : scanner(scanner)
    {
    }

    ~ScannerWorker()
    {
    }

signals:
    void queryFailed(DeviceScanner *scanner, QString barcode, QJsonObject result);
    void querySuccess(DeviceScanner *scanner, QString barcode, QJsonObject result);

public slots:
    void init();
    void querydone(bool error, QJsonObject result);
    void analysis(DeviceScanner *scanner, QString barcode);

private:
    QNetworkAccessManager *manager = nullptr;
    DeviceScanner *scanner = nullptr;
    QSettings settings;
    QString barcode;
};

#endif // SCANNERWORKER_H
