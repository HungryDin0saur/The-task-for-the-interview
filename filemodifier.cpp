#include "filemodifier.h"

FileModifier::FileModifier(QObject *parent)
    : QObject{parent}
{
    this->file = new QFile;
    this->dir = new QDir;
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
    //quint64 enKey = enencryptionKey.toULongLong(); //18446744073709551615 - max, добавить проверку
    quint64 enKey = enencryptionKey.toLongLong(); //18446744073709551615 - max, добавить проверку

    while(!fileList.empty())
    {
        file->setFileName(fileList.top());
        if(file->open(QFile::ReadWrite))
        {
            fileDataBuf = std::move(FileModifier::file->readAll());
            writeFile(methodFileModPtr(enKey, std::move(fileDataBuf)), fileList.top());
        }
        else{
            //Кунуть исключени
        }

        fileList.pop();
        FileModifier::file->close();
    }
}

void FileModifier::writeFile(QByteArray&& fileDataBuf, QString filePath)
{
    file->setFileName(filePath);
    if(file->open(QFile::WriteOnly))
    {
       file->write(fileDataBuf);
    }
    else{
        //Кунуть исключени
    }
}

QByteArray &&FileModifier::xOR(quint64 enKey, QByteArray&& fileDataBuf)
{
   QBitArray bitsEnKey(64, 0);
   for(short int i = 0; i < 64; i++)
   {
       bitsEnKey.setBit(((((i+1) * 64) - 1) % 65), enKey&(1ull<<i));
   }

   QBitArray bitsToXor(64, 0);

   unsigned int i = 0;
   for(auto itrBytes: fileDataBuf)
   {
       do {
           bitsToXor.setBit((((i * 7) - 1) % 8) + (i - (i % 8)), itrBytes&(1<<(i%8)));

           if((++i) == 64)
           {
               i = 0;

               //bitsToXor ^= bitsEnKey;
               //qDebug() << "Bit mass: " << bitsToXor;
               //qDebug() << "Variable xor: " << bitsEnKey;
               //qDebug() << "Res xor: " << bitsToXor;


                   fileDataBuf.resize(bits.count()/8+1);
                   fileDataBuf.fill(0);
                   // Convert from QBitArray to QByteArray
                   for(int b=0; b<bits.count(); ++b)
                       fileDataBuf[b/8] = ( fileDataBuf.at(b/8) | ((bits[b]?1:0)<<(b%8)));



               bitsToXor.fill(0, 64);
           }
       }
       while ((i % 8) != 0);
   }

   return std::move(fileDataBuf);
}

QByteArray &&FileModifier::modMethodSecond(quint64 enKey, QByteArray &&fileDataBuf)
{
    return std::move(fileDataBuf);
}

QByteArray &&FileModifier::modMethodThird(quint64 enKey, QByteArray &&fileDataBuf)
{
    return std::move(fileDataBuf);
}

QByteArray &&FileModifier::modMethodFourth(quint64 enKey, QByteArray &&fileDataBuf)
{
    return std::move(fileDataBuf);
}

QByteArray &&FileModifier::modMethodFifth(quint64 enKey, QByteArray &&fileDataBuf)
{
    return std::move(fileDataBuf);
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

    openAndModify(lookFiles(this->foolder, this->fileMask), methodFileModPtr, this->enencryptionKey);
}

