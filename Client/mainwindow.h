#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "client.h"
#include "screenshot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void getClient(Client* client);
    void setScr(Screenshot* screenshot);

public slots:
    void displayFiles();

private:
    Ui::MainWindow *ui;

    Client* client = nullptr;
    Screenshot* screenshot = nullptr;
};
#endif // MAINWINDOW_H
