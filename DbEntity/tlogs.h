#ifndef TLOGS_H
#define TLOGS_H

#include <QObject>
#include <QQuickItem>
#include <QDateTime>
#include <QSqlRecord>
#include <QJsonObject>

class Tlogs : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT
public:
    static const QString Col_RowsCtn;

    Tlogs();
    Tlogs(const Tlogs &right)
    {
        *this = right;
    }

    Q_PROPERTY (QDateTime testtime READ getTesttime WRITE setTesttime NOTIFY testtimeChanged);
    Q_PROPERTY (QString barcode READ getBarcode WRITE setBarcode NOTIFY barcodeChanged);
    Q_PROPERTY (double hotdiff READ getHotdiff WRITE setHotdiff NOTIFY hotdiffChanged);
    Q_PROPERTY (double hoteleca READ getHoteleca WRITE setHoteleca NOTIFY hotelecaChanged);
    Q_PROPERTY (double hotelecw READ getHotelecw WRITE setHotelecw NOTIFY hotelecwChanged);
    Q_PROPERTY (double hotmpa READ getHotmpa WRITE setHotmpa NOTIFY hotmpaChanged);
    Q_PROPERTY (double colddiff READ getColddiff WRITE setColddiff NOTIFY colddiffChanged);
    Q_PROPERTY (double coldeleca READ getColdeleca WRITE setColdeleca NOTIFY coldelecaChanged);
    Q_PROPERTY (double coldelecw READ getColdelecw WRITE setColdelecw NOTIFY coldelecwChanged);
    Q_PROPERTY (double coldmpa READ getColdmpa WRITE setColdmpa NOTIFY coldmpaChanged);
    Q_PROPERTY (double workeleca READ getWorkeleca WRITE setWorkeleca NOTIFY workelecaChanged);
    Q_PROPERTY (QString testresult READ getTestresult WRITE setTestresult NOTIFY testresultChanged);
    Q_PROPERTY (QString ip READ getIp WRITE setIp NOTIFY ipChanged);

    Q_INVOKABLE inline QDateTime getTesttime() { return this->testtime; }
    Q_INVOKABLE inline QString getBarcode() { return this->barcode; }
    Q_INVOKABLE inline double getHotdiff() { return this->hotdiff; }
    Q_INVOKABLE inline double getHoteleca() { return this->hoteleca; }
    Q_INVOKABLE inline double getHotelecw() { return this->hotelecw; }
    Q_INVOKABLE inline double getHotmpa() { return this->hotmpa; }
    Q_INVOKABLE inline double getColddiff() { return this->colddiff; }
    Q_INVOKABLE inline double getColdeleca() { return this->coldeleca; }
    Q_INVOKABLE inline double getColdelecw() { return this->coldelecw; }
    Q_INVOKABLE inline double getColdmpa() { return this->coldmpa; }
    Q_INVOKABLE inline double getWorkeleca() { return this->workeleca; }
    Q_INVOKABLE inline QString getTestresult() { return this->testresult; }
    Q_INVOKABLE inline QString getIp() { return this->ip; }

    Q_INVOKABLE inline void setTesttime(QDateTime v) { this->testtime = v; emit testtimeChanged(v); }
    Q_INVOKABLE inline void setBarcode(QString v) { this->barcode = v; emit barcodeChanged(v); }
    Q_INVOKABLE inline void setHotdiff(double v) { this->hotdiff = v; emit hotdiffChanged(v); }
    Q_INVOKABLE inline void setHoteleca(double v) { this->hoteleca = v; emit hotelecaChanged(v); }
    Q_INVOKABLE inline void setHotelecw(double v) { this->hotelecw = v; emit hotelecwChanged(v); }
    Q_INVOKABLE inline void setHotmpa(double v) { this->hotmpa = v; emit hotmpaChanged(v); }
    Q_INVOKABLE inline void setColddiff(double v) { this->colddiff = v; emit colddiffChanged(v); }
    Q_INVOKABLE inline void setColdeleca(double v) { this->coldeleca = v; emit coldelecaChanged(v); }
    Q_INVOKABLE inline void setColdelecw(double v) { this->coldelecw = v; emit coldelecwChanged(v); }
    Q_INVOKABLE inline void setColdmpa(double v) { this->coldmpa = v; emit coldmpaChanged(v); }
    Q_INVOKABLE inline void setWorkeleca(double v) { this->workeleca = v; emit workelecaChanged(v); }
    Q_INVOKABLE inline void setTestresult(QString v) { this->testresult = v; emit testresultChanged(v); }
    Q_INVOKABLE inline void setIp(QString v) { this->ip = v; emit ipChanged(v); }

    static QList<QString> fields()
    {
        const static QMetaObject* metaObj = Tlogs().metaObject();
        const static int propctn = metaObj->propertyCount();
        static QList<QString> fields;
        static QList<QString> pfields;

        if (pfields.size() == 0)
        {
            QQuickItem item;
            const QMetaObject *itemmobj = item.metaObject();

            for (int var = 0; var < itemmobj->propertyCount(); var++)
                pfields.append(itemmobj->property(var).name());
        }

        if (fields.size() == 0)
            for (int var = 0; var < propctn; var++)
                if (!pfields.contains(metaObj->property(var).name()))
                    fields.append(metaObj->property(var).name());

        return fields;
    }

    static Tlogs fromRecord(QSqlRecord record)
    {
        const static QMetaObject* metaObj = Tlogs().metaObject();
        const static int propctn = metaObj->propertyCount();
        QList<QString> fs = fields();

        Tlogs object;

        for (int var = 0; var < fs.size(); var++)
        {
            int rcol = record.indexOf(fs.at(var));
            if (rcol == -1) continue;
            object.setProperty(fs.at(var).toStdString().c_str(), record.value(rcol));
        }

        return Tlogs(object);
    }

    // Attention! Delete the Tlogs pointer after using it.
    static Tlogs *fromAscii(QString ascii)
    {
        Tlogs *tlogs = nullptr;

        if (!ascii.trimmed().size()) return tlogs;

        QStringList values = ascii.split("#");

        if (values.size() >= 13)
        {
            tlogs = new Tlogs;

            // 移除多余 "-" 符号
            values[0].replace(values[0].lastIndexOf("-"), 1, ' ');

            tlogs->setTesttime(QDateTime::fromString(values[0], "yyyy-MM-dd hh:mm:ss"));
            tlogs->setBarcode(values[1]);
            tlogs->setHotdiff((values[2].toDouble()));
            tlogs->setHoteleca(values[3].toDouble());
            tlogs->setHotelecw(values[4].toDouble());
            tlogs->setHotmpa(values[5].toDouble());
            tlogs->setColddiff(values[6].toDouble());
            tlogs->setColdeleca(values[7].toDouble());
            tlogs->setColdelecw(values[8].toDouble());
            tlogs->setColdmpa(values[9].toDouble());
            tlogs->setWorkeleca(values[10].toDouble());
            tlogs->setTestresult(values[11]);
            tlogs->setIp(values[12]);
        }

        return tlogs;
    }

    QJsonObject toJson()
    {
        QJsonObject jobj;
        QList<QString> fs = fields();

        for (int var = 0; var < fs.size(); var++)
        {
            jobj[fs[var]] = QJsonValue::fromVariant(property(fs[var].toStdString().c_str()));
        }

        return jobj;
    }

    QString toCreateSql()
    {
        QString sql = R"(INSERT INTO public.tlogs (:fields) VALUES(:values);)";
        QString sqlfields;
        QString sqlvalues;
        QList<QString> fs = fields();

        fs.removeIf([](QString v) {
            return v == "id";
        });

        for (int var = 0; var < fs.size(); var++)
        {
            QString end = var + 1 == fs.size() ? "" : ",";

            sqlfields.append(fs[var]).append(end);
            sqlvalues.append("\'").append(property(fs[var].toStdString().c_str()).toString()).append("\'").append(end);
        }

        sql = sql.replace(":fields", sqlfields).replace(":values", sqlvalues);

        return sql;
    }

    // 分页sql
    static QString toLimitSql(int curPage, int pageSize, QString startTime, QString endTime, QString ip, QString barcode, QString tr)
    {
        QString sql;
        QList<QString> fs = fields();
        QString sqlFields;
        QString timeCondition;

        sql = R"(   select
                        :fields
                    from public.tlogs
                    where 1 = 1
                        :timeCondition
                        and ip like '%:ip%'
                        and barcode like '%:barcode%'
                        and testresult like '%:testresult%'
                    order by testtime desc
                    offset (:curPage - 1) * :pageSize
                    limit :pageSize
                    ;
                )";

        // process parameters
        for (int var = 0; var < fs.size(); var++)
            sqlFields.append(fs[var]).append(var + 1 == fs.size() ? "" : ",");

        if (startTime.trimmed().size() && endTime.trimmed().size())
            timeCondition = QString("and (testtime >= '%1' and testtime <= '%2')").arg(startTime, endTime);

        // set parameters
        sql
            .replace(":fields", sqlFields)
            .replace(":timeCondition", timeCondition)
            .replace(":ip", ip)
            .replace(":barcode", barcode)
            .replace(":testresult", tr)
            .replace(":curPage", QString::number(curPage))
            .replace(":pageSize", QString::number(pageSize))
            ;

        return sql;
    }

    // 获取分页数据集总数sql
    static QString toLimitCtnSql(QString startTime, QString endTime, QString ip, QString barcode, QString tr)
    {
        QString sql;
        QString timeCondition;

        sql = R"(   select
                        count(1) as :Col_RowsCtn
                    from public.tlogs
                    where 1 = 1
                        :timeCondition
                        and ip like '%:ip%'
                        and barcode like '%:barcode%'
                        and testresult like '%:testresult%'
                    ;
                )";

        // process parameters
        if (startTime.trimmed().size() && endTime.trimmed().size())
            timeCondition = QString("and (testtime >= '%1' and testtime <= '%2')").arg(startTime, endTime);

        // set parameters
        sql
            .replace(":timeCondition", timeCondition)
            .replace(":Col_RowsCtn", Col_RowsCtn)
            .replace(":ip", ip)
            .replace(":barcode", barcode)
            .replace(":testresult", tr)
            ;

        return sql;
    }

    Tlogs &operator=(const Tlogs &right)
    {
        QList<QString> fs = fields();

        for (int var = 0; var < fs.size(); var++)
        {
            this->setProperty(fs[var].toStdString().c_str(), right.property(fs[var].toStdString().c_str()));
        }

        return *this;
    }

private:
    QDateTime testtime;
    QString barcode;
    double hotdiff;
    double hoteleca;
    double hotelecw;
    double hotmpa;
    double colddiff;
    double coldeleca;
    double coldelecw;
    double coldmpa;
    double workeleca;
    QString testresult;
    QString ip;

signals:
    void testtimeChanged(QDateTime);
    void barcodeChanged(QString);
    void hotdiffChanged(double);
    void hotelecaChanged(double);
    void hotelecwChanged(double);
    void hotmpaChanged(double);
    void colddiffChanged(double);
    void coldelecaChanged(double);
    void coldelecwChanged(double);
    void coldmpaChanged(double);
    void workelecaChanged(double);
    void testresultChanged(QString);
    void ipChanged(QString);
};

#endif // TLOGS_H
