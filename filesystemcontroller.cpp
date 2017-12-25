#include "filesystemcontroller.h"

FileSystemController::FileSystemController(QString root)
{
    rootDir_ = root;
}

FileSystemController::~FileSystemController()
{

}

void FileSystemController::setRootDir(QString root)
{
    rootDir_= root;
}

void FileSystemController::getFilesList(QStringList &list)
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

