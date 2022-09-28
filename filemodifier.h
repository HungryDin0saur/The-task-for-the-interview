#ifndef FILEMODIFIER_H
#define FILEMODIFIER_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QDirIterator>

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
    bool deleteImputFile;
    QString foolder;
    bool ActionsRepeatingFile;
    unsigned long int FrequencyCheckingFiles;
    unsigned short int FileModMethods;

private:
    QFile* file;
    QDir* dir;
    QByteArray fileDataBuf;
    std::stack<QString> fileList;

    const std::stack<QString>& lookFiles(const QString folder, QString fileFilters);
    void openAndModify(std::stack<QString> fileList, std::function<QByteArray&&(QByteArray&&)> methodFileModPtr);

    static QByteArray&& xOR(QByteArray &&fileDataBuf);
    static QByteArray&& modMethodSecond(QByteArray &&fileDataBuf);
    static QByteArray&& modMethodThird(QByteArray &&fileDataBuf);
    static QByteArray&& modMethodFourth(QByteArray &&fileDataBuf);
    static QByteArray&& modMethodFifth(QByteArray &&fileDataBuf);

    std::function<QByteArray&&(QByteArray&&)> methodFileModPtr = nullptr;

public slots:
    void setUpSettings(QString fileMask, const bool deleteImputFile, const QString &foolder,
                       const bool ActionsRepeatingFile, const unsigned long int FrequencyCheckingFiles,
                       const unsigned short int FileModMethods);

signals:

};


#endif // FILEMODIFIER_H
