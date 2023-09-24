#include "devicescanner.h"

DeviceScanner::DeviceScanner(QObject *parent)
    : QObject{parent}
{

}

void DeviceScanner::connect()
{
    qDebug() << "connect scanner(" << ip << ":" << port << ")";
}

void DeviceScanner::heartcheck()
{

}

DeviceScanner::~DeviceScanner()
{
    qDebug() << "scanner deleted";
}
