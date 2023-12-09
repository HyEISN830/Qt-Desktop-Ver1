#ifndef SCANNERWORKER_H
#define SCANNERWORKER_H

#include <QThread>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkRequest>
#include <QSettings>
#include <QUrlQuery>
#include <QStringBuilder>
#include <QTimer>
#include <QMap>

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
    void queryFailed(DeviceScanner *scanner, QString barcode, QJsonObject result, long cost);
    void querySuccess(DeviceScanner *scanner, QString barcode, QJsonObject result, long cost);
    void gotoNormal(DeviceScanner*, DeviceLineNo, QString barcode);  // 走正常线
    void gotoError(DeviceScanner*, DeviceLineNo, QString barcode);   // 走异常线
    void gotoChange(DeviceScanner*, DeviceLineNo, QString orderNo, int len, int wide, int height, bool bottom);  // 换产
    void pullUped(DeviceScanner*, DeviceLineNo, QString barcode);   // 物料已上传且加入到码垛中
    void noAvailableStack(DeviceScanner*);    // 发起了机器人已码垛请求, 但是未找到当前线体已扫码的物料
    void uploaded(DeviceScanner*, DeviceLineNo, QString barcode);   // 物料已扫码确认
    void txRobotParams(QJsonObject);   // 在查询后发送机器人参数
    void approveOut(DeviceScanner*, DeviceLineNo);  // 同意指定线体出板
    void rejectOut(DeviceScanner*, DeviceLineNo);   // 拒绝指定线体出板
    void sendKeepalive(QString);
    void sendedKeep(DeviceScanner*, QString);
    void gotoChangeReady(DeviceScanner *scanner, DeviceLineNo line);    // 在上传物料后, 发现需要换产时, 发送信号到plc, 准备换产

    void deleteTimer();

public slots:
    void init();
    void timerDeleteLater();
    void querydone(bool error, QUrl url, QJsonObject result);
    void analysis(DeviceScanner *scanner, QString barcode);
    void requestUploadMatl(DeviceLineNo line, QString order, QString barcode, int len, int wide, int height);
    void requestPullUpMatl(DeviceLineNo line);
    void requestRobotParams(DeviceLineNo line, int len, int wide, int height);
    void requestCommitStack(DeviceLineNo);
    void requestCStack(DeviceLineNo);
    void requestStartUpParams(DeviceLineNo);

    // @brief 由PlcWorker触发, 当指定线体机器人码好一个物料时
    void pullUp(DevicePLC*, DeviceLineNo);
    // @breif 由PlcWorker触发, 当指定线体PLC发起请求出板时
    void commitReq(DevicePLC*, DeviceLineNo);
    // @brief 由PlcWorker触发, 当指定线体PLC发起清线完成时
    void cleanReq(DevicePLC*, DeviceLineNo);

// functions
private:
    void requestLogCost(QUrl);
    long requestCost(QUrl);

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

    QMap<QUrl, long> apiCostLog; // 接口访问耗时(ms)记录
};

#endif // SCANNERWORKER_H
