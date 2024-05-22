#include "mainwindow.h"
#include "server.h"

#include <QApplication>

QString createDir();

int main(int argc, char *argv[]) {
    createDir();

    Server* server = new Server();
    QApplication a(argc, argv);
    MainWindow w;

    if(!server->listen(QHostAddress::Any, 55555)){
        qDebug() << "Failed to start server: " << server->errorString();
        return 1;
    }

    w.show();

    w.getServer(server);

    return a.exec();
}

QString createDir() {
    QString folderPath = QDir::currentPath() + "/screenshots";
    QDir dir(folderPath);

    if (dir.exists()) qDebug() << "Folder already exists";
    else dir.mkpath(folderPath);
    return folderPath;
}
