#include "qmlservice.h"

QmlService::QmlService()
{
    settings = new QSettings;
}

QmlService::~QmlService()
{
    delete settings;
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
