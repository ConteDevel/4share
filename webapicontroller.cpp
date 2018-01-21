#include "webapicontroller.h"

#include <QDebug>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include <qhttpserver.h>
#include <qhttprequest.h>
#include <qhttpresponse.h>

#include "logger.h"

WebApiController::WebApiController(int serverPort)
{
    // TODO: init server from Settings
    httpServer_ = new QHttpServer(this);
    connect(httpServer_, &QHttpServer::newRequest,
            this, &WebApiController::handleRequest);
    httpServerPort_ = serverPort;
}

bool WebApiController::startListen()
{
    // start server listenning (using listen QTcpServer method)
    bool couldStartListen =  httpServer_->listen(QHostAddress::Any, httpServerPort_);
    if (couldStartListen) {
        Logger::Instance()->logMsg("HTTP сервер запущен на порту: " + QString::number(httpServerPort_));
    }
    return couldStartListen;
}

bool WebApiController::onPortChangedRestart(int newServerPort)
{
    httpServer_->close();
    httpServerPort_ = newServerPort;
    return startListen();
}

int WebApiController::getCurrentPort()
{
    return httpServerPort_;
}

void WebApiController::handleRequest(QHttpRequest *req, QHttpResponse *resp)
{
    // system volume expressions
    QRegExp expVolumeSet("^/system/volume/set/([0-9]+)$");
    QRegExp expVolumeTurnUp("^/system/volume/up/([0-9]+)$");
    QRegExp expVolumeTurnDown("^/system/volume/down/([0-9]+)$");
    QRegExp expVolumeMute("^/system/volume/mute/$");
    QRegExp expVolumeUnmute("^/system/volume/unmute/$");
    // file system expressions
    QRegExp expFsFilesCopy("^/files/copy$");
    QRegExp expFsFilesList("^/files/list$");

    //TODO: add validation

    //qDebug() << "New http request:" << req->path();
    Logger::Instance()->logMsg("Новый HTTP запрос: " + req->path());
    if( expVolumeSet.indexIn(req->path()) != -1 )
    {
        int value = (expVolumeSet.capturedTexts()[1]).toInt();
        emit volumeSetValue(value);
        QString msg = QString("Volume set to %1!").arg(value);
        send200Response(resp, msg);
    }
    else if( expVolumeTurnUp.indexIn(req->path()) != -1 )
    {
        int value = (expVolumeTurnUp.capturedTexts()[1]).toInt();
        emit volumeTurnValue(1, value);
        QString msg = QString("Volume turn up for %1!").arg(value);
        send200Response(resp, msg);
    }
    else if( expVolumeTurnDown.indexIn(req->path()) != -1 )
    {
        int value = (expVolumeTurnDown.capturedTexts()[1]).toInt();
        emit volumeTurnValue(0, value);
        QString msg = QString("Volume turn down for %1!").arg(value);
        send200Response(resp, msg);
    }
    else if( expVolumeMute.indexIn(req->path()) != -1 )
    {
        emit volumeSetIsMute(1);
        send200Response(resp, "Volume is mute!");
    }
    else if( expVolumeUnmute.indexIn(req->path()) != -1 )
    {
        emit volumeSetIsMute(0);
        send200Response(resp, "Volume is unmute!");
    }
    else if( expFsFilesList.indexIn(req->path()) != -1 )
    {
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
        send200Response(resp, jsonDoc);
    }
    else if( expFsFilesCopy.indexIn(req->path()) != -1 )
    {
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
    }
    else
    {
        qDebug() << "Wrong request path!";
        send403Response(resp, "You are not allowed here!");
    }
}

void WebApiController::send200Response(QHttpResponse *resp, QJsonDocument jsonDoc)
{
    resp->setHeader("Content-Type", "application/json");
    resp->writeHead(200); // 200 OK

    QString jsonString = jsonDoc.toJson();

    resp->end(jsonString.toUtf8());
}

void WebApiController::send200Response(QHttpResponse *resp, QString msg)
{
    resp->setHeader("Content-Type", "application/json");
    resp->writeHead(200); // 200 OK

    QJsonDocument jsonDoc;
    QJsonObject jsonObj;
    jsonObj["result"] = msg;
    jsonDoc.setObject(jsonObj);
    QString jsonString = jsonDoc.toJson();

    resp->end(jsonString.toUtf8());
}

void WebApiController::send403Response(QHttpResponse *resp, QString msg)
{
    resp->setHeader("Content-Type", "text/html");
    resp->writeHead(403); // 403 Forbidden
    QString body = tr("%1");
    resp->end(body.arg(msg).toUtf8());
}
