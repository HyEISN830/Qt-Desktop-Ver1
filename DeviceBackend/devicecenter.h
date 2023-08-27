#ifndef DEVICECENTER_H
#define DEVICECENTER_H

#include <QQuickItem>
#include <QThread>


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

    Q_INVOKABLE void start();   // 开始处理设备逻辑
    Q_INVOKABLE void stop();    // 停止处理设备逻辑

private:
    bool running = false;

    void main();    // 主函数, 用于启动各类设置
    void loop();    // 任务主循环

signals:

};

#endif // DEVICECENTER_H
