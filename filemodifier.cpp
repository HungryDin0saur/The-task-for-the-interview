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

std::stack<QString>&& FileModifier::lookFiles(const QString folder, const QString fileFilters)
{
    this->dir->setPath(foolder.remove(0, 8) + '/');
    QDirIterator dirIter(dir->path(), dir->entryList(QStringList(fileFilters)));

    while (dirIter.hasNext())
    {
        this->fileList.emplace(dirIter.next());
    }

    return std::move(this->fileList);
}

void FileModifier::openAndModify(std::stack<QString> fileList,
                                 std::function<QByteArray&& (quint64, quint64, QByteArray&&, QByteArray&&)> methodFileModPtr, QString enencryptionKey)
{
    //quint64 enKey = enencryptionKey.toULongLong(); //18446744073709551615 - max, добавить проверку
    quint64 enKey = enencryptionKey.toLongLong(); //18446744073709551615 - max, добавить проверку
    qint64 fileSize = this->file->size();

    while(!fileList.empty())
    {
        this->file->setFileName(fileList.top());
        if((!this->file->isOpen()) && (this->file->open(QFile::ReadOnly)) && (fileSize != 0))
        {
            fileDataBuf = std::move(FileModifier::file->readAll());
            this->file->close();
            writeFile(methodFileModPtr(enKey, fileSize, std::move(fileDataBuf), std::move(outBytes)), std::move(fileList.top()));
        }
        else
        {
            //Кунуть исключени
            this->file->close();
            fileList.pop();

            return;
        }

        fileList.pop();
    }
}

void FileModifier::writeFile(QByteArray&& fileDataBuf, const QString&& filePath)
{
    this->file->setFileName(filePath);
    if((!this->file->isOpen()) && (this->file->open(QFile::WriteOnly)))
    {
      qDebug() << "writeFile SIZE: " << this->file->write(fileDataBuf);
      fileDataBuf.clear();
    }
    else{
        this->file->close();
        fileDataBuf.clear();
        //Кунуть исключени
    }

    this->file->close();
    fileDataBuf.clear();
}

QByteArray &&FileModifier::xOR(const quint64 enKey, const quint64 fileSize, QByteArray&& fileDataBuf, QByteArray&& outBytes)
{
/*
 *  Так нельзя, потому что мне было необходимо беззнаковой представление
    QBitArray bitsToXor;
    QByteArray fileDataBuf;
    fileDataBuf.push_back('v');
    fileDataBuf.push_back('e');
    fileDataBuf.push_back('N');
    fileDataBuf.push_back('m');
    fileDataBuf.push_back('v');
    fileDataBuf.push_back('F');
    fileDataBuf.push_back('R');
    fileDataBuf.push_back('o');

    bitsToXor = QBitArray::fromBits(fileDataBuf.constData(), 8);
    qDebug() << bitsToXor;
*/

   QBitArray bitsEnKey(64, 0);
   for(short int i = 0; i < 64; i++)
   {
       bitsEnKey.setBit(i, enKey&(1ull<<i)); //((((i+1) * 64) - 1) % 65)
   }

   QBitArray bitsToXor(64, 0);

   unsigned int i = 0;

   for(QByteArray::iterator itrBytes = fileDataBuf.begin(); itrBytes <= fileDataBuf.end(); itrBytes++) //auto itrBytes : fileDataBuf
   {
       do {
           bitsToXor.setBit(i, *itrBytes&(1ull<<(i%8))); //(((i * 7) - 1) % 8) + (i - (i % 8))

           if(((++i) == 64) || (itrBytes == fileDataBuf.end()))
           {
               i = 0;

               bitsToXor ^= bitsEnKey;

               outBytes.append(toQByteFromeQBit(std::move(bitsToXor)));

               bitsToXor.fill(0, 64);
           }
       }
       while ((i % 8) != 0);
   }

   outBytes.remove(fileSize, outBytes.size() - fileSize);

   return std::move(outBytes);
}

QByteArray&& FileModifier::modMethodSecond(const quint64 enKey, const quint64 fileSize, QByteArray &&fileDataBuf, QByteArray &&outBytes)
{
    return std::move(fileDataBuf);
}

QByteArray&& FileModifier::modMethodThird(const quint64 enKey, const quint64 fileSize, QByteArray &&fileDataBuf, QByteArray &&outBytes)
{
    return std::move(fileDataBuf);
}

QByteArray&& FileModifier::modMethodFourth(const quint64 enKey, const quint64 fileSize, QByteArray &&fileDataBuf, QByteArray &&outBytes)
{
    return std::move(fileDataBuf);
}

QByteArray&& FileModifier::modMethodFifth(const quint64 enKey, const quint64 fileSize, QByteArray &&fileDataBuf, QByteArray &&outBytes)
{
    return std::move(fileDataBuf);
}

QByteArray FileModifier::toQByteFromeQBit(QBitArray&& bits)
{
    QBitArray bufBits(8, 0);
    QByteArray bufBytes;
    bufBytes.resize(1);

    int bitsSize = bits.size();

    QByteArray bytes;
    bytes.clear();
    bytes.resize(bitsSize / 8);
    bytes.fill('\00');

    for(int i = 0; i < bitsSize; i++)
    {
            bufBits.setBit(i%8, bits.at(i));

            if(((i+1) % 8) == 0)
            {
                for(int j = 0; j < 8; j++)
                {
                    bufBytes[0] = (bufBytes.at(0) | (bufBits[j]<<(j%8)));
                }

                bytes[i/8] = bufBytes.at(0);

                bufBytes.clear();
                bufBytes.resize(1);
            }
    }

    return bytes;
}

void FileModifier::setUpSettings(QString fileMask, QString enencryptionKey, const bool deleteImputFile, const QString foolder,
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

     //Передать стек по двойной ссылке
    openAndModify(std::move(lookFiles(this->foolder, this->fileMask)), methodFileModPtr, this->enencryptionKey);

    methodFileModPtr = nullptr;
}

