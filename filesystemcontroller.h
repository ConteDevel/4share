#ifndef FILESYSTEMCONTROLLER_H
#define FILESYSTEMCONTROLLER_H

#include <QObject>
#include <QDir>

class FileSystemController : public QObject
{
    Q_OBJECT
public:
    FileSystemController(QString root = "");
    ~FileSystemController();

    void setRootDir(QString root);

public slots:
    void getFilesList(QStringList &list);

private:
    QString rootDir_;
};

#endif // FILESYSTEMCONTROLLER_H