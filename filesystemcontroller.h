#ifndef FILESYSTEMCONTROLLER_H
#define FILESYSTEMCONTROLLER_H

#include <QObject>
#include <QDir>

class FileSystemController : public QObject
{
    Q_OBJECT
public:
    FileSystemController(QString rootDir = "");
    ~FileSystemController();

public slots:
    void onRootDirChanged(QString newRootDir);

    void getFilesList(QStringList &list);
    void copyFiles(QStringList &list, QString path, bool isAbsolutePath, bool &res);

private:
    QString rootDir_;
};

#endif // FILESYSTEMCONTROLLER_H
