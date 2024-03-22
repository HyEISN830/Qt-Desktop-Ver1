#ifndef DEVICEPLC_H
#define DEVICEPLC_H

#include <QDebug>
#include <QObject>

#include "devicelineno.h"
#include "worker/modbustcpworker.h"


class DevicePLC : public QObject
{
    Q_OBJECT
public:
    // @brief 每次向plc通讯时, 指示本次通讯包作用
    enum PacketType
    {
        Unknow,
        PollingRegisters,
        WriteSingleRegister,
    };

    explicit DevicePLC(QObject *parent = nullptr);
    DevicePLC(int dId, QString ip, int port, DeviceLineNo line) : dId(dId), ip(ip), port(port), line(line) {}
    DevicePLC(const DevicePLC& plc) : dId(plc.dId), ip(plc.ip), port(plc.port), line(plc.line) {}
    ~DevicePLC();

    inline void setDId(int dId) { this->dId = dId; }
    inline void setIp(QString ip) { this->ip = ip; }
    inline void setPort(int port) { this->port = port; }
    inline void setLine(DeviceLineNo line) { this->line = line; }

    inline int getDId() { return this->dId; }
    inline QString getIp() { return this->ip; }
    inline int getPort() { return this->port; }
    inline DeviceLineNo getLine() { return this->line; }

    void start();
    void apply(QString ip, int port);   // call this function when modified ip or port after

signals:
    void connected(DevicePLC*);
    // @brief disconnect or connect failed
    void disconnected(DevicePLC*);
    void _writeRegister(PacketType type, int id, int addr, ushort value);
    void _readRegisters(PacketType type, int id, int startAddr, ushort length);
    // @param type type is DevicePLC::PacketType
    void received(int type, QList<ushort>, int, ushort);
    void applied(int dId, QString ip, int port);
    void tx(DevicePLC*);
    void rx(DevicePLC*);

public slots:
    void _connected() { emit connected(this); }
    void _disconnected() { emit disconnected(this); }
    void _received(PacketType type, QList<ushort> result, int addr, ushort value) { emit received(type, result, addr, value); }
    void writeRegister(PacketType type, int id, int addr, ushort value) { if (worker->getConnected()) emit _writeRegister(type, id, addr, value); }
    void readRegisters(PacketType type, int id, int startAddr, ushort length) { if (worker->getConnected()) emit _readRegisters(type, id, startAddr, length); }
    void _tx() { emit tx(this); }
    void _rx() { emit rx(this); }

private:
    int dId = 0;
    QString ip;
    int port = 0;
    DeviceLineNo line;
    ModbusTcpWorker *worker = nullptr;

};

#endif // DEVICEPLC_H
