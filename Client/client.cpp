#include "client.h"

void Client::connectToServer() {
    emit finding();

    do {
        clientSocket->connectToHost("localhost", 55555);
    } while(!clientSocket->waitForConnected());
    emit connected();
}

void Client::onConnected() {
    connect(clientSocket, &QTcpSocket::connected, [this]() { prepareList(); });
    connect(this, &Client::listPrepaired, this, &Client::sendData);
    connect(this, &Client::filePrepaired, this, &Client::sendData);
    connect(clientSocket, &QTcpSocket::readyRead, this, &Client::receiveData);
    connect(this, &Client::received, this, &Client::prepareFile);
}

void Client::prepareFile() {
    QFile file(QDir::currentPath() + "/screenshots/" + requestedFilename);
    if (!file.open(QIODevice::ReadOnly)) qDebug() << "failed to open file";

    data = file.readAll();

    emit filePrepaired(1);
}

void Client::prepareList() {
    data = "list";
    for(const QString& filename : screenshot->getActualFileList()) {
        data += filename.toUtf8() + "\n";
    }

    emit listPrepaired(0);
}

void Client::sendData(bool checkType) {

    if(checkType) emit sendingFile();

    if(data.size() != 0) {
        clientSocket->write(data);
        clientSocket->write("end");
    }

    data.clear();

    if(checkType) emit sentFile();
}

void Client::setScr(Screenshot* scr) {
    this->screenshot = scr;
}

QString Client::getFilename() { return QString(requestedFilename); }

QTcpSocket* Client::getSocket() { return clientSocket; }

Client::~Client() { };

Client::Client(QObject *parent) : QObject(parent) {
    connect(clientSocket, &QTcpSocket::connected, this, &Client::onConnected);
}

void Client::receiveData() {
    emit receiving();
    requestedFilename = clientSocket->readAll();
    emit received();
}
