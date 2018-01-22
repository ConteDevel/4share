#include "api_commands.h"

QVariant ApiCommand::getReturnedData()
{
    return data_;
}

void ApiCommand::setReturnedData(QVariant data)
{
    data_ = data;
}

VolumeMuteCommand::VolumeMuteCommand(bool isMute)
    : isMute_(isMute)
{
}

bool VolumeMuteCommand::execute(ApiController& apiController)
{
    emit apiController.volumeSetIsMute(isMute_);
    QString action;
    if (isMute_) {
        action = "mute";
    }
    else {
        action = "unmute";
    }
    data_ = "Volume is " + action;
    return true;
}

VolumeSetValueCommand::VolumeSetValueCommand(int value)
    : value_(value)
{
}

bool VolumeSetValueCommand::execute(ApiController &apiController)
{
    emit apiController.volumeSetValue(value_);
    data_ = QString("Volume set to %1!").arg(value_);
    return true;
}

VolumeTurnValueCommand::VolumeTurnValueCommand(bool isTurnUp, int value)
    : isTurnUp_(isTurnUp), value_(value)
{
}

bool VolumeTurnValueCommand::execute(ApiController &apiController)
{
    emit apiController.volumeTurnValue(isTurnUp_, value_);
    data_ = QString("Volume turn up for %1!").arg(value_);
    return true;
}
