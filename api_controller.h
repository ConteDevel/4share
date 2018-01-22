#ifndef APICONTROLLER_H
#define APICONTROLLER_H

#include <QObject>
#include <QJsonDocument>

#include "qhttpserverfwd.h"

#include "api_request_parser.h"

class ApiRequestParser;
class ApiController : public QObject
{
    Q_OBJECT
public:
    ApiController(int serverPort = defaultHttpServerPort_);
    bool startListen();
    int getCurrentPort();

signals:
    // control system signals
    void volumeSetValue(int newValue);
    void volumeTurnValue(bool isTurnUp, int value);
    void volumeSetIsMute(bool isMute);
    // file system signals
    void fsGetFilesList(QStringList &list);
    void fsCopyFiles(QStringList &list, QString path, bool isAbsolutePath, bool &res);

public slots:
    bool onPortChangedRestart(int newServerPort);

private slots:
    void handleRequest(QHttpRequest *req, QHttpResponse *resp);
    bool serializeResponse(QVariant data, QJsonDocument& jsonDoc);
    void send200Response(QHttpResponse *resp, QJsonDocument jsonDoc);
    void send403Response(QHttpResponse *resp, QString msg);

private:
    static constexpr int defaultHttpServerPort_ = 8080;
    int httpServerPort_;
    ApiRequestParser* requestParser_;
    QHttpServer* httpServer_;
};

#endif // APICONTROLLER_H
