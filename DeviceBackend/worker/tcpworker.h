#ifndef TCPWORKER_H
#define TCPWORKER_H

#include <QThread>
#include <QObject>
#include <QTcpSocket>
#include <QTimer>

#include "tcpworkersender.h"


class TcpWorker : public QThread
{
    Q_OBJECT
public:
    explicit TcpWorker(QObject *parent = nullptr);
    TcpWorker(QString ip, int port) : ip(ip), port(port) {}

    void run() override
    {
        tcp = new QTcpSocket;
        connect(tcp, &QTcpSocket::readyRead, this, &TcpWorker::rx);
        connect(tcp, &QTcpSocket::connected, this, &TcpWorker::connd);
        connect(tcp, &QTcpSocket::disconnected, this, &TcpWorker::conndis);
        connect(this, &QThread::finished, tcp, &QTcpSocket::deleteLater);

        sender = new TcpWorkerSender;
        sender->moveToThread(this);
        connect(this, &TcpWorker::send, sender, &TcpWorkerSender::sendMsg2);
        connect(this, &TcpWorker::sendb, sender , &TcpWorkerSender::sendMsg2b);
        connect(this, &QThread::finished, sender, &TcpWorkerSender::deleteLater);

        timer = new QTimer;
        timer->moveToThread(this);
        timer->setInterval(5000);
        timer->start();
        connect(timer, &QTimer::timeout, timer, [=] {   // tcp alive checking
            if (!connecting && !conn)
            {
                bool ok = false;

                connecting = true;
                tcp->connectToHost(ip, port);
                ok = tcp->waitForConnected(1000);
                if (!ok) emit connectFailed();
                connecting = false;
            }
            else if (a)
            {
                a = false;
                tcp->disconnectFromHost();
            }
        });
        connect(this, &QThread::finished, timer, &QTimer::stop);
        connect(this, &QThread::finished, timer, &QTimer::deleteLater);

        connect(this, &QThread::finished, this, &QThread::deleteLater);
        exec();
    }

    void setIp(QString ip) { this->ip = ip; }
    void setPort(int port) { this->port = port; }

signals:
    void send(QTcpSocket*, QString);    // send string to tcp
    void sendb(QTcpSocket*, QByteArray);    // send bytes to tcp
    void received(QByteArray);
    void sendError(QString);
    void connected();
    void connectFailed();
    void disconnected();

public slots:
    void write(QString content) { emit send(tcp, content); }
    void writeb(QByteArray data) { emit sendb(tcp, data); }
    void rx() { emit received(tcp->read(1024)); }
    void serr(QString reason) { emit sendError(reason); }
    void connd() { emit connected(); conn = true; }
    void connf() { emit connectFailed(); conn = false; }
    void conndis() { emit disconnected(); conn = false; }
    void apply(QString ip, int port) { this->ip = ip; this->port = port; this->a = true; }     // call this function if change ip or port after

private:
    QTcpSocket *tcp = nullptr;  // auto delete after used
    QTimer *timer = nullptr;    // auto delete after used
    TcpWorkerSender *sender = nullptr;  // auto delete after used
    QString ip;
    int port;

    bool a = false;
    bool conn = false;
    bool connecting = false;
};

#endif // TCPWORKER_H
