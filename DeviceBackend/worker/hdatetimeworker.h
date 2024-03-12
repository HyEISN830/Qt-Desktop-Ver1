#ifndef HDATETIMEWORKER_H
#define HDATETIMEWORKER_H

#include <QObject>
#include <QThread>
#include <QTimer>

#include "../struct/hdatetime.h"


class HDateTimeWorker : public QThread
{
    Q_OBJECT
public:
    explicit HDateTimeWorker(QObject *parent = nullptr);
    ~HDateTimeWorker();

    void run() override
    {
        // 设置时间戳自增循环线程与定时器
        utcTimer = new QTimer;
        utcTimer->setInterval(1);
        utcTimer->moveToThread(this);
        connect(utcTimer, &QTimer::timeout, utcTimer, [=] { HDateTime::utc_ms++; });
        connect(this, &QThread::started, this, [=] { utcTimer->start(); });
        connect(this, &QThread::finished, utcTimer, &QTimer::stop);
        connect(this, &QThread::finished, utcTimer, &QTimer::deleteLater);
        connect(this, &QThread::finished, this, &QThread::deleteLater);
        utcTimer->start();

        exec();
    }

private:
    QTimer *utcTimer = nullptr;

signals:
};

#endif // HDATETIMEWORKER_H
