#ifndef HDATETIME_H
#define HDATETIME_H

#include <QObject>
#include <QDateTime>


// @brief 程序内置时间, 从 1970-01-01开始跳动
// @brief 时间跳动在 DeviceCenter 中开始累加, 每 1ms 为 utc_ms 递增1
class HDateTime : public QObject
{
    Q_OBJECT
public:
    explicit HDateTime(QObject *parent = nullptr);

    static qint64 utc_ms;

    static QDateTime now();

signals:
};

#endif // HDATETIME_H
