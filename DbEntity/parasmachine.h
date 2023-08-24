#ifndef PARASMACHINE_H
#define PARASMACHINE_H

#include <QObject>
#include <QQuickItem>
#include <QSqlRecord>
#include <QJsonObject>
#include <QJsonDocument>
#include <QModbusClient>
#include <QModbusTcpClient>
#include <QRunnable>
#include <QThreadPool>
#include <QThread>
#include <QTimer>

#include "parasparas.h"

class ParasMachine : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT

public:
    ParasMachine() {}
    ParasMachine(const ParasMachine &obj) : ParasMachine(obj.id, obj.name, obj.ip, obj.port) {}
    ParasMachine(int id, QString name, QString ip, QString port)
    {
        this->id = id;
        this->name = name;
        this->ip = ip;
        this->port = port;
    }
    ~ParasMachine()
    {
        inDestroy = true;

        delete historylooper;
        delete m_mdclient;
    }

public:
    static const int sid = 2;   // modbus station id

    Q_PROPERTY(int id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString ip READ getIp WRITE setIp NOTIFY ipChanged)
    Q_PROPERTY(QString port READ getPort WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(bool connected READ getConnected WRITE setConnected NOTIFY connectedChanged)
    Q_PROPERTY(bool selected READ getSelected WRITE setSelected NOTIFY selectedChanged)

    Q_INVOKABLE inline int getId() { return this->id; }
    Q_INVOKABLE inline QString getName() { return this->name; }
    Q_INVOKABLE inline QString getIp() { return this->ip; }
    Q_INVOKABLE inline QString getPort() { return this->port; }
    Q_INVOKABLE inline bool getConnected() { return this->connected; }
    Q_INVOKABLE inline bool getSelected() { return this->selected; }

    Q_INVOKABLE inline void setId(int id) { this->id = id; emit idChanged(id);}
    Q_INVOKABLE inline void setName(QString name) { this->name = name; emit nameChanged(name); }
    Q_INVOKABLE inline void setIp(QString ip) { this->ip = ip; emit ipChanged(ip); }
    Q_INVOKABLE inline void setPort(QString port) { this->port = port; emit portChanged(port); }
    Q_INVOKABLE inline void setConnected(bool c) { this->connected = c; emit connectedChanged(c); }
    Q_INVOKABLE inline void setSelected(bool s) { this->selected = s; emit selectedChanged(s); }

    Q_INVOKABLE void openmdbus();
    Q_INVOKABLE QModbusDevice::State mdbusstate();
    Q_INVOKABLE void startheartb();
    Q_INVOKABLE void heartbeat();
    Q_INVOKABLE void stopheartb();  // 进行其他数据操作时, 应当关闭心跳, 防止读脏
    Q_INVOKABLE void upload(QJsonObject);
    void protectEvent();  // 数据区段1上载处理, 在每次数据上传后调用
    void testEvent(); // 数据区段2上载处理, 在每次数据上传后调用
    void checkhistory();    //  检查是否有历史数据可读
    void starthistory();    // 开始历史记录采集
    void stophistory();     // 停止历史记录采集, 历史记录提取出现任何异常时, 请先调用此函数, 防止线程不终止或其他错误

    inline QModbusTcpClient *client() { return this->m_mdclient; }
    inline bool destroyed() { return this->inDestroy; }
    inline bool inhistory() { return this->inHistory; }
    inline bool wrecording() { return this->w_recording; }

    ParasMachine &operator =(const ParasMachine &right)
    {
        this->id = right.id;
        this->name = right.name;
        this->ip = right.ip;
        this->port = right.port;
        this->connected = right.connected;
        this->selected = right.selected;
        return *this;
    }

    Q_INVOKABLE inline QJsonObject toJson()
    {
        QJsonObject jobj;
        jobj["id"] = getId();
        jobj["name"] = getName();
        jobj["ip"] = getIp();
        jobj["port"] = getPort();
        jobj["connected"] = getConnected();
        jobj["selected"] = getSelected();
        return jobj;
    }

    static ParasMachine fromRecord(QSqlRecord record)
    {
        const static QMetaObject* metaObj = ParasMachine().metaObject();
        const static int propctn = metaObj->propertyCount();
        static QList<QString> fields;

        if (fields.size() == 0)
            for (int var = 0; var < propctn; var++)
                fields.append(metaObj->property(var).name());

        ParasMachine object;

        for (int var = 0; var < fields.size(); var++)
        {
            int rcol = record.indexOf(fields.at(var));
            if (rcol == -1) continue;
            object.setProperty(fields.at(var).toStdString().c_str(), record.value(rcol));
        }

        return ParasMachine(object);
    }

public slots:
    void mdstateChanged(QModbusDevice::State);
    void takerecord();  // 在 MachHistoryWorker 不断延迟循环中进行历史记录采集

private:
    int id;
    QString name;
    QString ip;
    QString port;
    bool connected = false;
    bool selected = false;

    QModbusTcpClient *m_mdclient = nullptr;
    bool hearting = true;
    int protectdata = 0;    // 保护参数区段上传
    int testdata = 0;       // 测试参数区段上传
    bool inDestroy = false; // 正在销毁对象, 该状态一般用作于被connect的slot 或 lambda slot, 防止多次执行slot
    bool inHistory = false;  // 正在采集历史数据, 应当跳过重复操作
    bool w_recording = false;   // 通知 MachHistoryWorker 进行主动循环
    QTimer *historylooper = nullptr;   // 历史记录提取looper

    QList<quint16> dataarea(ParasParas);     // 保护参数, ASCII, start with: 199
    QList<quint16> dataarea1(ParasParas);    // 机型参数, ASCII, start with: 399
    QList<quint16> dataarea2(ParasParas);    // 制热参数, ASCII, start with: 599
    QList<quint16> dataarea3(ParasParas);    // 制冷参数, ASCII, start with: 799

signals:
    void idChanged(int);
    void nameChanged(QString);
    void ipChanged(QString);
    void portChanged(QString);
    void connectedChanged(bool);
    void selectedChanged(bool);

    void uploadFinished();
    void recordcomming(QString);    // 务必绑定此signal, 存在历史记录, 绑定后传递到前端, 前端再传递至api进行上传
};
#endif // PARASMACHINE_H
