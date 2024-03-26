#include "qmlservice.h"

QmlService::QmlService()
{
    settings = new QSettings("TEN-IRON-Scheduling");
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

QString QmlService::str2bytes(QString str)
{
    QByteArray arr = str.toLatin1();
    QJsonArray jarr;
    for (int var = 0; var < arr.size(); ++var)
        jarr.append((uint8_t)arr[var]);
    return QJsonDocument(jarr).toJson();
}

QByteArray QmlService::str2bytes1(QString str)
{
    return str.toLatin1();
}

short QmlService::bytes2int(uint8_t b, uint8_t b1)
{
    short s = b;
    s <<= 8;
    s |= b1;
    return s;
}

ushort QmlService::bytes2uint(uint8_t b, uint8_t b1)
{
    // ushort u = 5005;

    // uint8_t ub = u >> 8;
    // uint8_t ub1 = u & 0xFF;
    // qDebug() << ub << ub1;

    // ushort u1 = ub << 8 | ub1;
    // qDebug() << u1;

    ushort s = b << 8 | b1;
    return s;
}

int QmlService::bytes2int(uint8_t b, uint8_t b1, uint8_t b2, uint8_t b3)
{
    return int((unsigned char)(b) << 24 |
               (unsigned char)(b1) << 16 |
               (unsigned char)(b2) << 8 |
               (unsigned char)(b3));
}

float QmlService::bytes2float(uint8_t b, uint8_t b1, uint8_t b2, uint8_t b3)
{
    QByteArray d;
    d.append(b);
    d.append(b1);
    d.append(b2);
    d.append(b3);
    return d.toFloat();
}

QJsonArray QmlService::bytes2jarr(QByteArray bytes)
{
    QJsonArray jarr;
    for (int var = 0; var < bytes.size(); ++var) {
        jarr.append((uint8_t)bytes[var]);
    }
    return jarr;
}
