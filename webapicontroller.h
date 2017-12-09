#ifndef WEBAPICONTROLLER_H
#define WEBAPICONTROLLER_H

#include <QObject>

#include "qhttpserverfwd.h"

class WebApiController : public QObject
{
    Q_OBJECT
public:
    WebApiController();

private slots:
    void handleRequest(QHttpRequest *req, QHttpResponse *resp);

};

#endif // WEBAPICONTROLLER_H
