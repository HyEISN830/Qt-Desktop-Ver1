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

void DeviceCenter::main()
{


    loop();
}

void DeviceCenter::loop()
{
    while (running)
    {
        QThread::msleep(1);
    }
}

DeviceCenter::~DeviceCenter()
{

}
