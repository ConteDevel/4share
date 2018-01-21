#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "webapicontroller.h"
#include "systemmanager.h"
#include "filesystemmanager.h"
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
    SystemManager systemController;
    FileSystemManager fileSystemController(defaultRootDir);

    // connection GUI controller signals to slots
    QObject::connect(&guiController, &GuiController::portChanged,
                        &webApiController, &WebApiController::onPortChangedRestart);
    QObject::connect(&guiController, &GuiController::rootDirPathChanged,
                        &fileSystemController, &FileSystemManager::onRootDirChanged);
    // connection logger signals to slots
    QObject::connect(Logger::Instance(), &Logger::newLogMsg,
                        &guiController, &GuiController::onNewLogMsg);
    // connecting web controller signals to slots
    QObject::connect(&webApiController, &WebApiController::volumeSetValue,
                         &systemController, &SystemManager::setVolumeValue);
    QObject::connect(&webApiController, &WebApiController::volumeTurnValue,
                         &systemController, &SystemManager::turnVolumeValue);
    QObject::connect(&webApiController, &WebApiController::volumeSetIsMute,
                         &systemController, &SystemManager::setVolumeIsMute);
    // connectiong web api signals to slots
    QObject::connect(&webApiController, &WebApiController::fsGetFilesList,
                        &fileSystemController, &FileSystemManager::getFilesList);
    QObject::connect(&webApiController, &WebApiController::fsCopyFiles,
                        &fileSystemController, &FileSystemManager::copyFiles);

    guiController.updateServerPortField(webApiController.getCurrentPort());
    guiController.updateRootDirPathField(defaultRootDir);

    webApiController.startListen();

    const int retVal = app.exec();

    // cleaning up
    Logger::Destroy();

    return retVal;
}
