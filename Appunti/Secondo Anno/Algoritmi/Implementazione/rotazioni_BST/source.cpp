#include <iostream>
#include <fstream>

using namespace std;

template <class H>
class Node{
    private:
    H key;
    Node<H> *parent, *left, *right;
    public:
    Node(H key, Node<H>* parent = NULL,  Node<H>* left = NULL,  Node<H>* right = NULL){
        this->key = key;
        this->parent = parent;
        this->left = left;
        this->right = right;
    }
    H getKey(){ return key;}
    void setKey(H key) { this->key = key; }
    Node<H>* getParent(){ return parent;}
    void setParent(Node<H>* parent) { this->parent = parent;}
    Node<H>* getLeft(){ return left;}
    void setLeft(Node<H>* left) { this->left = left;}
    Node<H>* getRight(){ return right;}
    void setRight(Node<H>* right) { this->right = right;}
};

template <class H>
class BST{
    private:
    Node<H>* root;
    Node<H>* _search(H key, Node<H>* s){
        if(!s || s->getKey()==key) return s;
        if(key<s->getKey())
            return _search(key, s->getLeft());
        return _search(key, s->getRight());
        
    }
    Node<H>* _min(Node<H>* node){
        if(!node || !node->getLeft()) return node;
        return _min(node->getLeft());
    }
    void _preorder(Node<H>* node, fstream& output){
        if(!node) return;
        output << node->getKey() << " ";
        _preorder(node->getLeft(), output);
        _preorder(node->getRight(), output);
    }
    void _postorder(Node<H>* node, fstream& output){
        if(!node) return;
        _postorder(node->getLeft(), output);
        _postorder(node->getRight(), output);
        output << node->getKey() << " ";
    }
    void _inorder(Node<H>* node, fstream& output){
        if(!node) return;
        _inorder(node->getLeft(), output);
        output << node->getKey() << " ";
        _inorder(node->getRight(), output);
    }
    void _remove(H key, Node<H>* node){
        Node<H>* s = _search(key, node);
        if(!s) return;
        if(s->getLeft() && s->getRight()){
            Node<H>* succ = _min(s->getRight());
            s->setKey(succ->getKey());
            _remove(succ->getKey(), succ);
        }
        else{
            Node<H>* child = s->getLeft();
            if(!child) child = s->getRight();
            Node<H>* parent = s->getParent();
            if(parent){
                if(key<parent->getKey()) parent->setLeft(child);
                else parent->setRight(child);
            }
            else
                root = child;
            if(child) child->setParent(parent);
        }
    }

    void _rightRotate(Node<H>* node){
        Node<H>* parent = node->getParent();
        Node<H>* left = node->getLeft();
        if(!left)
            return;
        Node<H>* right_son = left->getRight();
        if(parent){
            if(parent->getLeft() == node)
                parent->setLeft(left);
            else
                parent->setRight(left);
        }
        else
            root = left;
        left->setParent(parent);
        node->setParent(left);
        left->setRight(node);
        node->setLeft(right_son);
        if(right_son)
            right_son->setParent(node);

    }
     void _leftRotate(Node<H>* node){
        Node<H>* parent = node->getParent();
        Node<H>* right = node->getRight();
        if(!node || !right)
            return;
        Node<H>* left_son = right->getLeft();
        if(parent){
            if(parent->getLeft() == node)
                parent->setLeft(right);
            else
                parent->setRight(right);
        }
        else
            root = right;
        right->setParent(parent);
        node->setParent(right);
        right->setLeft(node);
        node->setRight(left_son);
        if(left_son)
            left_son->setParent(node);
    }
    public: 
    BST(){
        root = NULL;
    }

    void insert(H key){
        Node<H>* cursor = root;
        Node<H>* prev = NULL;
        while(cursor){
            prev = cursor;
            if(key<=cursor->getKey())
                cursor = cursor->getLeft();
            else
                cursor = cursor->getRight();
        }
        Node<H>* node = new Node<H>(key, prev);
        if(!prev)
            root = node;
        else{
            if(key<=prev->getKey())
                prev->setLeft(node);
            else
                prev->setRight(node);
        }
    }

    void remove(H key){
        _remove(key, root);
    }

    void rightRotate(H key){
        _rightRotate(_search(key, root));
    }

    void leftRotate(H key){
        _leftRotate(_search(key, root));
    }

    void inorder(fstream& output){
        _inorder(root, output);
    }
    void preorder(fstream& output){
        _preorder(root, output);
    }

    void postorder(fstream& output){
        _postorder(root, output);
    }
};

template <class H>
void runtime(fstream& input, fstream& output, string order, int N, int R, H proto){
    BST<H>* tree = new BST<H>();
    string c;
    for(int i = 0; i<N; i++){
        input >> c;
        if(c[0]=='i'){
            tree->insert(atof(c.substr(4).c_str()));
        }
        else
            tree->remove(atof(c.substr(5).c_str()));
    }
    for(int i = 0; i<R; i++){
        input >> c;
        if(c[0] == 'r'){
            tree->rightRotate(atof(c.substr(6).c_str()));
        }
        else{
            tree->leftRotate(atof(c.substr(5).c_str()));
        }
    }
    if(order == "inorder")
        tree->inorder(output);
    if(order == "postorder")
        tree->postorder(output);
    if(order == "preorder")
        tree->preorder(output);
}

int main(){
    fstream input("input.txt", ios::in), output("output.txt", fstream::out);
    int N, R;
    string order, type;
    for(int i = 0; i<100; i++){
        input >> type >> N >> R >> order;
        runtime(input, output, order, N, R, double());
        output << endl;
    }
    return 0;
}