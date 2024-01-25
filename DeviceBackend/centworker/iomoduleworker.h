#ifndef IOMODULEWORKER_H
#define IOMODULEWORKER_H

#include <QObject>

class IOModuleWorker : public QObject
{
    Q_OBJECT
public:
    explicit IOModuleWorker(QObject *parent = nullptr);

signals:
};

#endif // IOMODULEWORKER_H
