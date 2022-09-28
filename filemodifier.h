#ifndef FILEMODIFIER_H
#define FILEMODIFIER_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QDirIterator>
#include <stack>
#include <iostream>

#include <QDebug>

class FileModifier : public QObject
{
    Q_OBJECT
public:
    explicit FileModifier(QObject *parent = nullptr);
    ~FileModifier();

    QStringList fileMask;
    bool deleteImputFile;
    QString foolder;
    bool ActionsRepeatingFile;
    unsigned long int FrequencyCheckingFiles;
    unsigned short int FileModMethods;

private:
    QFile* file;
    QDir* dir;
    std::stack<QString> fileList;

    const QFile* openFiles(const QString folder, QStringList fileFilters, QFile* file);

public slots:
    void setUpSettings(const QList<QString> &&fileMask, const bool deleteImputFile, const QString &foolder,
                       const bool ActionsRepeatingFile, const unsigned long int FrequencyCheckingFiles,
                       const unsigned short int FileModMethods);

signals:

};


#endif // FILEMODIFIER_H
