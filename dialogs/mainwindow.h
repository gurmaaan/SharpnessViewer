#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <widgets/clickablegraphicsscene.h>
#include <QGraphicsView>
//
#include <static.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsView *view_;
    ClickableGraphicsScene *scene_;
};

#endif // MAINWINDOW_H
