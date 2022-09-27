#ifndef FILEMODIFIER_H
#define FILEMODIFIER_H

#include <QObject>
#include <QQuickItem>


class FileModifier : public QObject
{
    Q_OBJECT
public:
    explicit FileModifier(QObject *parent = nullptr);

public slots:
    void setUpSettings();

signals:

};


#endif // FILEMODIFIER_H
