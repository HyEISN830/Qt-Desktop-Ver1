#include "parasdbapi.h"

ParasDbApi::ParasDbApi()
{

}

bool ParasDbApi::opendb()
{
    if (nullptr != psqldb)
    {
        return false;
    }

    psqldb = new QSqlDatabase(QSqlDatabase::addDatabase("QPSQL"));
    psqldb->setHostName("103.73.119.198");
    psqldb->setPort(5432);
    psqldb->setDatabaseName("postgres");
    psqldb->setUserName("postgres");
    psqldb->setPassword("Lovingahri1314+");

    bool ok = psqldb->open();

    if (!ok)
    {
        closedb();
    }

    return ok;
}

bool ParasDbApi::dbavailable()
{
    return nullptr != psqldb && psqldb->isOpen();
}

QJsonArray ParasDbApi::getMachines()
{
    QJsonArray machs;

    if (!dbavailable()) return machs;

    QSqlQuery query("select id, name, ip, port from public.machines where isdeleted = false order by id", *psqldb);
    query.executedQuery();

    while (query.next())
    {
        QSqlRecord record = query.record();
        machs.append(ParasMachine::fromRecord(record).toJson());
    }

    return machs;
}

QJsonObject ParasDbApi::getPara(qlonglong id)
{
    QJsonObject jobj;

    if (!dbavailable()) return jobj;

    QString sql;
#pragma region "Query by id SQL string"
    {
        sql = QString(R"(select
            id,
            p0f1,
            p0f2,
            p0f3,
            p0f4,
            p0f5,
            p0f6,
            p0f7,
            p1f1,
            p1f2,
            p1f3,
            p1f4,
            p1f5,
            p1f6,
            p1f7,
            p1f8,
            p1f9,
            p1f10,
            p2f1,
            p2f2,
            p2f3,
            p2f4,
            p2f5,
            p2f6,
            p2f7t,
            p2f8t,
            p2f9t,
            p2f10t,
            p2f11t,
            p2f7b,
            p2f8b,
            p2f9b,
            p2f10b,
            p2f11b,
            p2f12,
            p3f1,
            p3f2,
            p3f3,
            p3f4,
            p3f5,
            p3f6,
            p3f7t,
            p3f8t,
            p3f9t,
            p3f10t,
            p3f11t,
            p3f7b,
            p3f8b,
            p3f9b,
            p3f10b,
            p3f11b,
            p3f12
        from
            public.paras
        where isdeleted = false
        and id = %1
;)").arg(QString::number(id));
    }
#pragma endregion

    QSqlQuery query(sql);
    query.executedQuery();

    if (!query.next()) return jobj;

    return ParasParas::fromRecord(query.record()).toJson();
}

bool ParasDbApi::updPara(QJsonObject jobj)
{
    ParasParas paras = ParasParas::fromJson(jobj);

    QString sql;
#pragma region "Update SQL string"
    {
        QString kvs;
        QList<QString> fs = paras.fields();

        sql.append(QString("update public.paras set :kvs where id = %1 and isdeleted = false;").arg(paras.getId()));

        for (int var = 0; var < fs.size(); var++)
        {
            if (fs[var] == "id") continue;
            kvs.append(fs[var]).append("=").append("\'")
                .append(paras.property(fs[var].toStdString().c_str()).toString())
                .append("\'").append(var + 1 == fs.size() ? "" : ",");
        }
        sql.replace(":kvs", kvs);
    }
#pragma endregion

    QSqlQuery query(sql);
    query.executedQuery();

    return true;
}

QJsonArray ParasDbApi::getParas()
{
    QJsonArray paras;

    if (!dbavailable()) return paras;

    QString sql;
#pragma region "Query SQL string"
    {
        sql = (R"(select
            id,
            p0f1,
            p0f2,
            p0f3,
            p0f4,
            p0f5,
            p0f6,
            p0f7,
            p1f1,
            p1f2,
            p1f3,
            p1f4,
            p1f5,
            p1f6,
            p1f7,
            p1f8,
            p1f9,
            p1f10,
            p2f1,
            p2f2,
            p2f3,
            p2f4,
            p2f5,
            p2f6,
            p2f7t,
            p2f8t,
            p2f9t,
            p2f10t,
            p2f11t,
            p2f7b,
            p2f8b,
            p2f9b,
            p2f10b,
            p2f11b,
            p2f12,
            p3f1,
            p3f2,
            p3f3,
            p3f4,
            p3f5,
            p3f6,
            p3f7t,
            p3f8t,
            p3f9t,
            p3f10t,
            p3f11t,
            p3f7b,
            p3f8b,
            p3f9b,
            p3f10b,
            p3f11b,
            p3f12
        from
            public.paras
        where isdeleted = false
        order by id;)");
    }
#pragma endregion

    QSqlQuery query(sql, *psqldb);
    query.executedQuery();

    while (query.next())
    {
        QSqlRecord record = query.record();
        paras.append(ParasParas::fromRecord(record).toJson());
    }

    return paras;
}

bool ParasDbApi::createParas(QJsonObject obj)
{
    if (!dbavailable()) return false;

    QString createSql;
#pragma region "Create SQL string"
    {
        createSql = "insert into public.paras(:fields) values (:values)";
        QList<QString> fields = ParasParas::fields();
        QString fs;
        QString vs;

        for (int var = 0; var < fields.size(); var++)
        {
            if (!obj.contains(fields[var]) || fields[var] == "id") continue;

            bool end = var + 1 == fields.size();
            QJsonValue v = obj.value(fields[var]);
            QString val;

            switch (v.type())
            {
            case QJsonValue::Type::Double:
                val = QString::number(v.toInt());
                break;
            default:
                val = v.toString().replace("\'", "").replace("\"", "").replace("\n", "");
                break;
            }

            fs.append(fields[var]).append(end ? "" : ",");
            vs.append("\'").append(val).append("\'").append(end ? "" : ",");
        }
        createSql.replace(":fields", fs);
        createSql.replace(":values", vs);
    }
#pragma endregion

    QSqlQuery query(createSql);
    query.executedQuery();

    return true;
}

bool ParasDbApi::deleteParas(qlonglong id)
{
    if (!dbavailable()) return false;

    QString deleteSql;
#pragma region "Delete SQL string"
    {
        deleteSql = QString("update public.paras set isdeleted = true where id = %1;").arg(QString::number(id));
    }
#pragma endregion

    QSqlQuery query(deleteSql);
    query.executedQuery();

    return true;
}

bool ParasDbApi::createTlogsFromAscii(QString ascii)
{
    if (!dbavailable()) return false;

    Tlogs *tlogs = Tlogs::fromAscii(ascii);

    if (tlogs)
    {
        QSqlQuery query(tlogs->toCreateSql());
        query.executedQuery();
    }

    delete tlogs;
    return true;
}

QJsonArray ParasDbApi::getTlogs(int page, int pagesize, QString startTime, QString endTime, QString ip, QString barcode, QString tr)
{
    QJsonArray result;
    QString sql = Tlogs::toLimitSql(page, pagesize, startTime, endTime, ip, barcode, tr);
    QSqlQuery query(sql);
    query.executedQuery();

    while (query.next())
    {
        QSqlRecord record = query.record();
        result.append(Tlogs::fromRecord(record).toJson());
    }

    return result;
}

int ParasDbApi::getTlogsCtn(QString startTime, QString endTime, QString ip, QString barcode, QString tr)
{
    int result;
    QString sql = Tlogs::toLimitCtnSql(startTime, endTime, ip, barcode, tr);
    QSqlQuery query(sql);
    query.executedQuery();

    if (query.next())
    {
        QSqlRecord record = query.record();
        return record.value(Tlogs::Col_RowsCtn).toInt();
    }

    return 0;
}

void ParasDbApi::closedb()
{
    if (nullptr != psqldb)
    {
        psqldb->close();
        QSqlDatabase::removeDatabase(psqldb->connectionName());
    }

    delete psqldb;
    psqldb = nullptr;
}

ParasDbApi::~ParasDbApi()
{
    closedb();
}
