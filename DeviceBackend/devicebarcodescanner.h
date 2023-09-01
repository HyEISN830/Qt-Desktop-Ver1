#ifndef DEVICEBARCODESCANNER_H
#define DEVICEBARCODESCANNER_H

#include <QObject>

class DeviceBarcodeScanner : public QObject
{
    Q_OBJECT
public:
    explicit DeviceBarcodeScanner(QObject *parent = nullptr);

signals:

};

#endif // DEVICEBARCODESCANNER_H
