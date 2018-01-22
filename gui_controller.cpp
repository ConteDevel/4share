#include "gui_controller.h"

#include <QDebug>
#include <QQmlContext>

#include "logger.h"

GuiController::GuiController(QObject *parent) : QObject(parent)
{

}

bool GuiController::initialize()
{
    engine_.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine_.rootObjects().isEmpty())
        return false;
    rootAppWindow_ = engine_.rootObjects()[0];

    // connection QML signals to GUI controller slots
    QObject::connect(rootAppWindow_, SIGNAL(signalServerPortChanged(QString)),
                        this, SLOT(onServerPortChanged(QString)));
    QObject::connect(rootAppWindow_, SIGNAL(signalRootDirPathChanged(QString)),
                        this, SLOT(onRootDirPathChanged(QString)));

    updateLogListModel();
    return true;
}

void GuiController::updateLogListModel()
{
    engine_.rootContext()->setContextProperty("listModel", QVariant::fromValue(logListModel_));
}

void GuiController::displayErrorMsg(QString errorMsg)
{
    QObject* messageDialog = rootAppWindow_->findChild<QObject*>("obj_mderror");
    if(!messageDialog)
    {
        qDebug() << "Failed to find textfieldPort object!";
        return;
    }
    QVariant msg(errorMsg);
    QMetaObject::invokeMethod(messageDialog, "displayErrorDialog",
            Q_ARG(QVariant, msg));
}

void GuiController::onServerPortChanged(const QString &newPort)
{
    qDebug() << "New server port from gui: " << newPort;
    bool isIntegerNewPort = false;
    int port = newPort.toInt(&isIntegerNewPort);
    if (isIntegerNewPort) {
        qDebug() << "Port is ok";
        emit portChanged(port);
    }
}

void GuiController::onRootDirPathChanged(const QString &newPath)
{
    qDebug() << "New root dir path from gui: " << newPath;
    // TODO: validation
    emit rootDirPathChanged(newPath);
}

void GuiController::onNewLogMsg(QString logMsg)
{
    qDebug() << "New log msg: " << logMsg;
    logListModel_.insert(0, logMsg);
    updateLogListModel();
}

void GuiController::onNewErrorLogMsg(QString logMsg, QString errorMsg)
{
    qDebug() << "New error log msg: " << logMsg;
    logListModel_.insert(0, logMsg);
    displayErrorMsg(errorMsg);
    updateLogListModel();
}

void GuiController::updateServerPortField(int port)
{
    QObject* textFieldPort = rootAppWindow_->findChild<QObject*>("obj_textfieldport");
    if(!textFieldPort)
    {
        qDebug() << "Failed to find textfieldPort object!";
        return;
    }
    textFieldPort->setProperty("text", QString::number(port));
}

void GuiController::updateRootDirPathField(QString path)
{
    qDebug() << "updateRootDirPathField";
    QObject* textFieldPath = rootAppWindow_->findChild<QObject*>("obj_textfieldpath");
    if(!textFieldPath)
    {
        qDebug() << "Failed to find textfieldPath object!";
        return;
    }
    textFieldPath->setProperty("text", QString(path));
}

