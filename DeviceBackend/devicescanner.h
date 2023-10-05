#ifndef DEVICESCANNER_H
#define DEVICESCANNER_H

#include <QDebug>
#include <QObject>
#include <QTcpSocket>
#include <QTime>
#include <QThread>
#include <QRunnable>

#include "devicelineno.h"
#include "worker/tcpworker.h"

class DeviceScanner : public QObject
{
    Q_OBJECT
public:
    explicit DeviceScanner(QObject *parent = nullptr);
    DeviceScanner(int dId, QString ip, int port, DeviceLineNo lineNo) : dId(dId), ip(ip), port(port), line(lineNo) {}
    DeviceScanner(const DeviceScanner &scanner) : dId(scanner.dId), ip(scanner.ip), port(scanner.port), line(scanner.line) {}
    ~DeviceScanner();

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

signals:
    void connected(DeviceScanner*);
    void disconnected(DeviceScanner*);
    void connectFailed(DeviceScanner*);
    void barcodeReceived(DeviceScanner*, QString barcode);
    void _apply(QString ip, int port);
    void applied(int dId, QString ip, int port);

private:
    int dId = 0;
    DeviceLineNo line = Unknow;
    QString ip;
    int port = 0;
    TcpWorker *worker = nullptr;    // auto delete after quited
};

#endif // DEVICESCANNER_H
