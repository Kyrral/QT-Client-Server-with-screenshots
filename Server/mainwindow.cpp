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

void MainWindow::getServer(Server* server) {
    this->server = server;

    connect(this, &MainWindow::chosen, this, &MainWindow::checkRequestStatus);

    connect(ui->list_clients, &QListWidget::itemClicked, this, &MainWindow::setClient);
    connect(ui->list_clients, &QListWidget::itemClicked, this, &MainWindow::displayFiles);
    connect(ui->list_files, &QListWidget::itemClicked, this, &MainWindow::setFilename);
    connect(ui->btn_request, &QPushButton::clicked, server, &Server::aware);

    connect(server, &Server::clientDisconnected, this, &MainWindow::clearRequest);
    connect(server, &Server::fileListUpdated, this, &MainWindow::displayFiles);
    connect(server, &Server::clientListUpdated, this, &MainWindow::displayClients);
    connect(server, &Server::saved, this, &MainWindow::setPic);
}

void MainWindow::clearRequest(int id) {
    if(id == ui->label_chosenClient->text().toInt()) {
        ui->label_chosenClient->clear();
        ui->label_chosenFile->clear();
        ui->list_files->clear();
        ui->btn_request->setEnabled(false);
    }
}

void MainWindow::setClient(QListWidgetItem* item) {
    ui->label_chosenClient->setText(item->text());
    emit chosen();
}

void MainWindow::setFilename(QListWidgetItem* item) {
    ui->label_chosenFile->setText(item->text());
    server->setFilename(ui->label_chosenFile->text());
    emit chosen();
}

void MainWindow::checkRequestStatus() {
    if(!(ui->label_chosenClient->text().isEmpty()) && !(ui->label_chosenFile->text().isEmpty()))
        ui->btn_request->setEnabled(true);
    server->setClientID(ui->label_chosenClient->text());
}

void MainWindow::setPic(QPixmap pixmap) {
    int labelWidth = ui->label_pic->width();
    int labelHeight = ui->label_pic->height();

    if(!pixmap.isNull()) {
        scaledPixmap = pixmap.scaled(labelWidth, labelHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        ui->label_pic->setPixmap(scaledPixmap);

        ui->label_pic->setScaledContents(false);
    }
}

void MainWindow::displayFiles() {
    ui->list_files->clear();

    auto clientsList = server->getClientsList();

    if (!clientsList.empty()) {
        if (ui->label_chosenClient->text() == "")
            server->setClientID(QString::number((*clientsList[0]).getId()));
        else server->setClientID(ui->label_chosenClient->text());
    }

    auto files = server->getFileList();
    if(!files.empty())
        for(const QString& str : files)
            ui->list_files->addItem(new QListWidgetItem(str));

    if (ui->list_files->findItems(ui->label_chosenFile->text(), Qt::MatchExactly).empty()) {
        ui->label_chosenFile->clear();
        ui->btn_request->setEnabled(false);
    }
}

void MainWindow::displayClients() {
    ui->list_clients->clear();

    auto clientsList = server->getClientsList();
    if(!clientsList.empty())
        for(ClientSocket* socket : clientsList)
            ui->list_clients->addItem(QString::number(socket->getId()));
}
