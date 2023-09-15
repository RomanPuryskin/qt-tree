
#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_
#include <QPainter>
class BinarySearchTree
{
public:
    class Node
    {
    public:
        Node(int key)
        {
            m_key = key;
            x = 0;
            m_left = nullptr;
            m_right = nullptr;
        }
        ~Node() = default;
        int GetKey() { return m_key; }
        void SetKey(int key) { m_key = key; }
        Node *GetLeft() { return m_left; }
        Node *GetRight() { return m_right; }
        void SetLeft(Node *left) { m_left = left; }
        void SetRight(Node *right) { m_right = right; }
        void SetX(int pos) {x = pos ;}
        int GetX(){return x;}
    private:
        int m_key;
        int x;//координата х ноды
        Node *m_left;
        Node *m_right;
    };
    BinarySearchTree() {m_root = nullptr;}
    ~BinarySearchTree();
    void addNode (int key);
    void draw(QPainter *painter);
    bool deleteNode(int key);
    bool isEmpty();
    void searchNode(int key);
private:
    QPainter *painter;
    Node* found; // окрашиваемая нода для поиска
    Node *m_root;
    int nodeRadius = 20;
    void DestroyTree(Node *);
    Node* addNode(Node* root,int key);
    void deleteNode(Node *node);
    Node* findParent(Node* node, Node* temp);
    Node* searchNode(Node* root, int key);
    Node* searchNodeForDelete(int key);
    void recursiveDraw(Node *node,QPainter *painter);
    int getNodeLevel(Node *node);
    int getXofRightTree(Node *node);
    int getXofParent(Node *node);
    void resetNodePosition(Node *node);
};


#endif /* BINARYSEARCHTREE_H_ */
