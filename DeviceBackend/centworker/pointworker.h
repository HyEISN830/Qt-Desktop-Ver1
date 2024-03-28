#ifndef POINTWORKER_H
#define POINTWORKER_H

#include <QObject>
#include <QTimer>
#include <QQueue>
#include <QMutex>

#include "../worker/tcpworker.h"


class PointWorker : public QObject
{
    Q_OBJECT
public:
    explicit PointWorker(QObject *parent = nullptr);
    PointWorker(int dId, QString ip, int port) : did(dId), ip(ip), port(port)
    {
        framesender.setInterval(900);
        connect(&framesender, &QTimer::timeout, this, [=] { m.lock(); if (!datas.isEmpty()) write(datas.dequeue()); m.unlock(); });
        framesender.start();
    }
    ~PointWorker()
    {
        if (worker)
        {
            worker->quit();
            worker->wait();
        }
    }

    inline int getDId() { return this->did; }
    inline QString getIp() { return this->ip; }
    inline int getPort() { return this->port; }
    inline void pushdata(QByteArray data) { m.lock(); this->datas.enqueue(data); m.unlock(); }

signals:
    void connected(int dId);
    void disconnected(int dId);
    void received(int dId, QByteArray);
    void sended(int dId, QByteArray);

    void _write(QByteArray);

public slots:
    void start()
    {
        if (!worker)
        {
            worker = new TcpWorker(ip, port);
            connect(worker, &TcpWorker::connected, this, [=] { emit connected(did); datas.enqueue(QByteArray(1, 0)); });
            connect(worker, &TcpWorker::disconnected, this, [=] { emit disconnected(did); });
            connect(worker, &TcpWorker::received, this, [=] (QByteArray data) { emit received(did, data); });
            connect(this, &PointWorker::_write, worker, &TcpWorker::writeb);
            worker->start();
        }
    }

    void write(QByteArray data)
    {
        if (worker && worker->getConnected())
        {
            emit _write(data);
            emit sended(did, data);
        }
    }

private:
    int did;
    QString ip;
    int port;
    QTimer framesender;
    QQueue<QByteArray> datas;
    QMutex m;

    TcpWorker *worker = nullptr;
};

#endif // POINTWORKER_H