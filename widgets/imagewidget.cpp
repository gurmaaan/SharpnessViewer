#include "imagewidget.h"
#include "ui_imagewidget.h"

ImageWidget::ImageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageWidget)
{
    ui->setupUi(this);
    previewModel_ = new QStandardItemModel;
    scene_ = new ClickableGraphicsScene;
    scaleRatio_ = 0;

    ui->preview_table->setModel(previewModel_);
    ui->main_photo_gv->setScene(scene_);
}

ImageWidget::~ImageWidget()
{
    delete ui;
}

void ImageWidget::loadImages(QString baseAbsolutePath, QStringList imagesLocalPathes)
{
    previewModel_->clear();
    QList<QStandardItem*> previewRow;
    QList<QStandardItem*> imgNameRow;
    QVector<QPixmap> imgVector;
    for (int i = 0; i < imagesLocalPathes.size(); i++)
    {
        QString imgName = imagesLocalPathes.at(i);
        QString fullPath = baseAbsolutePath + "/" + imgName;
        QPixmap pixMapAtI(fullPath);
        imgVector.push_back(pixMapAtI);
        QStandardItem* item = new QStandardItem();
        QFileInfo imgFile(fullPath);
        if(imgFile.exists() && imgFile.isFile())
        {
            item->setIcon(pixMapAtI);
        }
        else
        {            
            QString errorMsg = imagesLocalPathes.at(i) + "\n" + "doesn't exist";
            qDebug() << errorMsg << endl << fullPath << endl;
            QPixmap nullPixmap = createPixmapWithtext(errorMsg);
            item->setIcon(QIcon(nullPixmap));
        }
        previewRow.append(item);
        QStandardItem* nameItem = new QStandardItem(imgName);
        nameItem->setStatusTip(imgName);
        nameItem->setWhatsThis(imgName);
        imgNameRow.append(nameItem);
    }

    setImages(imgVector);
    setFrontImage(imgVector.first());

    previewModel_->appendRow(previewRow);
    previewModel_->appendRow(imgNameRow);
    ui->preview_table->setRowHeight(0,100);
    ui->preview_table->setCurrentIndex( ui->preview_table->model()->index(0,0));
}

QSize ImageWidget::scaledSize(int k)
{
    double H0 = static_cast<double>(frontImage_.height());
    double W0 = static_cast<double>(frontImage_.width());
    double dk = static_cast<double>(k) / static_cast<double>(100);

    int W = static_cast<int>(W0 + W0*dk);
    int H = static_cast<int>(H0 + H0*dk);

    return QSize(W, H);
}

QPixmap ImageWidget::createPixmapWithtext(QString text, QSize size)
{
    QPixmap pixmap(size);
    pixmap.fill( QColor(Qt::white) );
    QPainter painter( &pixmap );
    painter.setFont( QFont("Arial") );
    painter.drawText( QPoint(size.width() / 2, size.height() / 2), text );
    return pixmap;
}

void ImageWidget::setImgNames(const QStringList &imgNames)
{
    imgNames_ = imgNames;
}

void ImageWidget::scaleImage(int k)
{
    scene_->clear();
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(frontImage_.scaled(scaledSize(k), Qt::KeepAspectRatio));
    scene_->addItem(item);

    ui->main_photo_gv->show();
    ui->main_photo_gv->mapToScene(ui->main_photo_gv->rect().center() );
}

void ImageWidget::setBasePath(const QString &basePath)
{
    QDir rootDir(basePath);
    if(rootDir.exists())
    {
        basePath_ = basePath;
        QStringList localPathes = rootDir.entryList(QDir::Files);
        if(!localPathes.isEmpty())
        {
            setImgNames(localPathes);
            emit imgCntChanged(localPathes.count());
            loadImages(basePath, localPathes);
        }
        else
        {
            qDebug() << QString("Error. Folder %1 doesn't contain eny files.").arg(basePath) << endl;
            qDebug() << "Folder contains: " << rootDir.entryList();
            return;
        }
    }
    else
    {
        qDebug() << QString("Error. Folder %1 doen't exists").arg(basePath);
    }
}

void ImageWidget::setImages(const QVector<QPixmap> &value)
{
    images_ = value;
}

void ImageWidget::setFrontImage(const QPixmap &value)
{
    frontImage_ = value;

    scaleImage(0);
}

void ImageWidget::on_fullscreen_toolbtn_clicked()
{
    showImgFullScreen();
}

void ImageWidget::on_preview_table_clicked(const QModelIndex &index)
{
    setFrontImage(images_.at(index.column()));
}

void ImageWidget::on_plus_toolbtn_clicked()
{
    defaultZoomIn();
}

void ImageWidget::on_minus_toolbtn_clicked()
{
    defaultZoomOut();
}

void ImageWidget::defaultZoomIn()
{
    setScaleRatio(scaleRatio_+=5);
}

void ImageWidget::defaultZoomOut()
{
    setScaleRatio(scaleRatio_-=5);
}

void ImageWidget::on_zoom_v_slider_sliderMoved(int position)
{
    scaleRatio_ = position;
    scaleImage(scaleRatio_);
}

int ImageWidget::scaleRatio() const
{
    return scaleRatio_;
}

void ImageWidget::setScaleRatio(int k)
{
    scaleRatio_ = k;
    scaleImage(scaleRatio_);
    ui->zoom_v_slider->setValue(scaleRatio_);
}

void ImageWidget::showImgFullScreen()
{
    QDialog *fsDialog = new QDialog;
    QVBoxLayout *layout = new QVBoxLayout;
    QLabel *label = new QLabel;

    QPixmap activePm;
    if(!images_.empty())
    {
        int index = ui->preview_table->selectionModel()->selectedIndexes().first().column();
        if(index >= 0)
            activePm = images_.at(index);
        else
            activePm = images_.first();
    }
    else
        activePm = createPixmapWithtext( "NULL", QGuiApplication::screens().first()->size() );

    label->setPixmap(activePm.scaled( QGuiApplication::screens().first()->size() ));
    layout->addWidget(label);
    fsDialog->setLayout(layout);
    fsDialog->showFullScreen();
}
