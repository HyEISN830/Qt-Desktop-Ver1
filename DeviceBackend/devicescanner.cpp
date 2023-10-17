#include "devicescanner.h"

DeviceScanner::DeviceScanner(QObject *parent)
    : QObject{parent}
{

}

void DeviceScanner::start()
{
    if (!worker)
    {
        worker = new TcpWorker(ip, port);
        connect(worker, &TcpWorker::connected, this, [=] { emit connected(this); });
        connect(worker, &TcpWorker::disconnected, this, [=] { emit disconnected(this); });
        connect(worker, &TcpWorker::connectFailed, this, [=] { emit connectFailed(this); });
        connect(worker, &TcpWorker::received, this, [=] (QByteArray data) { emit barcodeReceived(this, data); });
        connect(this, &DeviceScanner::_send, worker, &TcpWorker::write);
        worker->start();
    }
}

void DeviceScanner::apply(QString ip, int port)
{
    if (worker)
    {
        this->ip = ip;
        this->port = port;
        worker->apply(ip, port);
        emit applied(dId, ip, port);
    }
}

void DeviceScanner::send(QString content)
{
    if (worker && worker->getConnected())
        emit _send(content);
}

DeviceScanner::~DeviceScanner()
{
    if (worker)
    {
        worker->quit();
        worker->wait();
    }

    delete worker;
}
