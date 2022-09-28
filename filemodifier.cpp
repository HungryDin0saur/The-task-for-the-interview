#include "filemodifier.h"

//while(!fileList.empty())
//{
//    file->open(QFile::ReadOnly); fileList.top();
//    fileList.pop();
//}

FileModifier::FileModifier(QObject *parent)
    : QObject{parent}
{
    file = new QFile;
    dir = new QDir;
}

FileModifier::~FileModifier()
{
    fileDataBuf.clear();

    delete file;
    delete dir;
}

const std::stack<QString> &FileModifier::lookFiles(const QString folder, QString fileFilters)
{
    dir->setPath(foolder.remove(0, 8) + '/');
    QDirIterator dirIter(dir->path(), dir->entryList(QStringList(fileFilters)));

    while (dirIter.hasNext())
    {
        this->fileList.emplace(dirIter.next());
    }

    return this->fileList;
}

void FileModifier::openAndModify(std::stack<QString> fileList, const unsigned short FileModMethods)
{
    while(!fileList.empty())
    {
        this->file->setFileName(fileList.top());
        if(this->file->open(QFile::ReadWrite))
        {
            fileDataBuf = std::move(this->file->readAll());
            qDebug() << fileDataBuf.size();
        }
        else{
            //Кунуть исключени
        }

        fileList.pop();
    }


    //switch (FileModMethods) {
    //case value:

    //    break;
    //default:
    //    break;
    //}

}


void FileModifier::setUpSettings(QString fileMask, const bool deleteImputFile, const QString& foolder,
                                 const bool ActionsRepeatingFile, const unsigned long FrequencyCheckingFiles,
                                 const unsigned short FileModMethods)
{
    this->fileMask = fileMask;
    this->deleteImputFile = deleteImputFile;
    this->foolder = foolder;
    this->ActionsRepeatingFile = ActionsRepeatingFile;
    this->FrequencyCheckingFiles = FrequencyCheckingFiles;
    this->FileModMethods = FileModMethods;

    openAndModify(lookFiles(this->foolder, this->fileMask), this->FileModMethods);
}
