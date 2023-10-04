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
//        connect(worker, &TcpWorker::finished, worker, &TcpWorker::deleteLater);
        worker->start();
    }
}

void DeviceScanner::apply(QString ip, int port)
{
    if (worker)
    {
        worker->setIp(ip);
        worker->setPort(port);
        worker->apply();
    }
}

DeviceScanner::~DeviceScanner()
{
    worker->quit();
    worker->wait();

    delete worker;
}
