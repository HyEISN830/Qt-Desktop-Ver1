#ifndef DEVICESCANNER_H
#define DEVICESCANNER_H

#include <QDebug>
#include <QObject>
#include <QRunnable>
#include <QTcpSocket>

#include "devicelineno.h"

class DeviceScanner : public QObject
{
    Q_OBJECT
public:
    class ConnectTask : QRunnable
    {
    public:
        ConnectTask(DeviceScanner *scanner) : scanner(scanner) {}

        void run() override
        {
            QTcpSocket *tcp = nullptr;
            bool ok = false;

            if (!scanner->tcp)
            {
                tcp = new QTcpSocket;
                scanner->tcp = tcp;
            }
            else
            {
                tcp = scanner->tcp;
            }

            // TODO: 连接到扫码枪通过TCP; 准备测试
            tcp->connectToHost(scanner->ip, scanner->port);
            ok = tcp->waitForConnected(3000);
            if (ok)
                emit scanner->connected(*scanner);
            else
                emit scanner->connectFailed(*scanner);
        }

    private:
        DeviceScanner *scanner = nullptr;
    };

    explicit DeviceScanner(QObject *parent = nullptr);
    DeviceScanner(int dId, QString ip, int port, DeviceLineNo lineNo) : dId(dId), ip(ip), port(port), line(lineNo) {}
    DeviceScanner(const DeviceScanner& scanner) : dId(scanner.dId), ip(scanner.ip), port(scanner.port), line(scanner.line) {}

    inline void setDId(int dId) { this->dId = dId; }
    inline void setIp(QString ip) { this->ip = ip; }
    inline void setPort(int port) { this->port = port; }
    inline void setLine(DeviceLineNo lineNo) { this->line = lineNo; }

    inline int getDId() { return this->dId; }
    inline QString getIp() { return this->ip; }
    inline int getPort() { return this->port; }
    inline DeviceLineNo getLine() { return this->line; }
    inline bool getConnected() { return this->c; }

    void connect();
    void heartcheck();

    ~DeviceScanner();

signals:
    void connected(DeviceScanner);
    void disconnected(DeviceScanner);
    void connectFailed(DeviceScanner);
    void barcodeReceived(DeviceScanner, QString barcode);

private:
    QTcpSocket *tcp = nullptr;
    int dId = 0;
    DeviceLineNo line = Unknow;
    QString ip;
    int port = 0;
    bool c = false;

};

#endif // DEVICESCANNER_H
