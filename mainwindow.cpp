
#include "mainwindow.h"

#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    bst = new BinarySearchTree;

    deleteButton = new QPushButton("Удалить", this); // добавили кнопку Удалить
    insertButton = new QPushButton("Вставить", this); // добавили кнопку Вставить
    searchButton = new QPushButton("Найти",this); // добавили кнопку Найти
    insertValueLineEdit = new QLineEdit; // добавили поля для ввода чисел
    deleteValueLineEdit = new QLineEdit; //
    searchValueLineEdit = new QLineEdit; //


    // добавляем связь поле задействовано - действие
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteClicked()));
    connect(insertButton, SIGNAL(clicked()), this, SLOT(insertClicked()));
    connect(searchButton , SIGNAL(clicked()), this , SLOT(searchClicked()));
    connect(searchValueLineEdit, SIGNAL(returnPressed()),this , SLOT(searchClicked()));
    connect(insertValueLineEdit, SIGNAL(returnPressed()), this, SLOT(insertClicked()));
    connect(deleteValueLineEdit, SIGNAL(returnPressed()), this, SLOT(deleteClicked()));

    // добавляем наши кнопки на поле
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(deleteValueLineEdit);
    buttonLayout->addWidget(insertButton);
    buttonLayout->addWidget(insertValueLineEdit);
    buttonLayout->addWidget(searchButton);
    buttonLayout->addWidget(searchValueLineEdit);
    buttonLayout->addStretch(0);

    renderArea = new RenderArea(bst);   //
    ScrollArea = new QScrollArea;       // создаем поле
    ScrollArea->setWidget(renderArea);  //

    mainLayout = new QVBoxLayout;   //создаем главный
    mainLayout->addWidget(ScrollArea); // добавляем туда поле для рисования
    mainLayout->addLayout(buttonLayout); // добавляем все кнопочки

    // создаем наше окно приложения
    centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    this->setCentralWidget(centralWidget);
    this->setWindowTitle("Дерево поиска GUI");
}

MainWindow::~MainWindow()
{
    delete renderArea;
    delete deleteButton;
    delete insertButton;
    delete searchButton;
    delete ScrollArea;
    delete bst;
    delete centralWidget;
}

// Описание действия кнопки Удалить
void MainWindow::deleteClicked() const
{
    QString value = deleteValueLineEdit->text(); // считали число

    this->bst->deleteNode(value.toInt()); // удалили его из дерева

    renderArea->repaint(); // перерисовываем
    deleteValueLineEdit->setText(""); //очистили поле для ввода нового числа
}

// описание действия кнопки Вставить
void MainWindow::insertClicked() const
{
    QString value = insertValueLineEdit->text(); // считали число
    bst->addNode(value.toInt()); // вставили его в дерево
    renderArea->repaint(); // перерисовываем
    insertValueLineEdit->setText(""); // очистили поле для ввода нового числа
}

//описание кнопки найти
void MainWindow::searchClicked() const
{
    QString value = searchValueLineEdit->text(); //считали число
    bst->searchNode(value.toInt());
    renderArea->repaint();
    searchValueLineEdit->setText("");
}

