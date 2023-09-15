
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QScrollArea>
#include <QVBoxLayout>
#include "renderarea.h"
#include "binarysearchtree.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QWidget *centralWidget;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    RenderArea *renderArea;
    QPushButton *deleteButton;
    QPushButton *insertButton;
    QPushButton *searchButton;
    QLineEdit *insertValueLineEdit;
    QLineEdit *deleteValueLineEdit;
    QLineEdit *searchValueLineEdit;
    QScrollArea *ScrollArea;
    QVBoxLayout *mainLayout;
    BinarySearchTree *bst;


private slots:
    void insertClicked() const;
    void deleteClicked() const;
    void searchClicked() const;
};

#endif // MAINWINDOW_H
