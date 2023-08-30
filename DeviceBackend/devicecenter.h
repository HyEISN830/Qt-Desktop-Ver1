#ifndef DEVICECENTER_H
#define DEVICECENTER_H

#include <QQuickItem>
#include <QThread>
#include <QJsonArray>


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

#pragma region "设备启动以及生命周期相关相关 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
    // @brief 设置设备列表, 在启动后调用无效, 需要通过设备设置相关函数进行更改
    Q_INVOKABLE void setDevices(QJsonArray deviceList);
    // @brief 开始处理设备逻辑
    Q_INVOKABLE void start();
    // @brief 停止处理设备逻辑
    Q_INVOKABLE void stop();
#pragma endregion

#pragma region "控制设备相关 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
    // @brief 基于指定设备一个新的连接参数
    Q_INVOKABLE void reconnect(int dId, QString ip, QString port);
#pragma endregion

private:
    bool running = false;

    void main();    // 主函数, 用于启动各类设置
    void loop();    // 任务主循环

signals:
    // @brief 当 DeviceCenter 启动时
    void onStarted();
    // @brief 当 DeviceCenter 停止时
    void onStoped();
    // @brief 当某个设备连接成功时
    void onDeviceConnected(int dId);
    // @brief 当某个设备断开连接时
    void onDeviceDisconnect(int dId);
};

#endif // DEVICECENTER_H
