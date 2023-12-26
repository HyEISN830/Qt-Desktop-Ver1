#ifndef MODBUSTCPWORKERSENDER_H
#define MODBUSTCPWORKERSENDER_H

#include <QObject>
#include <QModbusTcpClient>
#include <QModbusReply>


class ModbusTcpWorkerSender : public QObject
{
    Q_OBJECT
public:
    explicit ModbusTcpWorkerSender(QObject *parent = nullptr);

signals:
    void finished(int type, QModbusReply *reply);

public slots:
    void writeRegister(QModbusTcpClient *modbus, int type, int id, int addr, ushort value)
    {
        QModbusDataUnit readedData;

        readedData.setRegisterType(QModbusDataUnit::HoldingRegisters);
        readedData.setStartAddress(addr);
        readedData.setValues({ value });

        QModbusReply *reply = modbus->sendWriteRequest(readedData, id);

        if (nullptr == reply)
        {
            emit finished(type, nullptr);
        }
        else
        {
            reply->connect(reply, &QModbusReply::finished, this, [=] {
                emit finished(type, reply);
            });
        }
    }

    void readRegisters(QModbusTcpClient *modbus, int type, int id, int startAddr, ushort length)
    {
        QModbusDataUnit data;

        data.setRegisterType(QModbusDataUnit::HoldingRegisters);
        data.setStartAddress(startAddr);
        data.setValueCount(length);

        QModbusReply *reply = modbus->sendReadRequest(data, id);

        if (nullptr == reply)
        {
            emit finished(type, nullptr);
        }
        else
        {
            reply->connect(reply, &QModbusReply::finished, this, [=] {
                emit finished(type, reply);
            });
        }
    }
};

#endif // MODBUSTCPWORKERSENDER_H
