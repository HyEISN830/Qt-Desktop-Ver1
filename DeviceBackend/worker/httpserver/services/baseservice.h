#ifndef BASESERVICE_H
#define BASESERVICE_H

#include <QObject>

#include "../httpserverworker.h"


class BaseService : public QThread
{
    Q_OBJECT
public:
    explicit BaseService(QObject *parent = nullptr);

    virtual void registeRoutes(HttpServerWorker *worker) = 0;

signals:
};

#endif // BASESERVICE_H
