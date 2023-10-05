#ifndef PLCWORKER_H
#define PLCWORKER_H

#include <QObject>
#include <QTimer>
#include <QDateTime>

#include "../deviceplc.h"


class PlcWorker : public QObject
{
    Q_OBJECT
public:
    explicit PlcWorker(QObject *parent = nullptr);
    PlcWorker(DevicePLC *plc);
    ~PlcWorker();

signals:
    void writeRegister(DevicePLC::PacketType type, int id, int addr, ushort value);
    void readRegisters(DevicePLC::PacketType type, int id, int startAddr, ushort length);

public slots:
    void received(int type, QList<ushort> result);

private:
    // @brief salve id
    const int id = 1;
    // @brief register start address
    const int startAddr = 321;
    // @brief register length
    const ushort length = 12;

    DevicePLC *plc = nullptr;
    QTimer *timer = nullptr;
    ushort registers[65535];

};

#endif // PLCWORKER_H
