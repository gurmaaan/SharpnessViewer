#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QFileInfo>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QLabel>
#include <QGuiApplication>
#include <QScreen>
#include <QDialog>
#include <QDesktopWidget>

#include <static.h>

namespace Ui {
class ImageWidget;
}

class ImageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImageWidget(QWidget *parent = nullptr);
    ~ImageWidget();
    void loadImages(QString baseAbsolutePath, QStringList imagesLocalPathes);
    void setFrontImage(const QPixmap &value);
    void setImages(const QVector<QPixmap> &value);
    void scaleImage(int k);

public slots:
    void setBasePath(const QString &basePath);
    void setImgNames(const QStringList &imgNames);
    void on_plus_toolbtn_clicked();
    void on_minus_toolbtn_clicked();
    void on_fullscreen_toolbtn_clicked();

private slots:
    void on_preview_table_clicked(const QModelIndex &index);
    void on_zoom_v_slider_sliderMoved(int position);

private:
    Ui::ImageWidget *ui;
    QStandardItemModel *previewModel_;
    QPixmap frontImage_;
    QVector<QPixmap> images_;
    QString basePath_;
    QStringList imgNames_;
    QGraphicsScene *scene_;
    int k_;

    bool fileExists(QString path);
    QSize scaledSize(int k);
    QPixmap createPixmapWithtext(QString text, QSize size = QSize(100, 100));
};

#endif // IMAGEWIDGET_H
