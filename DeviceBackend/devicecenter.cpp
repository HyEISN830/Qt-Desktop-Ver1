#include "devicecenter.h"


DeviceCenter::DeviceCenter()
{
}

#pragma region "设备启动以及生命周期相关相关 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" {
void DeviceCenter::start()
{
    // Logger
    logWorker = new HttpAddLogWorker;
    workerThreads[gid()] = logWorker;
    connect(this, &DeviceCenter::_appendLog, logWorker, &HttpAddLogWorker::appendLog);
    connect(logWorker, &HttpAddLogWorker::finished, logWorker, &HttpAddLogWorker::deleteLater);
    logWorker->start();

    utcThread = new HDateTimeWorker;
    workerThreads[gid()] = utcThread;
    connect(utcThread, &HDateTimeWorker::finished, utcThread, &HDateTimeWorker::deleteLater);
    utcThread->start();

    // TODO: 改为外部传入的地图大小或外部地图配置
    QString mapfile_path = "Configuration/map.json";
    pfWorker = new PathfindingWorker(mapfile_path);
    workerThreads[gid()] = utcThread;
    connect(this, &DeviceCenter::_pf_test, pfWorker, &PathfindingWorker::calcpaths);
    connect(this, &DeviceCenter::_pf_wa, pfWorker, &PathfindingWorker::setwalkable);
    connect(pfWorker, &PathfindingWorker::calculated, this, &DeviceCenter::pathCalculated);
    connect(pfWorker, &PathfindingWorker::finished, pfWorker, &PathfindingWorker::deleteLater);
    pfWorker->start();
}

void DeviceCenter::stop()
{
}

ScannerWorker* DeviceCenter::findScannerWorker(DeviceLineNo line)
{
    ScannerWorker *worker = nullptr;
    QList<int> keys = scannerWorkers.keys();

    for (int var = 0; var < keys.size(); ++var)
    {
        if (scannerWorkers[keys[var]]->getLineNo() == line)
            worker = scannerWorkers[keys[var]];
    }

    return worker;
}

RobotWorker* DeviceCenter::findRobotWorker(DeviceLineNo line)
{
    RobotWorker *worker = nullptr;
    QList<int> keys = robotWorkers.keys();

    for (int var = 0; var < keys.size(); ++var)
    {
        if (robotWorkers[keys[var]]->getLineNo() == line)
            worker = robotWorkers[keys[var]];
    }

    return worker;
}

PlcWorker* DeviceCenter::findPlcWorker(DeviceLineNo line)
{
    PlcWorker *worker = nullptr;
    QList<int> keys = plcWorkers.keys();

    for (int var = 0; var < keys.size(); ++var)
    {
        DeviceLineNo workerline = plcWorkers[keys[var]]->getLineNo();
        if (workerline == line || workerline == DeviceLineNo::All)
            worker = plcWorkers[keys[var]];
    }

    return worker;
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
    scannerWorkers[dId] = worker;
    connect(scanner, &DeviceScanner::barcodeReceived, worker, &ScannerWorker::analysis);
    connect(worker, &ScannerWorker::queryFailed, this, &DeviceCenter::scannerQueryFailed);
    connect(worker, &ScannerWorker::querySuccess, this, &DeviceCenter::scannerQuerySuccess);
    connect(worker, &ScannerWorker::gotoNormal, this, &DeviceCenter::scannerGotoNormal);
    connect(worker, &ScannerWorker::gotoError, this, &DeviceCenter::scannerGotoError);
    connect(worker, &ScannerWorker::gotoChange, this, &DeviceCenter::scannerGotoChange);
    connect(worker, &ScannerWorker::pullUped, this, &DeviceCenter::scannerPullUped);
    connect(worker, &ScannerWorker::noAvailableStack, this, &DeviceCenter::scannerNoAvailableStack);
    connect(worker, &ScannerWorker::uploaded, this, &DeviceCenter::scannerUploaded);
    connect(worker, &ScannerWorker::approveOut, this, &DeviceCenter::scannerApproveOut);
    connect(worker, &ScannerWorker::rejectOut, this, &DeviceCenter::scannerRejectOut);
    connect(worker, &ScannerWorker::sendKeepalive, scanner, &DeviceScanner::send);
    connect(worker, &ScannerWorker::sendedKeep, this, &DeviceCenter::scannerSendedKeep);
    connect(worker, &ScannerWorker::gotoChangeReady, this, &DeviceCenter::scannerChangeReady);
    connect(thread, &QThread::started, worker, &ScannerWorker::init);
    connect(thread, &QThread::finished, worker, &ScannerWorker::timerDeleteLater);
    connect(thread, &QThread::finished, worker, &ScannerWorker::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    worker->moveToThread(thread);
    thread->start();
}

void DeviceCenter::addrobot(int dId, QString ip, int port, DeviceLineNo lineNo)
{
    DeviceRobot *robot = new DeviceRobot(dId, ip, port, lineNo);
    RobotWorker *worker = new RobotWorker(robot);
    QThread *thread = new QThread;

    robotList[dId] = robot;
    connect(robot, &DeviceRobot::connected, this, &DeviceCenter::robotConnected);
    connect(robot, &DeviceRobot::connectFailed, this, &DeviceCenter::robotConnectFailed);
    connect(robot, &DeviceRobot::disconnected, this, &DeviceCenter::robotDisconnected);
    connect(robot, &DeviceRobot::sended, this, &DeviceCenter::_robotSended);
    connect(robot, &DeviceRobot::received, this, &DeviceCenter::_robotReceived);
    connect(robot, &DeviceRobot::received_b, this, &DeviceCenter::_robotReceived_b);
    connect(robot, &DeviceRobot::applied, this, &DeviceCenter::deviceApplied);
    connect(robot, &DeviceRobot::tx, this, &DeviceCenter::_robotTx);
    connect(robot, &DeviceRobot::rx, this, &DeviceCenter::_robotRx);
    connect(thread, &QThread::finished, robot, &DeviceScanner::deleteLater);
    robot->moveToThread(thread);
    robot->start();

    workerThreads[dId] = thread;
    robotWorkers[dId] = worker;
    connect(worker, &RobotWorker::writeParams, robot, &DeviceRobot::writeParams);
    connect(worker, &RobotWorker::robotHeartStopped, this, &DeviceCenter::_robotHeartStopped);
    connect(robot, &DeviceRobot::received, worker, &RobotWorker::robotReceived);
    connect(robot, &DeviceRobot::connected, worker, &RobotWorker::robotConnected);
    connect(robot, &DeviceRobot::disconnected, worker, &RobotWorker::robotDisconnected);
    connect(thread, &QThread::finished, worker, &RobotWorker::timerDeleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    worker->moveToThread(thread);
    thread->start();
}

void DeviceCenter::addplc(int dId, QString ip, int port, DeviceLineNo lineNo, QList<int> allowLines)
{
    DevicePLC *plc = new DevicePLC(dId, ip, port, lineNo);
    PlcWorker *worker = new PlcWorker(plc, allowLines);
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
    plcWorkers[dId] = worker;
    connect(worker, &PlcWorker::writeRegister, plc, &DevicePLC::writeRegister);
    connect(worker, &PlcWorker::readRegisters, plc, &DevicePLC::readRegisters);
    connect(worker, &PlcWorker::writed, this, &DeviceCenter::_plcWrited);
    connect(worker, &PlcWorker::duplicateClamped, this, &DeviceCenter::_plcDuplicateClamped);
    connect(plc, &DevicePLC::received, worker, &PlcWorker::received);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    worker->moveToThread(thread);
    thread->start();
}

void DeviceCenter::addscheduling(int dId, QString ip, int port, DeviceLineNo lineNo)
{
    SchedulingWorker *worker = new SchedulingWorker(dId, ip, port, lineNo);
    QThread *thread = new QThread;

    workerThreads[dId] = thread;
    schedulingWorkers[dId] = worker;
    connect(worker, &SchedulingWorker::connected, this, &DeviceCenter::_schedulingConnected);
    connect(worker, &SchedulingWorker::disconnected, this, &DeviceCenter::_schedulingDisconnected);
    connect(worker, &SchedulingWorker::tx, this, &DeviceCenter::_schedulingTx);
    connect(worker, &SchedulingWorker::rx, this, &DeviceCenter::_schedulingRx);
    connect(worker, &SchedulingWorker::applied, this, &DeviceCenter::deviceApplied);
    connect(thread, &QThread::finished, worker, &SchedulingWorker::timerDeleteLater);
    connect(thread, &QThread::finished, worker, &SchedulingWorker::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    worker->moveToThread(thread);
    worker->start();
    thread->start();
}

void DeviceCenter::reconnect(int dId, QString ip, int port)
{
    if (scannerList.contains(dId))
    {
        scannerList[dId]->apply(ip, port);
        return;
    }

    if (plcList.contains(dId))
    {
        plcList[dId]->apply(ip, port);
        return;
    }

    if (robotList.contains(dId))
    {
        robotList[dId]->apply(ip, port);
        return;
    }

    if (schedulingWorkers.contains(dId))
    {
        schedulingWorkers[dId]->apply(ip, port);
        return;
    }
}
#pragma endregion }


#pragma region "其他实用函数 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" {
void DeviceCenter::appendLog(QString url, QString content, int level)
{
    emit _appendLog(url, content, level);
}

void DeviceCenter::pathfinding_test(int id, int startX, int startY, int endX, int endY, bool block_it)
{
    emit _pf_test(id, startX, startY, endX, endY, block_it);
}

void DeviceCenter::set_walkable(QJsonArray pointers, bool b)
{

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

void DeviceCenter::scannerQueryFailed(DeviceScanner *scanner, QString barcode, QJsonObject result, long cost)
{
    emit barcodeQueryFailed(scanner->getDId(), barcode, result, cost);
}

void DeviceCenter::scannerQuerySuccess(DeviceScanner *scanner, QString barcode, QJsonObject result, long cost)
{
    emit barcodeQuerySuccess(scanner->getDId(), barcode, result, cost);
}

void DeviceCenter::scannerGotoNormal(DeviceScanner *scanner, DeviceLineNo line, QString barcode)
{
    QList<int> keys = plcWorkers.keys();

    for (int var = 0; var < keys.size(); ++var)
        if (plcWorkers[keys[var]]->allowLine(line))
            plcWorkers[keys[var]]->scaned(line, true);

    emit barcodeGotoNormal(scanner->getDId(), barcode);
}

void DeviceCenter::scannerGotoError(DeviceScanner *scanner, DeviceLineNo line, QString barcode)
{
    QList<int> keys = plcWorkers.keys();

    for (int var = 0; var < keys.size(); ++var)
        if (plcWorkers[keys[var]]->allowLine(line))
            plcWorkers[keys[var]]->scaned(line, false);

    emit barcodeGotoError(scanner->getDId(), barcode);
}

void DeviceCenter::scannerGotoChange(DeviceScanner *scanner, DeviceLineNo line, QString orderNo, int len, int wide, int height)
{
    emit barcodeGotoChange(scanner->getDId(), line, orderNo, len, wide, height);
}

void DeviceCenter::scannerNoAvailableStack(DeviceScanner *scanner)
{
    emit barcodeNoAvailableStack(scanner->getDId());
}

void DeviceCenter::scannerPullUped(DeviceScanner *scanner, DeviceLineNo line, QString barcode)
{
    emit barcodePullUped(scanner->getDId(), barcode);
}

void DeviceCenter::scannerUploaded(DeviceScanner *scanner, DeviceLineNo line, QString barcode)
{
    emit barcodeUploaded(scanner->getDId(), barcode);
}

void DeviceCenter::scannerApproveOut(DeviceScanner *scanner, DeviceLineNo line)
{
    emit barcodeApproveOut(scanner->getDId());
}

void DeviceCenter::scannerRejectOut(DeviceScanner *scanner, DeviceLineNo line)
{
    emit barcodeRejectOut(scanner->getDId());
}

void DeviceCenter::scannerSendedKeep(DeviceScanner *scanner, QString cmd)
{
    emit barcodeSendedKeep(scanner->getDId(), cmd);
}

void DeviceCenter::scannerChangeReady(DeviceScanner *scanner, DeviceLineNo line)
{
    emit barcodeChangeReady(scanner->getDId());
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

void DeviceCenter::_plcWrited(DevicePLC *plc, int addr, ushort value)
{
    emit plcWrited(plc->getDId(), addr, value);
}

void DeviceCenter::_plcPullUp(DevicePLC *plc, DeviceLineNo line)
{
    emit plcPullUp(plc->getDId(), line);
}

void DeviceCenter::_plcDuplicateClamped(DevicePLC *plc, DeviceLineNo line, long diff)
{
    emit plcDuplicateClamped(plc->getDId(), line, diff);
}

void DeviceCenter::_robotSended(DeviceRobot *robot, QString content)
{
    emit robotSended(robot->getDId(), content);
}

void DeviceCenter::_robotReceived(DeviceRobot *robot, QString content)
{
    if (!content.contains(robot->keepaliveStr))
        emit robotReceived(robot->getDId(), content);
}

void DeviceCenter::_robotReceived_b(DeviceRobot *robot, QByteArray content)
{
    emit robotReceived_b(robot->getDId(), content);
}

void DeviceCenter::_robotHeartStopped(DeviceRobot *robot)
{
    if (robot->getConnected())
        emit robotHeartStopped(robot->getDId());
}

void DeviceCenter::robotConnected(DeviceRobot *robot)
{
    emit deviceConnected(robot->getDId());
}

void DeviceCenter::robotConnectFailed(DeviceRobot *robot)
{
    emit deviceConnectFailed(robot->getDId());
}

void DeviceCenter::robotDisconnected(DeviceRobot *robot)
{
    emit deviceDisconnect(robot->getDId());
}

void DeviceCenter::_robotTx(DeviceRobot *robot)
{
    emit robotTx(robot->getDId());
}

void DeviceCenter::_robotRx(DeviceRobot *robot)
{
    emit robotRx(robot->getDId());
}

void DeviceCenter::_schedulingConnected(SchedulingWorker *worker)
{
    emit deviceConnected(worker->getDId());
}

void DeviceCenter::_schedulingDisconnected(SchedulingWorker *worker)
{
    emit deviceDisconnect(worker->getDId());
}

void DeviceCenter::_schedulingTx(SchedulingWorker *worker)
{
    emit schedulingTx(worker->getDId());
}

void DeviceCenter::_schedulingRx(SchedulingWorker *worker)
{
    emit schedulingRx(worker->getDId());
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

    dIds = robotList.keys();
    for (int i = 0; i < dIds.size(); ++i)
        robotList.remove(dIds[i]);

    dIds = scannerWorkers.keys();
    for (int i = 0; i < dIds.size(); ++i)
        scannerWorkers.remove(dIds[i]);

    dIds = plcWorkers.keys();
    for (int i = 0; i < dIds.size(); ++i)
        plcWorkers.remove(dIds[i]);

    dIds = robotWorkers.keys();
    for (int i = 0; i < dIds.size(); ++i)
        robotWorkers.remove(dIds[i]);

    dIds = schedulingWorkers.keys();
    for (int i = 0; i < dIds.size(); ++i)
        schedulingWorkers.remove(dIds[i]);

    dIds = workerThreads.keys();
    for (int i = 0; i < dIds.size(); ++i)
    {   // QThread is automatically delete by QThread::deleteLater after sending QThread::finished signal
        workerThreads[dIds[i]]->quit();
        workerThreads[dIds[i]]->wait();
        workerThreads.remove(dIds[i]);
    }
}
