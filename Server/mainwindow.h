#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QList>
#include <QListWidgetItem>
#include <QDir>

#include "server.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;

    Server* server = nullptr;

    QPixmap scaledPixmap;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void getServer(Server* server);

signals:
    void chosen();

private slots:
    void displayFiles();
    void displayClients();

    void setClient(QListWidgetItem* item);
    void setFilename(QListWidgetItem* item);
    void setPic(QPixmap pixmap);
    void clearRequest(int id);

    void checkRequestStatus();
};
