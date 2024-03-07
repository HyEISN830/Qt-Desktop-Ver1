#ifndef CMDPACKET_H
#define CMDPACKET_H

#include <QObject>

class CMDPacket : public QObject
{
    Q_OBJECT
public:
    enum HoldingType
    {
        NONE,
        FEW
    };

    explicit CMDPacket(QObject *parent = nullptr) : QObject{parent} {}
    CMDPacket(QByteArray cmd, int delay = 20, QByteArray fewcmd = QByteArray(), int fewdelay = 20, HoldingType type = HoldingType::NONE) : cmd(cmd), delay(delay), fewcmd(fewcmd), fewdelay(fewdelay), type(type) {}
    CMDPacket(const CMDPacket& p)
    {
        *this = p;
    }

    CMDPacket& operator=(const CMDPacket& p)
    {
        this->type = p.type;
        this->delay = p.delay;
        this->cmd = p.cmd;
        this->fewcmd = p.fewcmd;
        this->fewdelay = p.fewdelay;
        return *this;
    }
signals:

public:
    HoldingType type;   // @breif
    int delay;  // @brief
    QByteArray cmd; // @breif
    int fewdelay;   // @breif
    QByteArray fewcmd; // @breif executed after <delay>
};

#endif // CMDPACKET_H
