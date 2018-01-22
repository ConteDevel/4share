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
    if (!guiController.initialize())
        return -1;

    const QString defaultRootDir = "/home/anastasia/tp/cpp/mydir";

    ApiController apiController;
    SystemManager systemController;
    FileSystemManager fileSystemController(defaultRootDir);

    // connection GUI controller signals to slots
    QObject::connect(&guiController, &GuiController::portChanged,
                        &apiController, &ApiController::onPortChangedRestart);
    QObject::connect(&guiController, &GuiController::rootDirPathChanged,
                        &fileSystemController, &FileSystemManager::onRootDirChanged);
    // connection logger signals to slots
    QObject::connect(Logger::Instance(), &Logger::newLogMsg,
                        &guiController, &GuiController::onNewLogMsg);
    QObject::connect(Logger::Instance(), &Logger::newErrorLogMsg,
                        &guiController, &GuiController::onNewErrorLogMsg);
    // connecting web controller signals to slots
    QObject::connect(&apiController, &ApiController::volumeSetValue,
                         &systemController, &SystemManager::setVolumeValue);
    QObject::connect(&apiController, &ApiController::volumeTurnValue,
                         &systemController, &SystemManager::turnVolumeValue);
    QObject::connect(&apiController, &ApiController::volumeSetIsMute,
                         &systemController, &SystemManager::setVolumeIsMute);
    // connectiong web api signals to slots
    QObject::connect(&apiController, &ApiController::fsGetFilesList,
                        &fileSystemController, &FileSystemManager::getFilesList);
    QObject::connect(&apiController, &ApiController::fsCopyFiles,
                        &fileSystemController, &FileSystemManager::copyFiles);

    guiController.updateServerPortField(apiController.getCurrentPort());
    guiController.updateRootDirPathField(defaultRootDir);

    apiController.startListen();

    const int retVal = app.exec();

    // cleaning up
    Logger::Destroy();

    return retVal;
}
