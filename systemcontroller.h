#ifndef SYSTEMCONTROLLER_H
#define SYSTEMCONTROLLER_H

#include <QObject>

class SystemController : public QObject
{
    Q_OBJECT
public:
    SystemController();

public slots:
    void setVolumeValue(int value);
    void turnVolumeValue(bool isTurnUp, int value);
    void setVolumeIsMute(bool isMute);

private:

};

#endif // SYSTEMCONTROLLER_H
