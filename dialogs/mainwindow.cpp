#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connectAll();
    setupWidgets();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::messageReceiver(QString msgText)
{
    ui->statusBar->showMessage(msgText);
}

void MainWindow::connectAll()
{

}

void MainWindow::setupWidgets()
{
    ui->path->setDialogType(PathType::Folder);
}
