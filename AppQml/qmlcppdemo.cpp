#include "qmlcppdemo.h"

QmlCppDemo::QmlCppDemo(QQuickItem *parent)
    : QQuickItem{parent}
{
//    qDebug() << "cpp inited by parent:" << parent;
}

void QmlCppDemo::demoprint(QString str)
{
    using namespace std;

    qDebug() << "sample demo print:" << str;
}

QString QmlCppDemo::trysendmodbus(QString host, QString port)
{
    QModbusTcpClient mdclient = QModbusTcpClient();

    mdclient.setConnectionParameter(QModbusDevice::NetworkAddressParameter, host);
    mdclient.setConnectionParameter(QModbusDevice::NetworkPortParameter, port.toInt());

    if (mdclient.connectDevice())
    {
        QModbusDataUnit data;

        data.setRegisterType(QModbusDataUnit::HoldingRegisters);
        data.setStartAddress(0);
        data.setValues({
            1, 2, 3, 4, 5, 6, 7, 8
        });

        QModbusReply *reply = mdclient.sendWriteRequest(data, 2);
        if (nullptr == reply)
        {
            return "Write Holding Register failed. Reason: " + mdclient.errorString();
        }

        return "Success";
    } else {
        return "Could not connect to host => " + host + ":" + port;
    }
}

bool QmlCppDemo::openmdclient(QString host, QString port)
{
    if (nullptr != m_mdclient)
        return false;

    m_mdclient = new QModbusTcpClient(this);
    m_mdclient->setConnectionParameter(QModbusDevice::NetworkAddressParameter, host);
    m_mdclient->setConnectionParameter(QModbusDevice::NetworkPortParameter, port.toInt());

    bool ok = m_mdclient->connectDevice();

    if (ok)
    {
        m_mdclient->connect(m_mdclient, &QModbusTcpClient::stateChanged, this, &QmlCppDemo::mdstateChanged);
        return ok;
    }

    delete m_mdclient;
    return false;
}

void QmlCppDemo::mdclientsend()
{
    if (nullptr == m_mdclient)
        return;

    QModbusDataUnit data;

    data.setRegisterType(QModbusDataUnit::HoldingRegisters);
    data.setStartAddress(0);
    data.setValues({
        1, 2, 3, 4, 5, 6, 7, 8
    });
    m_mdclient->sendWriteRequest(data, 2);
}

QModbusDevice::State QmlCppDemo::mdclientstate()
{
    if (!m_mdclient)
        return QModbusDevice::State::UnconnectedState;

    return m_mdclient->state();
}

void QmlCppDemo::mdstateChanged(QModbusDevice::State state)
{
    emit mdclientChanged(state);
}

bool QmlCppDemo::openurlwithbrowser(QString url)
{
    return QDesktopServices::openUrl(url);
}

bool QmlCppDemo::openpostgresql(QString host, QString port)
{
    if (nullptr != m_database)
        return false;

    m_database = new QSqlDatabase(QSqlDatabase::addDatabase("QPSQL"));
    m_database->setHostName(host);
    m_database->setPort(port.toInt());
    m_database->setDatabaseName("postgres");
    m_database->setUserName("postgres");
    m_database->setPassword("Lovingahri1314+");

    bool ok = m_database->open();

    if (!ok)
    {
        closedatabase();
    }

    return ok;
}

QList<QString> QmlCppDemo::querypostgresql()
{
    QList<QString> result;

    if (nullptr == m_database)
        return result;

    QSqlQuery query("select id, name, ip from machines", *m_database);
    query.executedQuery();
    while (query.next())
    {
        QString s(query.value(0).toString().append(", "));
        s.append(query.value(1).toString()).append(", ");
        s.append(query.value(2).toString());
        result.append(s);
    }

    return result;
}

bool QmlCppDemo::isdbopen()
{
    if (nullptr == m_database)
        return false;

    return m_database->isOpen();
}

void QmlCppDemo::closedatabase()
{
    if (nullptr != m_database)
    {
        m_database->close();
        QSqlDatabase::removeDatabase(m_database->connectionName());
    }
    delete m_database;
}

QmlCppDemo::~QmlCppDemo()
{
    closedatabase();
    delete m_mdclient;
}
