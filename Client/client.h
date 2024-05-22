#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QFile>
#include <QDir>

#include "screenshot.h"

class Client : public QObject
{
    Q_OBJECT
private:
    QTcpSocket* clientSocket = new QTcpSocket(this);
    QByteArray requestedFilename;

    QByteArray data { };

    Screenshot* screenshot = nullptr;

public:
    explicit Client(QObject *parent = nullptr);
    virtual ~Client() override;
    void connectToServer();
    void connectWithClient();

    QString getFilename();
    QTcpSocket* getSocket();
    void setScr(Screenshot* scr);

public slots:
    void onConnected();

    void receiveData();
    void sendData(bool checkType);

    void prepareFile();
    void prepareList();

signals:
    void connected();
    void finding();
    void sentFile();
    void sendingFile();
    void receiving();
    void received();
    void listPrepaired(bool checkType);
    void filePrepaired(bool checkType);
};
