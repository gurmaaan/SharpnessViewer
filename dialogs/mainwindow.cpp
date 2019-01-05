#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    view_ = ui->graphicsView;
    scene_ = new ClickableGraphicsScene;
    view_->setScene(scene_);
}

MainWindow::~MainWindow()
{
    delete ui;
}
