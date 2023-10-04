#ifndef QMLSERVICE_H
#define QMLSERVICE_H

#include <QObject>
#include <QQuickItem>
#include <QClipboard>
#include <QGuiApplication>
#include <QDesktopServices>
#include <QSettings>
#include <QTcpSocket>
#include <QFile>
#include <QDir>


// qml 一般后台服务, 如append 到 剪贴板, 打开浏览器等..
class QmlService : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT
public:
    QmlService();
    ~QmlService();

    Q_INVOKABLE bool openurlwithbrowser(QString);
    Q_INVOKABLE void copy2clipboard(QString);
    Q_INVOKABLE QVariant takeSetting(QString key);
    Q_INVOKABLE void saveSettings(QString key, QString value);
    Q_INVOKABLE bool testTcpConn(QString host, int port);
    Q_INVOKABLE bool saveContent2Log(QString name, QString content);

private:
    QSettings *settings = nullptr;

signals:

};

#endif // QMLSERVICE_H
