#ifndef QMLSERVICE_H
#define QMLSERVICE_H

#include <QObject>
#include <QQuickItem>
#include <QClipboard>
#include <QGuiApplication>
#include <QDesktopServices>

// qml 一般后台服务, 如append 到 剪贴板, 打开浏览器等..
class QmlService : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT
public:
    QmlService();

    Q_INVOKABLE bool openurlwithbrowser(QString);
    Q_INVOKABLE void copy2clipboard(QString);

signals:

};

#endif // QMLSERVICE_H
