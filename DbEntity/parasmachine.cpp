#include "parasmachine.h"

void ParasMachine::mdstateChanged(QModbusDevice::State state)
{
    // 销毁时取消动作
    if (inDestroy) return;

    // 当指示连接成功时, 检验是否为假连接
    if (state == QModbusDevice::State::ConnectedState)
    {
        // 发送心跳数据, 防止假连接
        QModbusDataUnit data;

        data.setRegisterType(QModbusDataUnit::HoldingRegisters);
        data.setStartAddress(0);
        data.setValueCount(1);

        QModbusReply *reply = m_mdclient->sendReadRequest(data, 2);

        if (nullptr != reply)
        {
            reply->connect(reply, &QModbusReply::finished, this, [=]() {
                if (inDestroy) return;  // 销毁时取消动作
                QModbusDataUnit result = reply->result();
                bool ok = result.values().size() == 0;
                setConnected(!ok);
                if (connected) checkhistory(); // 在心跳后检查是否有历史记录可读
            });
        }
        else
        {
            // 异常, 默认连接已断开
            setConnected(false);
        }
        return;
    }

    setConnected(false);
}

QModbusDevice::State ParasMachine::mdbusstate()
{
    return m_mdclient->state();
}

void ParasMachine::openmdbus()
{
    if (nullptr == m_mdclient)
        m_mdclient = new QModbusTcpClient(this);

    m_mdclient->setConnectionParameter(QModbusDevice::NetworkAddressParameter, getIp());
    m_mdclient->setConnectionParameter(QModbusDevice::NetworkPortParameter, getPort().toInt());
    m_mdclient->setTimeout(1000);

    bool ok = m_mdclient->connectDevice();

    // 关于连接状态, 请查看mdstateChanged中处理
    if (ok)
    {
        m_mdclient->connect(m_mdclient, &QModbusTcpClient::stateChanged, this, &ParasMachine::mdstateChanged);
        return;
    }
}

void ParasMachine::startheartb()
{
    hearting = true;
}

void ParasMachine::heartbeat()
{
    // 当已建立连接时, 进行心跳检测; 否则将尝试进行重连设备

    if (nullptr == m_mdclient || !hearting) return;

    if (!connected)
        // 同样会触发mdstateChanged, 最终取决与mdstateChanged如何处理连接状态
        m_mdclient->connectDevice();
    else
        // 利用状态改变slot, 实现心跳+状态检测
        mdstateChanged(QModbusDevice::State::ConnectedState);
}

void ParasMachine::stopheartb()
{
    hearting = false;
}

void ParasMachine::upload(QJsonObject jobj)
{
    if (nullptr == m_mdclient || !connected) return;

    stopheartb();
    const ParasParas paras = ParasParas::fromJson(jobj);

    // 重置参数上载状态
    protectdata = 0;
    testdata = 0;

    /*
        参数上载:
          1. 当寄存器完成后, 调用rangeEvent..(), 通知部分参数上载完成
          2. 在rangeEvent..()中, 当达到指定参数上载完成数量后,
             则点亮指定线圈, 以表示应用参数更改
          3. 最终结果以及处理以 "检测参数" 完成为准
    */

#pragma region "address 199"
    {
        QModbusDataUnit data;
        QList<quint16> darea = dataarea(paras);

        data.setRegisterType(QModbusDataUnit::HoldingRegisters);
        data.setStartAddress(199);
        data.setValues(darea);

        QModbusReply *reply = m_mdclient->sendWriteRequest(data, sid);

        if (nullptr != reply)
            reply->connect(reply, &QModbusReply::finished, this, [=]() {
                // "保护参数设置", 参数上载 + 1, 表示改区段已上传完成一次
                protectdata += 1;
                protectEvent();
            });
    }
#pragma endregion

#pragma region "address 399"
    {
        QModbusDataUnit data;
        QList<quint16> darea1 = dataarea1(paras);

        data.setRegisterType(QModbusDataUnit::HoldingRegisters);
        data.setStartAddress(399);
        data.setValues(darea1);

        QModbusReply *reply = m_mdclient->sendWriteRequest(data, sid);

        if (nullptr != reply)
            reply->connect(reply, &QModbusReply::finished, this, [=]() {
                // "检测参数设置", 参数上载 + 1, 表示改区段已上传完成一次
                testdata += 1;
                testEvent();
            });
    }
#pragma endregion

#pragma region "address 599"
    {
        QModbusDataUnit data;
        QList<quint16> darea2 = dataarea2(paras);

        data.setRegisterType(QModbusDataUnit::HoldingRegisters);
        data.setStartAddress(599);
        data.setValues(darea2);

        QModbusReply *reply =  m_mdclient->sendWriteRequest(data, sid);

        if (nullptr != reply)
            reply->connect(reply, &QModbusReply::finished, this, [=]() {
                // "检测参数设置", 参数上载 + 1, 表示改区段已上传完成一次
                testdata += 1;
                testEvent();
            });
    }
#pragma endregion

#pragma region "address 799"
    {
        QModbusDataUnit data;
        QList<quint16> darea3 = dataarea3(paras);

        data.setRegisterType(QModbusDataUnit::HoldingRegisters);
        data.setStartAddress(799);
        data.setValues(darea3);

        QModbusReply *reply = m_mdclient->sendWriteRequest(data, sid);

        if (nullptr != reply)
            reply->connect(reply, &QModbusReply::finished, this, [=]() {
                // "检测参数设置", 参数上载 + 1, 表示改区段已上传完成一次
                testdata += 1;
                testEvent();
            });
    }
#pragma endregion
}

void ParasMachine::protectEvent()
{
    // 当参数 1 寄存器完成后, 将线圈设置 为 1, 确认上传

    if (protectdata >= 1)
    {
        QModbusDataUnit data;
        data.setRegisterType(QModbusDataUnit::Coils);
        data.setStartAddress(1);
        data.setValues({ 1 });
        m_mdclient->sendWriteRequest(data, sid);
    }
}

void ParasMachine::testEvent()
{
    // 当参数 2,3,4 寄存器完成后, 将线圈设置为 1, 确认上传

    if (testdata >= 3)
    {
        QModbusDataUnit data;
        data.setRegisterType(QModbusDataUnit::Coils);
        data.setStartAddress(2);
        data.setValues({ 1 });

        QModbusReply *reply = m_mdclient->sendWriteRequest(data, sid);

        if (nullptr != reply)
            reply->connect(reply, &QModbusReply::finished, this, [=]() {
                startheartb();
                emit uploadFinished();
            });
    }
}

QList<quint16> ParasMachine::dataarea(ParasParas paras)
{
    QList<quint16> data;
    QString str;

    str.append(paras.getP1f1()).append("#");
    str.append(paras.getP1f3()).append("#");
    str.append(paras.getP1f5()).append("#");
    str.append(paras.getP1f7()).append("#");
    str.append(paras.getP1f9()).append("#");
    str.append(paras.getP1f10()).append("#");
    str.append(paras.getP1f2()).append("#");
    str.append(paras.getP1f4()).append("#");
    str.append(paras.getP1f6()).append("#");
    str.append(paras.getP1f8()).append("#");
    str.append(paras.getP0f1()).append("#");
    str.append(paras.getP0f7());

    QByteArray bytes = str.toLatin1();

    for (int var = 0; var < bytes.length(); var++)
        data.append(bytes[var]);

    return data;
}

QList<quint16> ParasMachine::dataarea1(ParasParas paras)
{
    QList<quint16> data;
    QString str;
    QString rawName = paras.getP0f5();
    const QChar cnPoint = QString("·").at(0);
    const QChar cnSplitC = '*';

    str.append(paras.getP0f2()).append("#");

    // Simplified Chinese "name" start ---------------
    for (int var = 0; var < 8; var++)
    {
        if (rawName.length() >= var + 1)
            str.append(QString::number(rawName.at(var).unicode()));
        else
            str.append(QString::number(cnPoint.unicode()));
        if (var + 1 != 8)
            str.append(cnSplitC);
    }
    str.append("#");
    // Simplified Chinese "name" end ---------------

    str.append(paras.getP0f4()).append("#");
    str.append(paras.getP0f3()).append("#");
    str.append(paras.getP2f12()).append("#");
    str.append(paras.getP2f1()).append("#");
    str.append(paras.getP2f2()).append("#");
    str.append(paras.getP2f3());

    QByteArray bytes = str.toLatin1();

    for (int var = 0; var < bytes.length(); var++)
        data.append(bytes[var]);

    return data;
}

QList<quint16> ParasMachine::dataarea2(ParasParas paras)
{
    QList<quint16> data;
    QString str;

    str.append(paras.getP2f4()).append("#");
    str.append(paras.getP2f5()).append("#");
    str.append(paras.getP2f6()).append("#");
    str.append(paras.getP2f7t()).append("#");
    str.append(paras.getP2f7b()).append("#");
    str.append(paras.getP2f8t()).append("#");
    str.append(paras.getP2f8b()).append("#");
    str.append(paras.getP2f9t()).append("#");
    str.append(paras.getP2f9b()).append("#");
    str.append(paras.getP2f10t()).append("#");
    str.append(paras.getP2f10b()).append("#");
    str.append(paras.getP2f11t()).append("#");
    str.append(paras.getP2f11b()).append("#");
    str.append(paras.getP3f12()).append("#");
    str.append(paras.getP3f1());

    QByteArray bytes = str.toLatin1();

    for (int var = 0; var < bytes.length(); var++)
        data.append(bytes[var]);

    return data;
}

QList<quint16> ParasMachine::dataarea3(ParasParas paras)
{
    QList<quint16> data;
    QString str;

    str.append(paras.getP3f2()).append("#");
    str.append(paras.getP3f3()).append("#");
    str.append(paras.getP3f4()).append("#");
    str.append(paras.getP3f5()).append("#");
    str.append(paras.getP3f6()).append("#");
    str.append(paras.getP3f7t()).append("#");
    str.append(paras.getP3f7b()).append("#");
    str.append(paras.getP3f8t()).append("#");
    str.append(paras.getP3f8b()).append("#");
    str.append(paras.getP3f9t()).append("#");
    str.append(paras.getP3f9b()).append("#");
    str.append(paras.getP3f10t()).append("#");
    str.append(paras.getP3f10b()).append("#");
    str.append(paras.getP3f11t()).append("#");
    str.append(paras.getP3f11b());

    QByteArray bytes = str.toLatin1();

    for (int var = 0; var < bytes.length(); var++)
        data.append(bytes[var]);

    return data;
}

void ParasMachine::checkhistory()
{
    // 在心跳后操作
    // 线圈 0x00 指定是否有历史数据可读, 读取完成后将 0x03 置 1, 等待下次 0x00 为 1
    // 循环数据利用 MachHistoryWorker 进行
    // 销毁时停止所有动作

    if (nullptr == m_mdclient || !connected || inDestroy || inHistory) return;

    QModbusDataUnit data;

    data.setRegisterType(QModbusDataUnit::Coils);
    data.setStartAddress(0);
    data.setValueCount(1);

    QModbusReply *reply = m_mdclient->sendReadRequest(data, sid);

    if (nullptr != reply)
    {
        reply->connect(reply, &QModbusReply::finished, this, [=]() {
            if (inDestroy) return;  // 销毁时停止所有动作
            QModbusDataUnit result = reply->result();
            QList<quint16> values = result.values();

            if (values.size() > 0 && values[0])
            {
                stopheartb();
                starthistory(); // 开始记录检测采集
            }
        });
    }
}

void ParasMachine::takerecord()
{
    /*
        采集单条历史记录
          1. 检查是否有 线圈 0x00 true; 否则关闭数据采集, stophistory();
          2. 检查读出记录长度是否为0; 否则关闭数据采集, stophistory();
          3. 其他情况, 如 reply 是 nullptr, 则关闭数据采集, stophistory();
          4. 销毁时不可用
    */

    if (inDestroy || !inHistory)
    {
        stophistory();
        return;
    }

    // 线圈 0x00 检查
    QModbusDataUnit data;
    data.setRegisterType(QModbusDataUnit::Coils);
    data.setStartAddress(0);
    data.setValueCount(1);

    QModbusReply *reply = m_mdclient->sendReadRequest(data, sid);

    if (nullptr == reply)
    {
        stophistory();
        return;
    }

    // 线圈 0x00 检查 finished callback
    reply->connect(reply, &QModbusReply::finished, this, [=]() {
        if (inDestroy || !inHistory)
        {
            stophistory();
            return;
        }

        QModbusDataUnit result = reply->result();
        QList<quint16> values = result.values();

        if (!values.size() || !values[0])
        {
            stophistory();
            return;
        }

        QModbusDataUnit dataascii;
        dataascii.setRegisterType(QModbusDataUnit::HoldingRegisters);
        dataascii.setStartAddress(0);
        dataascii.setValueCount(125);

        QModbusReply *reply1 = m_mdclient->sendReadRequest(dataascii, sid);

        if (nullptr == reply1)
        {
            stophistory();
            return;
        }

        // 历史记录 寄存器 0~125 读取 finished callback
        reply1->connect(reply1, &QModbusReply::finished, this, [=]() {
            if (inDestroy || !inHistory)
            {
                stophistory();
                return;
            }

            QModbusDataUnit resultascii = reply1->result();
            QList<quint16> valueascii = resultascii.values();
            QByteArray bytes;

            if (!valueascii.size())
            {
                stophistory();
                return;
            }

            for (int var = 0; var < valueascii.size(); var++)
                if (valueascii[var]) bytes.append(valueascii[var]);

            QString ascii = QString::fromLatin1(bytes);
            emit recordcomming(ascii.append("#").append(getIp()));

            // 通知 线圈 0x03 单条历史记录读取完成
            QModbusDataUnit readedData;
            readedData.setRegisterType(QModbusDataUnit::Coils);
            readedData.setStartAddress(3);
            readedData.setValues({ 1 });
            m_mdclient->sendWriteRequest(readedData, sid);
        });
    });
}

void ParasMachine::starthistory()
{
    w_recording = true;
    inHistory = true;

    if (!historylooper)
    {
        historylooper = new QTimer(this);
        historylooper->connect(historylooper, &QTimer::timeout, this, [=]() {
            if (!destroyed() && inhistory() && wrecording())
                takerecord();
            else
                stophistory();
        });
    }
    historylooper->start(1500);
}

void ParasMachine::stophistory()
{
    w_recording = false;
    inHistory = false;
    startheartb();  // 恢复心跳机制
    if (!inDestroy && historylooper) historylooper->stop();
}
