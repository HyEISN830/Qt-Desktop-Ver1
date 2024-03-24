#ifndef CTUSERVICE_H
#define CTUSERVICE_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMutex>

#include "baseservice.h"
#include "../httpserverworker.h"


class CTUService : public BaseService
{
    Q_OBJECT
public:
    enum TaskType
    {
        Pick,   // 取料任务
        Cancel, // 取消任务
        Report  // 上报任务执行结果
    };

    struct TaskParams
    {

    };

    explicit CTUService(QObject *parent = nullptr);

    void registeRoutes(HttpServerWorker *server) override
    {
        if (!server) return;

        server->addRouter("/api/pick", QHttpServerRequest::Method::Post, [=] (const QHttpServerRequest &request) {
            QJsonObject data = QJsonDocument::fromJson(request.body()).object();
            qDebug() << data;
            return HttpServerWorker::ok("任务已接受");
        });

        server->addRouter("/api/cancel", QHttpServerRequest::Method::Post, [=] (const QHttpServerRequest &request) {
            QJsonObject data = QJsonDocument::fromJson(request.body()).object();
            qDebug() << data;
            return HttpServerWorker::ok("任务已接受");
        });
    }

    void run() override
    {
        connect(this, &CTUService::triggerExecuteTask, this, &CTUService::executeTask);
        connect(this, &CTUService::finished, this, &CTUService::deleteLater);
        exec();
    }

private slots:
    void executeTask(TaskType, TaskParams)
    {

    }

signals:
    void triggerExecuteTask(TaskType, TaskParams);
};

#endif // CTUSERVICE_H
