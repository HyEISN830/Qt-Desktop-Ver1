#ifndef BASEENTITY_H
#define BASEENTITY_H

#include <QObject>
#include <QQuickItem>
#include <QSqlRecord>

class BaseEntity : public virtual QObject
{
    Q_OBJECT
public:
    BaseEntity fromRecord(QSqlRecord);

signals:

};

#endif // BASEENTITY_H
