#ifndef IOGATEWAY_H
#define IOGATEWAY_H

#include <QObject>

#include "../worker/tcpserverworker.h"


class IOGateway : public QObject
{
    Q_OBJECT
public:
    IOGateway(int dId, int port) : did(dId), port(port) {}
    ~IOGateway()
    {
        if (server)
        {
            server->quit();
            server->wait();
        }

        delete server;
    }

    inline int getDId() { return did; }

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
        connect(server, &TcpServerWorker::clientConnected, this, &IOGateway::_clientConnected);
        connect(server, &TcpServerWorker::clientDisconnected, this, &IOGateway::_clientDisconnected);
        connect(server, &TcpServerWorker::clientReceived, this, &IOGateway::_clientReceived);
        server->start();
    }

    void _clientConnected(QTcpSocket* client)
    {
        if (client)
        {
            this->client = client;
            clientIp = client->localAddress().toString();
            clientPort = client->localPort();
            connect(this, &IOGateway::_write, client, [=] (QByteArray data) { if (client) client->write(data); });
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
    int maxclients = 1;
    QString clientIp;
    int clientPort;
    quint16 agvCode;

    TcpServerWorker *server = nullptr;
    QTcpSocket *client = nullptr;
};

#endif // IOGATEWAY_H
