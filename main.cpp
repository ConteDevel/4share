#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "webapicontroller.h"
#include "systemcontroller.h"
#include "filesystemcontroller.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    QString defRoot = "/home/anastasia/tp/cpp/mydir";

    WebApiController webApiController;
    SystemController systemController;
    FileSystemController fileSystemController(defRoot);

    // connecting web api signals to control system slots
    QObject::connect(&webApiController, &WebApiController::volumeSetValue,
                         &systemController, &SystemController::setVolumeValue);
    QObject::connect(&webApiController, &WebApiController::volumeTurnValue,
                         &systemController, &SystemController::turnVolumeValue);
    QObject::connect(&webApiController, &WebApiController::volumeSetIsMute,
                         &systemController, &SystemController::setVolumeIsMute);
    // connectiong web api signals to file system slots
    QObject::connect(&webApiController, &WebApiController::fsGetList,
                        &fileSystemController, &FileSystemController::getFilesList);

    return app.exec();
}
