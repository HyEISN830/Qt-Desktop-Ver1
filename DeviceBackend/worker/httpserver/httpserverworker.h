#ifndef HTTPSERVERWORKER_H
#define HTTPSERVERWORKER_H

#include <QObject>
#include <QThread>
#include <QHttpServer>
#include <QHttpServerRequest>
#include <QHttpServerResponse>
#include <QJsonObject>
#include <QJsonArray>
#include <QDateTime>
#include <QDebug>
#include <QQueue>


class HttpServerWorker : public QThread
{
    Q_OBJECT
public:
    typedef std::function<QHttpServerResponse(const QHttpServerRequest &)> Handle;

    struct H {
        QString url;
        QHttpServerRequest::Method method;
        Handle h;
    };

    explicit HttpServerWorker(int port = 5006, QObject *parent = nullptr) : port(port), QThread{parent}
    {
    }

    static QHttpServerResponse ok(QJsonValue var, QString msg = "ok") { return QHttpServerResponse(v(var, msg, QHttpServerResponse::StatusCode::Ok)); }
    static QHttpServerResponse err(QJsonValue var, QString msg = "unknow") { return QHttpServerResponse(v(var, msg, QHttpServerResponse::StatusCode::InternalServerError)); }

    void run() override
    {
        server = new QHttpServer;
        addRouter("/", QHttpServerRequest::Method::AnyKnown, [](const QHttpServerRequest &request) { return ok("Hello there!"); });
        while (!_routes.isEmpty())
        {
            H h = _routes.dequeue();
            server->route(h.url, h.method, h.h);
        }
        server->listen(QHostAddress::Any, port);
        exec();
    }

    void addRouter(QString url, QHttpServerRequest::Method method, Handle f)
    {
        H h;
        h.h = f;
        h.url = url;
        h.method = method;
        _routes.enqueue(h);
    }

private:
    QHttpServer *server = nullptr;
    int port;
    QQueue<H> _routes;

    static QJsonObject v(QJsonValue var, QString message, QHttpServerResponse::StatusCode code)
    {
        QJsonObject o;
        o["code"] = QString::number((int)code);
        o["result"] = var;
        o["tick"] = QString::number(QDateTime::currentDateTime().toMSecsSinceEpoch());
        o["time"] = QDateTime::currentDateTime().toString();
        o["message"] = message;
        return o;
    }
};

#endif // HTTPSERVERWORKER_H
