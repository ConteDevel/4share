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
    QRegExp exp("^/hello/([a-z]+)$");
    if( exp.indexIn(req->path()) != -1 )
    {
        qDebug() << "New http request:" << req->path();
        resp->setHeader("Content-Type", "text/html");
        resp->writeHead(200);

        QString name = exp.capturedTexts()[1];
        QString body = tr("<html><head><title>4Share</title></head><body><h1>Hello %1!</h1></body></html>");
        resp->end(body.arg(name).toUtf8());
    }
    else
    {
        qDebug() << "New http request:" << req->path() << " Wrong request path!";
        resp->writeHead(403);
        resp->end(QByteArray("You aren't allowed here!"));
    }
}
