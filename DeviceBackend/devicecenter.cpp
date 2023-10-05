#include "devicecenter.h"
#include "centworker/scannerworker.h"
#include "centworker/plcworker.h"


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
    connect(scanner, &DeviceScanner::barcodeReceived, this, &DeviceCenter::scannerReceived);
    connect(scanner, &DeviceScanner::applied, this, &DeviceCenter::deviceApplied);
    connect(thread, &QThread::finished, scanner, &DeviceScanner::deleteLater);
    scanner->moveToThread(thread);
    scanner->start();

    workerThreads[dId] = thread;
    connect(scanner, &DeviceScanner::barcodeReceived, worker, &ScannerWorker::analysis);
    connect(worker, &ScannerWorker::queryFailed, this, &DeviceCenter::scannerQueryFailed);
    connect(worker, &ScannerWorker::querySuccess, this, &DeviceCenter::scannerQuerySuccess);
    connect(thread, &QThread::started, worker, &ScannerWorker::init);
    connect(thread, &QThread::finished, worker, &ScannerWorker::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    worker->moveToThread(thread);
    thread->start();
}

void DeviceCenter::addrobot(int dId, QString ip, int port, DeviceLineNo lineNo)
{

}

void DeviceCenter::addplc(int dId, QString ip, int port, DeviceLineNo lineNo)
{
    DevicePLC *plc = new DevicePLC(dId, ip, port, lineNo);
    PlcWorker *worker = new PlcWorker(plc);
    QThread *thread = new QThread;

    plcList[dId] = plc;
    connect(plc, &DevicePLC::connected, this, &DeviceCenter::plcConnected);
    connect(plc, &DevicePLC::disconnected, this, &DeviceCenter::plcDisconnected);
    connect(plc, &DevicePLC::applied, this, &DeviceCenter::deviceApplied);
    connect(plc, &DevicePLC::tx, this, &DeviceCenter::_plcTx);
    connect(plc, &DevicePLC::rx, this, &DeviceCenter::_plcRx);
    connect(thread, &QThread::finished, plc, &DevicePLC::deleteLater);
    plc->moveToThread(thread);
    plc->start();

    workerThreads[dId] = thread;
    connect(worker, &PlcWorker::writeRegister, plc, &DevicePLC::writeRegister);
    connect(worker, &PlcWorker::readRegisters, plc, &DevicePLC::readRegisters);
    connect(plc, &DevicePLC::received, worker, &PlcWorker::received);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    worker->moveToThread(thread);
    thread->start();
}

void DeviceCenter::reconnect(int dId, QString ip, int port)
{
    if (scannerList.contains(dId))
        scannerList[dId]->apply(ip, port);

    if (plcList.contains(dId))
        plcList[dId]->apply(ip, port);
}
#pragma endregion }


#pragma region "插槽事件处理 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" {
void DeviceCenter::scannerReceived(DeviceScanner *scanner, QString barcode)
{
    emit barcodeReceived(scanner->getDId(), barcode);
}

void DeviceCenter::scannerConnected(DeviceScanner *scanner)
{
    emit deviceConnected(scanner->getDId());
}

void DeviceCenter::scannerConnectFailed(DeviceScanner *scanner)
{
    emit deviceConnectFailed(scanner->getDId());
}

void DeviceCenter::scannerDisconnected(DeviceScanner *scanner)
{
    emit deviceDisconnect(scanner->getDId());
}

void DeviceCenter::scannerQueryFailed(DeviceScanner *scanner, QString barcode, QJsonObject result)
{
    emit barcodeQueryFailed(scanner->getDId(), barcode, result);
}

void DeviceCenter::scannerQuerySuccess(DeviceScanner *scanner, QString barcode, QJsonObject result)
{
    emit barcodeQuerySuccess(scanner->getDId(), barcode, result);
}

void DeviceCenter::plcConnected(DevicePLC *plc)
{
    emit deviceConnected(plc->getDId());
}

void DeviceCenter::plcDisconnected(DevicePLC *plc)
{
    emit deviceConnectFailed(plc->getDId());
}

void DeviceCenter::_plcTx(DevicePLC *plc)
{
    emit plcTx(plc->getDId());
}

void DeviceCenter::_plcRx(DevicePLC *plc)
{
    emit plcRx(plc->getDId());
}
#pragma endregion }


DeviceCenter::~DeviceCenter()
{
    QList<int> dIds = scannerList.keys();

    for (int i = 0; i < dIds.size(); ++i)
        scannerList.remove(dIds[i]);    // DeviceScanner is automatically delete by QObject::deleteLater after sending QThread::finished signal

    dIds = plcList.keys();
    for (int i = 0; i < dIds.size(); ++i)
        plcList.remove(dIds[i]);

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
