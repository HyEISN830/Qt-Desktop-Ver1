#ifndef PLCWORKER_H
#define PLCWORKER_H

#include <QObject>
#include <QTimer>
#include <QDateTime>
#include <QSettings>

#include "../deviceplc.h"
#include "../devicescanner.h"


class PlcWorker : public QObject
{
    Q_OBJECT
public:
    PlcWorker(DevicePLC *plc, QList<int> allowLines);
    ~PlcWorker();

    DeviceLineNo getLineNo() { return plc->getLine(); }
    bool allowLine(DeviceLineNo line) { return allowLines.contains(DeviceLineNo::All) || allowLines.contains(line); }

signals:
    void writeRegister(DevicePLC::PacketType type, int id, int addr, ushort value);
    void readRegisters(DevicePLC::PacketType type, int id, int startAddr, ushort length);
    void writed(DevicePLC*, int addr, ushort value);
    void pullUp(DevicePLC*, DeviceLineNo);
    void commitReq(DevicePLC*, DeviceLineNo);

public slots:
    void received(int type, QList<ushort> result);
    // @brief scan barcode finished
    void scaned(DeviceLineNo line, bool ok);
    void gotoChange(DeviceScanner *scanner, DeviceLineNo line, QString orderNo, int len, int wide, int height);
    // @breif 处理某线体机器人已码好
    void processPullUp();
    // @brief plc 申请出板处理
    void processCommit();
    // @brief wms 同意指定线体出板
    void approveOut(DeviceScanner*, DeviceLineNo);
    // @brief 拒绝指定线体出板
    void rejectOut(DeviceScanner*, DeviceLineNo);

private:
    QSettings settings;
    // @brief salve id
    const int id = 1;
    // @brief register start address
    const int startAddr = 330;
    // @brief register length
    const ushort length = 50;
    // @brief 扫码成功寄存器写入值
    const ushort _scanOK = 1;
    // @brief 扫码失败寄存器写入值
    const ushort _scanNG = 2;
    // @brief 当机器人IO转PLC寄存器中为该值则说明机器人已动作完成
    const ushort _pullUpR = 1;
    // @brief 当机器人IO转PLC寄存器中为完成值后, 读取完则将指定寄存器复位为该值
    const ushort _pullUpT = 0;
    // @breif 当换产后, 将PLC寄存器中写为该值后, 表示换产
    const ushort _changeT = 1;
    // @brief 当PLC请求出板寄存器为该值时, 则PLC请求出板
    const ushort _commitReq = 1;
    // @brief 读取到申请出料时, 写入该值, 防止重复读取
    const ushort _commitReaded = 5;
    // @brief 当PLC请求出板后, 如码垛提交成功, 则写入该值后, PLC动作出板
    const ushort _commitOK = 2;
    // @brief 当PLC请求出板后, 如码垛提交失败, 则写入该值后, PLC无出板动作
    const ushort _commitNG = 3;
    int len = 0;
    int wide = 0;
    int height = 0;

    DevicePLC *plc = nullptr;
    QTimer *pollingTimer = nullptr;
    ushort registers[65535];
    QList<DeviceLineNo> lines =
    {
        DeviceLineNo::W1,
        DeviceLineNo::W2,
        DeviceLineNo::W3,
        DeviceLineNo::N3,
        DeviceLineNo::N2,
        DeviceLineNo::N1,
    };
    QMap<DeviceLineNo, ushort> scanPlcRegisters {   // 对应线体扫码完成寄存器; 可写-1:OK|2:NG
        { DeviceLineNo::W1, 330 },
        { DeviceLineNo::W2, 332 },
        { DeviceLineNo::W3, 334 },
        { DeviceLineNo::N3, 340 },
        { DeviceLineNo::N2, 338 },
        { DeviceLineNo::N1, 336 },
    };
    QMap<DeviceLineNo, ushort> changePlcRegisters {   // 对应线体换产通知寄存器; 可写-1:换产
        { DeviceLineNo::W1, 360 },
        { DeviceLineNo::W2, 362 },
        { DeviceLineNo::W3, 364 },
        { DeviceLineNo::N3, 358 },
        { DeviceLineNo::N2, 356 },
        { DeviceLineNo::N1, 354 },
    };
    QMap<DeviceLineNo, ushort> pullPlcRegisters {   // 对应线体, 机器人已将单个物料码好; 可读-1:已码好; 可写-复位0
        { DeviceLineNo::W1, 372 },
        { DeviceLineNo::W2, 374 },
        { DeviceLineNo::W3, 376 },
        { DeviceLineNo::N3, 370 },
        { DeviceLineNo::N2, 368 },
        { DeviceLineNo::N1, 366 },
    };
    QMap<DeviceLineNo, ushort> commitPlcRegisters {   // 对应线体, PLC出板; 可读-1: PLC请求出板; 可写-2:允许出板|3:不予出板
        { DeviceLineNo::W1, 348 },
        { DeviceLineNo::W2, 350 },
        { DeviceLineNo::W3, 352 },
        { DeviceLineNo::N3, 346 },
        { DeviceLineNo::N2, 344 },
        { DeviceLineNo::N1, 342 },
    };
    QMap<DeviceLineNo, ushort> widePlcRegisters {   // 对应线体 PLC产品宽度, 378地址为无用地址
        { DeviceLineNo::W1, 500 },
        { DeviceLineNo::W2, 502 },
        { DeviceLineNo::W3, 504 },
//        { DeviceLineNo::N3, 378 },
//        { DeviceLineNo::N2, 378 },
//        { DeviceLineNo::N1, 378 },
    };
    QList<DeviceLineNo> allowLines;

};

#endif // PLCWORKER_H
