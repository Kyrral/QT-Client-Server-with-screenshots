#pragma once

#include <QObject>
#include <QtNetwork>
#include <QImage>
#include <QPixmap>
#include <QList>
#include <QDir>
#include <QAtomicInt>
#include <QThread>
#include <QMutex>

#include <clientsocket.h>

class Server : public QTcpServer
{
    Q_OBJECT

private:
    QMutex mtx;

    QList<ClientSocket*> clientsList = { };
    QStringList fileList = { };
    QString fileName;
    int clientID = 1;

    void incomingConnection(qintptr socketDescriptor) override;

    void checkFile();
    void removeClient();
    ClientSocket* findClient();

public:
    explicit Server(QObject* parent = nullptr);

    QStringList getFileList();
    QList<ClientSocket*> getClientsList();
    int getID();

    void setFilename(QString filename);
    void setClientID(QString cID);

public slots:
    void handleClient(qintptr socketDescriptor);
    void aware();

signals:
    void clientDisconnected(int id);
    void saved(QPixmap pixmap);
    void fileListUpdated();
    void clientListUpdated();
};
