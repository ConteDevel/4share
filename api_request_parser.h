#ifndef APIREQUESTPARSER_H
#define APIREQUESTPARSER_H

#include <QRegExp>

#include "qhttprequest.h"

#include "api_commands.h"

class ApiCommand;
class ApiRequestParser
{
public:
    ApiRequestParser();
    ApiCommand* parseRequest(QHttpRequest* request);

private:
    // routes
    // system volume expressions
    const QRegExp expVolumeSet_ = QRegExp("^/system/volume/set/([0-9]+)$");
    const QRegExp expVolumeTurnUp_ = QRegExp("^/system/volume/up/([0-9]+)$");
    const QRegExp expVolumeTurnDown_ = QRegExp("^/system/volume/down/([0-9]+)$");
    const QRegExp expVolumeMute_ = QRegExp("^/system/volume/mute/$");
    const QRegExp expVolumeUnmute_ = QRegExp("^/system/volume/unmute/$");
    // file system expressions
    const QRegExp expFsFilesCopy_ = QRegExp("^/files/copy$");
    const QRegExp expFsFilesList_ = QRegExp("^/files/list$");
};

#endif // APIREQUESTPARSER_H
