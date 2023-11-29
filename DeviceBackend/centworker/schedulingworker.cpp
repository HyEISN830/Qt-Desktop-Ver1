#include "schedulingworker.h"

SchedulingWorker::SchedulingWorker(QObject *parent)
    : QObject{parent}
{
}

SchedulingWorker::SchedulingWorker(int dId, QString ip, int port, DeviceLineNo line) : dId(dId), ip(ip), port(port), line(line)
{
    heartcheckTimer = new QTimer;
    heartcheckTimer->setInterval(3000);
    connect(heartcheckTimer, &QTimer::timeout, this, [=]{
        if (schedulingconn && ((QDateTime::currentSecsSinceEpoch() - heartcheckDate) >= 15))
        {
            heartcheckDate = QDateTime::currentSecsSinceEpoch();
            apply(this->getIp(), this->getPort());
        }
    });
    connect(this, &SchedulingWorker::deleteTimer, heartcheckTimer, &QTimer::deleteLater);
    heartcheckTimer->start();
}

void SchedulingWorker::start()
{
    if (!worker)
    {
        worker = new TcpWorker(ip, port);
        connect(worker, &TcpWorker::connected, this, [=] { emit connected(this); });
        connect(worker, &TcpWorker::disconnected, this, [=] { emit disconnected(this); });
        connect(worker, &TcpWorker::connectFailed, this, [=] { emit connectFailed(this); });
        connect(worker, &TcpWorker::received, this, &SchedulingWorker::received);
        connect(this, &SchedulingWorker::_write, worker, &TcpWorker::write);
        worker->start();
    }
}

void SchedulingWorker::apply(QString ip, int port)
{
    if (worker)
    {
        this->ip = ip;
        this->port = port;
        worker->apply(ip, port);
        emit applied(dId, ip, port);
    }
}

void SchedulingWorker::write(QString content)
{
    emit tx(this);
    emit _write(content);
}

void SchedulingWorker::received(QString data)
{
    emit rx(this);
    heartcheckDate = QDateTime::currentSecsSinceEpoch();

    if (!data.trimmed().size()) return;

    if (data.trimmed() == keepaliveStr)
    {
        write(keepaliveResp);
        return;
    }

    QJsonDocument result = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject message = result.object();

    if (message["taskId"].toInteger() <= 0) return;

    QJsonObject jmsg = message["message"].toObject();
    switch((TaskType)message["type"].toInt())
    {
        case SendStartUpParams:
            emit exWriteRobotParams(jmsg, (DeviceLineNo)message["paramLine"].toInt());
            write(taskResult(message["taskId"].toInteger(), true, "任务执行完毕! (" + QString::number(jmsg["len"].toInt()) + "L*" + QString::number(jmsg["wide"].toInt()) + "W*" + QString::number(jmsg["height"].toInt()) + "H" + ")"));
            break;

        case SendManualParams:
            emit exWriteRobotParams(jmsg, (DeviceLineNo)message["paramLine"].toInt());
            write(taskResult(message["taskId"].toInteger(), true, "任务执行完毕! (" + QString::number(jmsg["len"].toInt()) + "L*" + QString::number(jmsg["wide"].toInt()) + "W*" + QString::number(jmsg["height"].toInt()) + "H" + ")"));
            break;

        default:
            write(taskResult(message["taskId"].toInteger(), false, "指定的任务不存在!"));
            break;
    }
}

QString SchedulingWorker::taskResult(qint64 taskId, bool success, QString message)
{
    QJsonDocument jdoc;
    QJsonObject result;

    result["TaskId"] = taskId;
    result["ExecuteStatus"] = success;
    result["TaskReason"] = message;
    jdoc.setObject(result);

    return jdoc.toJson();
}

bool SchedulingWorker::getConnected()
{
    return worker && worker->getConnected();
}

SchedulingWorker::~SchedulingWorker()
{
    if (worker)
    {
        worker->quit();
        worker->wait();
    }

    delete worker;
}
