#include "api_request_parser.h"
#include "logger.h"

ApiRequestParser::ApiRequestParser()
{

}

ApiCommand* ApiRequestParser::parseRequest(QHttpRequest *req)
{
    ApiCommand* command = nullptr;

    Logger::Instance()->logMsg("Новый HTTP запрос: " + req->path());
    if( expVolumeSet_.indexIn(req->path()) != -1 )
    {
        int value = (expVolumeSet_.capturedTexts()[1]).toInt();
        command = new VolumeSetValueCommand(value);
    }
    else if( expVolumeTurnUp_.indexIn(req->path()) != -1 )
    {
        int value = (expVolumeTurnUp_.capturedTexts()[1]).toInt();
        command = new VolumeTurnValueCommand(true, value);
    }
    else if( expVolumeTurnDown_.indexIn(req->path()) != -1 )
    {
        int value = (expVolumeTurnDown_.capturedTexts()[1]).toInt();
        command = new VolumeTurnValueCommand(false, value);
    }
    else if( expVolumeMute_.indexIn(req->path()) != -1 )
    {
        command = new VolumeMuteCommand(true);
    }
    else if( expVolumeUnmute_.indexIn(req->path()) != -1 )
    {
        command = new VolumeMuteCommand(false);
    }
    else if( expFsFilesList_.indexIn(req->path()) != -1 )
    {
        command = new GetFileListCommand();
    }

    return command;
}
