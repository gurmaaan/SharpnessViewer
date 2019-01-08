#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showMaximized();
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
    connect(ui->actionFullScreen, &QAction::triggered,
            ui->img_view, &ImageWidget::showImgFullScreen);
    connect(ui->actionZoomIn, &QAction::triggered,
            ui->img_view, &ImageWidget::defaultZoomIn);
    connect(ui->actionZoomOut, &QAction::triggered,
            ui->img_view, &ImageWidget::defaultZoomOut);

    connect(ui->path_widget, &PathWidget::pathChanged,
            ui->img_view, &ImageWidget::setBasePath);
    connect(ui->img_view, &ImageWidget::imgCntChanged,
            ui->fileAll_sb, &QSpinBox::setMaximum);
    connect(ui->img_view, &ImageWidget::imgCntChanged,
            ui->fileAll_sb, &QSpinBox::setValue);
}

void MainWindow::setupWidgets()
{
    ui->path_widget->setDialogType(PathType::Folder);
}

void MainWindow::openResFile(const QString &resPath, const QString &tempFileName)
{
    //TODO отрефакторить чтобы без повторений (на свежую голову надо)
    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    QDir dir(appDataPath);
    QString tempFilePath = dir.path() + tempFileName;
    if ( !dir.exists() )
    {
        if ( dir.mkpath(appDataPath) )
        {
            QFile::copy(resPath, tempFilePath);
            QDesktopServices::openUrl( QUrl(FILEURL + tempFilePath, QUrl::TolerantMode) );
        }
        else
        {
            qDebug() << QString("Couldn't create %1").arg(appDataPath);
            messageReceiver(QString("Couldn't create %1").arg(appDataPath));
            return;
        }
    }
    else
    {
        QFile testFile(tempFilePath);
        if(testFile.exists())
            QDesktopServices::openUrl( QUrl(FILEURL + tempFilePath, QUrl::TolerantMode) );
        else
        {
            QFile::copy(resPath, tempFilePath);
            QDesktopServices::openUrl( QUrl(FILEURL + tempFilePath, QUrl::TolerantMode) );
        }

    }

}

void MainWindow::on_actionOpenFolder_triggered()
{
    ui->path_widget->setPath( ui->path_widget->initFileDialog() );
}

void MainWindow::on_actionNextImg_triggered()
{

}

void MainWindow::on_actionPreviousImg_triggered()
{

}

void MainWindow::on_actionLastImg_triggered()
{

}

void MainWindow::on_actionFirstImg_triggered()
{

}

void MainWindow::on_actionChoseFragment_triggered()
{

}

void MainWindow::on_actionChangeFragment_triggered()
{

}

void MainWindow::on_actionFragmentForAll_triggered(bool checked)
{
    ui->actionFragmentForCurrent->setChecked(!checked);
}

void MainWindow::on_actionFragmentForCurrent_triggered(bool checked)
{
    ui->actionFragmentForAll->setChecked(!checked);
}

void MainWindow::on_fragmentModeAll_rb_clicked(bool checked)
{
    on_actionFragmentForAll_triggered(checked);
    ui->actionFragmentForCurrent->setChecked(!checked);
}

void MainWindow::on_fragmentModeCurrent_rb_clicked(bool checked)
{
    on_actionFragmentForCurrent_triggered(checked);
    ui->actionFragmentForAll->setChecked(!checked);
}

void MainWindow::on_actionbaseImgAccept_triggered()
{

}

void MainWindow::on_actionBaseImgReset_triggered()
{

}

void MainWindow::on_actionGitHub_triggered()
{
    QDesktopServices::openUrl( QUrl(GITHUB) );
}

void MainWindow::on_actionOpenManual_triggered()
{
    openResFile(USERMANUAL_RES, USERMANUAL_FILENAME);
}

void MainWindow::on_actionOpenDevReference_triggered()
{
    openResFile(DEVREF_RES, DEVREF_FILENAME);
}

void MainWindow::on_actionBuildPlot_triggered()
{

}

void MainWindow::on_actionSaveImgs_triggered()
{

}

void MainWindow::on_actionUndoSave_triggered()
{

}
