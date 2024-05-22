#include "threadmanager.h"

ThreadManager::ThreadManager() {}

void ThreadManager::makeThread(MainWindow* w, Screenshot* screenshot, Client* client) {
    w->setScr(screenshot);
    connect(screenshot, &Screenshot::listUpdated, client, &Client::prepareList);
    connect(screenshot, &Screenshot::listUpdated, w, &MainWindow::displayFiles);
    QThread* thread = new QThread();

    screenshot->moveToThread(thread);
    QObject::connect(thread, &QThread::started, screenshot, &Screenshot::makeScreenshots);
    QObject::connect(thread, &QThread::finished, screenshot, &Screenshot::deleteLater);
    thread->start();
}

void ThreadManager::makeThread(Client* client) {
    QThread* thread = new QThread();
    QObject::connect(thread, &QThread::started, client, &Client::connectToServer);
    QObject::connect(client->getSocket(), &QTcpSocket::disconnected, thread, &QThread::quit);
    QObject::connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    QObject::connect(thread, &QThread::finished, [&]() { makeThread(client); });
    client->moveToThread(thread);
    thread->start();
}
