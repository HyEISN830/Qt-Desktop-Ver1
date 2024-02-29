#include "hdatetime.h"

qint64 HDateTime::utc_ms = 0;

HDateTime::HDateTime(QObject *parent)
    : QObject{parent}
{}

QDateTime HDateTime::now()
{
    return QDateTime::fromMSecsSinceEpoch(utc_ms);
}
