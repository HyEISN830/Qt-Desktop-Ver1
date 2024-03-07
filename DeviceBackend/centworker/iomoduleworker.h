#ifndef IOMODULEWORKER_H
#define IOMODULEWORKER_H

#include <QObject>
#include <QTcpSocket>
#include <QThread>
#include <QByteArray>
#include <bitset>
#include <QTimer>
#include <QDateTime>

#include "../worker/tcpworker.h"
#include "./struct/cmdpacket.h"


class IOModuleWorker : public QObject
{
    Q_OBJECT
public:
    IOModuleWorker(int did, int no, QString ip, int port);
    ~IOModuleWorker();

    void start();
    inline int getDId() { return did; }

private:
    QList<CMDPacket> handleGate(QStringList);

signals:
    void clientConnected(int dId);
    void clientDisconnected(int dId);
    // @brief OK or NIL
    void result(QByteArray);
    void connIO(QString, int);
    void sendTCP(QByteArray);
    void received(QByteArray);
    void sended(int, QByteArray);

    void _deleteTimer();

public slots:
    void receiveCMD(int, int, QString);
    void apply(QString ip, int port);

private slots:
    void _clientConnected();
    void _clientDisconnected();
    void receiveTCP(QByteArray);
    void _sended(QTcpSocket*, QByteArray);

private:
    int did;
    int no;
    QString ip;
    int port;
    TcpWorker *tcp = nullptr;
    std::bitset<8> io;
    QTimer *timer = nullptr;
    qint64 executelog = QDateTime::currentMSecsSinceEpoch();

    const QString OK = "OK";    // @breif on success or yes or ok result string
    const QString NG = "NIL";   // @brefi on error or no result string
    const QString GATE = "GATE";
    const QString GOPEN = "OPEN";
    const QString GCLOSE = "CLOSE";
    const QString GQUERY = "QUERY";
};

#endif // IOMODULEWORKER_H
