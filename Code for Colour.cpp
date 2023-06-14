#include <bits/stdc++.h>
using namespace std;

struct node {
    int data{};
    node* left = nullptr;
    node* right = nullptr;
    node* parent = nullptr;
    <span style="color: #A6E22E;">string color;</span>
};

class RB_TREE {
    node* root;
public:
    RB_TREE() : root(nullptr) {}

    node* GetRoot(){ return root; }

    void InsertNode(int stuff) {
        if(root == nullptr){
            root = new node();
            root->data = stuff;
            root->parent = nullptr;
            <span style="color: #A6E22E;">root->color = "BLACK";</span>
            cout << "Element inserted.\n";
        }
        else {
            auto linker = GetRoot();
            node* newnode = new node();
            newnode->data = stuff;

            while(linker != nullptr){
                if(linker->data > stuff){
                    if(linker->left == nullptr){
                        linker->left = newnode;
                        <span style="color: #A6E22E;">newnode->color = "RED";</span>
                        newnode->parent = linker;
                        cout << "Element inserted.\n"; break; }
                    else { linker = linker->left; }
                } else {
                    if(linker->right == nullptr){
                        linker->right = newnode;
                        <span style="color: #A6E22E;">newnode->color = "RED";</span>
                        newnode->parent = linker;
                        cout << "Element inserted.\n"; break; }
                    else {  linker = linker->right; }
                }
            }
            RB_Insert_Fixup(newnode);
        }
    }

    void RB_Insert_Fixup(node* z) {
        while(z->parent->color == "RED") {
            auto grandparent = z->parent->parent;
            auto uncle = GetRoot();
            if(z->parent == grandparent->left) {
                if(grandparent->right) { uncle = grandparent->right; }
                if(uncle->color == "RED"){
                    z->parent->color = "BLACK";
                    uncle->color = "BLACK";
                    grandparent->color = "RED";
                    if(grandparent->data != root->data){ z = grandparent; }
                    else { break; }
                }
                else if(z == grandparent->left->right) {
                    LeftRotate(z->parent);
                }
                else {
                    z->parent->color = "BLACK";
                    grandparent->color = "RED";
                    RightRotate(grandparent);
                    if(grandparent->data != root->data){ z = grandparent; }
                    else { break; }
                }
            }
            else {
                if(grandparent->left) { uncle = grandparent->left; }
                if(uncle->color == "RED"){
                    z->parent->color = "BLACK";
                    uncle->color = "BLACK";
                    grandparent->color = "RED";
                    if(grandparent->data != root->data){ z = grandparent; }
                    else { break; }
                }
                else if(z == grandparent->right->left){
                    RightRotate(z->parent);
                }
                else {
                    z->parent->color = "BLACK";
                    grandparent->color = "RED";
                    LeftRotate(grandparent);
                    if(grandparent->data != root->data){ z = grandparent; }
                    else { break; }
                }
            }
        }
        root->color = "BLACK";
    }

    void LeftRotate(node* x) {
        auto y = x->right;
        x->right = y->left;
        if(y->left){ y->left->parent = x; }
        y->parent = x->parent;
        if(x->parent == nullptr){ root = y; }
        else if(x == x->parent->left){ x->parent->left = y; }
        else { x->parent->right = y; }
        y->left = x;
        x->parent = y;
    }

    void RightRotate(node* y) {
        auto x = y->left;
        y->left = x->right;
        if(x->right){ x->right->parent = y; }
        x->parent = y->parent;
        if(y->parent == nullptr){ root = x; }
        else if(y == y->parent->left){ y->parent->left = x; }
        else { y->parent->right = x; }
        x->right = y;
        y->parent = x;
    }

    void PrintTree(node* r, int s = 0) {
        if (r != nullptr) {
            PrintTree(r->right, s + 5);
            cout << setw(s) << " " << r->data << " (" << r->color << ")" << endl;
            PrintTree(r->left, s + 5);
        }
    }
};

int main() {
    RB_TREE rb;
    int choice, stuff;

    while(true) {
        cout << "\n-------------------------" << endl;
        cout << "Red-Black Tree Operations" << endl;
        cout << "-------------------------" << endl;
        cout << "1. Insert Element" << endl;
        cout << "2. Print Tree" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter element to be inserted: ";
                cin >> stuff;
                rb.InsertNode(stuff);
                break;
            case 2:
                cout << "\nRed-Black Tree:" << endl;
                rb.PrintTree(rb.GetRoot());
                break;
            case 3:
                cout << "Exiting..." << endl;
                exit(0);
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
    return 0;
}
