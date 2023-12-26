#ifndef SCHEDULINGWORKER_H
#define SCHEDULINGWORKER_H

#include <QObject>
#include <QTimer>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>

#include "devicelineno.h"
#include "worker/tcpworker.h"

class SchedulingWorker : public QObject
{
    Q_OBJECT
public:
    enum TaskType
    {
        SendStartUpParams,
        SendManualParams
    };

    explicit SchedulingWorker(QObject *parent = nullptr);
    SchedulingWorker(int dId, QString ip, int port, DeviceLineNo line);
    ~SchedulingWorker();

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
    bool getConnected();

private:
    QString taskResult(qint64, bool, QString);

signals:
    void connected(SchedulingWorker*);
    void disconnected(SchedulingWorker*);
    void connectFailed(SchedulingWorker*);
    void _apply(QString ip, int port);
    void applied(int dId, QString ip, int port);
    void _write(QString content);
    void tx(SchedulingWorker*);
    void rx(SchedulingWorker*);
    void deleteTimer();
    void exWriteRobotParams(QJsonObject, DeviceLineNo);

public slots:
    void write(QString content);
    void received(QString data);
    void timerDeleteLater() { emit deleteTimer(); }

public:
    // @breif server心跳数据
    const QString keepaliveStr = "PING";
    // @brief 响应server心跳数据
    const QString keepaliveResp = "PONG";

private:
    int dId = 0;
    DeviceLineNo line = Unknow;
    QString ip;
    int port = 0;
    TcpWorker *worker = nullptr;    // auto delete after quited

    QTimer *heartcheckTimer = nullptr;
    qint64 heartcheckDate = QDateTime::currentSecsSinceEpoch();
    bool schedulingconn = false;
};

#endif // SCHEDULINGWORKER_H
