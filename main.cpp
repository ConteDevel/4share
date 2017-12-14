#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "webapicontroller.h"
#include "systemcontroller.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    WebApiController webApiController;
    SystemController systemController;

    // Connect web api signals to system slots
    QObject::connect(&webApiController, &WebApiController::volumeSetValue,
                         &systemController, &SystemController::setVolumeValue);
    QObject::connect(&webApiController, &WebApiController::volumeTurnValue,
                         &systemController, &SystemController::turnVolumeValue);
    QObject::connect(&webApiController, &WebApiController::volumeSetIsMute,
                         &systemController, &SystemController::setVolumeIsMute);

    return app.exec();
}
