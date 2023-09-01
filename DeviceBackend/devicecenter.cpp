#include "devicecenter.h"


DeviceCenter::DeviceCenter()
{

}

#pragma region "设备启动以及生命周期相关相关 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" {
void DeviceCenter::start()
{
    running = true;
    main();
}

void DeviceCenter::stop()
{
    running = false;
}

void DeviceCenter::setDevices(QJsonArray deviceList)
{

}

void DeviceCenter::main()
{
    // set up codes here


    while (running)
    {
        // infinty loop without delay
        // if you want to delay, you should add it in loop()
        loop();
    }
}

void DeviceCenter::loop()
{
    QThread::msleep(1);
}
#pragma endregion }

#pragma region "控制设备相关 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" {
void DeviceCenter::reconnect(int dId, QString ip, int port, char deviceProtocol)
{

}
#pragma endregion }

#pragma region "插槽事件处理 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" {
void DeviceCenter::bscannerReceived(int dId, QString ip, int port, QString barcode)
{

}
#pragma endregion }

DeviceCenter::~DeviceCenter()
{

}
