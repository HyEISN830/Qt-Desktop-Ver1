#include "devicecenter.h"


DeviceCenter::DeviceCenter()
{

}

#pragma region "设备启动以及生命周期相关相关 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" {
void DeviceCenter::start()
{
    main();
}

void DeviceCenter::stop()
{
    if (loopTask)
        loopTask->stop();
}

void DeviceCenter::main()
{
    // set up codes here


    // infinty loop without delay
    // if you want to delay, you should add it in LoopTask::run()
//    LoopTask *loopTask = new LoopTask(this);
//    this->loopTask = loopTask;
//    QThreadPool::globalInstance()->start(loopTask);
}

void DeviceCenter::loop()
{
//    QList<int> keys = scannerList.keys();

    // scanners connection heart check
//    for (int i = 0; i < keys.size(); ++i)
//        scannerList[keys[i]]->heartcheck();
}
#pragma endregion }


#pragma region "控制设备相关 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" {
void DeviceCenter::addscanner(int dId, QString ip, int port, DeviceLineNo lineNo)
{
    DeviceScanner *scanner  = new DeviceScanner(dId, ip, port, lineNo);
    ScannerWorker *worker = new ScannerWorker(scanner);
    QThread *thread = new QThread;

    scannerList[dId] = scanner;
    connect(scanner, &DeviceScanner::connected, this, &DeviceCenter::scannerConnected);
    connect(scanner, &DeviceScanner::connectFailed, this, &DeviceCenter::scannerConnectFailed);
    connect(scanner, &DeviceScanner::disconnected, this, &DeviceCenter::scannerDisconnected);
    connect(thread, &QThread::finished, scanner, &DeviceScanner::deleteLater);
    scanner->moveToThread(thread);
    scanner->start();

    workerThreads[dId] = thread;
    connect(scanner, &DeviceScanner::barcodeReceived, worker, &ScannerWorker::analysis);
    connect(thread, &QThread::finished, worker, &ScannerWorker::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    worker->moveToThread(thread);
    thread->start();
}

void DeviceCenter::addrobot(int dId, QString ip, int port, DeviceLineNo lineNo)
{

}

void DeviceCenter::addplc(int dId, QString ip, int port)
{

}

void DeviceCenter::reconnect(int dId, QString ip, int port, char deviceProtocol)
{

}
#pragma endregion }


#pragma region "插槽事件处理 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" {
void DeviceCenter::scannerReceived(DeviceScanner *scanner, QString barcode)
{
    qDebug() << "id:" << scanner->getDId() << "barcode received => " << barcode;
}

void DeviceCenter::scannerConnected(DeviceScanner *scanner)
{
    qDebug() << "scanner" << scanner->getIp() << "connected.";
    emit deviceConnected(scanner->getDId());
}

void DeviceCenter::scannerConnectFailed(DeviceScanner *scanner)
{
    qDebug() << "scanner" << scanner->getIp() << "connect failed.";
}

void DeviceCenter::scannerDisconnected(DeviceScanner *scanner)
{
    qDebug() << "scanner" << scanner->getIp() << "disconnected.";
    emit deviceDisconnect(scanner->getDId());
}
#pragma endregion }


DeviceCenter::~DeviceCenter()
{
    QList<int> dIds = scannerList.keys();

    for (int i = 0; i < dIds.size(); ++i)
        scannerList.remove(dIds[i]);    // DeviceScanner is automatically delete by QObject::deleteLater after sending QThread::finished signal

    dIds = plcList.keys();
    for (int i = 0; i < dIds.size(); ++i)
    {
        delete plcList[dIds[i]];
        plcList.remove(dIds[i]);
    }

    dIds = workerThreads.keys();
    for (int i = 0; i < dIds.size(); ++i)
    {   // QThread is automatically delete by QThread::deleteLater after sending QThread::finished signal
        workerThreads[dIds[i]]->quit();
        workerThreads[dIds[i]]->wait();
        workerThreads.remove(dIds[i]);
    }

    if (loopTask)
        loopTask->stop();

    delete loopTask;
}
