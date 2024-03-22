#ifndef MODBUSTCPWORKER_H
#define MODBUSTCPWORKER_H

#include <QThread>
#include <QObject>
#include <QModbusTcpClient>
#include <QVariant>
#include <QTimer>
#include <QModbusDataUnit>

#include "modbustcpworkersender.h"


class ModbusTcpWorker : public QThread
{
    Q_OBJECT
public:
    explicit ModbusTcpWorker(QObject *parent = nullptr);
    ModbusTcpWorker(QString ip, int port) : ip(ip), port(port) {}

    void run() override
    {
        modbus = new QModbusTcpClient;
        modbus->setTimeout(1000);
        modbus->moveToThread(this);
        connect(modbus, &QModbusTcpClient::stateChanged, this, &ModbusTcpWorker::mdStateChanged);
        connect(this, &ModbusTcpWorker::finished, modbus, &QModbusTcpClient::deleteLater);

        aliveTimer = new QTimer;
        aliveTimer->setInterval(5000);
        aliveTimer->moveToThread(this);
        aliveTimer->start();
        connect(aliveTimer, &QTimer::timeout, aliveTimer, [=] {    // modbus tcp alive checking
            if (!conn && !connecting)
            {
                connecting = true;
                modbus->setConnectionParameter(QModbusDevice::NetworkAddressParameter, ip);
                modbus->setConnectionParameter(QModbusDevice::NetworkPortParameter, port);
                modbus->connectDevice();
                connecting = false;
            }
            else if (a)
            {
                // use new connect parameters to reconnect
                a = false;
                modbus->disconnectDevice();
            }
        });
        connect(this, &ModbusTcpWorker::finished, aliveTimer, &QTimer::stop);
        connect(this, &ModbusTcpWorker::finished, aliveTimer, &QTimer::deleteLater);

        sender = new ModbusTcpWorkerSender;
        sender->moveToThread(this);
        connect(this, &ModbusTcpWorker::_writeRegister, sender, &ModbusTcpWorkerSender::writeRegister);
        connect(this, &ModbusTcpWorker::_readRegisters, sender, &ModbusTcpWorkerSender::readRegisters);
        connect(sender, &ModbusTcpWorkerSender::finished, this, &ModbusTcpWorker::modbusFinished);
        connect(this, &ModbusTcpWorker::finished, sender, &ModbusTcpWorkerSender::deleteLater);

        connect(this, &ModbusTcpWorker::finished, this, &ModbusTcpWorker::deleteLater);
        exec();
    }

    inline bool getConnected() { return this->conn; }
    inline bool getConnecting() { return this->connecting; }

signals:
    void _writeRegister(QModbusTcpClient *modbus, int type, int id, int addr, ushort value);
    void _readRegisters(QModbusTcpClient *modbus, int type, int id, int startAddr, ushort length);
    void connected();
    void disconnected();
    // @brief type - customer action code
    void received(int type, QList<ushort>, int, ushort);
    void rxtxFailed();
    void tx();
    void rx();

public slots:
    void mdStateChanged(QModbusTcpClient::State state)
    {
        if (state == QModbusDevice::ConnectedState)
        {
            conn = true;
            emit connected();
        }
        else if (state == QModbusDevice::UnconnectedState)
        {
            conn = false;
            emit disconnected();
        }
    }

    void writeRegister(int type, int id, int addr, ushort value)
    {
        emit tx();
        emit _writeRegister(modbus, type, id, addr, value);
    }

    void readRegisters(int type, int id, int startAddr, ushort length)
    {
        emit tx();
        emit _readRegisters(modbus, type, id, startAddr, length);
    }

    void modbusFinished(int type, QModbusReply *reply, int addr, ushort value)
    {
        if (nullptr == reply)
        {
            emit rxtxFailed();
        }
        else
        {
            QList<ushort> result =  reply->result().values();
            emit rx();
            emit received(type, result.size() > 0 ? result : QList<ushort>(), addr, value);
            reply->deleteLater();
        }
    }

    // @brief use new connect parameters to reconnect
    void apply(QString ip, int port)
    {
        this->ip = ip;
        this->port = port;
        this->a = true;
    }

private:
    QString ip;
    int port;
    QModbusTcpClient *modbus = nullptr;
    QTimer *aliveTimer = nullptr;   // modbus tcp alive checking
    QTimer *pollTimer = nullptr;   // modbus tcp register polling

    bool a = false;
    bool conn = false;
    bool connecting = false;
    ModbusTcpWorkerSender *sender = nullptr;
};

#endif // MODBUSTCPWORKER_H
