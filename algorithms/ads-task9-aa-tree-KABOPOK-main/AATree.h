#include <iostream>
#include <fstream>
struct Node{
    Node* right;
    Node* left;
    Node* parent;
    int level;
    int power;

    Node(int power) : right(nullptr), left(nullptr), parent(nullptr), level(1), power(power) {}
    Node* minimum() {
        Node* now = this;
        while (now->left != nullptr) {
            now = now->left;
        }
        return now;
    }
    ~Node(){
        delete left;
        delete right;
    }

};

class AATree{
    Node* root;
    void skew(Node *T){
        if(!T){return;}
        if(!T->left){return;}
        if(T->level != T->left->level){return;}

        Node *B = T->left->right;
        Node *L = T->left;

        L->right = T;
        T->left = B;
        if(B){B->parent = T;}

        L->parent = T->parent;
        T->parent = L;
        if(L->parent != nullptr){
            if(L->parent->left == T){
                L->parent->left = L;
            }
            else{
                L->parent->right = L;
            }
        }
        else{
            root = L;
        }
    }
    void split(Node *T){
        if(!T){return;}
        if(!T->right){return;}
        if(!T->right->right){return;}
        if(!(T->level == T->right->level && T->right->level == T->right->right->level)){return;}

        Node* R = T->right;;
        Node* B = R->left;;

        T->right = B;
        if(B){B->parent = T;}

        R->parent = T->parent;
        T->parent = R;
        R->left = T;
        if(R->parent){
            if(R->parent->left == T){
                R->parent->left = R;
            }
            else{
                R->parent->right = R;
            }
        }
        else{
            root = R;
        }

        ++R->level;
    }
public:
    AATree():root(nullptr){}
    int getBalance()const {
        if (root) { return root->level; }
        return 0;
    }
    void insert(int X) {
        if (root == nullptr) {
            root = new Node(X);
            return;
        }
        Node* tmp(root);
        Node* p(root);
        bool isLeft;
        //>=
        while (tmp) {
            p = tmp;
            if (X < tmp->power) {
                tmp = tmp->left;
                isLeft = true;
            }
            else {
                tmp = tmp->right;
                isLeft = false;
            }
        }
        tmp = new Node(X);
        tmp->parent = p;
        if (isLeft) {
            p->left = tmp;
        }
        else {
            p->right = tmp;
        }

        tmp = tmp->parent;
        while(tmp){
            skew(tmp);
            split(tmp);
            tmp = tmp->parent;
        }


    }
    Node* find(int X) const {
        Node* tmp = root;
        while (tmp) {
            if (X == tmp->power) {return tmp;}
            if (X < tmp->power) { tmp = tmp->left; }
            else {tmp = tmp->right;}
        }
        return nullptr;
    }
    void erase(int X) {
        Node *toDelete = find(X);
        if (toDelete == nullptr) return;

        Node *notBalanced;
        Node *alt = nullptr;
        if (toDelete->right == nullptr) {
        alt = toDelete->left;
        notBalanced = toDelete->parent;
        }
        else if (toDelete->left == nullptr) {
            alt = toDelete->right;
            notBalanced = toDelete->parent;
        }
        else{
             alt = toDelete->right->minimum();
             if(alt->parent != toDelete){
                 alt->parent->left = alt->right;
                 if (alt->right) { alt->right->parent = alt->parent; }
                 alt->right = toDelete->right;
                 toDelete->right->parent = alt;
                 notBalanced = alt->parent;
             }
             else{
                 notBalanced = alt;
             }
            alt->left = toDelete->left;
            toDelete->left->parent = alt;
        }


        if (toDelete->parent == nullptr) {
            root = alt;
        }
        else {
            if (toDelete->parent->left == toDelete){
                toDelete->parent->left = alt;
            }
            else {
                toDelete->parent->right = alt;
            }
        }
        if (alt != nullptr) {
            alt->level = toDelete->level;
            alt->parent = toDelete->parent;
        }

        toDelete->right = nullptr;
        toDelete->left = nullptr;
        delete toDelete;

        //Для этого необходимо проверить уровень вершины и если он на 2 больше
        //чем у потомков, то снизить уровень на 1.
        //• Если после этого уровень правого потомка больше уровня в узле, то сделать
        //уровень правого потомка равным уровню текущего узла.
        //• Так как изменение уровней могло вызвать нарушение правила построения
        //дерева, необходимо
        //balance
        int min=0;
        while(notBalanced){
            if(notBalanced->right && notBalanced->left) {
                min = std::min(notBalanced->right->level,notBalanced->left->level);
            }
            else{
                min = 0;
            }
            if(notBalanced->level - min > 1){
                --notBalanced->level;
                if(notBalanced->right && notBalanced->right->level > notBalanced->level){
                    notBalanced->right->level = notBalanced->level;
                }
            }
            skew(notBalanced);
            skew(notBalanced->right);
            if(notBalanced->right){
                skew(notBalanced->right->right);
            }
            split(notBalanced);
            if(notBalanced->parent) {
            split(notBalanced->parent->right);
            }
            notBalanced= notBalanced->parent;
        }
    }
    ~AATree(){
        delete root;
    }
};
