#ifndef WEBAPICONTROLLER_H
#define WEBAPICONTROLLER_H

#include <QObject>
#include <QJsonDocument>

#include "qhttpserverfwd.h"

class WebApiController : public QObject
{
    Q_OBJECT
public:
    WebApiController(int serverPort = defaultHttpServerPort);
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
    void send200Response(QHttpResponse *resp, QJsonDocument jsonDoc);
    void send200Response(QHttpResponse *resp, QString msg);
    void send403Response(QHttpResponse *resp, QString msg);

private:
    static constexpr int defaultHttpServerPort = 8080;
    int httpServerPort_;
    QHttpServer* httpServer_;
};

#endif // WEBAPICONTROLLER_H
