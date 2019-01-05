#include "clickablegraphicsview.h"
#include "ui_clickablegraphicsview.h"

ClickableGraphicsView::ClickableGraphicsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClickableGraphicsView)
{
    ui->setupUi(this);
}

ClickableGraphicsView::~ClickableGraphicsView()
{
    delete ui;
}
