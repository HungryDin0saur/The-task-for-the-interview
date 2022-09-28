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
                                 std::function<QByteArray&& (quint64, QByteArray&&)> methodFileModPtr, QString enencryptionKey)
{
    quint64 enKey = enencryptionKey.toULongLong(); //18446744073709551615 - max, добавить проверку

    while(!fileList.empty())
    {
        this->file->setFileName(fileList.top());
        if(this->file->open(QFile::ReadWrite))
        {
            fileDataBuf = std::move(this->file->readAll());
            methodFileModPtr(enKey, std::move(fileDataBuf));
        }
        else{
            //Кунуть исключени
        }

        fileList.pop();
        this->file->close();
    }
}

QByteArray &&FileModifier::xOR(quint64 enKey, QByteArray &&fileDataBuf)
{
    QBitArray bitsToHex(64);

    short int i=0;
    for(auto itrBytes: fileDataBuf)
    {
        while(i<64)
        {
            bitsToHex.setBit(i, itrBytes&(1<<i));
            i++;
            if(i == ((64 % 8) - 1))
            {
              qDebug() << i;
                if(i == 63)
                {
                   i = 0;
                }
                break;
            }
        }
            break; //временно
    }

    qDebug() << "TEST: " << bitsToHex;

    //for(int i=0; i<bytes.count(); ++i)
    //    for(int b=0; b<8; ++b)
    //        bitsToHex.setBit(i*8+b, bytes.at(i)&(1<<b));

    ////for(QByteArray::iterator itr=fileDataBuf.begin(); itr!=fileDataBuf.end();itr++)
    //{
    //    // Convert from QByteArray to QBitArray
    //
    //}
    return nullptr;
}

QByteArray &&FileModifier::modMethodSecond(quint64 enKey, QByteArray &&fileDataBuf)
{

}

QByteArray &&FileModifier::modMethodThird(quint64 enKey, QByteArray &&fileDataBuf)
{

}

QByteArray &&FileModifier::modMethodFourth(quint64 enKey, QByteArray &&fileDataBuf)
{

}

QByteArray &&FileModifier::modMethodFifth(quint64 enKey, QByteArray &&fileDataBuf)
{

}

void FileModifier::setUpSettings(QString fileMask, QString enencryptionKey, const bool deleteImputFile, const QString& foolder,
                                 const bool actionsRepeatingFile, const unsigned long frequencyCheckingFiles,
                                 const unsigned short FileModMethods)
{
    this->fileMask = fileMask;
    this->deleteImputFile = deleteImputFile;
    this->foolder = foolder;
    this->actionsRepeatingFile = actionsRepeatingFile;
    this->frequencyCheckingFiles = frequencyCheckingFiles;
    this->enencryptionKey = enencryptionKey;

    switch (FileModMethods) {
    case 0:
        methodFileModPtr = xOR;
        break;
    //case 1:
    //    methodFileModPtr = modMethodSecond;
    //    break;
    //case 2:
    //    methodFileModPtr = modMethodThird;
    //    break;
    //case 3:
    //    methodFileModPtr = modMethodFourth;
    //    break;
    //case 4:
    //    methodFileModPtr = modMethodFifth;
    //    break;
    default:
        //Здесь можно бросить исключение
        break;
    }

    openAndModify(lookFiles(this->foolder, this->fileMask), methodFileModPtr, this->enencryptionKey);
}

