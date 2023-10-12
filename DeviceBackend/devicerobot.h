#ifndef DEVICEROBOT_H
#define DEVICEROBOT_H

#include <QObject>
#include <QStringBuilder>

#include "devicelineno.h"
#include "worker/tcpworker.h"


class DeviceRobot : public QObject
{
    Q_OBJECT
public:
    explicit DeviceRobot(QObject *parent = nullptr);
    DeviceRobot(int dId, QString ip, int port, DeviceLineNo lineNo) : dId(dId), ip(ip), port(port), line(lineNo) {}
    ~DeviceRobot();

    inline void setDId(int dId) { this->dId = dId; }
    inline void setIp(QString ip) { this->ip = ip; }
    inline void setPort(int port) { this->port = port; }
    inline void setLine(DeviceLineNo lineNo) { this->line = lineNo; }

    inline int getDId() { return this->dId; }
    inline QString getIp() { return this->ip; }
    inline int getPort() { return this->port; }
    inline DeviceLineNo getLine() { return this->line; }

    void start();
    void apply(QString ip, int port);   // modify ip and port and reconnect

signals:
    void connected(DeviceRobot*);
    void disconnected(DeviceRobot*);
    void connectFailed(DeviceRobot*);
    void sended(DeviceRobot*, QString content);
    void received(DeviceRobot*, QString content);
    void _apply(QString ip, int port);
    void applied(int dId, QString ip, int port);
    void _write(QString content);
    void tx(DeviceRobot*);
    void rx(DeviceRobot*);

public slots:
    void write(QString content) { emit tx(this); emit sended(this, content); emit _write(content); }
    // @brief 向机器人发送参数: 长宽高行列层
    void writeParams(int len, int wide, int height, int row, int col, int layer);

private:
    int dId = 0;
    DeviceLineNo line = Unknow;
    QString ip;
    int port = 0;
    TcpWorker *worker = nullptr;    // auto delete after quited

};

#endif // DEVICEROBOT_H
