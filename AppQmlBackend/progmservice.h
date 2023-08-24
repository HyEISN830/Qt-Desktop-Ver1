#ifndef PROGMSERVICE_H
#define PROGMSERVICE_H

#include <QObject>
#include <QQuickItem>
#include <QThreadPool>
#include <QDesktopServices>

/*  应用程序qml backend, 可用于:
 *   1. 程序启动前, 做些事
 *   2. 程序关闭后, 做些事
 *  以上等需要特殊处理的场景, 都可使用或修改此类
*/
class ProgmService : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT
public:
    ProgmService();

    Q_INVOKABLE void closethreadpool(); // 关闭全局线程池, 停止所有正在工作的线程, 防止应用程序未退出

signals:

};

#endif // PROGMSERVICE_H
