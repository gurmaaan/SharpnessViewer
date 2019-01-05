#include "clickablegraphicsscene.h"

ClickableGraphicsScene::ClickableGraphicsScene(QObject *parent) :
    QGraphicsScene(parent)
{
    //this->setBackgroundBrush(Qt::gray);
}

void ClickableGraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QRectF pointBoundingRect(mouseEvent->scenePos(), QSizeF(20.0, 20.0));
    QGraphicsEllipseItem *point = new QGraphicsEllipseItem(pointBoundingRect);

    point->setPen(QPen(Qt::black, 2));
    point->setBrush(QBrush(Qt::red, Qt::Dense3Pattern));

    this->addItem(point);
}

void ClickableGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    qDebug() << "Размер сцены : " << this->sceneRect().size() << Q_FUNC_INFO << mouseEvent->scenePos();
}

void ClickableGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    qDebug() << "Размер сцены : " << this->sceneRect().size() << Q_FUNC_INFO << mouseEvent->scenePos();
}

void ClickableGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    qDebug() << "Размер сцены : " << this->sceneRect().size() << Q_FUNC_INFO << mouseEvent->scenePos();
}
