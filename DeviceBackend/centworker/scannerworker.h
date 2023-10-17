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
#include <QStringBuilder>
#include <QTimer>

#include "devicescanner.h"
#include "deviceplc.h"


// @brief Scanner logic process
class ScannerWorker : public QObject
{
    Q_OBJECT
public:
    ScannerWorker(DeviceScanner *scanner);

    ~ScannerWorker();

    DeviceLineNo getLineNo() { return scanner->getLine(); }

signals:
    void queryFailed(DeviceScanner *scanner, QString barcode, QJsonObject result);
    void querySuccess(DeviceScanner *scanner, QString barcode, QJsonObject result);
    void gotoNormal(DeviceScanner*, DeviceLineNo, QString barcode);  // 走正常线
    void gotoError(DeviceScanner*, DeviceLineNo, QString barcode);   // 走异常线
    void gotoChange(DeviceScanner*, DeviceLineNo, QString orderNo, int len, int wide, int height);  // 换产
    void pullUped(DeviceScanner*, DeviceLineNo, QString barcode);   // 物料已上传且加入到码垛中
    void noAvailableStack(DeviceScanner*);    // 发起了机器人已码垛请求, 但是未找到当前线体已扫码的物料
    void uploaded(DeviceScanner*, DeviceLineNo, QString barcode);   // 物料已扫码确认
    void txRobotParams(int len, int wide, int height, int row, int col, int layer);   // 在查询后发送机器人参数
    void approveOut(DeviceScanner*, DeviceLineNo);  // 同意指定线体出板
    void rejectOut(DeviceScanner*, DeviceLineNo);   // 拒绝指定线体出板
    void sendKeepalive(QString);
    void sendedKeep(DeviceScanner*, QString);

public slots:
    void init();
    void querydone(bool error, QUrl url, QJsonObject result);
    void analysis(DeviceScanner *scanner, QString barcode);
    void requestUploadMatl(DeviceLineNo line, QString order, QString barcode, int len, int wide, int height);
    void requestPullUpMatl(DeviceLineNo line);
    void requestRobotParams(DeviceLineNo line, int len, int wide, int height);
    void requestCommitStack(DeviceLineNo);

    // @brief 由PlcWorker触发, 当指定线体机器人码好一个物料时
    void pullUp(DevicePLC*, DeviceLineNo);
    // @breif 由PlcWorker触发, 当指定线体PLC发起请求出板时
    void commitReq(DevicePLC*, DeviceLineNo);

private:
    QNetworkAccessManager *manager = nullptr;
    DeviceScanner *scanner = nullptr;
    QTimer *keepaliveTimmer = nullptr;
    QSettings settings;
    QString barcode;
    const QString keepaliveCmd = "KEYENCE\r\n";

    QJsonObject barcodeInfoResult;
    QJsonObject uploadMatlResult;
    QJsonObject robotParamsResult;
};

#endif // SCANNERWORKER_H
