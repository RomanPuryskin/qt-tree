
#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include "binarysearchtree.h"
//#include <QColor>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    RenderArea(BinarySearchTree *bst, QWidget *parent = 0);
//    QSize sizeHint() const override;
    void autoSize();

protected:
    void paintEvent(QPaintEvent *event) override;
private:
    BinarySearchTree *bst;
    int scale;
};

#endif // RENDERAREA_H
