#include "guicontroller.h"

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

void GuiController::onNewLogMsg(const QString msg)
{
    qDebug() << "New log msg: " << msg;
    logListModel_.append(msg);
    updateLogListModel();
}

void GuiController::updateServerPortField(const int port)
{
    QObject* textFieldPort = rootAppWindow_->findChild<QObject*>("obj_textfieldport");
    if(!textFieldPort)
    {
        qDebug() << "Failed to find textfieldPort object!";
        return;
    }
    textFieldPort->setProperty("text", QString::number(port));
}

void GuiController::updateRootDirPathField(const QString path)
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

