#include "binarysearchtree.h"

//------------Деструктор-------------//
BinarySearchTree::~BinarySearchTree()
{
    DestroyTree(m_root);
}

void BinarySearchTree::DestroyTree(Node *node)
{
    if(node)
    {
        DestroyTree(node->GetLeft());
        DestroyTree(node->GetRight());
        delete node;
    }

}
//----------------------------------//

//----Проверка на пустоту----//
bool BinarySearchTree::isEmpty()
{
    if (m_root == nullptr)
        return true;
    return false;
}
//---------------------------//

//----------------------Вставка элемента-----------------------//
BinarySearchTree::Node* BinarySearchTree::addNode(Node* root,int key)
{
    if (!root)
        root = new Node(key);
    else if (key < root->GetKey())
        root->SetLeft(addNode(root->GetLeft(), key));
    else if (key> root->GetKey())
        root->SetRight(addNode(root->GetRight(), key));
    return root;
}

void BinarySearchTree::addNode(int key)
{
    m_root = addNode(m_root,key);
}
//-------------------------------------------------------------//


// все позиции нод ставим на 0
void BinarySearchTree::resetNodePosition(Node *node)
{
    if (node == nullptr)
        return;
    resetNodePosition(node->GetLeft());
    node->SetX(0);
    resetNodePosition(node->GetRight());
    return;
}

//--------------------------рисование дерева----------------------------//
void BinarySearchTree::draw(QPainter *painter)
{

    if(isEmpty())
        return;
    resetNodePosition(m_root); // все позиции нод поставим на 0
    m_root->SetX(100); // поставили позицию корня
    this->recursiveDraw(m_root , painter); // рисуем дерево
    return;
}

void BinarySearchTree::recursiveDraw(Node *node, QPainter *painter)
{
    if (node == nullptr)
        return;
    //настроим окраску нод
    QBrush brush;
    brush.setColor(Qt::white);
    brush.setStyle(Qt::SolidPattern);
    painter->setBrush(brush);

    recursiveDraw(node->GetLeft(),painter); // рекурсивно рисуем левое поддерево
    int level = getNodeLevel(node); // найдем уровень вершины
    int y = level * nodeRadius * 2 + 50 * (level-1);//найдем координату (у) узла на основании уровня
    if (node->GetLeft() != nullptr)
    {
        node->SetX(getXofRightTree(node->GetLeft())+ nodeRadius+10); // обозначим координату Х для левого поддерева относительно правого
        //рисуем линию соединяющую кружочки
        painter -> drawLine(QPoint(node->GetX(), y + nodeRadius), QPoint(node->GetLeft()->GetX(),((level + 1)* nodeRadius * 2 + 50 * level) - nodeRadius));
    }
    else if (node->GetX() == 0)
        node->SetX(getXofParent(node) + nodeRadius+10);//для новой ноды найдем координату предка и относительно нее уже ставим эту ноду

    // рисуем ноду
    //если нода, которую ищем, меняем кисть чтобы ее окрасить и возвращаем обратно
    if(node == found)
    {
        brush.setColor(Qt::red);
        painter->setBrush(brush);
    }
    painter -> drawEllipse(QPoint(node->GetX(), y),nodeRadius,nodeRadius);// тут сам кружочек
    QRectF textBounds(node->GetX()-nodeRadius,y-nodeRadius,nodeRadius*2,nodeRadius*2);
    painter -> drawText(textBounds, Qt::AlignCenter, QString::number(node->GetKey()));// тут текст в кружочке
    brush.setColor(Qt::white);
    painter->setBrush(brush);

    //рекурсивно рисуем правое поддерево
    recursiveDraw(node->GetRight(),painter);

    if (node->GetRight() != nullptr)
        painter -> drawLine(QPoint(node->GetX(), y + nodeRadius), QPoint(node->GetRight()->GetX(),((level + 1)* nodeRadius*2 + 50 * level) - nodeRadius));//рисуем линию соединяющую кружочки
    return;
}
//-------------------------------------------------------------------------------//

// найдем уровень ноды чтобы потом определить координату у для рисования ноды
int BinarySearchTree::getNodeLevel(Node *node)
{
    int level = 1;
    Node *current = node;

    while(findParent(current,m_root) != nullptr){
        current = findParent(current,m_root);
        ++level;
    }
    return level;
}


int BinarySearchTree::getXofRightTree(Node *node)
{
    if(node->GetRight() == nullptr){
        return node->GetX();
    }
    return getXofRightTree(node->GetRight());
}

int BinarySearchTree::getXofParent(Node *node)
{
    Node *currentNode = findParent(node,m_root);

    while(currentNode->GetX() == 0)
        currentNode = findParent(currentNode,m_root);

    return currentNode->GetX();
}

//----------------- нахождения родителя узла---------------------//
BinarySearchTree::Node* BinarySearchTree::findParent(Node* node, Node* temp)
{
    if (m_root == node || temp == nullptr)
        return nullptr;

    if (temp->GetLeft() == node || temp->GetRight() == node)
        return temp;

    Node* parent = findParent(node, temp->GetLeft());
    if (parent != nullptr)
        return parent;

    parent = findParent(node, temp->GetRight());
    return parent;
}
//---------------------------------------------------------------//

//------------------------Удаление узла----------------------//
void BinarySearchTree::deleteNode(Node *node)
{

    Node *parent = findParent(node, m_root);
    if (parent == nullptr && node != m_root)
    {
        return;
    }

    Node *replace = nullptr;
    Node *temp = nullptr;
    // у узла нет потомков, а потомков много и не нужно
    if (node->GetLeft() == nullptr && node->GetRight() == nullptr)
        replace = nullptr;

    // у удаляемого узла только правый потомок, но есть же и левый
    else if (node->GetLeft() == nullptr && node->GetRight() != nullptr)
    {
        replace = node->GetRight();
    }

    // у удаляемого узла только левый потомок, а правый был выше
    else if (node->GetRight() == nullptr && node->GetLeft() != nullptr)
    {
        replace = node->GetLeft();
    }
    // у удаляемого узла два потомка
    else
    {
        temp = node->GetRight();
        while (temp->GetLeft() != nullptr)
            temp = temp->GetLeft();
        replace = temp;

        //найдем родителя у узла для замены
        Node *tempParent = findParent(temp, m_root);
        if (tempParent != node) {
            tempParent->SetLeft(replace->GetRight());
            replace->SetRight(node->GetRight());
        }
        replace->SetLeft(node->GetLeft());
    }

    if( parent != nullptr)
    {
        if (parent->GetLeft() == node)
            parent->SetLeft(replace);
        else
            parent->SetRight(replace);
        delete node;
    }
    else
    {
        delete m_root;
        m_root = replace;
    }

}


bool BinarySearchTree::deleteNode(int key) {
    Node *node =  searchNodeForDelete(key);
    if (!node)
        return false;

    deleteNode(node);
    return true;
}
//-----------------------------------------------------------//

//----------------------Поиск узла по ключу--------------------------//
BinarySearchTree::Node *BinarySearchTree::searchNode(Node* root, int key)
{
    if (root == nullptr || root->GetKey() == key)
        return root;

    if (root->GetKey() < key)
        return searchNode(root->GetRight(), key);

    return searchNode(root->GetLeft(), key);
}

BinarySearchTree::Node* BinarySearchTree::searchNodeForDelete(int key)
{
    return searchNode(m_root,key);
}

void BinarySearchTree::searchNode(int key)
{
    found = searchNode(m_root ,key);
}
//--------------------------------------------------------------------//
