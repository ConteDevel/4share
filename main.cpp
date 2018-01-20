#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "webapicontroller.h"
#include "systemcontroller.h"
#include "filesystemcontroller.h"
#include "guicontroller.h"
#include "logger.h"
#include "QDebug"
#include "QQmlContext"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    GuiController guiController(nullptr);
    if (!guiController.initialize()) {
        return -1;
    }

    const QString defaultRootDir = "/home/anastasia/tp/cpp/mydir";

    WebApiController webApiController;
    SystemController systemController;
    FileSystemController fileSystemController(defaultRootDir);

    // connection gui controller signals to slots
    QObject::connect(&guiController, &GuiController::portChanged,
                        &webApiController, &WebApiController::onPortChangedRestart);
    // connection logger signals to slots
    QObject::connect(Logger::Instance(), &Logger::newLogMsg,
                        &guiController, &GuiController::onNewLogMsg);
    // connecting web controller signals to slots
    QObject::connect(&webApiController, &WebApiController::volumeSetValue,
                         &systemController, &SystemController::setVolumeValue);
    QObject::connect(&webApiController, &WebApiController::volumeTurnValue,
                         &systemController, &SystemController::turnVolumeValue);
    QObject::connect(&webApiController, &WebApiController::volumeSetIsMute,
                         &systemController, &SystemController::setVolumeIsMute);
    // connectiong web api signals to slots
    QObject::connect(&webApiController, &WebApiController::fsGetFilesList,
                        &fileSystemController, &FileSystemController::getFilesList);
    QObject::connect(&webApiController, &WebApiController::fsCopyFiles,
                        &fileSystemController, &FileSystemController::copyFiles);

    guiController.updateServerPortField(webApiController.getCurrentPort());
    webApiController.startListen();

    const int retVal = app.exec();

    // cleaning up
    Logger::Destroy();

    return retVal;
}
