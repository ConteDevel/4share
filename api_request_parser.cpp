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
/*
        QStringList filesList;
        emit fsGetFilesList(filesList);

        QJsonArray jsonArray;
        for (int i = 0; i < filesList.size(); ++i)
        {
            QJsonObject jsonObj;
            jsonObj["fileName"] = filesList[i];
            jsonArray.append(jsonObj);
        }
        QJsonDocument jsonDoc;
        jsonDoc.setArray(jsonArray);
        send200Response(resp, jsonDoc);*/
    }
    else if( expFsFilesCopy_.indexIn(req->path()) != -1 )
    {
        /*
        req->storeBody();
        QByteArray ba = req->body();
        QJsonParseError err;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(req->body(), &err);
        if (jsonDoc.isNull())
        {
            qDebug() << "Wrong request data! Error: " << err.errorString();
            send403Response(resp, "Wrong request body format!");
        }
        else
        {
            QStringList filesList;
            QString pathCopyTo;
            bool isAbsolute;

            QJsonObject jsonObj = jsonDoc.object();
            qDebug() << "Request json body: " << jsonObj;
            if (jsonObj.contains("path_copy_to"))
            {
                QJsonArray filesJsonArray = jsonObj["files"].toArray();
                for (int i = 0; i < filesJsonArray.size(); ++i)
                {
                    filesList << filesJsonArray[i].toString();
                }
                if (jsonObj.contains("path_copy_to"))
                    pathCopyTo = jsonObj["path_copy_to"].toString("");
                if (jsonObj.contains("is_absolute"))
                    isAbsolute = jsonObj["is_absolute"].toBool(false);

                bool result = false;
                emit fsCopyFiles(filesList, pathCopyTo, isAbsolute, result);

                if (result)
                {
                    send200Response(resp, "Files are copied.");
                }
                else
                {
                    qDebug() << "Can't complete api copy files command!";
                    send403Response(resp, "Can't copy files!"); // TODO: bad request
                }
            }
            else
            {
                qDebug() << "Wrong request data!";
                send403Response(resp, "Wrong request body format!"); // TODO: bad request
            }
        }
    */
    }

    return command;
}
