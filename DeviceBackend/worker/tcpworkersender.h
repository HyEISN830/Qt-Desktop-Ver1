#ifndef TCPWORKERSENDER_H
#define TCPWORKERSENDER_H

#include <QObject>
#include <QTcpSocket>


class TcpWorkerSender : public QObject
{
    Q_OBJECT
public:
    explicit TcpWorkerSender(QObject *parent = nullptr);

signals:
    void sendError(QString reason);

public slots:
    void sendMsg2(QTcpSocket *tcp, QString msg)
    {
        bool ok = false;

        tcp->write(msg.toStdString().c_str());
        ok = tcp->waitForBytesWritten(1000);

        if (!ok)
            emit sendError("Write Tcp Socket Timeout.");
    }

    void sendMsg2b(QTcpSocket *tcp, QByteArray data)
    {
        bool ok = false;

        tcp->write(data);
        ok = tcp->waitForBytesWritten(1000);

        if (!ok)
            emit sendError("Write Tcp Socket Timeout.");
    }

};

#endif // TCPWORKERSENDER_H
