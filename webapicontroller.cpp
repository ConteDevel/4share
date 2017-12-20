#include "webapicontroller.h"

#include <QDebug>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include <qhttpserver.h>
#include <qhttprequest.h>
#include <qhttpresponse.h>

WebApiController::WebApiController()
{
    // TODO: init server from Settings
    QHttpServer *server = new QHttpServer(this);
    connect(server, &QHttpServer::newRequest,
            this, &WebApiController::handleRequest);
    qDebug() << "Server created";
    // start server listenning
    server->listen(QHostAddress::Any, 8080);
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
    QRegExp expFsFilesList("^/files/$");

    //TODO: add validation

    qDebug() << "New http request:" << req->path();
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
        emit fsGetList(filesList);

        QJsonArray json_array;
        for (int i = 0; i < filesList.size(); ++i)
        {
            QJsonObject json_obj;
            json_obj["fileName"] = filesList[i];
            json_array.append(json_obj);
        }
        QJsonDocument json_doc;
        json_doc.setArray(json_array);
        send200Response(resp, json_doc);
    }
    else
    {
        qDebug() << "Wrong request path!";
        send403Response(resp, "You are not allowed here!");
    }
}

void WebApiController::send200Response(QHttpResponse *resp, QJsonDocument json_doc)
{
    resp->setHeader("Content-Type", "application/json");
    resp->writeHead(200); // 200 OK

    QString json_string = json_doc.toJson();

    resp->end(json_string.toUtf8());
}

void WebApiController::send200Response(QHttpResponse *resp, QString msg)
{
    resp->setHeader("Content-Type", "application/json");
    resp->writeHead(200); // 200 OK

    QJsonDocument json_doc;
    QJsonObject json_obj;
    json_obj["result"] = msg;
    json_doc.setObject(json_obj);
    QString json_string = json_doc.toJson();

    resp->end(json_string.toUtf8());
}

void WebApiController::send403Response(QHttpResponse *resp, QString msg)
{
    resp->setHeader("Content-Type", "text/html");
    resp->writeHead(403); // 403 Forbidden
    QString body = tr("%1");
    resp->end(body.arg(msg).toUtf8());
}
