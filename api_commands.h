#ifndef API_COMMANDS_H
#define API_COMMANDS_H

#include <QObject>
#include <QVariant>

#include "api_controller.h"

class ApiController;
class ApiCommand
{
public:
    virtual bool execute(ApiController& apiController) = 0;
    QVariant getReturnedData();

protected:
    void setReturnedData(QVariant data);

    QVariant data_;
};

class VolumeMuteCommand : public ApiCommand
{
public:
    explicit VolumeMuteCommand(bool isMute = true);
    virtual bool execute(ApiController& apiController);

protected:
    bool isMute_;
};

class VolumeSetValueCommand : public ApiCommand
{
public:
    explicit VolumeSetValueCommand(int value = 0);
    virtual bool execute(ApiController& apiController);

protected:
    int value_;
};

class VolumeTurnValueCommand : public ApiCommand
{
public:
    explicit VolumeTurnValueCommand(bool isTurnUp, int value = 0);
    virtual bool execute(ApiController& apiController);

protected:
    bool isTurnUp_;
    int value_;
};

#endif // API_COMMANDS_H
