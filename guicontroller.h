#ifndef GUICONTROLLER_H
#define GUICONTROLLER_H

#include <QQmlApplicationEngine>
#include <QObject>

class GuiController : public QObject
{
    Q_OBJECT
public:
    explicit GuiController(QObject *parent = nullptr);
    bool initialize();

    void updateServerPortField(const int port);
    void updateRootDirPathField(const QString path);

private:
    void updateLogListModel();

signals:
    void portChanged(int newPort);
    void rootDirPathChanged(QString newPath);

public slots:
    void onServerPortChanged(const QString &newPort);
    void onRootDirPathChanged(const QString &newPath);
    void onNewLogMsg(const QString msg);

private:
    QStringList logListModel_;

    QQmlApplicationEngine engine_;
    QObject* rootAppWindow_;
};

#endif // GUICONTROLLER_H
