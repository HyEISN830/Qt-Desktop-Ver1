#ifndef DEVICEPLC_H
#define DEVICEPLC_H

#include <QObject>

class DevicePLC : public QObject
{
    Q_OBJECT
public:
    explicit DevicePLC(QObject *parent = nullptr);

signals:

};

#endif // DEVICEPLC_H
