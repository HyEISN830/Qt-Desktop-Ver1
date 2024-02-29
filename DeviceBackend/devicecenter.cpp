#include "devicecenter.h"


DeviceCenter::DeviceCenter()
{
}

#pragma region "设备启动以及生命周期相关相关 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" {
void DeviceCenter::start()
{
    // TODO: 在此处处理所有的worker相关connect
    // W1
    ScannerWorker *w1sw = findScannerWorker(DeviceLineNo::W1);
    PlcWorker *w1pw = findPlcWorker(DeviceLineNo::W1);
    RobotWorker *w1rw = findRobotWorker(DeviceLineNo::W1);
    connect(w1pw, &PlcWorker::pullUp, w1sw, &ScannerWorker::pullUp);
    connect(w1pw, &PlcWorker::commitReq, w1sw, &ScannerWorker::commitReq);
    connect(w1pw, &PlcWorker::cleanReq, w1sw, &ScannerWorker::cleanReq);
    connect(w1sw, &ScannerWorker::gotoChange, w1pw, &PlcWorker::gotoChange);
    connect(w1sw, &ScannerWorker::gotoChangeReady, w1pw, &PlcWorker::gotoChangeReady);
    connect(w1sw, &ScannerWorker::txRobotParams, w1rw, &RobotWorker::_writeParams);
    connect(w1sw, &ScannerWorker::approveOut, w1pw, &PlcWorker::approveOut);
    connect(w1sw, &ScannerWorker::rejectOut, w1pw, &PlcWorker::rejectOut);
    connect(w1rw, &RobotWorker::requestStartUpParams, w1sw, &ScannerWorker::requestStartUpParams);

    // W2
    ScannerWorker *w2sw = findScannerWorker(DeviceLineNo::W2);
    PlcWorker *w2pw = findPlcWorker(DeviceLineNo::W2);
    RobotWorker *w2rw = findRobotWorker(DeviceLineNo::W2);
    connect(w2pw, &PlcWorker::pullUp, w2sw, &ScannerWorker::pullUp);
    connect(w2pw, &PlcWorker::commitReq, w2sw, &ScannerWorker::commitReq);
    connect(w2pw, &PlcWorker::cleanReq, w2sw, &ScannerWorker::cleanReq);
    connect(w2sw, &ScannerWorker::gotoChange, w2pw, &PlcWorker::gotoChange);
    connect(w2sw, &ScannerWorker::gotoChangeReady, w2pw, &PlcWorker::gotoChangeReady);
    connect(w2sw, &ScannerWorker::txRobotParams, w2rw, &RobotWorker::_writeParams);
    connect(w2sw, &ScannerWorker::approveOut, w2pw, &PlcWorker::approveOut);
    connect(w2sw, &ScannerWorker::rejectOut, w2pw, &PlcWorker::rejectOut);
    connect(w2rw, &RobotWorker::requestStartUpParams, w2sw, &ScannerWorker::requestStartUpParams);
    connect(w2rw, &RobotWorker::robotSendOk, w2pw, &PlcWorker::robotSendOk);

    // W3
    ScannerWorker *w3sw = findScannerWorker(DeviceLineNo::W3);
    PlcWorker *w3pw = findPlcWorker(DeviceLineNo::W3);
    RobotWorker *w3rw = findRobotWorker(DeviceLineNo::W3);
    connect(w3pw, &PlcWorker::pullUp, w3sw, &ScannerWorker::pullUp);
    connect(w3pw, &PlcWorker::commitReq, w3sw, &ScannerWorker::commitReq);
    connect(w3pw, &PlcWorker::cleanReq, w3sw, &ScannerWorker::cleanReq);
    connect(w3sw, &ScannerWorker::gotoChange, w3pw, &PlcWorker::gotoChange);
    connect(w3sw, &ScannerWorker::gotoChangeReady, w3pw, &PlcWorker::gotoChangeReady);
    connect(w3sw, &ScannerWorker::txRobotParams, w3rw, &RobotWorker::_writeParams);
    connect(w3sw, &ScannerWorker::approveOut, w3pw, &PlcWorker::approveOut);
    connect(w3sw, &ScannerWorker::rejectOut, w3pw, &PlcWorker::rejectOut);
    connect(w3rw, &RobotWorker::requestStartUpParams, w3sw, &ScannerWorker::requestStartUpParams);

    // N3
    ScannerWorker *n3sw = findScannerWorker(DeviceLineNo::N3);
    PlcWorker *n3pw = findPlcWorker(DeviceLineNo::N3);
    RobotWorker *n3rw = findRobotWorker(DeviceLineNo::N3);
    connect(n3pw, &PlcWorker::pullUp, n3sw, &ScannerWorker::pullUp);
    connect(n3pw, &PlcWorker::commitReq, n3sw, &ScannerWorker::commitReq);
    connect(n3pw, &PlcWorker::cleanReq, n3sw, &ScannerWorker::cleanReq);
    connect(n3sw, &ScannerWorker::gotoChange, n3pw, &PlcWorker::gotoChange);
    connect(n3sw, &ScannerWorker::gotoChangeReady, n3pw, &PlcWorker::gotoChangeReady);
    connect(n3sw, &ScannerWorker::txRobotParams, n3rw, &RobotWorker::_writeParams);
    connect(n3sw, &ScannerWorker::approveOut, n3pw, &PlcWorker::approveOut);
    connect(n3sw, &ScannerWorker::rejectOut, n3pw, &PlcWorker::rejectOut);
    connect(n3rw, &RobotWorker::requestStartUpParams, n3sw, &ScannerWorker::requestStartUpParams);

    // N2
    ScannerWorker *n2sw = findScannerWorker(DeviceLineNo::N2);
    PlcWorker *n2pw = findPlcWorker(DeviceLineNo::N2);
    RobotWorker *n2rw = findRobotWorker(DeviceLineNo::N2);
    connect(n2pw, &PlcWorker::pullUp, n2sw, &ScannerWorker::pullUp);
    connect(n2pw, &PlcWorker::commitReq, n2sw, &ScannerWorker::commitReq);
    connect(n2pw, &PlcWorker::cleanReq, n2sw, &ScannerWorker::cleanReq);
    connect(n2sw, &ScannerWorker::gotoChange, n2pw, &PlcWorker::gotoChange);
    connect(n2sw, &ScannerWorker::gotoChangeReady, n2pw, &PlcWorker::gotoChangeReady);
    connect(n2sw, &ScannerWorker::txRobotParams, n2rw, &RobotWorker::_writeParams);
    connect(n2sw, &ScannerWorker::approveOut, n2pw, &PlcWorker::approveOut);
    connect(n2sw, &ScannerWorker::rejectOut, n2pw, &PlcWorker::rejectOut);
    connect(n2rw, &RobotWorker::requestStartUpParams, n2sw, &ScannerWorker::requestStartUpParams);

    // N1
    ScannerWorker *n1sw = findScannerWorker(DeviceLineNo::N1);
    PlcWorker *n1pw = findPlcWorker(DeviceLineNo::N1);
    RobotWorker *n1rw = findRobotWorker(DeviceLineNo::N1);
    connect(n1pw, &PlcWorker::pullUp, n1sw, &ScannerWorker::pullUp);
    connect(n1pw, &PlcWorker::commitReq, n1sw, &ScannerWorker::commitReq);
    connect(n1pw, &PlcWorker::cleanReq, n1sw, &ScannerWorker::cleanReq);
    connect(n1sw, &ScannerWorker::gotoChange, n1pw, &PlcWorker::gotoChange);
    connect(n1sw, &ScannerWorker::gotoChangeReady, n1pw, &PlcWorker::gotoChangeReady);
    connect(n1sw, &ScannerWorker::txRobotParams, n1rw, &RobotWorker::_writeParams);
    connect(n1sw, &ScannerWorker::approveOut, n1pw, &PlcWorker::approveOut);
    connect(n1sw, &ScannerWorker::rejectOut, n1pw, &PlcWorker::rejectOut);
    connect(n1rw, &RobotWorker::requestStartUpParams, n1sw, &ScannerWorker::requestStartUpParams);

    // Scheduling Worker
    SchedulingWorker *sworker = schedulingWorkers.first();
    connect(sworker, &SchedulingWorker::exWriteRobotParams, w1rw, &RobotWorker::exWriteParams);
    connect(sworker, &SchedulingWorker::exWriteRobotParams, w2rw, &RobotWorker::exWriteParams);
    connect(sworker, &SchedulingWorker::exWriteRobotParams, w3rw, &RobotWorker::exWriteParams);
    connect(sworker, &SchedulingWorker::exWriteRobotParams, n3rw, &RobotWorker::exWriteParams);
    connect(sworker, &SchedulingWorker::exWriteRobotParams, n2rw, &RobotWorker::exWriteParams);
    connect(sworker, &SchedulingWorker::exWriteRobotParams, n1rw, &RobotWorker::exWriteParams);

    // Logger
    logWorker = new HttpAddLogWorker;
    workerThreads[222] = logWorker;
    connect(this, &DeviceCenter::_appendLog, logWorker, &HttpAddLogWorker::appendLog);
    logWorker->start();

    utcThread = new HDateTimeWorker;
    connect(utcThread, &HDateTimeWorker::finished, utcThread, &HDateTimeWorker::deleteLater);
    utcThread->start();
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

    if (utcThread)
    {
        utcThread->quit();
        utcThread->wait();
    }
}
