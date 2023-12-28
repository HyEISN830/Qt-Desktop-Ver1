#ifndef TCPSERVERWORKERSENDER_H
#define TCPSERVERWORKERSENDER_H

#include <QObject>

class TcpServerWorkerSender : public QObject
{
    Q_OBJECT
public:
    explicit TcpServerWorkerSender(QObject *parent = nullptr);

signals:
};

#endif // TCPSERVERWORKERSENDER_H
