#ifndef HTTPADDLOGWORKER_H
#define HTTPADDLOGWORKER_H

#include <QObject>
#include <QThread>
#include <QNetworkAccessManager>
#include <QQueue>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QMutex>

#include "./struct/logstruct.h"


class HttpAddLogWorker : public QThread
{
    Q_OBJECT
public:
    explicit HttpAddLogWorker(QObject *parent = nullptr);
    ~HttpAddLogWorker()
    {

    }

    void run() override
    {
        network = new QNetworkAccessManager;
        connect(this, &HttpAddLogWorker::finished, network, &QNetworkAccessManager::deleteLater);

        connect(network, &QNetworkAccessManager::finished, network, [=] (QNetworkReply *reply) {
            quering = false;

            if (!logs.isEmpty())
                emit triggerPush();

            if (reply)
                reply->deleteLater();
        });
        connect(this, &HttpAddLogWorker::triggerPush, network, [=] {
            mutex.lock();
            if (network && !quering && !logs.isEmpty())
            {
                quering = true;
                LogStruct *s = logs.dequeue();
                QUrl url = s->url;

                if (url.toString().length())
                {
                    QUrlQuery query;

                    query.addQueryItem("content", s->content);
                    query.addQueryItem("level", QString::number(s->level));
                    url.setQuery(query);

                    network->get(QNetworkRequest(url));
                }

                delete s;
            }
            mutex.unlock();
        });

        connect(this, &HttpAddLogWorker::finished, this, &HttpAddLogWorker::deleteLater);
        exec();
    }

signals:
    void triggerPush();

public slots:
    void appendLog(QString url, QString content, int level)
    {
        logs.enqueue(new LogStruct(url, content, level));
        emit triggerPush();
    }

private:
    bool quering = false;
    QMutex mutex;

    QNetworkAccessManager *network = nullptr;
    QQueue<LogStruct*> logs;
};

#endif // HTTPADDLOGWORKER_H
