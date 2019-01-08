#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QGraphicsView>
#include <QDesktopServices>
#include <QTemporaryDir>
#include <QGuiApplication>
#include <QUrl>
//
#include <static.h>
#include "widgets/clickablegraphicsscene.h"
#include "widgets/imagewidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void messageReceiver(QString msgText);

private slots:
    void on_actionOpenFolder_triggered();
    void on_actionNextImg_triggered();
    void on_actionPreviousImg_triggered();
    void on_actionLastImg_triggered();
    void on_actionFirstImg_triggered();
    void on_actionChoseFragment_triggered();
    void on_actionChangeFragment_triggered();
    void on_actionFragmentForAll_triggered(bool checked);
    void on_actionFragmentForCurrent_triggered(bool checked);
    void on_fragmentModeAll_rb_clicked(bool checked);
    void on_fragmentModeCurrent_rb_clicked(bool checked);
    void on_actionbaseImgAccept_triggered();
    void on_actionBaseImgReset_triggered();
    void on_actionGitHub_triggered();
    void on_actionOpenManual_triggered();
    void on_actionOpenDevReference_triggered();
    void on_actionBuildPlot_triggered();
    void on_actionSaveImgs_triggered();
    void on_actionUndoSave_triggered();

private:
    //varibles
    Ui::MainWindow *ui;
    QGraphicsView *view_;
    ClickableGraphicsScene *scene_;

    //methods
    void connectAll();
    void setupWidgets();
    void openResFile(const QString &resPath, const QString &tempFileName);
};

#endif // MAINWINDOW_H
