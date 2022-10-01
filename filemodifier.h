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
    bool deleteImputFile = false;
    QString foolder;
    bool actionsRepeatingFile = true;
    unsigned long int frequencyCheckingFiles = 0;
    QString enencryptionKey;

private:
    QFile* file;
    QDir* dir;
    QByteArray fileDataBuf;
    std::stack<QString> fileList;
    QByteArray outBytes;

    std::stack<QString>&& lookFiles(const QString folder, const QString fileFilters);

     //QByteArray&& не потоко безопасно, зато быстро :)
    static QByteArray&& xOR(const quint64 enKey, const quint64 fileSize, QByteArray&& fileDataBuf, QByteArray &&outBytes);
    static QByteArray&& modMethodSecond(const quint64 enKey, const quint64 fileSize, QByteArray&& fileDataBuf, QByteArray &&outBytes);
    static QByteArray&& modMethodThird(const quint64 enKey, const quint64 fileSize, QByteArray&& fileDataBuf, QByteArray &&outBytes);
    static QByteArray&& modMethodFourth(const quint64 enKey, const quint64 fileSize, QByteArray&& fileDataBuf, QByteArray &&outBytes);
    static QByteArray&& modMethodFifth(const quint64 enKey, const quint64 fileSize, QByteArray&& fileDataBuf, QByteArray &&outBytes);
    std::function<QByteArray&& (const quint64, const quint64, QByteArray&&, QByteArray&&)> methodFileModPtr = nullptr;

    static QByteArray toQByteFromeQBit(QBitArray &&bits);

    void writeFile(QByteArray&& fileDataBuf, const QString &&filePath);

public slots:
    void setUpSettings(QString fileMask, QString enencryptionKey,  const bool deleteImputFile, const QString foolder,
                       const bool actionsRepeatingFile, const unsigned long int frequencyCheckingFiles,
                       const unsigned short int FileModMethods);

    void openAndModify(std::stack<QString> fileList, std::function<QByteArray&& (quint64, quint64, QByteArray &&, QByteArray &&)> methodFileModPtr,
                       QString enencryptionKey);
signals:

};


#endif // FILEMODIFIER_H
