#ifndef SYSWORKER_H
#define SYSWORKER_H

#include <QObject>
#include <QTcpSocket>
#include <QDateTime>

#include "../worker/tcpserverworker.h"


class SysWorker : public QObject
{
    Q_OBJECT
public:
    explicit SysWorker(QObject *parent = nullptr);
    SysWorker(int did, int port, int maxclients, quint8 agvCode) : did(did), port(port), maxclients(maxclients), agvCode(agvCode) {}
    ~SysWorker() { server->quit(); server->wait(); }

    quint8 getAgvCode() { return agvCode; }
    QString getaip() { return curaip; }
    void setaip(QString aip) { this->curaip = aip; };

signals:
    void clientConnected(int dId, QString ip, int port);
    void clientDisconnected(int dId, QString ip, int port);
    void clientReceived(int dId, QByteArray data);
    void clientSended(int dId, QByteArray data);

    void _write(QByteArray);

public slots:
    void start()
    {
        server = new TcpServerWorker(port, maxclients);
        connect(server, &TcpServerWorker::clientConnected, this, &SysWorker::_clientConnected);
        connect(server, &TcpServerWorker::clientDisconnected, this, &SysWorker::_clientDisconnected);
        connect(server, &TcpServerWorker::clientReceived, this, &SysWorker::_clientReceived);
        server->start();
    }

    void _clientConnected(QTcpSocket* client)
    {
        if (client)
        {
            this->client = client;
            clientIp = client->localAddress().toString();
            clientPort = client->localPort();
            connect(this, &SysWorker::_write, client, [=] (QByteArray data) { if (client) client->write(data); });
            emit clientConnected(did, clientIp, clientPort);
        }
    }

    void _clientDisconnected()
    {
        emit clientDisconnected(did, clientIp, clientPort);
    }

    void _clientReceived(QTcpSocket *client, QByteArray data)
    {
        emit clientReceived(did, data);
    }

    void _clientWrite(QByteArray data)
    {
        if (client)
        {
            emit _write(data);
            emit clientSended(did, data);
        }
    }

private:
    int did;
    int port;
    int maxclients;
    QString clientIp;
    int clientPort;
    quint16 agvCode;
    QString curaip;

    TcpServerWorker *server = nullptr;
    QTcpSocket *client = nullptr;
};

#endif // SYSWORKER_H
