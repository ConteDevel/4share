#include "api_controller.h"

#include <QDebug>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include <qhttpserver.h>
#include <qhttprequest.h>
#include <qhttpresponse.h>

#include "api_commands.h"
#include "logger.h"

ApiController::ApiController(int serverPort)
{
    // initialize request parser
    requestParser_ = new ApiRequestParser();

    // TODO: init server from Settings
    httpServer_ = new QHttpServer(this);
    connect(httpServer_, &QHttpServer::newRequest,
            this, &ApiController::handleRequest);
    httpServerPort_ = serverPort;
}

bool ApiController::startListen()
{
    // start server listenning (using listen QTcpServer method)
    bool couldStartListen =  httpServer_->listen(QHostAddress::Any, httpServerPort_);
    if (couldStartListen) {
        Logger::Instance()->logMsg("HTTP сервер запущен на порте: "
                                        + QString::number(httpServerPort_));
    }
    else {
        Logger::Instance()->logMsg("Не удалось запустить сервер на порте: "
                                   + QString::number(httpServerPort_),
                                   Logger::LogLevel::ERROR);
    }
    return couldStartListen;
}

bool ApiController::onPortChangedRestart(int newServerPort)
{
    httpServer_->close();
    httpServerPort_ = newServerPort;
    return startListen();
}

int ApiController::getCurrentPort()
{
    return httpServerPort_;
}

void ApiController::handleRequest(QHttpRequest *req, QHttpResponse *resp)
{
    ApiCommand* command = requestParser_->parseRequest(req);
    if (!command)
    {
        qDebug() << "Wrong request!";
        send403Response(resp, "Wrong request!");
        return;
    }

    if (command->execute(*this))
    {
        send200Response(resp, command->getReturnedData().toString());
    }
    else
    {
        send403Response(resp, "Something is wrong");
    }
}

void ApiController::send200Response(QHttpResponse *resp, QJsonDocument jsonDoc)
{
    resp->setHeader("Content-Type", "application/json");
    resp->writeHead(200); // 200 OK

    QString jsonString = jsonDoc.toJson();

    resp->end(jsonString.toUtf8());
}

void ApiController::send200Response(QHttpResponse *resp, QString msg)
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

void ApiController::send403Response(QHttpResponse *resp, QString msg)
{
    resp->setHeader("Content-Type", "text/html");
    resp->writeHead(403); // 403 Forbidden
    QString body = tr("%1");
    resp->end(body.arg(msg).toUtf8());
}
