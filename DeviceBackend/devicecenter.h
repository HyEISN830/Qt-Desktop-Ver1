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
#include "centworker/scannerworker.h"


/*
    @brief 在该类中处理所有的设备逻辑; 启动与停止, 以及生命周期由前端管理
*/
class DeviceCenter : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT
public:
    class LoopTask : public QRunnable
    {
    public:
        LoopTask(DeviceCenter *deviceCenter) : deviceCenter(deviceCenter) { running = true; }
        ~LoopTask() { qDebug() << "DeviceCenter.LoopTask finished."; }

        void run() override
        {
            // TODO: 修复程序退出时崩溃
            while (running)
            {
                QThread::msleep(1000);
                deviceCenter->loop();
            }
        }

        void stop() { running = false; }

    private:
        DeviceCenter *deviceCenter = nullptr;
        bool running = false;
    };

    DeviceCenter();
    ~DeviceCenter();

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
    Q_INVOKABLE void addplc(int dId, QString ip, int port);

    /*
        @brief 基于指定设备一个新的连接参数
        @param deviceType - GlobalEnums.DeviceType
    */
    Q_INVOKABLE void reconnect(int dId, QString ip, int port, char deviceType);
#pragma endregion }

private:
    QMap<int, DeviceScanner*> scannerList;
    QMap<int, QThread*> workerThreads;
    QMap<int, DevicePLC*> plcList;
    bool running = false;
    LoopTask *loopTask = nullptr;

    void main();    // 主函数, 用于启动各类设置
    void loop();    // 任务主循环

public slots:
    // @brief 收到来自扫码枪的条码
    void scannerReceived(DeviceScanner*, QString barcode);
    // @brief 扫码枪已连接
    void scannerConnected(DeviceScanner*);
    // @brief 扫码枪连接失败
    void scannerConnectFailed(DeviceScanner*);
    // @brief 扫码枪已断开连接
    void scannerDisconnected(DeviceScanner*);

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
};

#endif // DEVICECENTER_H
