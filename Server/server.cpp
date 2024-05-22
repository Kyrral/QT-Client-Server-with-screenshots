#include "server.h"
#include <QDebug>

Server::Server(QObject* parent) : QTcpServer(parent) { }

void Server::incomingConnection(qintptr socketDescriptor){
    QThread* thread = new QThread();
    connect(thread, &QThread::started, [=, this]() { handleClient(socketDescriptor); });
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    thread->start();
}

void Server::aware() { emit findClient()->sendAware(fileName); }

void Server::handleClient(qintptr socketDescriptor) {

    QThread* thread = QThread::currentThread();
    ClientSocket* newClientSocket = new ClientSocket(nullptr);

    if(!newClientSocket->setSocketDescriptor(socketDescriptor)) return;

    mtx.lock();
    clientsList.append(newClientSocket);
    mtx.unlock();

    emit clientListUpdated();

    connect(newClientSocket, &QTcpSocket::disconnected, this, &Server::removeClient);
    connect(newClientSocket, &ClientSocket::saved, [&](QPixmap pixmap) { emit saved(pixmap); } );

    connect(newClientSocket, &QTcpSocket::disconnected, thread, &QThread::quit);
    connect(thread, &QThread::finished, newClientSocket, &QTcpSocket::close);
    connect(thread, &QThread::finished, newClientSocket, &QTcpSocket::deleteLater);

    connect(newClientSocket, &ClientSocket::fileListUpdated, [this](){ emit fileListUpdated(); } );
}

ClientSocket* Server::findClient() {
    if(clientsList.empty()) return nullptr;
    mtx.lock();
    auto list = clientsList;
    mtx.unlock();

    auto clientSocket = list.end();
    for(auto iter = list.begin(); iter != list.end(); ++iter) {
        if((*iter)->getId() == clientID) {
            clientSocket = iter;
            break;
        }
    }
    return *clientSocket;
}

void Server::removeClient() {
    ClientSocket* socket = qobject_cast<ClientSocket*>(sender());
    mtx.lock();
    clientsList.removeOne(socket);
    mtx.unlock();

    emit clientDisconnected(socket->getId());
    emit clientListUpdated();
}

QStringList Server::getFileList() { return findClient()->getFileList(); }
int Server::getID() { return clientID; }
QList<ClientSocket*> Server::getClientsList(){ return clientsList; }

void Server::setFilename(QString filename) { this->fileName = filename; }
void Server::setClientID(QString cID){ this->clientID = cID.toInt(); }
