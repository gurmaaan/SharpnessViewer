#ifndef CLICKABLEGRAPHICSVIEW_H
#define CLICKABLEGRAPHICSVIEW_H

#include <QWidget>

namespace Ui {
class ClickableGraphicsView;
}

class ClickableGraphicsView : public QWidget
{
    Q_OBJECT

public:
    explicit ClickableGraphicsView(QWidget *parent = nullptr);
    ~ClickableGraphicsView();

private:
    Ui::ClickableGraphicsView *ui;
};

#endif // CLICKABLEGRAPHICSVIEW_H
