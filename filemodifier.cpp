#include "filemodifier.h"

FileModifier::FileModifier(QObject *parent)
    : QObject{parent}
{
    file = new QFile;
    dir = new QDir;
}

FileModifier::~FileModifier()
{
    delete file;
    delete dir;
}

const QFile* FileModifier::openFiles(QString folder, QStringList fileFilters, QFile* file = nullptr)
{
    dir->setPath(foolder.remove(0, 8) + '/');
    dir->entryInfoList(fileFilters);
    QDirIterator dirIter(dir->path());


    while (dirIter.hasNext())
    {
        fileList.emplace(dirIter.next());
    }

    while(!fileList.empty())
    {
        qDebug() << fileList.top();
        fileList.pop();
    }


    //dir->setPath(foolder.remove(0, 8) + '/');
    //QFileInfoList list = dir->entryInfoList(QStringList(), QDir::Files);

    //
    //quint64 s = list.size();
    //for(quint64 i=0;i<s;i++)
    //{
    //    qDebug() << list.at(i).fileName();
    //}



    //file-
    //file->open(QFile::ReadOnly);
    return file;
}


void FileModifier::setUpSettings(const QList<QString>&& fileMask, const bool deleteImputFile, const QString& foolder,
                                 const bool ActionsRepeatingFile, const unsigned long FrequencyCheckingFiles,
                                 const unsigned short FileModMethods)
{
    this->fileMask.swap(fileMask);
    this->deleteImputFile = deleteImputFile;
    this->foolder = foolder;
    this->ActionsRepeatingFile = ActionsRepeatingFile;
    this->FrequencyCheckingFiles = FrequencyCheckingFiles;
    this->FileModMethods = FileModMethods;

    FileModifier::openFiles(this->foolder, this->fileMask, this->file);
}
