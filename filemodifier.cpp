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

    methodFileModPtr = nullptr;

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

void FileModifier::openAndModify(std::stack<QString> fileList,
                                 std::function<QByteArray &&(QByteArray &&)> methodFileModPtr)
{


    while(!fileList.empty())
    {
        this->file->setFileName(fileList.top());
        if(this->file->open(QFile::ReadWrite))
        {
            fileDataBuf = std::move(this->file->readAll());
            //methodFileModPtr(fileDataBuf)
        }
        else{
            //Кунуть исключени
        }

        fileList.pop();
    }



}

QByteArray &&FileModifier::xOR(QByteArray &&fileDataBuf)
{
    return nullptr;
}

QByteArray &&FileModifier::modMethodSecond(QByteArray &&fileDataBuf)
{

}

QByteArray &&FileModifier::modMethodThird(QByteArray &&fileDataBuf)
{

}

QByteArray &&FileModifier::modMethodFourth(QByteArray &&fileDataBuf)
{

}

QByteArray &&FileModifier::modMethodFifth(QByteArray &&fileDataBuf)
{

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


    switch (FileModMethods) {
    case 0:
        methodFileModPtr = xOR;
        break;
    case 1:
        methodFileModPtr = modMethodSecond;
        break;
    case 2:
        methodFileModPtr = modMethodThird;
        break;
    case 3:
        methodFileModPtr = modMethodFourth;
        break;
    case 4:
        methodFileModPtr = modMethodFifth;
        break;
    default:
        //Здесь можно бросить исключение
        break;
    }

    openAndModify(lookFiles(this->foolder, this->fileMask), this->FileModMethods);
}

