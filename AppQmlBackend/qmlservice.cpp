#include "qmlservice.h"

QmlService::QmlService()
{

}

bool QmlService::openurlwithbrowser(QString url)
{
    return QDesktopServices::openUrl(url);
}

void QmlService::copy2clipboard(QString content)
{
    QGuiApplication::clipboard()->setText(content);
}
