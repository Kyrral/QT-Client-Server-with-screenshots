#ifndef THREADMANAGERH_H
#define THREADMANAGERH_H

#include <QObject>
#include <QThread>

#include "mainwindow.h"
#include "screenshot.h"

class ThreadManager : public QObject
{
    Q_OBJECT

public:
    ThreadManager();

    void makeThread(MainWindow* w, Screenshot* screenshot, Client* client);
    void makeThread(Client* client);
};

#endif // THREADMANAGERH_H
