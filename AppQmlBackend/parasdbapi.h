#ifndef PARASDBAPI_H
#define PARASDBAPI_H

#include <QQuickItem>
#include <QJsonObject>
#include <QJsonArray>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

#include "../DbEntity/parasmachine.h"
#include "../DbEntity/parasparas.h"
#include "../DbEntity/tlogs.h"

// 后台数据库api
class ParasDbApi : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT
public:
    ParasDbApi();
    ~ParasDbApi();

    // Database start -------------------------------------------
    Q_INVOKABLE bool opendb();
    Q_INVOKABLE bool dbavailable();
    void closedb();
    // Database end -------------------------------------------

    // Machines entity start -------------------------------------------
    Q_INVOKABLE QJsonArray getMachines();
    // Machines entity end -------------------------------------------

    // ParasParas entity start -------------------------------------------
    Q_INVOKABLE QJsonArray getParas();
    Q_INVOKABLE QJsonObject getPara(qlonglong);
    Q_INVOKABLE bool updPara(QJsonObject);
    Q_INVOKABLE bool createParas(QJsonObject);
    Q_INVOKABLE bool deleteParas(qlonglong);
    // ParasParas entity end -------------------------------------------

    // Tlogs entity start -------------------------------------------
    Q_INVOKABLE bool createTlogsFromAscii(QString);
    Q_INVOKABLE QJsonArray getTlogs(int, int, QString, QString, QString, QString, QString);
    Q_INVOKABLE int getTlogsCtn(QString, QString, QString, QString, QString);
    // Tlogs entity end -------------------------------------------

private:
    QSqlDatabase *psqldb = nullptr;

signals:

};

#endif // PARASDBAPI_H
