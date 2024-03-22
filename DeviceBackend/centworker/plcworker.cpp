#include "plcworker.h"

PlcWorker::PlcWorker(DevicePLC *plc, QList<int> allowLines) : plc(plc)
{
    for (int var = 0; var < allowLines.size(); ++var)
        this->allowLines.append((DeviceLineNo)allowLines[var]);

    pollingTimer = new QTimer;
    pollingTimer->setInterval(1000);
    connect(pollingTimer, &QTimer::timeout, this, [=] { emit readRegisters(DevicePLC::PollingRegisters, id, startAddr, length); });
    pollingTimer->start();

    // init registers
    for (int var = 0; var < length; ++var)
        registers[var] = 0;

//    emit writeRegister(DevicePLC::WriteSingleRegister, id, 300, QDateTime::currentDateTime().time().second());
}

void PlcWorker::received(int type, QList<ushort> result, int addr, ushort value)
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

            // processPullUp();
            // processCommit();
            // processClean();
        }
        break;
    }

    case DevicePLC::WriteSingleRegister:
        emit writed(plc, addr, value);
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

            // HACK: PLC 3秒内重复夹起无效
            qint64 diff = 0;
            if ((diff = (HDateTime::utc_ms - pullLog[line])) >= 3000)
            {
                emit writeRegister(DevicePLC::PacketType(lines[var] + 13), plc->getDId(), addr, _pullUpT);
                QThread::msleep(100);
                pullLog[line] = HDateTime::utc_ms;
                emit pullUp(plc, lines[var]);
            }
            else
            {
                emit duplicateClamped(plc, line, diff);
            }
            // emit pullUp(plc, lines[var]);
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
