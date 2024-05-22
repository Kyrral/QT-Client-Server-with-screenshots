#include "screenshot.h"

void Screenshot::createFileName(const int& num) {
    fileName = dirName + "/" + QDateTime::currentDateTime().toString("yyyy.MM.dd") + "_" + QString::number(num) + ".png";
}

void Screenshot::saveFile() {
    if (!fileName.isEmpty()) {
        screenshot.save(fileName);
        setFileList();
        emit listIsReady();
    }
    else {
        qDebug() << "not saved";
    }
}

void Screenshot::configureImage() {
    int num = 0;
    do {
        screenshot = QGuiApplication::primaryScreen()->grabWindow(0);
        ++num;
        createFileName(num);
        saveFile();
        QThread::sleep(10);
    } while(true);
}

void Screenshot::makeScreenshots() {
    configureImage();
}

void Screenshot::setFileList() {
    QDir dir(dirName);
    actualFileList = dir.entryList(QDir::Files);
    emit listUpdated();
}

QList<QString>& Screenshot::getActualFileList() {
    return actualFileList;
}

Screenshot::Screenshot(const QString& dirName) : dirName(dirName) { };
