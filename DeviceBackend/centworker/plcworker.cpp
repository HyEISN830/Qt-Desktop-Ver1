#include "plcworker.h"

PlcWorker::PlcWorker(DevicePLC *plc, QList<int> allowLines) : plc(plc)
{
    for (int var = 0; var < allowLines.size(); ++var)
        this->allowLines.append((DeviceLineNo)allowLines[var]);

    pollingTimer = new QTimer;
    pollingTimer->setInterval(1000);
    connect(pollingTimer, &QTimer::timeout, this, [=] { emit readRegisters(DevicePLC::PollingRegisters, id, startAddr, length); });
    pollingTimer->start();

//    emit writeRegister(DevicePLC::WriteSingleRegister, id, 300, QDateTime::currentDateTime().time().second());
}

void PlcWorker::received(int type, QList<ushort> result)
{
    switch ((DevicePLC::PacketType)type)
    {
    case DevicePLC::PollingRegisters:
    {
        if (result.size() >= length)
        {
            int i = 0;
            for (int var = startAddr; var < startAddr + length; ++var)
            {
                registers[var] = result[i];
                i++;
            }

            processPullUp();
            processCommit();
            processClean();
        }
        break;
    }

    case DevicePLC::WriteSingleRegister:
        qDebug() << "write single register ok.";
        break;

    case DevicePLC::WriteW1RobotOk:
    case DevicePLC::WriteW2RobotOk:
    case DevicePLC::WriteW3RobotOk:
    case DevicePLC::WriteN3RobotOk:
    case DevicePLC::WriteN2RobotOk:
    case DevicePLC::WriteN1RobotOk:
        emit writed(plc, robotOkRegisters[DeviceLineNo(type - 58)], _robotOk);
        break;

    case DevicePLC::WriteW1CleanReaded:
    case DevicePLC::WriteW2CleanReaded:
    case DevicePLC::WriteW3CleanReaded:
    case DevicePLC::WriteN3CleanReaded:
    case DevicePLC::WriteN2CleanReaded:
    case DevicePLC::WriteN1CleanReaded:
        emit writed(plc, cleanPlcRegisters[DeviceLineNo(type - 52)], _cleanRst);
        break;

    case DevicePLC::WriteW1ChangeReady:
    case DevicePLC::WriteW2ChangeReady:
    case DevicePLC::WriteW3ChangeReady:
    case DevicePLC::WriteN3ChangeReady:
    case DevicePLC::WriteN2ChangeReady:
    case DevicePLC::WriteN1ChangeReady:
        emit writed(plc, cnotifyPlcRegisters[DeviceLineNo(type - 46)], _neworderOK);
        break;

    case DevicePLC::WriteW1CommitReject:
    case DevicePLC::WriteW2CommitReject:
    case DevicePLC::WriteW3CommitReject:
    case DevicePLC::WriteN3CommitReject:
    case DevicePLC::WriteN2CommitReject:
    case DevicePLC::WriteN1CommitReject:
        emit writed(plc, commitPlcRegisters[DeviceLineNo(type - 40)], _commitNG);
        break;

    case DevicePLC::WriteW1CommitApprove:
    case DevicePLC::WriteW2CommitApprove:
    case DevicePLC::WriteW3CommitApprove:
    case DevicePLC::WriteN3CommitApprove:
    case DevicePLC::WriteN2CommitApprove:
    case DevicePLC::WriteN1CommitApprove:
        emit writed(plc, commitPlcRegisters[DeviceLineNo(type - 34)], _commitOK);
        break;

    case DevicePLC::WriteW1CommitReaded:
    case DevicePLC::WriteW2CommitReaded:
    case DevicePLC::WriteW3CommitReaded:
    case DevicePLC::WriteN3CommitReaded:
    case DevicePLC::WriteN2CommitReaded:
    case DevicePLC::WriteN1CommitReaded:
        emit writed(plc, commitPlcRegisters[DeviceLineNo(type - 28)], _commitReaded);
        break;

    case DevicePLC::WriteW1Wide:
    case DevicePLC::WriteW2Wide:
    case DevicePLC::WriteW3Wide:
        emit writed(plc, widePlcRegisters[DeviceLineNo(type - 25)], wideLog[DeviceLineNo(type - 25)]);
        break;

    case DevicePLC::WriteW1Change:
    case DevicePLC::WriteW2Change:
    case DevicePLC::WriteW3Change:
    case DevicePLC::WriteN3Change:
    case DevicePLC::WriteN2Change:
    case DevicePLC::WriteN1Change:
        emit writed(plc, changePlcRegisters[DeviceLineNo(type - 19)], bottomLog[DeviceLineNo(type - 19)] ? _changeB : _changeT);
        break;

    case DevicePLC::WriteW1PullUp:
    case DevicePLC::WriteW2PullUp:
    case DevicePLC::WriteW3PullUp:
    case DevicePLC::WriteN3PullUp:
    case DevicePLC::WriteN2PullUp:
    case DevicePLC::WriteN1PullUp:
        emit writed(plc, pullPlcRegisters[DeviceLineNo(type - 13)], _pullUpT);
        break;

    case DevicePLC::WriteW1ScanOK:
    case DevicePLC::WriteW2ScanOK:
    case DevicePLC::WriteW3ScanOK:
    case DevicePLC::WriteN3ScanOK:
    case DevicePLC::WriteN2ScanOK:
    case DevicePLC::WriteN1ScanOK:
        emit writed(plc, scanPlcRegisters[DeviceLineNo(type - 1)], _scanOK);
        break;

    case DevicePLC::WriteW1ScanNG:
    case DevicePLC::WriteW2ScanNG:
    case DevicePLC::WriteW3ScanNG:
    case DevicePLC::WriteN3ScanNG:
    case DevicePLC::WriteN2ScanNG:
    case DevicePLC::WriteN1ScanNG:
        emit writed(plc, scanPlcRegisters[DeviceLineNo(type - 7)], _scanNG);
        break;

    default:
        break;
    }
}

void PlcWorker::processPullUp()
{

    for (int var = 0; var < lines.size(); ++var)
    {
        DeviceLineNo line = lines[var];
        int addr = pullPlcRegisters[line];

        if (registers[addr] == _pullUpR)
        {
            // HACK: 托管开关设置
            if (settings.value(DC::DC_TOSTRING(lines[var]) + "Auto").toString() != "true") continue;
            registers[addr] = 0;
            emit writeRegister(DevicePLC::PacketType(lines[var] + 13), plc->getDId(), addr, _pullUpT);

            // HACK: PLC 3秒内重复夹起无效
            long diff = 0;
            if ((diff = (QDateTime::currentMSecsSinceEpoch() - pullLog[line])) >= 3)
            {
                pullLog[line] = QDateTime::currentMSecsSinceEpoch();
                emit pullUp(plc, lines[var]);
            }
            else
            {
                emit duplicateClamped(plc, line, diff);
            }
        }
    }
}

void PlcWorker::processCommit()
{
    for (int var = 0; var < lines.size(); ++var)
    {
        int addr = commitPlcRegisters[lines[var]];

        if (registers[addr] == _commitReq)
        {
            // HACK: 交收开关设置
//            if ((settings.value(DC::DC_TOSTRING(lines[var]) + "Commit").toString()) != "true") continue;
            registers[addr] = 0;
            emit writeRegister(DevicePLC::PacketType(lines[var] + 28), plc->getDId(), addr, _commitReaded);
            emit commitReq(plc, lines[var]);
        }
    }
}

void PlcWorker::processClean()
{
    for (int var = 0; var < lines.size(); ++var)
    {
        int addr = cleanPlcRegisters[lines[var]];

        if (registers[addr] == _cleanOk)
        {
            registers[addr] = 0;
            emit writeRegister(DevicePLC::PacketType(lines[var] + 52), plc->getDId(), addr, _cleanRst);
            emit cleanReq(plc, lines[var]);
        }
    }
}

void PlcWorker::approveOut(DeviceScanner* scanner, DeviceLineNo line)
{
    emit writeRegister(DevicePLC::PacketType(line + 34), id, commitPlcRegisters[line], _commitOK);
}

void PlcWorker::rejectOut(DeviceScanner* scanner, DeviceLineNo line)
{
    emit writeRegister(DevicePLC::PacketType(line + 40), id, commitPlcRegisters[line], _commitNG);
}

void PlcWorker::robotSendOk(DeviceLineNo line)
{
    if (robotOkRegisters.contains(line))
        emit writeRegister(DevicePLC::PacketType(line + 58), id, robotOkRegisters[line], _robotOk);
}

void PlcWorker::scaned(DeviceLineNo line, bool ok)
{
    DevicePLC::PacketType type = (DevicePLC::PacketType)(line + (ok ? 1 : 7));
    emit writeRegister(type, id, scanPlcRegisters[line], ok ? _scanOK : _scanNG);
}

void PlcWorker::gotoChangeReady(DeviceScanner *scanner, DeviceLineNo line)
{
    emit writeRegister(DevicePLC::PacketType(line + 46), id, cnotifyPlcRegisters[line], _neworderOK);
}

void PlcWorker::gotoChange(DeviceScanner *scanner, DeviceLineNo line, QString orderNo, int len, int wide, int height, bool bottom)
{
    bottomLog[line] = bottom;
    wideLog[line] = wide;

    if (widePlcRegisters.contains(line))
        emit writeRegister(DevicePLC::PacketType(line + 25), id, widePlcRegisters[line], wide);

    QThread::msleep(200);
    emit writeRegister(DevicePLC::PacketType(line + 19), id, changePlcRegisters[line], bottom ? _changeB : _changeT);
}

PlcWorker::~PlcWorker()
{
    if (pollingTimer)
        pollingTimer->stop();

    delete pollingTimer;
}
