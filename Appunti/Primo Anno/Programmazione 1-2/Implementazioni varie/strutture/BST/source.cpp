#include <iostream>
using namespace std;

template<typename H>
class Node{
    private:
    H* key;
    Node<H> *parent, *left, *right;
    public:
    Node(H key, Node<H>* parent = NULL, Node<H>* left = NULL, Node<H>* right = NULL){
        this->key = new H(key);
        this->parent = parent;
        this->left = left;
        this->right = right;
    }

    H* getKey() { return key; }

    Node<H>* getParent() { return parent; }

    Node<H>* getLeft() { return left; }

    Node<H>* getRight() { return right; }

    void setKey(H key) { *this->key = key; }

    void setParent(Node<H>* parent) { this->parent = parent; }

    void setLeft(Node<H>* left) { this->left = left; }

    void setRight(Node<H>* right) { this->right = right; }
};

template<typename H>
class BST{
    private:
    int n_nodes;
    Node<H>* root;

    Node<H>* _search(Node<H>* r, H key){
        if(!r || *r->getKey() == key) return r;
        if(key <= *r->getKey())
            return _search(r->getLeft(), key);
        return _search(r->getRight(), key);
    }

    void _inorder(Node<H>* r){
        if(r){
            _inorder(r->getLeft());
            cout << *r->getKey() << " ";
            _inorder(r->getRight());
        }
    }

    void _preorder(Node<H>* r){
        if(r){
            cout << *r->getKey() << " ";
            _preorder(r->getLeft());
            _preorder(r->getRight());
        }
    }

    void _postorder(Node<H>* r){
        if(r){
            _postorder(r->getLeft());
            _postorder(r->getRight());
            cout << *r->getKey() << " ";
        }
    }

    Node<H>* _min(Node<H>* r){
        if(!r || !r->getLeft()) return r;
        return _min(r->getLeft());
    }

    Node<H>* _max(Node<H>* r){
        if(!r || !r->getRight()) return r;
        return _max(r->getRight());
    }

    int _leaf_count(Node<H>* r){
        if(!r) return 0;
        if(r->getRight() || r->getLeft())
            return _leaf_count(r->getRight()) + _leaf_count(r->getLeft());
        return 1;

    }

    int _height(Node<H>* r){
        if(!r) return -1;
        int m = _height(r->getRight());
        int n = _height(r->getLeft());
        if(n>m) m = n;
        return m+1;
    }
    
    int _deep(Node<H>* r){
        if(r == root) return 0;
        return 1 + _deep(r->getParent());
    }

    void _canc(Node<H>* r, H key){
        Node<H>* s = _search(r, key);
        if(!s) return;
        if(s->getLeft() && s->getRight()){
            Node<H>* suc = _min(s->getRight());
            s->setKey(*suc->getKey());
            _canc(suc, *suc->getKey());
        } else{
            Node<H>* child = s->getRight();
            if(!child) child = s->getLeft();
            Node<H>* parent = s->getParent();
            if(parent){
                if(key < *parent->getKey()) parent->setLeft(child);
                else parent->setRight(child);
            }
            else{
                root = child;
            }
            if(child)
                child->setParent(parent);
        }

        n_nodes--;
    }

    int _weight(Node<H>* r){
        if(!r) return 0;
        return _weight(r->getRight()) + _weight(r->getLeft()) +1;
    }

    public:
    BST(){
        n_nodes = 0;
        root = NULL;
    }

    bool isEmpty(){ return root==NULL; }

    void insert(H key){
        Node<H>* prev = NULL;
        Node<H>* cursor = root;
        while(cursor){
            prev = cursor;
            if(key <= *cursor->getKey()) cursor = cursor->getLeft();
            else cursor = cursor->getRight();
        }
        Node<H>* tmp = new Node<H>(key, prev);
        if(!prev)
            root = tmp;
        else {
            if(key<= *prev->getKey())
                prev->setLeft(tmp);
            else prev->setRight(tmp);
        }
        n_nodes++;
    }

    void canc(H key){
        return _canc(root, key);
    }

    Node<H>* search(H key){ return _search(root, key); }

    void inorder() { return _inorder(root); }

    void preorder() {return _preorder(root); }

    void postorder() { return _postorder(root); }

    H* min(){ return _min(root)->getKey(); }

    H* max() { return _max(root)->getKey(); }

    H* successore(H key){
        Node<H>* tmp = _search(root, key);
        if(!tmp) return NULL;
        if(tmp->getRight()){
            return _min(tmp->getRight())->getKey();
        }
        do{
            tmp = tmp->getParent();
        }while(tmp && *tmp->getKey()<key);
        if(!tmp) return NULL;
        return tmp->getKey();
    }

    H* predecessore(H key){
        Node<H>* tmp = _search(root, key);
        if(!tmp) return NULL;
        if(tmp->getLeft()){
            return _max(tmp->getLeft())->getKey();
        }
        do{
            tmp = tmp->getParent();
        }while(tmp && *tmp->getKey() > key);
        if(!tmp) return NULL;
        return tmp->getKey();
    }

    int leaf_count() { return _leaf_count(root); }

    int height() { return _height(root); }

    int deep(H key){
        Node<H>* s = _search(root, key);
        if(!s) return -1;
        return _deep(s);
    }

    int weight(H key){
        Node<H>* s = _search(root, key);
        if(!s) return -1;
        return _weight(s);
    }
};

int main(){
    auto b = new BST<int>();
    b->insert(24);
    b->insert(18);
    b->insert(14);
    b->insert(7);
    b->insert(13);
    b->insert(16);
    b->insert(11);
    b->insert(9);
    b->insert(32);
    b->insert(25);
    b->insert(26);
    b->insert(28);
    b->insert(31);
    b->insert(41);
    b->insert(34);
    b->insert(38);
    b->insert(45);
    b->postorder();
    cout << endl;
    Node<int>* s;
    s = b->search(100);
    if(s) cout << "TROVATO" << endl;
    else cout << "NON TROVATO" << endl;
    s = b->search(21);
    if(s) cout << "TROVATO" << endl;
    else cout << "NON TROVATO" << endl;
    s = b->search(7);
    if(s) cout << "TROVATO" << endl;
    else cout << "NON TROVATO" << endl;
    cout << "MAX:" << *b->max() << endl << "MIN: " << *b->min();
    cout << endl << b->height() << endl << b->leaf_count() << endl;
    int *a = b->successore(100);
    if(a) cout << "TROVATO " << *a << endl;
    else cout << "NON TROVATO" << endl;
    a = b->predecessore(9);
    if(a) cout << "TROVATO " << *a << endl;
    else cout << "NON TROVATO" << endl;
    a = b->predecessore(32);
    if(a) cout << "TROVATO " << *a << endl;
    else cout << "NON TROVATO" << endl;
    b->canc(32);
    b->postorder();
    cout << endl;
    b->canc(11);
    b->postorder();
    cout << endl;
    b->canc(24);
    b->postorder();
    cout << endl << b->deep(100) << " " << b->deep(9) << endl << b->weight(7);
    return 0;
}