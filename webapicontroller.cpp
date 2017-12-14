#include "webapicontroller.h"

#include <QDebug>

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
    QRegExp expVolumeSet("^/system/volume/set/([0-9]+)$");
    QRegExp expVolumeTurnUp("^/system/volume/up/([0-9]+)$");
    QRegExp expVolumeTurnDown("^/system/volume/down/([0-9]+)$");
    QRegExp expVolumeMute("^/system/volume/mute/$");
    QRegExp expVolumeUnmute("^/system/volume/unmute/$");

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
    else
    {
        qDebug() << "Wrong request path!";
        send403Response(resp, "You are not allowed here!");
    }
}

void WebApiController::send200Response(QHttpResponse *resp, QString msg)
{
    resp->setHeader("Content-Type", "text/html");
    resp->writeHead(200); // 200 OK
    QString body = tr("<html><head><title>4Share</title></head><body><h1>%1!</h1></body></html>");
    resp->end(body.arg(msg).toUtf8());
}

void WebApiController::send403Response(QHttpResponse *resp, QString msg)
{
    resp->setHeader("Content-Type", "text/html");
    resp->writeHead(403); // 403 Forbidden
    QString body = tr("<html><head><title>4Share</title></head><body><h1>%1</h1></body></html>");
    resp->end(body.arg(msg).toUtf8());
}
