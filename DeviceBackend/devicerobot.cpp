#include "devicerobot.h"

DeviceRobot::DeviceRobot(QObject *parent)
    : QObject{parent}
{

}

void DeviceRobot::start()
{
    if (!worker)
    {
        worker = new TcpWorker(ip, port);
        connect(worker, &TcpWorker::connected, this, [=] { emit connected(this); });
        connect(worker, &TcpWorker::disconnected, this, [=] { emit disconnected(this); });
        connect(worker, &TcpWorker::connectFailed, this, [=] { emit connectFailed(this); });
        connect(worker, &TcpWorker::received, this, [=] (QByteArray data) { emit rx(this); emit received(this, data); });
        connect(this, &DeviceRobot::_write, worker, &TcpWorker::write);
        worker->start();
    }
}

void DeviceRobot::apply(QString ip, int port)
{
    if (worker)
    {
        this->ip = ip;
        this->port = port;
        worker->apply(ip, port);
        emit applied(dId, ip, port);
    }
}

void DeviceRobot::writeParams(int len, int wide, int height, int row, int col, int layer)
{
    QString params = ""
    % QString::number(len) % "#"
    % QString::number(wide) % "#"
    % QString::number(height) % "#"
    % QString::number(row) % "#"
    % QString::number(col) % "#"
    % QString::number(layer);
    write(params);
}

DeviceRobot::~DeviceRobot()
{
    if (worker)
    {
        worker->quit();
        worker->wait();
    }

    delete worker;
}
