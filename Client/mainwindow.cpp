#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getClient(Client* client) {
    this->client = client;
    connect(client, &Client::finding, [&]() { ui->label_connection_status->setText("Looking for server..."); });
    connect(client, &Client::connected, [&]() { ui->label_connection_status->setText("Connected successfully!"); });
    connect(client, &Client::receiving, [&]() { ui->label_receive_status->setText("Receiving request from server..."); });
    connect(client, &Client::received, [&]() { ui->label_receive_status->setText("Requested data: " + client->getFilename()); });
    connect(client, &Client::sendingFile, [&]() {ui->label_sending_status->setText("Sending data to server...");});
    connect(client, &Client::sentFile, [&]() {ui->label_sending_status->setText("File " + client->getFilename() + " sent successfully"); });
}

void MainWindow::setScr(Screenshot* screenshot) {
    this->screenshot = screenshot;
}

void MainWindow::displayFiles() {
    ui->list_files->clear();

    for(const QString& str : screenshot->getActualFileList()) {
        QListWidgetItem* item = new QListWidgetItem(str);
        ui->list_files->addItem(item);
    }
}
