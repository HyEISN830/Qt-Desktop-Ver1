#ifndef ROBOTWORKER_H
#define ROBOTWORKER_H

#include <QObject>
#include <QSettings>
#include <QTimer>
#include <QJsonObject>

#include "devicerobot.h"
#include "devicescanner.h"


class RobotWorker : public QObject
{
    Q_OBJECT
public:
    explicit RobotWorker(QObject *parent = nullptr);
    RobotWorker(DeviceRobot *robot) : robot(robot)
    {
        heartcheckTimer = new QTimer;
        heartcheckTimer->setInterval(3000);
        connect(heartcheckTimer, &QTimer::timeout, this, [=]{
            qDebug() << robotconn << QDateTime::currentSecsSinceEpoch() << heartcheckDate;
            if (robotconn && ((QDateTime::currentSecsSinceEpoch() - heartcheckDate) >= 15))
            {
                heartcheckDate = QDateTime::currentSecsSinceEpoch();
                emit robotHeartStopped(robot);
            }
        });
        connect(this, &RobotWorker::deleteTimer, heartcheckTimer, &QTimer::deleteLater);
        heartcheckTimer->start();
    }
    ~RobotWorker()
    {

    }

    DeviceLineNo getLineNo() { return robot->getLine(); }

signals:
    void writeParams(QJsonObject);
    // @brief 在接收到机器人请求参数字符串后, 发送此signal, 应当由ScannerWorker接收
    void requestStartUpParams(DeviceLineNo);
    void robotHeartStopped(DeviceRobot*);
    void deleteTimer();

public slots:
    void _writeParams(DeviceScanner*, DeviceLineNo, QJsonObject jobj) { emit writeParams(jobj); }
    void robotReceived(DeviceRobot*, QString content)
    {
        if (content.contains(robot->kawasakiReq) || content.contains(robot->fanucReq)) emit requestStartUpParams(robot->getLine());
        heartcheckDate = QDateTime::currentDateTime().currentSecsSinceEpoch();
    }
    void robotConnected(DeviceRobot*)
    {
        robotconn = true;
        heartcheckDate = QDateTime::currentDateTime().currentSecsSinceEpoch();
    }
    void robotDisconnected(DeviceRobot*) { robotconn = false; }
    void timerDeleteLater() { emit deleteTimer(); }

private:
    DeviceRobot *robot = nullptr;
    QTimer *heartcheckTimer = nullptr;
    QSettings settings;

    qint64 heartcheckDate = QDateTime::currentSecsSinceEpoch();
    bool robotconn = false;

};

#endif // ROBOTWORKER_H
