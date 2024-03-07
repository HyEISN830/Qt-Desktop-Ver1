#ifndef DEVICECENTER_H
#define DEVICECENTER_H

#include <QQuickItem>
#include <QThread>
#include <QJsonArray>
#include <QTcpSocket>
#include <QModbusClient>
#include <QModbusTcpClient>
#include <QList>
#include <QMap>
#include <QTimer>
#include <QRunnable>
#include <QThreadPool>

#include "devicelineno.h"
#include "devicescanner.h"
#include "deviceplc.h"
#include "devicerobot.h"
#include "centworker/scannerworker.h"
#include "centworker/plcworker.h"
#include "centworker/robotworker.h"
#include "centworker/schedulingworker.h"
#include "centworker/sysworker.h"
#include "centworker/pointworker.h"
#include "centworker/iogateway.h"
#include "centworker/iomoduleworker.h"


/*
    @brief 在该类中处理所有的设备逻辑; 启动与停止, 以及生命周期由前端管理
*/
class DeviceCenter : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT
public:
    DeviceCenter();
    ~DeviceCenter();

    ScannerWorker* findScannerWorker(DeviceLineNo line);
    RobotWorker* findRobotWorker(DeviceLineNo line);
    PlcWorker* findPlcWorker(DeviceLineNo line);

#pragma region "设备启动以及生命周期相关相关 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" {
    // @brief 开始处理设备逻辑
    Q_INVOKABLE void start();
    // @brief 停止处理设备逻辑
    Q_INVOKABLE void stop();
#pragma endregion }

#pragma region "控制设备相关 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" {
    // @brief 连接扫码枪
    Q_INVOKABLE void addscanner(int dId, QString ip, int port, DeviceLineNo lineNo);

    // @brief 连接机器人
    Q_INVOKABLE void addrobot(int dId, QString ip, int port, DeviceLineNo lineNo);

    // @brief 连接PLC
    Q_INVOKABLE void addplc(int dId, QString ip, int port, DeviceLineNo lineNo, QList<int> allowLines);

    // @brief 订阅调度服务
    Q_INVOKABLE void addscheduling(int dId, QString ip, int port, DeviceLineNo lineNo);

    // @breif 添加本地TCPServer
    Q_INVOKABLE void addserver(int dId, int port, int maxclients, quint8 agvCode);

    // @breif 添加光通讯点位
    Q_INVOKABLE void addpoint(int dId, QString ip, int port);

    // @breif 添加自动门控制网关
    Q_INVOKABLE void addgateserver(int dId, int port);

    // @breif 添加自动门IO模块
    Q_INVOKABLE void addgateclient(int dId, int no, QString ip, int port);

    /*
        @brief 基于指定设备一个新的连接参数
        @param deviceType - GlobalEnums.DeviceType
    */
    Q_INVOKABLE void reconnect(int dId, QString ip, int port);
#pragma endregion }

private:
    QMap<int, DeviceScanner*> scannerList;
    QMap<int, ScannerWorker*> scannerWorkers;   // worker is automatically deleted after use
    QMap<int, DevicePLC*> plcList;
    QMap<int, PlcWorker*> plcWorkers;   // worker is automatically deleted after use
    QMap<int, DeviceRobot*> robotList;
    QMap<int, RobotWorker*> robotWorkers;   // worker is automatically deleted after use
    QMap<int, SchedulingWorker*> schedulingWorkers;
    QMap<int, SysWorker*> sysWorkers;
    QMap<int, PointWorker*> pointWorkers;
    QMap<int, IOGateway*> iogateWorkers;
    QMap<int, IOModuleWorker*> ioWorkers;
    QMap<int, QThread*> workerThreads;  // thread is automatically deleted after use
    bool running = false;

    void main();    // 主函数, 用于启动各类设置
    void loop();    // 任务主循环
    QList<quint8> toU8List(QByteArray); // 将 QByteArray 抓换位 QList<quint8> , 方便展示
    QByteArray toBytes(QList<quint8>);  // 将 QList<quint8> 转换为 QByteArray, 方便发送

public slots:
    // @brief 收到来自扫码枪的条码
    void scannerReceived(DeviceScanner*, QString barcode);
    // @brief 扫码枪已连接
    void scannerConnected(DeviceScanner*);
    // @brief 扫码枪连接失败
    void scannerConnectFailed(DeviceScanner*);
    // @brief 扫码枪已断开连接
    void scannerDisconnected(DeviceScanner*);
    // @brief 扫码枪查询条码失败
    void scannerQueryFailed(DeviceScanner*, QString barcode, QJsonObject result, long cost);
    // @brief 扫码枪查询条码成功
    void scannerQuerySuccess(DeviceScanner*, QString barcode, QJsonObject result, long cost);
    // @brief 扫码结果产品流向正常线
    void scannerGotoNormal(DeviceScanner*, DeviceLineNo, QString barcode);
    // @brief 扫码结果产品流向异常线
    void scannerGotoError(DeviceScanner*, DeviceLineNo, QString barcode);
    // @brief 扫码结果即将换产
    void scannerGotoChange(DeviceScanner*, DeviceLineNo, QString orderNo, int len, int wide, int height);
    // @brief 发起了机器人已码垛请求, 但是未找到当前线体已扫码的物料
    void scannerNoAvailableStack(DeviceScanner*);
    // @brief 物料已上传且加入到码垛中
    void scannerPullUped(DeviceScanner*, DeviceLineNo, QString barcode);
    // @breif 物料扫码已确认
    void scannerUploaded(DeviceScanner*, DeviceLineNo, QString barcode);
    // @brief 允许指定线体出板
    void scannerApproveOut(DeviceScanner*, DeviceLineNo);
    // @brief 拒绝指定线体出板
    void scannerRejectOut(DeviceScanner*, DeviceLineNo);
    // @brief 发送扫码枪心跳数据
    void scannerSendedKeep(DeviceScanner*, QString);
    // @breif 准备换产
    void scannerChangeReady(DeviceScanner*, DeviceLineNo);
    // @brief PLC连接成功时
    void plcConnected(DevicePLC*);
    // @brief PLC断开连接或连接失败时
    void plcDisconnected(DevicePLC*);
    // @brief on PLC TX
    void _plcTx(DevicePLC*);
    // @brief on PLC RX
    void _plcRx(DevicePLC*);
    // @breif PLC register writed
    void _plcWrited(DevicePLC*, int addr, ushort value);
    // @brief 指定线体机器人已码好
    void _plcPullUp(DevicePLC*, DeviceLineNo);
    // @brief 指定线体PLC在一定秒数内重复发起夹料完成
    void _plcDuplicateClamped(DevicePLC*, DeviceLineNo, long);
    // @brief 发送内容到机器人
    void _robotSended(DeviceRobot*, QString content);
    // @brief 收到来自机器人的响应
    void _robotReceived(DeviceRobot*, QString content);
    // @brief 长时间未收到机器人心跳数据, 应当重新连接
    void _robotHeartStopped(DeviceRobot*);
    // @brief 机器人已连接
    void robotConnected(DeviceRobot*);
    // @brief 机器人连接失败
    void robotConnectFailed(DeviceRobot*);
    // @brief 机器人已断开连接
    void robotDisconnected(DeviceRobot*);
    // @brief on Robot TX
    void _robotTx(DeviceRobot*);
    // @brief on Robot RX
    void _robotRx(DeviceRobot*);
    // @breif on Scheduling Connected
    void _schedulingConnected(SchedulingWorker*);
    // @breif on Scheduling Disconnected
    void _schedulingDisconnected(SchedulingWorker*);
    // @brief on Scheduling Task Tx
    void _schedulingTx(SchedulingWorker*);
    // @breif on Scheduling Task Rx
    void _schedulingRx(SchedulingWorker*);

    void received() { qDebug() << "received"; }

signals:
    // @brief 当 DeviceCenter 启动时
    void started();
    // @brief 当 DeviceCenter 停止时
    void stoped();
    // @brief 当某个设备连接成功时
    void deviceConnected(int dId);
    // @brief 当某个设备断开连接时
    void deviceDisconnect(int dId);
    // @breif 当某个设备接收到数据时
    void deviceReceived(int dId, QByteArray data);
    // @brief 当某个设备发送数据时
    void deviceSended(int dId, QByteArray data);
    // @brief 当某个设备重新应用了新的连接参数时
    void deviceApplied(int dId, QString ip, int port);
    // @biref 当某个设备连接失败时
    void deviceConnectFailed(int dId);
    // @breif 当扫码枪接收到条码时
    void barcodeReceived(int dId, QString barcode);
    // @brief 当条码查询失败时
    void barcodeQueryFailed(int dId, QString barcode, QJsonObject result, long cost);
    // @brief 当条码查询成功时
    void barcodeQuerySuccess(int dId, QString barcode, QJsonObject result, long cost);
    // @brief 扫码结果产品流向正常线
    void barcodeGotoNormal(int dId, QString barcode);
    // @brief 扫码结果产品流向异常线
    void barcodeGotoError(int dId, QString barcode);
    // @brief 扫码结果产品流向异常线
    void barcodeGotoChange(int dId, int line, QString orderNo, int len, int wide, int height);
    // @brief 发起了机器人已码垛请求, 但是未找到当前线体已扫码的物料
    void barcodeNoAvailableStack(int dId);
    // @brief 物料已上传且加入到码垛中
    void barcodePullUped(int dId, QString barcode);
    // @breif 物料扫码已确认
    void barcodeUploaded(int dId, QString barcode);
    // @brief 允许指定线体出板
    void barcodeApproveOut(int dId);
    // @brief 拒绝指定线体出板
    void barcodeRejectOut(int dId);
    // @breif 已向扫码枪发送心跳指令
    void barcodeSendedKeep(int dId, QString cmd);
    // @breif 准备换产
    void barcodeChangeReady(int dId);
    // @brief on PLC TX
    void plcTx(int dId);
    // @brief on PLC RX
    void plcRx(int dId);
    // @brief plc register writed
    void plcWrited(int dId, int addr, int value);
    // @breif 指定线体机器人已码好
    void plcPullUp(int dId, int line);
    // @brief 指定线体PLC在一定秒数内重复发起夹料完成
    void plcDuplicateClamped(int dId, int line, long diff);
    // @breif 当向机器人发送内容时
    void robotSended(int dId, QString content);
    // @breif 当机器人返回内容时
    void robotReceived(int dId, QString content);
    // @brief 当长时间未收到机器人心跳数据, 应当重新连接
    void robotHeartStopped(int dId);
    // @brief on Robot TX
    void robotTx(int dId);
    // @brief on Robot RX
    void robotRx(int dId);
    // @brief on Scheduling Task Tx
    void schedulingTx(int dId);
    // @brief on Scheduling Task Rx
    void schedulingRx(int dId);
    // @breif when tcpsocket connected on socketserver
    void clientConnectIn(int dId, QString ip, int port);
    // @breif when tcpsocket disconnected on socketserver
    void clientConnectOut(int did, QString ip, int port);
    // @breif 当tcpclient 发送数据到 tcpserver时
    void clientReceived(int did, QList<quint8> data);
    // @breif 当需要发送指令到模块时
    void sendCMD2(int dId, int no, QByteArray data);
    // @brief 当接收到来自光通讯点位的数据时
    void pointReceived(int did, QList<quint8> data);
    // @breif 发送到光通讯呆腻味数据时
    void pointSended(int did, QList<quint8> data);
    // @brief 当自动门网关接收到指令时, 自动门模块应当connect此signal, 当gno与gateclient.dId相等时, 则执行指令, 否则忽略
    void gatesReceived(int gno, QString cmd);
    // @breif 当自动门返回指令执行结果时
    void ioModuleResult(QByteArray);
};

#endif // DEVICECENTER_H
