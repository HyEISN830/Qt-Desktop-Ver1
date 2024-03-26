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
#include <QNetworkAccessManager>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QXmlStreamReader>
#include <QTextDocument>
#include <QJsonArray>
#include <QJsonDocument>


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
    Q_INVOKABLE void addAppLog(QString content, int level);
    Q_INVOKABLE QString html2PlainText(QString);
    Q_INVOKABLE QString str2bytes(QString);
    Q_INVOKABLE QByteArray str2bytes1(QString);
    Q_INVOKABLE short bytes2int(uint8_t b, uint8_t b1);
    Q_INVOKABLE ushort bytes2uint(uint8_t b, uint8_t b1);
    Q_INVOKABLE int bytes2int(uint8_t b, uint8_t b1, uint8_t b2, uint8_t b3);
    Q_INVOKABLE float bytes2float(uint8_t b, uint8_t b1, uint8_t b2, uint8_t b3);
    Q_INVOKABLE QJsonArray bytes2jarr(QByteArray);

private:
    QSettings *settings = nullptr;
    QNetworkAccessManager *manager = nullptr;

signals:

};

#endif // QMLSERVICE_H
