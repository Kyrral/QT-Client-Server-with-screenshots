#pragma once
#include <QPixmap>
#include <QScreen>
#include <QFileDialog>
#include <QObject>
#include <QString>
#include <QDateTime>
#include <QThread>
#include <QList>

class Screenshot : public QObject
{
    Q_OBJECT
private:
    QPixmap screenshot;
    QString dirName;
    QString fileName;

    QList<QString> actualFileList { };
    // QList<QString> formerFileList { };

    void createFileName(const int& num);
    void configureImage();
    void saveFile();

    void setFileList();

public:
    void makeScreenshots();
    QList<QString>& getActualFileList();
    // QList<QString>& getFormerFileList();

    Screenshot(const QString& dirName);

signals:
    void listUpdated();
    void listIsReady();
};
