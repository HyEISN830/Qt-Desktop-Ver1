#include "qmlservice.h"

QmlService::QmlService()
{
    settings = new QSettings;
    manager = new QNetworkAccessManager;
}

QmlService::~QmlService()
{
    delete settings;
    delete manager;
}

bool QmlService::openurlwithbrowser(QString url)
{
    return QDesktopServices::openUrl(url);
}

void QmlService::copy2clipboard(QString content)
{
    QGuiApplication::clipboard()->setText(content);
}

QVariant QmlService::takeSetting(QString key)
{
    if (!settings)
        return "Invalid Object.";
    return settings->value(key);
}

void QmlService::saveSettings(QString key, QString value)
{
    if (!settings) return;
    settings->setValue(key, value);
    settings->sync();
}

bool QmlService::testTcpConn(QString host, int port)
{
    QTcpSocket tcp;
    bool ok = false;

    tcp.connectToHost(host, port);
    ok = tcp.waitForConnected(5000);    // timeout of 5 seconds
    tcp.disconnectFromHost();

    return ok;
}

bool QmlService::saveContent2Log(QString name, QString content)
{
    QDir dir("");
    if (!dir.exists("log")) dir.mkdir("log");
    QFile file("log/" + name.replace(":", "_"));
    file.open(QFile::ReadWrite);
    QTextStream in(&file);
    in << content;
    file.close();
    return true;
}

void QmlService::addAppLog(QString content, int level)
{
    QUrl url = takeSetting("appLogURL").toString().trimmed();

    if (url.toString().length())
    {
        QUrlQuery query;

        query.addQueryItem("content", content);
        query.addQueryItem("level", QString::number(level));
        url.setQuery(query);

        QNetworkReply *reply = manager->get(QNetworkRequest(url));

        if (reply)
            reply->deleteLater();
    }
}

QString QmlService::html2PlainText(QString content)
{
    QTextDocument textDocument;
    textDocument.setHtml(content);
    return textDocument.toPlainText();
}
