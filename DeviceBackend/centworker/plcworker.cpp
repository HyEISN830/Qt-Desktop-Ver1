#include "plcworker.h"

PlcWorker::PlcWorker(QObject *parent)
    : QObject{parent}
{

}

PlcWorker::PlcWorker(DevicePLC *plc) : plc(plc)
{
    timer = new QTimer;
    timer->setInterval(5000);
    connect(timer, &QTimer::timeout, this, [=] { emit readRegisters(DevicePLC::PollingRegisters, id, startAddr, length); emit writeRegister(DevicePLC::WriteSingleRegister, id, 300, QDateTime::currentDateTime().time().second()); });
    timer->start(5000);
}

void PlcWorker::received(int type, QList<ushort> result)
{
    switch ((DevicePLC::PacketType)type)
    {
    case DevicePLC::PollingRegisters:
        qDebug() << result;
        break;
    case DevicePLC::WriteSingleRegister:
        qDebug() << "write single register ok.";
        break;
    default:
        break;
    }
}

PlcWorker::~PlcWorker()
{
    if (timer)
        timer->stop();

    delete timer;
}
