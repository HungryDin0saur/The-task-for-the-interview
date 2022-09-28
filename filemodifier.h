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

    const std::stack<QString>& lookFiles(const QString folder, QString fileFilters);

     //Это не потоко безопасно, зато быстро :)
    static QByteArray&& xOR(quint64 enKey, QByteArray &&fileDataBuf);
    static QByteArray&& modMethodSecond(quint64 enKey, QByteArray &&fileDataBuf);
    static QByteArray&& modMethodThird(quint64 enKey, QByteArray &&fileDataBuf);
    static QByteArray&& modMethodFourth(quint64 enKey, QByteArray &&fileDataBuf);
    static QByteArray&& modMethodFifth(quint64 enKey, QByteArray &&fileDataBuf);

    std::function<QByteArray&& (quint64, QByteArray&&)> methodFileModPtr = nullptr;

public slots:
    void setUpSettings(QString fileMask, QString enencryptionKey,  const bool deleteImputFile, const QString &foolder,
                       const bool actionsRepeatingFile, const unsigned long int frequencyCheckingFiles,
                       const unsigned short int FileModMethods);

    void openAndModify(std::stack<QString> fileList, std::function<QByteArray&& (quint64, QByteArray&&)> methodFileModPtr,
                       QString enencryptionKey);

signals:

};


#endif // FILEMODIFIER_H
