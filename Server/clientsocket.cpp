#include "clientsocket.h"

QAtomicInt ClientSocket::counter = 0;

ClientSocket::ClientSocket(QObject *parent) : QTcpSocket(parent) {
    ID = ++counter;

    connect(this, &ClientSocket::receivedFile, this, &ClientSocket::processFile);
    connect(this, &ClientSocket::receivedList, this, &ClientSocket::processList);
    connect(this, &ClientSocket::sendAware, this, &ClientSocket::sendData);
    connect(this, &QTcpSocket::readyRead, this, &ClientSocket::receiveData);
};

ClientSocket::ClientSocket (const ClientSocket& other) : QTcpSocket(other.parent()) {
    this->ID = other.ID;
    this->fileList = other.fileList;
}

void ClientSocket::setFileList(QStringList newList) {
    fileList.clear();
    fileList = newList;
}

QStringList ClientSocket::getFileList() const { return fileList; }
int ClientSocket::getId() const { return ID; }

void ClientSocket::sendData(const QString& filename) {
    this->filename = filename;
    write(this->filename.toUtf8());
    // qDebug() << "data sent";
}

void ClientSocket::receiveData() {
    // qDebug() << "Receiving data";

    data += readAll();

    if(data.contains("end")) {
        // qDebug() << "All data received, processing...";

        data.remove(data.indexOf("\nend"), 4);

        if(data.contains("list")) emit receivedList();
        else emit receivedFile();
    }
}

void ClientSocket::processFile() {
    // qDebug() << "processing file";
    saveScreenshot();
    data.clear();
}

void ClientSocket::processList() {
    if(data.size() != 0)
    {
        QStringList tempList;

        mtx.lock();
        QList<QByteArray> preList = data.split('\n');
        for(int i = 0; i < preList.size(); ++i) {
            QByteArray& filename = preList[i];
            if(i == 0 && filename.startsWith("list")) {
                filename.remove(0, 4);
            }
            tempList.append(QString::fromUtf8(filename));
        }

        data.clear();

        mtx.unlock();

        setFileList(tempList);
        emit fileListUpdated();
    }
}

void ClientSocket::saveScreenshot() {
    checkFile();
    QImage image;

    if(data.size() != 0) image.loadFromData(data);

    pixmap = new QPixmap(QPixmap::fromImage(image));
    mtx.lock();
    pixmap->save(QDir::currentPath() + "/screenshots/" + filename + ".png");
    mtx.unlock();

    emit saved(*pixmap);

    data.clear();

    // qDebug() << "sreenshot saved successfully!";
}

void ClientSocket::checkFile() {
    QDir dir(QDir::currentPath() + "/screenshots/");
    dir.setNameFilters(QStringList("*.png"));

    QStringList fileList = dir.entryList(QDir::Files);

    foreach(const QString& listFileName, fileList) {
        QFile file(dir.absoluteFilePath(listFileName));
        file.remove();
    }
}
