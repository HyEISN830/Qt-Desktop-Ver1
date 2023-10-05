#include "deviceplc.h"

DevicePLC::DevicePLC(QObject *parent)
    : QObject{parent}
{

}

void DevicePLC::start()
{
    worker = new ModbusTcpWorker(ip, port);
    connect(worker, &ModbusTcpWorker::connected, this, &DevicePLC::_connected);
    connect(worker, &ModbusTcpWorker::disconnected, this, &DevicePLC::_disconnected);
    connect(worker, &ModbusTcpWorker::received, this, &DevicePLC::received);
    connect(worker, &ModbusTcpWorker::tx, this, &DevicePLC::_tx);
    connect(worker, &ModbusTcpWorker::rx, this, &DevicePLC::_rx);
    connect(this, &DevicePLC::_writeRegister, worker, &ModbusTcpWorker::writeRegister);
    connect(this, &DevicePLC::_readRegisters, worker, &ModbusTcpWorker::readRegisters);
    worker->start();
}

void DevicePLC::apply(QString ip, int port)
{
    this->ip = ip;
    this->port = port;
    worker->apply(ip, port);
    emit applied(dId, ip, port);
}

DevicePLC::~DevicePLC()
{
    if (worker)
    {
        worker->quit();
        worker->wait();
    }

    delete worker;
}
