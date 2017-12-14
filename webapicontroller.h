#ifndef WEBAPICONTROLLER_H
#define WEBAPICONTROLLER_H

#include <QObject>

#include "qhttpserverfwd.h"

class WebApiController : public QObject
{
    Q_OBJECT
public:
    WebApiController();

signals:
    void volumeSetValue(int newValue);
    void volumeTurnValue(bool isTurnUp, int value);
    void volumeSetIsMute(bool isMute);

private slots:
    void handleRequest(QHttpRequest *req, QHttpResponse *resp);
    void send200Response(QHttpResponse *resp, QString msg);
    void send403Response(QHttpResponse *resp, QString msg);

};

#endif // WEBAPICONTROLLER_H
