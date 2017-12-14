#include "systemcontroller.h".h"

#include <QProcess>
#include <QDebug>

SystemController::SystemController()
{

}

void SystemController::setVolumeValue(int value)
{
    QString command = QString("amixer -D pulse sset Master %1\%").arg(value);
    qDebug() << "System command: " << command;
    QProcess::execute(command);
}

void SystemController::turnVolumeValue(bool isTurnUp, int value)
{
    QString sign;
    if (isTurnUp)
        sign = "+";
    else
        sign = "-";
    QString command = QString("amixer -D pulse sset Master %1\%%2").arg(value).arg(sign);
    qDebug() << "System command: " << command;
    QProcess::execute(command);
}

void SystemController::setVolumeIsMute(bool isMute)
{
    QString value;
    if (isMute)
        value = "mute";
    else
        value = "unmute";
    QString command = QString("amixer -D pulse sset Master %1").arg(value);
    qDebug() << "System command: " << command;
    QProcess::execute(command);
}
