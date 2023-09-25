#include "devicescanner.h"

DeviceScanner::DeviceScanner(QObject *parent)
    : QObject{parent}
{

}

void DeviceScanner::connect()
{
    QTimer::singleShot(100, this, [=] () {
        if (connecting) return;

        bool ok = false;

        connecting = true;
        if (!tcp)
            tcp = new QTcpSocket;
        tcp->connectToHost(ip, port);
        ok = tcp->waitForConnected(3000);

        if (ok && (c = true))
            emit connected(this);
        else
            emit connectFailed(this);

        if (!readTcpSlotConnected)
        {
            this->QObject::connect(tcp, &QIODevice::readyRead, this, [=] () {
                readTcpSlotConnected = true;
                emit barcodeReceived(this, tcp->readAll());
            });
            this->QObject::connect(tcp, &QTcpSocket::disconnected, this, [=] () {
                c = false;
                emit disconnected(this);
            });
        }
        connecting = false;
    });
}

void DeviceScanner::heartcheck()
{
    if (!c)
        connect();
}

DeviceScanner::~DeviceScanner()
{
    delete tcp;
}
