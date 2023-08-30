#include "devicecenter.h"


DeviceCenter::DeviceCenter()
{

}

void DeviceCenter::start()
{
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

void DeviceCenter::reconnect(int dId, QString ip, QString port)
{

}

DeviceCenter::~DeviceCenter()
{

}
