#ifndef CLICKABLEGRAPHICSSCENE_H
#define CLICKABLEGRAPHICSSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>

class ClickableGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit ClickableGraphicsScene(QObject *parent = nullptr);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * mouseEvent);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent);

signals:

public slots:

private:

};

#endif // CLICKABLEGRAPHICSSCENE_H
