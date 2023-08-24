#ifndef QMLCPPDEMO_H
#define QMLCPPDEMO_H

#include <QObject>
#include <QQmlEngine>
#include <QtQuick>
#include <QModbusTcpClient>
#include <QModbusDataUnit>
#include <QDesktopServices>
#include <QSqlDatabase>
#include <QSqlQuery>

class QmlCppDemo : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit QmlCppDemo(QQuickItem *parent = nullptr);
    ~QmlCppDemo();

    Q_INVOKABLE void demoprint(QString);
    Q_INVOKABLE QString trysendmodbus(QString, QString);
    Q_INVOKABLE bool openmdclient(QString, QString);
    Q_INVOKABLE void mdclientsend();
    Q_INVOKABLE QModbusDevice::State mdclientstate();
    Q_INVOKABLE bool openurlwithbrowser(QString);
    Q_INVOKABLE bool openpostgresql(QString, QString);
    Q_INVOKABLE QList<QString> querypostgresql();
    Q_INVOKABLE bool isdbopen();

private:
    QModbusTcpClient *m_mdclient = nullptr;
    QSqlDatabase *m_database = nullptr;

    void closedatabase();

public slots:
    void mdstateChanged(QModbusDevice::State);

signals:
    void mdclientChanged(QModbusDevice::State);
};

#endif // QMLCPPDEMO_H
