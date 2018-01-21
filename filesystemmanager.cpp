#include "filesystemmanager.h"

FileSystemManager::FileSystemManager(QString rootDir)
{
    rootDir_ = rootDir;
}

FileSystemManager::~FileSystemManager()
{

}

void FileSystemManager::onRootDirChanged(QString newRootDir)
{
    rootDir_= newRootDir;
}

void FileSystemManager::getFilesList(QStringList &list)
{
    // Set settings for root directory
    QDir dir(rootDir_);
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);

    // Get file list
    QFileInfoList fileInfolist = dir.entryInfoList();
    for (int i = 0; i < fileInfolist.size(); ++i)
    {
        list << fileInfolist.at(i).fileName();
    }
}

void FileSystemManager::copyFiles(QStringList &list, QString path,
                                     bool isAbsolutePath, bool& res)
{
    res = true;
    QString copyTo;
    for (int i = 0; i < list.size(); ++i)
    {
        if (isAbsolutePath)
            copyTo = path+list[i];
        else
            copyTo = rootDir_ + path + list[i];
        if (!QFile::copy(rootDir_+list[i], copyTo))
        {
            res = false;
            return;
        }
    }
}

