#ifndef PARASPARAS_H
#define PARASPARAS_H

#include <QObject>
#include <QQuickItem>
#include <QJsonObject>
#include <QSqlRecord>

class ParasParas : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT
public:
    ParasParas();
    ParasParas(const ParasParas& val)
    {
        *this = val;
    }

    static QList<QString> fields()
    {
        const static QMetaObject* metaObj = ParasParas().metaObject();
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

    static ParasParas fromRecord(QSqlRecord record)
    {
        QList<QString> fs = fields();
        ParasParas object;

        for (int var = 0; var < fs.size(); var++)
        {
            int rcol = record.indexOf(fs.at(var));
            if (rcol == -1) continue;
            QVariant v = record.value(rcol);
            object.setProperty(fs.at(var).toStdString().c_str(), v);
        }

        return object;
    }

    static ParasParas fromJson(QJsonObject jobj)
    {
        ParasParas paras;
        QList<QString> fs = fields();

        for (int var = 0; var < fs.size(); var++)
        {
            if (!jobj.contains(fs[var])) continue;

            QJsonValue val = jobj.value(fs[var]);
            QVariant v;

            switch (val.type())
            {
                case QJsonValue::Type::Double:
                    v = val.toInt();
                    break;
                default:
                    v = val.toString();
                    break;
            }

            if (fs[var] == "id")
            {
                v = val.toInteger();
            }

            paras.setProperty(fs[var].toStdString().c_str(), v);
        }

        return paras;
    }

    Q_INVOKABLE inline QJsonObject toJson()
    {
        QJsonObject jobj;
        QList<QString> fs = fields();

        for (int var = 0; var < fs.size(); var++)
        {
            if (fs[var] == "id")
            {
                jobj["id"] = QString::number(this->id);
                continue;
            }
            jobj[fs[var]] = this->property(fs[var].toStdString().c_str()).toString();
        }

        return jobj;
    }

    ParasParas &operator =(const ParasParas& right)
    {
        QList<QString> fs = fields();

        for (int var = 0; var < fs.size(); var++)
        {
            this->setProperty(fs[var].toStdString().c_str(), right.property(fs[var].toStdString().c_str()));
        }

        return *this;
    }

public:
    Q_PROPERTY(qulonglong id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString p0f1 READ getP0f1 WRITE setP0f1 NOTIFY p0f1Changed)
    Q_PROPERTY(QString p0f2 READ getP0f2 WRITE setP0f2 NOTIFY p0f2Changed)
    Q_PROPERTY(QString p0f3 READ getP0f3 WRITE setP0f3 NOTIFY p0f3Changed)
    Q_PROPERTY(QString p0f4 READ getP0f4 WRITE setP0f4 NOTIFY p0f4Changed)
    Q_PROPERTY(QString p0f5 READ getP0f5 WRITE setP0f5 NOTIFY p0f5Changed)
    Q_PROPERTY(QString p0f6 READ getP0f6 WRITE setP0f6 NOTIFY p0f6Changed)
    Q_PROPERTY(QString p0f7 READ getP0f7 WRITE setP0f7 NOTIFY p0f7Changed)
    Q_PROPERTY(QString p1f1 READ getP1f1 WRITE setP1f1 NOTIFY p1f1Changed)
    Q_PROPERTY(QString p1f2 READ getP1f2 WRITE setP1f2 NOTIFY p1f2Changed)
    Q_PROPERTY(QString p1f3 READ getP1f3 WRITE setP1f3 NOTIFY p1f3Changed)
    Q_PROPERTY(QString p1f4 READ getP1f4 WRITE setP1f4 NOTIFY p1f4Changed)
    Q_PROPERTY(QString p1f5 READ getP1f5 WRITE setP1f5 NOTIFY p1f5Changed)
    Q_PROPERTY(QString p1f6 READ getP1f6 WRITE setP1f6 NOTIFY p1f6Changed)
    Q_PROPERTY(QString p1f7 READ getP1f7 WRITE setP1f7 NOTIFY p1f7Changed)
    Q_PROPERTY(QString p1f8 READ getP1f8 WRITE setP1f8 NOTIFY p1f8Changed)
    Q_PROPERTY(QString p1f9 READ getP1f9 WRITE setP1f9 NOTIFY p1f9Changed)
    Q_PROPERTY(QString p1f10 READ getP1f10 WRITE setP1f10 NOTIFY p1f10Changed)
    Q_PROPERTY(QString p2f1 READ getP2f1 WRITE setP2f1 NOTIFY p2f1Changed)
    Q_PROPERTY(QString p2f2 READ getP2f2 WRITE setP2f2 NOTIFY p2f2Changed)
    Q_PROPERTY(QString p2f3 READ getP2f3 WRITE setP2f3 NOTIFY p2f3Changed)
    Q_PROPERTY(QString p2f4 READ getP2f4 WRITE setP2f4 NOTIFY p2f4Changed)
    Q_PROPERTY(QString p2f5 READ getP2f5 WRITE setP2f5 NOTIFY p2f5Changed)
    Q_PROPERTY(QString p2f6 READ getP2f6 WRITE setP2f6 NOTIFY p2f6Changed)
    Q_PROPERTY(QString p2f7t READ getP2f7t WRITE setP2f7t NOTIFY p2f7tChanged)
    Q_PROPERTY(QString p2f8t READ getP2f8t WRITE setP2f8t NOTIFY p2f8tChanged)
    Q_PROPERTY(QString p2f9t READ getP2f9t WRITE setP2f9t NOTIFY p2f9tChanged)
    Q_PROPERTY(QString p2f10t READ getP2f10t WRITE setP2f10t NOTIFY p2f10tChanged)
    Q_PROPERTY(QString p2f11t READ getP2f11t WRITE setP2f11t NOTIFY p2f11tChanged)
    Q_PROPERTY(QString p2f7b READ getP2f7b WRITE setP2f7b NOTIFY p2f7bChanged)
    Q_PROPERTY(QString p2f8b READ getP2f8b WRITE setP2f8b NOTIFY p2f8bChanged)
    Q_PROPERTY(QString p2f9b READ getP2f9b WRITE setP2f9b NOTIFY p2f9bChanged)
    Q_PROPERTY(QString p2f10b READ getP2f10b WRITE setP2f10b NOTIFY p2f10bChanged)
    Q_PROPERTY(QString p2f11b READ getP2f11b WRITE setP2f11b NOTIFY p2f11bChanged)
    Q_PROPERTY(QString p2f12 READ getP2f12 WRITE setP2f12 NOTIFY p2f12Changed)
    Q_PROPERTY(QString p3f1 READ getP3f1 WRITE setP3f1 NOTIFY p3f1Changed)
    Q_PROPERTY(QString p3f2 READ getP3f2 WRITE setP3f2 NOTIFY p3f2Changed)
    Q_PROPERTY(QString p3f3 READ getP3f3 WRITE setP3f3 NOTIFY p3f3Changed)
    Q_PROPERTY(QString p3f4 READ getP3f4 WRITE setP3f4 NOTIFY p3f4Changed)
    Q_PROPERTY(QString p3f5 READ getP3f5 WRITE setP3f5 NOTIFY p3f5Changed)
    Q_PROPERTY(QString p3f6 READ getP3f6 WRITE setP3f6 NOTIFY p3f6Changed)
    Q_PROPERTY(QString p3f7t READ getP3f7t WRITE setP3f7t NOTIFY p3f7tChanged)
    Q_PROPERTY(QString p3f8t READ getP3f8t WRITE setP3f8t NOTIFY p3f8tChanged)
    Q_PROPERTY(QString p3f9t READ getP3f9t WRITE setP3f9t NOTIFY p3f9tChanged)
    Q_PROPERTY(QString p3f10t READ getP3f10t WRITE setP3f10t NOTIFY p3f10tChanged)
    Q_PROPERTY(QString p3f11t READ getP3f11t WRITE setP3f11t NOTIFY p3f11tChanged)
    Q_PROPERTY(QString p3f7b READ getP3f7b WRITE setP3f7b NOTIFY p3f7bChanged)
    Q_PROPERTY(QString p3f8b READ getP3f8b WRITE setP3f8b NOTIFY p3f8bChanged)
    Q_PROPERTY(QString p3f9b READ getP3f9b WRITE setP3f9b NOTIFY p3f9bChanged)
    Q_PROPERTY(QString p3f10b READ getP3f10b WRITE setP3f10b NOTIFY p3f10bChanged)
    Q_PROPERTY(QString p3f11b READ getP3f11b WRITE setP3f11b NOTIFY p3f11bChanged)
    Q_PROPERTY(QString p3f12 READ getP3f12 WRITE setP3f12 NOTIFY p3f12Changed)

    Q_INVOKABLE inline qulonglong getId() { return this->id; }
    Q_INVOKABLE inline QString getP0f1() { return this->p0f1; }
    Q_INVOKABLE inline QString getP0f2() { return this->p0f2; }
    Q_INVOKABLE inline QString getP0f3() { return this->p0f3; }
    Q_INVOKABLE inline QString getP0f4() { return this->p0f4; }
    Q_INVOKABLE inline QString getP0f5() { return this->p0f5; }
    Q_INVOKABLE inline QString getP0f6() { return this->p0f6; }
    Q_INVOKABLE inline QString getP0f7() { return this->p0f7; }
    Q_INVOKABLE inline QString getP1f1() { return this->p1f1; }
    Q_INVOKABLE inline QString getP1f2() { return this->p1f2; }
    Q_INVOKABLE inline QString getP1f3() { return this->p1f3; }
    Q_INVOKABLE inline QString getP1f4() { return this->p1f4; }
    Q_INVOKABLE inline QString getP1f5() { return this->p1f5; }
    Q_INVOKABLE inline QString getP1f6() { return this->p1f6; }
    Q_INVOKABLE inline QString getP1f7() { return this->p1f7; }
    Q_INVOKABLE inline QString getP1f8() { return this->p1f8; }
    Q_INVOKABLE inline QString getP1f9() { return this->p1f9; }
    Q_INVOKABLE inline QString getP1f10() { return this->p1f10; }
    Q_INVOKABLE inline QString getP2f1() { return this->p2f1; }
    Q_INVOKABLE inline QString getP2f2() { return this->p2f2; }
    Q_INVOKABLE inline QString getP2f3() { return this->p2f3; }
    Q_INVOKABLE inline QString getP2f4() { return this->p2f4; }
    Q_INVOKABLE inline QString getP2f5() { return this->p2f5; }
    Q_INVOKABLE inline QString getP2f6() { return this->p2f6; }
    Q_INVOKABLE inline QString getP2f7t() { return this->p2f7t; }
    Q_INVOKABLE inline QString getP2f8t() { return this->p2f8t; }
    Q_INVOKABLE inline QString getP2f9t() { return this->p2f9t; }
    Q_INVOKABLE inline QString getP2f10t() { return this->p2f10t; }
    Q_INVOKABLE inline QString getP2f11t() { return this->p2f11t; }
    Q_INVOKABLE inline QString getP2f7b() { return this->p2f7b; }
    Q_INVOKABLE inline QString getP2f8b() { return this->p2f8b; }
    Q_INVOKABLE inline QString getP2f9b() { return this->p2f9b; }
    Q_INVOKABLE inline QString getP2f10b() { return this->p2f10b; }
    Q_INVOKABLE inline QString getP2f11b() { return this->p2f11b; }
    Q_INVOKABLE inline QString getP2f12() { return this->p2f12; }
    Q_INVOKABLE inline QString getP3f1() { return this->p3f1; }
    Q_INVOKABLE inline QString getP3f2() { return this->p3f2; }
    Q_INVOKABLE inline QString getP3f3() { return this->p3f3; }
    Q_INVOKABLE inline QString getP3f4() { return this->p3f4; }
    Q_INVOKABLE inline QString getP3f5() { return this->p3f5; }
    Q_INVOKABLE inline QString getP3f6() { return this->p3f6; }
    Q_INVOKABLE inline QString getP3f7t() { return this->p3f7t; }
    Q_INVOKABLE inline QString getP3f8t() { return this->p3f8t; }
    Q_INVOKABLE inline QString getP3f9t() { return this->p3f9t; }
    Q_INVOKABLE inline QString getP3f10t() { return this->p3f10t; }
    Q_INVOKABLE inline QString getP3f11t() { return this->p3f11t; }
    Q_INVOKABLE inline QString getP3f7b() { return this->p3f7b; }
    Q_INVOKABLE inline QString getP3f8b() { return this->p3f8b; }
    Q_INVOKABLE inline QString getP3f9b() { return this->p3f9b; }
    Q_INVOKABLE inline QString getP3f10b() { return this->p3f10b; }
    Q_INVOKABLE inline QString getP3f11b() { return this->p3f11b; }
    Q_INVOKABLE inline QString getP3f12() { return this->p3f12; }

    Q_INVOKABLE inline void setId (qulonglong v) { this->id = v; emit idChanged(v); }
    Q_INVOKABLE inline void setP0f1 (QString v) { this->p0f1 = v; emit p0f1Changed(v); }
    Q_INVOKABLE inline void setP0f2 (QString v) { this->p0f2 = v; emit p0f2Changed(v); }
    Q_INVOKABLE inline void setP0f3 (QString v) { this->p0f3 = v; emit p0f3Changed(v); }
    Q_INVOKABLE inline void setP0f4 (QString v) { this->p0f4 = v; emit p0f4Changed(v); }
    Q_INVOKABLE inline void setP0f5 (QString v) { this->p0f5 = v; emit p0f5Changed(v); }
    Q_INVOKABLE inline void setP0f6 (QString v) { this->p0f6 = v; emit p0f6Changed(v); }
    Q_INVOKABLE inline void setP0f7 (QString v) { this->p0f7 = v; emit p0f7Changed(v); }
    Q_INVOKABLE inline void setP1f1 (QString v) { this->p1f1 = v; emit p1f1Changed(v); }
    Q_INVOKABLE inline void setP1f2 (QString v) { this->p1f2 = v; emit p1f2Changed(v); }
    Q_INVOKABLE inline void setP1f3 (QString v) { this->p1f3 = v; emit p1f3Changed(v); }
    Q_INVOKABLE inline void setP1f4 (QString v) { this->p1f4 = v; emit p1f4Changed(v); }
    Q_INVOKABLE inline void setP1f5 (QString v) { this->p1f5 = v; emit p1f5Changed(v); }
    Q_INVOKABLE inline void setP1f6 (QString v) { this->p1f6 = v; emit p1f6Changed(v); }
    Q_INVOKABLE inline void setP1f7 (QString v) { this->p1f7 = v; emit p1f7Changed(v); }
    Q_INVOKABLE inline void setP1f8 (QString v) { this->p1f8 = v; emit p1f8Changed(v); }
    Q_INVOKABLE inline void setP1f9 (QString v) { this->p1f9 = v; emit p1f9Changed(v); }
    Q_INVOKABLE inline void setP1f10 (QString v) { this->p1f10 = v; emit p1f10Changed(v); }
    Q_INVOKABLE inline void setP2f1 (QString v) { this->p2f1 = v; emit p2f1Changed(v); }
    Q_INVOKABLE inline void setP2f2 (QString v) { this->p2f2 = v; emit p2f2Changed(v); }
    Q_INVOKABLE inline void setP2f3 (QString v) { this->p2f3 = v; emit p2f3Changed(v); }
    Q_INVOKABLE inline void setP2f4 (QString v) { this->p2f4 = v; emit p2f4Changed(v); }
    Q_INVOKABLE inline void setP2f5 (QString v) { this->p2f5 = v; emit p2f5Changed(v); }
    Q_INVOKABLE inline void setP2f6 (QString v) { this->p2f6 = v; emit p2f6Changed(v); }
    Q_INVOKABLE inline void setP2f7t (QString v) { this->p2f7t = v; emit p2f7tChanged(v); }
    Q_INVOKABLE inline void setP2f8t (QString v) { this->p2f8t = v; emit p2f8tChanged(v); }
    Q_INVOKABLE inline void setP2f9t (QString v) { this->p2f9t = v; emit p2f9tChanged(v); }
    Q_INVOKABLE inline void setP2f10t (QString v) { this->p2f10t = v; emit p2f10tChanged(v); }
    Q_INVOKABLE inline void setP2f11t (QString v) { this->p2f11t = v; emit p2f11tChanged(v); }
    Q_INVOKABLE inline void setP2f7b (QString v) { this->p2f7b = v; emit p2f7bChanged(v); }
    Q_INVOKABLE inline void setP2f8b (QString v) { this->p2f8b = v; emit p2f8bChanged(v); }
    Q_INVOKABLE inline void setP2f9b (QString v) { this->p2f9b = v; emit p2f9bChanged(v); }
    Q_INVOKABLE inline void setP2f10b (QString v) { this->p2f10b = v; emit p2f10bChanged(v); }
    Q_INVOKABLE inline void setP2f11b (QString v) { this->p2f11b = v; emit p2f11bChanged(v); }
    Q_INVOKABLE inline void setP2f12 (QString v) { this->p2f12 = v; emit p2f12Changed(v); }
    Q_INVOKABLE inline void setP3f1 (QString v) { this->p3f1 = v; emit p3f1Changed(v); }
    Q_INVOKABLE inline void setP3f2 (QString v) { this->p3f2 = v; emit p3f2Changed(v); }
    Q_INVOKABLE inline void setP3f3 (QString v) { this->p3f3 = v; emit p3f3Changed(v); }
    Q_INVOKABLE inline void setP3f4 (QString v) { this->p3f4 = v; emit p3f4Changed(v); }
    Q_INVOKABLE inline void setP3f5 (QString v) { this->p3f5 = v; emit p3f5Changed(v); }
    Q_INVOKABLE inline void setP3f6 (QString v) { this->p3f6 = v; emit p3f6Changed(v); }
    Q_INVOKABLE inline void setP3f7t (QString v) { this->p3f7t = v; emit p3f7tChanged(v); }
    Q_INVOKABLE inline void setP3f8t (QString v) { this->p3f8t = v; emit p3f8tChanged(v); }
    Q_INVOKABLE inline void setP3f9t (QString v) { this->p3f9t = v; emit p3f9tChanged(v); }
    Q_INVOKABLE inline void setP3f10t (QString v) { this->p3f10t = v; emit p3f10tChanged(v); }
    Q_INVOKABLE inline void setP3f11t (QString v) { this->p3f11t = v; emit p3f11tChanged(v); }
    Q_INVOKABLE inline void setP3f7b (QString v) { this->p3f7b = v; emit p3f7bChanged(v); }
    Q_INVOKABLE inline void setP3f8b (QString v) { this->p3f8b = v; emit p3f8bChanged(v); }
    Q_INVOKABLE inline void setP3f9b (QString v) { this->p3f9b = v; emit p3f9bChanged(v); }
    Q_INVOKABLE inline void setP3f10b (QString v) { this->p3f10b = v; emit p3f10bChanged(v); }
    Q_INVOKABLE inline void setP3f11b (QString v) { this->p3f11b = v; emit p3f11bChanged(v); }
    Q_INVOKABLE inline void setP3f12 (QString v) { this->p3f12 = v; emit p3f12Changed(v); }

signals:
    void idChanged(qulonglong);
    void p0f1Changed(QString);
    void p0f2Changed(QString);
    void p0f3Changed(QString);
    void p0f4Changed(QString);
    void p0f5Changed(QString);
    void p0f6Changed(QString);
    void p0f7Changed(QString);
    void p1f1Changed(QString);
    void p1f2Changed(QString);
    void p1f3Changed(QString);
    void p1f4Changed(QString);
    void p1f5Changed(QString);
    void p1f6Changed(QString);
    void p1f7Changed(QString);
    void p1f8Changed(QString);
    void p1f9Changed(QString);
    void p1f10Changed(QString);
    void p2f1Changed(QString);
    void p2f2Changed(QString);
    void p2f3Changed(QString);
    void p2f4Changed(QString);
    void p2f5Changed(QString);
    void p2f6Changed(QString);
    void p2f7tChanged(QString);
    void p2f8tChanged(QString);
    void p2f9tChanged(QString);
    void p2f10tChanged(QString);
    void p2f11tChanged(QString);
    void p2f7bChanged(QString);
    void p2f8bChanged(QString);
    void p2f9bChanged(QString);
    void p2f10bChanged(QString);
    void p2f11bChanged(QString);
    void p2f12Changed(QString);
    void p3f1Changed(QString);
    void p3f2Changed(QString);
    void p3f3Changed(QString);
    void p3f4Changed(QString);
    void p3f5Changed(QString);
    void p3f6Changed(QString);
    void p3f7tChanged(QString);
    void p3f8tChanged(QString);
    void p3f9tChanged(QString);
    void p3f10tChanged(QString);
    void p3f11tChanged(QString);
    void p3f7bChanged(QString);
    void p3f8bChanged(QString);
    void p3f9bChanged(QString);
    void p3f10bChanged(QString);
    void p3f11bChanged(QString);
    void p3f12Changed(QString);

private:
    qulonglong id;
    QString p0f1;
    QString p0f2;
    QString p0f3;
    QString p0f4;
    QString p0f5;
    QString p0f6;
    QString p0f7;
    QString p1f1;
    QString p1f2;
    QString p1f3;
    QString p1f4;
    QString p1f5;
    QString p1f6;
    QString p1f7;
    QString p1f8;
    QString p1f9;
    QString p1f10;
    QString p2f1;
    QString p2f2;
    QString p2f3;
    QString p2f4;
    QString p2f5;
    QString p2f6;
    QString p2f7t;
    QString p2f8t;
    QString p2f9t;
    QString p2f10t;
    QString p2f11t;
    QString p2f7b;
    QString p2f8b;
    QString p2f9b;
    QString p2f10b;
    QString p2f11b;
    QString p2f12;
    QString p3f1;
    QString p3f2;
    QString p3f3;
    QString p3f4;
    QString p3f5;
    QString p3f6;
    QString p3f7t;
    QString p3f8t;
    QString p3f9t;
    QString p3f10t;
    QString p3f11t;
    QString p3f7b;
    QString p3f8b;
    QString p3f9b;
    QString p3f10b;
    QString p3f11b;
    QString p3f12;

signals:

};

#endif // PARASPARAS_H
