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

    QObject::connect(rootAppWindow_, SIGNAL(signalServerPortChanged(QString)),
                        this, SLOT(onServerPortChanged(QString)));

    updateLogListModel();
    return true;
}

void GuiController::updateLogListModel()
{
    engine_.rootContext()->setContextProperty("listModel", QVariant::fromValue(logListModel_));
}

void GuiController::onServerPortChanged(const QString &newPort)
{
    qDebug() << "New port from gui: " << newPort;
    bool isIntegerNewPort = false;
    int port = newPort.toInt(&isIntegerNewPort);
    if (isIntegerNewPort) {
        qDebug() << "Port is ok";
        emit portChanged(port);
    }
}

void GuiController::onNewLogMsg(const QString msg)
{
    qDebug() << "New log msg: " << msg;
    logListModel_.append(msg);
    updateLogListModel();
}

void GuiController::updateServerPortField(const int port)
{
    qDebug() << "onServerPortUpdated";
    QObject* textFieldPort = rootAppWindow_->findChild<QObject*>("obj_textfieldport");
    if(!textFieldPort)
    {
        qDebug() << "Failed to find textfieldPort object!";
        return;
    }
    textFieldPort->setProperty("text", QString::number(port));
}

