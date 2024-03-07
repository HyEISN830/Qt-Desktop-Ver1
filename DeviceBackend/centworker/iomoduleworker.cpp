#include "iomoduleworker.h"

IOModuleWorker::IOModuleWorker(int did, int no, QString ip, int port) : did(did), no(no), ip(ip), port(port)
{
    timer = new QTimer;
    timer->setInterval(500);
    connect(timer, &QTimer::timeout, timer, [=] {
        emit sendTCP(QByteArray("\x01\x00\x00\x00\x00\x06\x01\x02\x00\x00\x00\x04", 12));
    });
    connect(this, &IOModuleWorker::_deleteTimer, timer, &QTimer::deleteLater);
    timer->start();
}

void IOModuleWorker::_clientConnected()
{
    emit clientConnected(did);
}

void IOModuleWorker::_clientDisconnected()
{
    emit clientDisconnected(did);
}

void IOModuleWorker::start()
{
    tcp = new TcpWorker;
    connect(tcp, &TcpWorker::connected, this, &IOModuleWorker::_clientConnected);
    connect(tcp, &TcpWorker::disconnected, this, &IOModuleWorker::_clientDisconnected);
    connect(tcp, &TcpWorker::received, this, &IOModuleWorker::receiveTCP);
    connect(tcp, &TcpWorker::sendb, this, &IOModuleWorker::_sended);
    connect(this, &IOModuleWorker::sendTCP, tcp, &TcpWorker::writeb);
    tcp->setIp(ip);
    tcp->setPort(port);
    tcp->start();
}

void IOModuleWorker::apply(QString ip, int port)
{
    if (tcp)
        tcp->apply(ip, port);
}

void IOModuleWorker::receiveCMD(int dId, int no, QString cmd)
{
    if (no == this->no && cmd.size())
    {
        QStringList strs = cmd.split(",");
        QList<CMDPacket> cmds;

        if (strs.size() < 2)
        {
            emit result(NG.toLatin1());
            return;
        }

        if (strs[0] == GATE)
        {
            cmds = handleGate(strs);

            foreach (CMDPacket c, cmds)
            {
                if (c.type == CMDPacket::NONE)
                {
                    emit sendTCP(c.cmd);
                    QThread::msleep(60);
                }
                else if (c.type == CMDPacket::FEW)
                {
                    emit sendTCP(c.cmd);
                    QThread::msleep(c.fewdelay);

                    if (c.fewcmd.size())
                        emit sendTCP(c.fewcmd);
                }
            }
        }
    }
}

QList<CMDPacket> IOModuleWorker::handleGate(QStringList cmd)
{
    QList<CMDPacket> cmds;

    if (cmd[2] == GOPEN)
    {
        if (cmd.size() >= 3 && cmd[3] == GQUERY)
        {
            emit result((io[0] ? OK : NG).toLatin1());
        }
        else
        {
            cmds.append(QByteArray("\x02\x00\x00\x00\x00\x06\x01\x05\x00\x00\xFF\x00", 12));
            cmds.append(QByteArray("\x02\x00\x00\x00\x00\x06\x01\x05\x00\x01\x00\x00", 12));
        }
    }
    else if (cmd[2] == GCLOSE)
    {
        if (cmd.size() >= 3 && cmd[3] == GQUERY)
        {
            emit result((io[1] ? OK : NG).toLatin1());
        }
        else
        {
            cmds.append(QByteArray("\x02\x00\x00\x00\x00\x06\x01\x05\x00\x00\x00\x00", 12));
            cmds.append(CMDPacket(QByteArray("\x02\x00\x00\x00\x00\x06\x01\x05\x00\x01\xFF\x00", 12), 20, QByteArray("\x02\x00\x00\x00\x00\x06\x01\x05\x00\x01\x00\x00", 12), 1500, CMDPacket::FEW));
        }
    }

    return cmds;
}

void IOModuleWorker::receiveTCP(QByteArray data)
{
    if (data.size())
        emit received(data);
    // qDebug() << data;
    // emit received(data);

    if (data.size() && data[0] == 0x01)
    {
        // QList<bool> bits;
        io = std::bitset<8>(data[data.size() - 1]);
        // for (int var = 0; var < io.size(); ++var)
        //     bits.append(io[var]);
        // qDebug() << bits;
    }
    else if (data.size() && data[0] == 0x02)
        if (QDateTime::currentMSecsSinceEpoch() - executelog > 100)
        {
            executelog = QDateTime::currentMSecsSinceEpoch();
            emit result(OK.toLatin1());
        }
}

void IOModuleWorker::_sended(QTcpSocket *tcp, QByteArray data)
{
    emit sended(did, data);
}

IOModuleWorker::~IOModuleWorker()
{
    if (tcp)
    {
        tcp->quit();
        tcp->wait();
    }

    emit _deleteTimer();
    delete tcp;
}
