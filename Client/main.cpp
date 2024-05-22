#include "mainwindow.h"
#include "client.h"
#include "screenshot.h"
#include "threadmanager.h"

#include <QApplication>
#include <QDir>

QString createDir();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Screenshot screenshot = Screenshot(createDir());
    Client* client = new Client;
    ThreadManager tm;
    MainWindow w;

    client->setScr(&screenshot);

    w.show();
    w.getClient(client);

    QObject::connect(client->getSocket(), &QTcpSocket::connected, [&client]() { emit client->listPrepaired(0); } );
    tm.makeThread(&w, &screenshot, client);

    tm.makeThread(client);

    return a.exec();
}

QString createDir() {
    QString folderPath = QDir::currentPath() + "/screenshots";
    QDir dir(folderPath);

    if (dir.exists()) qDebug() << "Folder already exists";
    else {
        dir.mkpath(folderPath);
        qDebug() << "Folder created successfully";
    }
    return folderPath;
}
