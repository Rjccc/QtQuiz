#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    server = new cServer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotPBServerToggled()
{
    if(server->isStarted())
    {
        server->stopServer();
        if(!server->isStarted())
        {
            ui->lStatus->setText("off");
            ui->pbServer->setText("Start server");
        }
    }   else
    {
        server->startServer();
        if(server->isStarted())
        {
            ui->lStatus->setText("started");
            ui->pbServer->setText("Turn off server");
        }
    }
}
