#ifndef ROBOTWORKER_H
#define ROBOTWORKER_H

#include <QObject>
#include <QSettings>
#include <QTimer>

#include "devicerobot.h"
#include "devicescanner.h"


class RobotWorker : public QObject
{
    Q_OBJECT
public:
    explicit RobotWorker(QObject *parent = nullptr);
    RobotWorker(DeviceRobot *robot) : robot(robot)
    {

    }
    ~RobotWorker()
    {
        if (timer)
            timer->stop();

        delete timer;
    }

    DeviceLineNo getLineNo() { return robot->getLine(); }

signals:
    void writeParams(int len, int wide, int height, int row, int col, int layer);

public slots:
    void _writeParams(DeviceScanner*, DeviceLineNo, int len, int wide, int height, int row, int col, int layer) { emit writeParams(len, wide, height, row, col, layer); }

private:
    DeviceRobot *robot = nullptr;
    QTimer *timer = nullptr;
    QSettings settings;

};

#endif // ROBOTWORKER_H
