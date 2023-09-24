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
void DeviceCenter::addscanner(int dId, QString ip, int port, DeviceLineNo lineNo)
{
    DeviceScanner *scanner  = new DeviceScanner(dId, ip, port, lineNo);

    scannerList[dId] = scanner;
    connect(scanner, &DeviceScanner::barcodeReceived, this, &DeviceCenter::bscannerReceived);
    connect(scanner, &DeviceScanner::connected, this, &DeviceCenter::scannerConnected);
    connect(scanner, &DeviceScanner::disconnected, this, &DeviceCenter::scannerDisconnected);
    scanner->connect();
}

void DeviceCenter::addplc(int dId, QString ip, int port)
{

}

void DeviceCenter::reconnect(int dId, QString ip, int port, char deviceProtocol)
{

}
#pragma endregion }


#pragma region "插槽事件处理 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" {
void DeviceCenter::bscannerReceived(DeviceScanner scanner, QString barcode)
{
    qDebug() << "id:" << scanner.getDId() << "barcode received => " << barcode;
}

void DeviceCenter::scannerConnected(DeviceScanner scanner)
{
    qDebug() << "scanner" << scanner.getIp() << "connected.";
}

void DeviceCenter::scannerConnectFailed(DeviceScanner scanner)
{
    qDebug() << "scanner" << scanner.getIp() << "connect failed.";
}

void DeviceCenter::scannerDisconnected(DeviceScanner scanner)
{
    qDebug() << "scanner" << scanner.getIp() << "disconnected.";
}
#pragma endregion }


DeviceCenter::~DeviceCenter()
{
    QList<int> dIds = scannerList.keys();

    for (int i = 0; i < dIds.size(); ++i)
    {
        delete scannerList[dIds[i]];
        scannerList.remove(dIds[i]);
    }

    dIds = plcList.keys();

    for (int i = 0; i < dIds.size(); ++i)
    {
        delete plcList[dIds[i]];
        plcList.remove(dIds[i]);
    }

}
