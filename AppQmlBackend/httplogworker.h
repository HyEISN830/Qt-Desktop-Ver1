#ifndef HTTPLOGWORKER_H
#define HTTPLOGWORKER_H

#include <QObject>
#include <QThread>

class HttpLogWorker : public QThread
{
    Q_OBJECT
public:
    explicit HttpLogWorker(QObject *parent = nullptr);
};

#endif // HTTPLOGWORKER_H
