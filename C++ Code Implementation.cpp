#include <iostream>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node* left;
    Node* right;
    Node* parent;

    Node(int value) : data(value), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node* root;

public:
    RedBlackTree() : root(nullptr) {}

    Node* GetRoot() {
        return root;
    }

    void Insert(int value) {
        Node* newNode = new Node(value);
        Node* parent = nullptr;
        Node* current = root;

        while (current != nullptr) {
            parent = current;
            if (value < current->data)
                current = current->left;
            else
                current = current->right;
        }

        newNode->parent = parent;

        if (parent == nullptr)
            root = newNode;
        else if (value < parent->data)
            parent->left = newNode;
        else
            parent->right = newNode;

        InsertFixup(newNode);
        cout << "Element inserted.\n";
    }

    void InsertFixup(Node* node) {
        while (node != root && node->parent->color == RED) {
            Node* grandparent = node->parent->parent;

            if (node->parent == grandparent->left) {
                Node* uncle = grandparent->right;

                if (uncle != nullptr && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    node = grandparent;
                } else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        LeftRotate(node);
                    }

                    node->parent->color = BLACK;
                    grandparent->color = RED;
                    RightRotate(grandparent);
                }
            } else {
                Node* uncle = grandparent->left;

                if (uncle != nullptr && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    node = grandparent;
                } else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        RightRotate(node);
                    }

                    node->parent->color = BLACK;
                    grandparent->color = RED;
                    LeftRotate(grandparent);
                }
            }
        }

        root->color = BLACK;
    }

    void Remove(int value) {
        Node* node = Search(value);
        if (node == nullptr) {
            cout << "Element doesn't exist in the tree.\n";
            return;
        }

        Node* child = nullptr;
        Node* sibling = nullptr;

        if (node->left == nullptr || node->right == nullptr)
            child = node;
        else
            child = Successor(node);

        if (child->left != nullptr)
            sibling = child->left;
        else
            sibling = child->right;

        if (sibling != nullptr)
            sibling->parent = child->parent;

        if (child->parent == nullptr)
            root = sibling;
        else if (child == child->parent->left)
            child->parent->left = sibling;
        else
            child->parent->right = sibling;

        if (child != node)
            node->data = child->data;

        if (child->color == BLACK)
            RemoveFixup(sibling);

        delete child;
        cout << "Element removed.\n";
    }

    void RemoveFixup(Node* node) {
        while (node != root && node != nullptr && node->color == BLACK) {
            if (node == node->parent->left) {
                Node* sibling = node->parent->right;

                if (sibling != nullptr && sibling->color == RED) {
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    LeftRotate(node->parent);
                    sibling = node->parent->right;
                }

                if (sibling != nullptr && sibling->left != nullptr && sibling->right != nullptr &&
                    sibling->left->color == BLACK && sibling->right->color == BLACK) {
                    sibling->color = RED;
                    node = node->parent;
                } else {
                    if (sibling != nullptr && sibling->right != nullptr && sibling->right->color == BLACK) {
                        sibling->left->color = BLACK;
                        sibling->color = RED;
                        RightRotate(sibling);
                        sibling = node->parent->right;
                    }

                    if (sibling != nullptr)
                        sibling->color = node->parent->color;

                    node->parent->color = BLACK;
                    sibling->right->color = BLACK;
                    LeftRotate(node->parent);
                    node = root;
                }
            } else {
                Node* sibling = node->parent->left;

                if (sibling != nullptr && sibling->color == RED) {
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    RightRotate(node->parent);
                    sibling = node->parent->left;
                }

                if (sibling != nullptr && sibling->right != nullptr && sibling->left != nullptr &&
                    sibling->right->color == BLACK && sibling->left->color == BLACK) {
                    sibling->color = RED;
                    node = node->parent;
                } else {
                    if (sibling != nullptr && sibling->left != nullptr && sibling->left->color == BLACK) {
                        sibling->right->color = BLACK;
                        sibling->color = RED;
                        LeftRotate(sibling);
                        sibling = node->parent->left;
                    }

                    if (sibling != nullptr)
                        sibling->color = node->parent->color;

                    node->parent->color = BLACK;
                    sibling->left->color = BLACK;
                    RightRotate(node->parent);
                    node = root;
                }
            }
        }

        if (node != nullptr)
            node->color = BLACK;
    }

    Node* Search(int value) {
        return SearchNode(root, value);
    }

    Node* Minimum(Node* node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    Node* Maximum(Node* node) {
        while (node->right != nullptr)
            node = node->right;
        return node;
    }

    Node* Successor(Node* node) {
        if (node->right != nullptr)
            return Minimum(node->right);

        Node* parent = node->parent;
        while (parent != nullptr && node == parent->right) {
            node = parent;
            parent = parent->parent;
        }
        return parent;
    }

    Node* Predecessor(Node* node) {
        if (node->left != nullptr)
            return Maximum(node->left);

        Node* parent = node->parent;
        while (parent != nullptr && node == parent->left) {
            node = parent;
            parent = parent->parent;
        }
        return parent;
    }

    void LeftRotate(Node* node) {
        Node* rightChild = node->right;
        node->right = rightChild->left;

        if (rightChild->left != nullptr)
            rightChild->left->parent = node;

        rightChild->parent = node->parent;

        if (node->parent == nullptr)
            root = rightChild;
        else if (node == node->parent->left)
            node->parent->left = rightChild;
        else
            node->parent->right = rightChild;

        rightChild->left = node;
        node->parent = rightChild;
    }

    void RightRotate(Node* node) {
        Node* leftChild = node->left;
        node->left = leftChild->right;

        if (leftChild->right != nullptr)
            leftChild->right->parent = node;

        leftChild->parent = node->parent;

        if (node->parent == nullptr)
            root = leftChild;
        else if (node == node->parent->left)
            node->parent->left = leftChild;
        else
            node->parent->right = leftChild;

        leftChild->right = node;
        node->parent = leftChild;
    }

    void PrintTree() {
        PrintInOrder(root);
    }

    void PrintInOrder(Node* node) {
        if (node != nullptr) {
            PrintInOrder(node->left);
            cout << node->data << "(" << ((node->color == RED) ? "Red" : "Black") << ") ";
            PrintInOrder(node->right);
        }
    }
};

int main() {
    RedBlackTree tree;

    tree.Insert(7);
    tree.Insert(3);
    tree.Insert(18);
    tree.Insert(10);
    tree.Insert(22);
    tree.Insert(8);
    tree.Insert(11);
    tree.Insert(26);
    tree.Insert(2);
    tree.Insert(6);
    tree.Insert(13);

    tree.PrintTree();

    cout << "\n\n";

    tree.Remove(18);
    tree.Remove(11);
    tree.Remove(3);
    tree.Remove(10);
    tree.Remove(22);
    tree.Remove(8);
    tree.Remove(26);

    tree.PrintTree();

    return 0;
}
