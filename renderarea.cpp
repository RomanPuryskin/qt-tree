
#include "renderarea.h"
#include <QApplication>
#include <QPainter>
#include <QHBoxLayout>

RenderArea::RenderArea(BinarySearchTree *bst, QWidget *parent) : QWidget(parent), bst(),
    scale(1)
{
    this->bst = bst;
    setLayout(new QHBoxLayout());
}


//QSize RenderArea::sizeHint() const
//{
//   return QSize(50, 50); // поставим сразу размер окошка
//}

void RenderArea::paintEvent(QPaintEvent*)
{
    if (bst->isEmpty())
        return;
    QPainter painter(this); // создаем пеинтер
    bst->draw(&painter); // рисуем дерево нашим пеинтером
    autoSize();// после нарисовки дерева нужно снова поставить размер
}

void RenderArea::autoSize()
{
    QSize size(10000,10000);
    resize(size);
}
