#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTime>
#include <QDateTime>


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    app.setOrganizationName("AOS");
    app.setOrganizationDomain("HyEISN.AOS");
    app.setApplicationName("AOS");

    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
    engine.addImportPath(":/");
    engine.loadFromModule("AC_OU_CMS", "Main");

    return app.exec();
}
