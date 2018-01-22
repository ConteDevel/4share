#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "api_controller.h"
#include "system_manager.h"
#include "filesystem_manager.h"
#include "gui_controller.h"
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

    ApiController ApiController;
    SystemManager systemController;
    FileSystemManager fileSystemController(defaultRootDir);

    // connection GUI controller signals to slots
    QObject::connect(&guiController, &GuiController::portChanged,
                        &ApiController, &ApiController::onPortChangedRestart);
    QObject::connect(&guiController, &GuiController::rootDirPathChanged,
                        &fileSystemController, &FileSystemManager::onRootDirChanged);
    // connection logger signals to slots
    QObject::connect(Logger::Instance(), &Logger::newLogMsg,
                        &guiController, &GuiController::onNewLogMsg);
    QObject::connect(Logger::Instance(), &Logger::newErrorLogMsg,
                        &guiController, &GuiController::onNewErrorLogMsg);
    // connecting web controller signals to slots
    QObject::connect(&ApiController, &ApiController::volumeSetValue,
                         &systemController, &SystemManager::setVolumeValue);
    QObject::connect(&ApiController, &ApiController::volumeTurnValue,
                         &systemController, &SystemManager::turnVolumeValue);
    QObject::connect(&ApiController, &ApiController::volumeSetIsMute,
                         &systemController, &SystemManager::setVolumeIsMute);
    // connectiong web api signals to slots
    QObject::connect(&ApiController, &ApiController::fsGetFilesList,
                        &fileSystemController, &FileSystemManager::getFilesList);
    QObject::connect(&ApiController, &ApiController::fsCopyFiles,
                        &fileSystemController, &FileSystemManager::copyFiles);

    guiController.updateServerPortField(ApiController.getCurrentPort());
    guiController.updateRootDirPathField(defaultRootDir);

    ApiController.startListen();

    const int retVal = app.exec();

    // cleaning up
    Logger::Destroy();

    return retVal;
}
