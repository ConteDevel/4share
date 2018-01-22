#ifndef FILESYSTEMCONTROLLER_H
#define FILESYSTEMCONTROLLER_H

#include <QObject>
#include <QDir>

class FileSystemManager : public QObject
{
    Q_OBJECT
public:
    FileSystemManager(QString rootDir = "");
    ~FileSystemManager();

public slots:
    void onRootDirChanged(QString newRootDir);

    void getFilesList(QStringList &list);
    void copyFiles(QStringList &list, QString path, bool isAbsolutePath, bool &res);

private:
    QString rootDir_;
};

#endif // FILESYSTEMCONTROLLER_H
