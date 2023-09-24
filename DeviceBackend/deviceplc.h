#ifndef DEVICEPLC_H
#define DEVICEPLC_H

#include <QDebug>
#include <QObject>

class DevicePLC : public QObject
{
    Q_OBJECT
public:
    explicit DevicePLC(QObject *parent = nullptr);
    DevicePLC(const DevicePLC& plc) : dId(plc.dId), ip(plc.ip), port(plc.port) {}

    inline void setDId(int dId) { this->dId = dId; }
    inline void setIp(QString ip) { this->ip = ip; }
    inline void setPort(int port) { this->port = port; }

    inline int getDId() { return this->dId; }
    inline QString getIp() { return this->ip; }
    inline int getPort() { return this->port; }
    inline bool getConnected() { return this->c; }

    void connect();
    void heartcheck();

    ~DevicePLC();

signals:
    void connected(DevicePLC);
    void disconnected(DevicePLC);

private:
    int dId = 0;
    QString ip;
    int port = 0;
    bool c = false;

};

#endif // DEVICEPLC_H
