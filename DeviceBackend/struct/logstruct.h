#ifndef LOGSTRUCT_H
#define LOGSTRUCT_H

#include <QObject>

class LogStruct : public QObject
{
    Q_OBJECT
public:
    explicit LogStruct(QObject *parent = nullptr);
    LogStruct(QString url, QString content, int level) : url(url), content(content), level(level), valid(new QObject), inc(123) {}
    ~LogStruct() { delete valid; }

    QString url = "";
    QString content = "";
    int level;
    QObject *valid = nullptr;
    int inc;

signals:
};

#endif // LOGSTRUCT_H
