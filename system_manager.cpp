#include "system_manager.h"

#include <QProcess>
#include <QDebug>

#include "logger.h"

SystemManager::SystemManager()
{

}

void SystemManager::setVolumeValue(int value)
{
    QString command = QString("amixer -D pulse sset Master %1\%").arg(value);
    qDebug() << "System command: " << command;
    QProcess::execute(command);
    Logger::Instance()->logMsg(QString("Громкость установлена на: %1\%").arg(value));
}

void SystemManager::turnVolumeValue(bool isTurnUp, int value)
{
    QString sign;
    if (isTurnUp)
        sign = "+";
    else
        sign = "-";
    QString command = QString("amixer -D pulse sset Master %1\%%2").arg(value).arg(sign);
    qDebug() << "System command: " << command;
    QProcess::execute(command);
    Logger::Instance()->logMsg(QString("Громкость изменена на: %1%2\%").arg(sign).arg(value));
}

void SystemManager::setVolumeIsMute(bool isMute)
{
    QString value;
    if (isMute)
        value = "mute";
    else
        value = "unmute";
    QString command = QString("amixer -D pulse sset Master %1").arg(value);
    qDebug() << "System command: " << command;
    QProcess::execute(command);
    Logger::Instance()->logMsg(QString("Громкость изменена на: %1").arg(value));
}
