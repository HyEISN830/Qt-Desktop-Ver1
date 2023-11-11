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

bool DeviceRobot::getConnected()
{
    return worker && worker->getConnected();
}

void DeviceRobot::writeParams(QJsonObject jobj)
{
    QString params = ""
    % (jobj["bType"].toBool() ? (jobj["sType"].toString().size() ? jobj["sType"].toString() : "0") : (jobj["sType1"].toString().size() ? jobj["sType1"].toString() : "0")) % "#"
    % QString::number(jobj["len"].toInt()) % "#"
    % QString::number(jobj["wide"].toInt()) % "#"
    % QString::number(jobj["height"].toInt()) % "#"
    % (jobj["bType"].toBool() ? "1" : "0")
    ;
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
