#ifndef TCPSERVERWORKER_H
#define TCPSERVERWORKER_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QTcpSocket>
#include <QTcpServer>
#include <QTimer>
#include <QByteArray>

#include "tcpserverworkersender.h"


class TcpServerWorker : public QThread
{
    Q_OBJECT
public:
    explicit TcpServerWorker(QObject *parent = nullptr);
    TcpServerWorker(int port, int maxClients) : port(port), maxClients(maxClients) {}

    void run() override
    {
        server = new QTcpServer;
        server->setMaxPendingConnections(maxClients);
        connect(server, &QTcpServer::pendingConnectionAvailable, server, [=] {
            if (clients + 1 > maxClients)
            {
                QTcpSocket *c = server->nextPendingConnection();
                c->disconnectFromHost();
                connect(c, &QTcpSocket::disconnected, c, &QTcpSocket::deleteLater);
                return;
            }

            QTcpSocket *client = server->nextPendingConnection();

            if (client)
            {
                this->client = client;
                connect(client, &QTcpSocket::disconnected, this, &TcpServerWorker::_clientDisconnected);
                connect(client, &QTcpSocket::disconnected, client, &QTcpSocket::deleteLater);
                connect(client, &QTcpSocket::readyRead, this, &TcpServerWorker::_clientReadyRead);
                connect(this, &QThread::finished, client, &QTcpSocket::deleteLater);
                clients++;
                emit clientConnected(client);
            }
        });
        connect(this, &QThread::finished, server, &QTcpServer::deleteLater);
        server->listen(QHostAddress::Any, port);

        connect(this, &QThread::finished, this, &QThread::deleteLater);
        exec();
    }

signals:
    void clientConnected(QTcpSocket*);
    void clientDisconnected();
    void clientReceived(QTcpSocket*, QByteArray);

public slots:
    void _clientDisconnected()
    {
        if (clients > 0)
            clients--;
        emit clientDisconnected();
    }

    void _clientReadyRead()
    {
        emit clientReceived(client, client->readAll());
    }

private:
    QTcpServer *server = nullptr;  // auto delete after used
    QTimer *timer = nullptr;    // auto delete after used
    TcpServerWorkerSender *sender = nullptr;  // auto delete after used
    int port;
    int maxClients;
    int clients = 0;
    QTcpSocket *client = nullptr;

    bool a = false;
    bool conn = false;
    bool connecting = false;
};

#endif // TCPSERVERWORKER_H
