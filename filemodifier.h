#ifndef FILEMODIFIER_H
#define FILEMODIFIER_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QDirIterator>
#include <QBitArray>

#include <stack>
#include <functional>

#include <QDebug>

class FileModifier : public QObject
{
    Q_OBJECT
public:
    explicit FileModifier(QObject *parent = nullptr);
    ~FileModifier();

    QString fileMask;
    bool actionsRepeatingFile = true;
    unsigned long int frequencyCheckingFiles = 0;

private:
    static QFile* file;
    static QDir* dir;
    QByteArray fileDataBuf;  //Добавить обработчик исключения std::bad_alloc и проверку на макс. длину файла
    std::stack<QString> fileList;
    QByteArray outBytes;

    std::stack<QString>&& lookFiles(QString folder, const QString fileFilters);

     //QByteArray&& не потоко безопасно, зато быстро :)
    static QByteArray&& xOR(const quint64 enKey, const quint64 fileSize, QByteArray&& fileDataBuf, QByteArray &&outBytes);
    static QByteArray&& modMethodSecond(const quint64 enKey, const quint64 fileSize, QByteArray&& fileDataBuf, QByteArray &&outBytes);
    static QByteArray&& modMethodThird(const quint64 enKey, const quint64 fileSize, QByteArray&& fileDataBuf, QByteArray &&outBytes);
    static QByteArray&& modMethodFourth(const quint64 enKey, const quint64 fileSize, QByteArray&& fileDataBuf, QByteArray &&outBytes);
    static QByteArray&& modMethodFifth(const quint64 enKey, const quint64 fileSize, QByteArray&& fileDataBuf, QByteArray &&outBytes);
    std::function<QByteArray&& (const quint64, const quint64, QByteArray&&, QByteArray&&)> methodFileModPtr = nullptr;

    static QByteArray toQByteFromeQBit(QBitArray &&bits);

    bool writeFile(QByteArray&& fileDataBuf, QString filePath, const bool deleteImputFile, const bool actionsRepeatingFile);
    qint64 writeModForWriteFile(QByteArray &&fileDataBuf, const bool actionsRepeatingFile);

    static quint64 nameCounter;

public slots:
    void setUpSettings(const QString fileMask, QString enencryptionKey,  const bool deleteImputFile, const QString folder,
                       const bool actionsRepeatingFile, const unsigned long int frequencyCheckingFiles,
                       const unsigned short int FileModMethods);

    void openAndModify(std::stack<QString> fileList, std::function<QByteArray&& (quint64, quint64, QByteArray &&, QByteArray &&)> methodFileModPtr,
                       QString enencryptionKey, const bool deleteImputFile);
signals:

};


#endif // FILEMODIFIER_H
