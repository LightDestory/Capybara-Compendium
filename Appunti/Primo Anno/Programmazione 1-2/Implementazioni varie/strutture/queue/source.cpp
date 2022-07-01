#include <iostream>

using namespace std;

template <typename H>
class Node{
private:
    H key;
    Node<H>* next;
public:
    Node(H key, Node<H>* next = NULL){
        this->key = key;
        this->next = next;
    }

    H getKey() { return key; }

    void setKey(H key) { this->key = key; }

    Node<H>* getNext() { return next; }

    void setNext(Node<H>* next) { this->next = next; }
};

template <typename H>
class Queue{
private:
    int size;
    Node<H> *head;
public:
    Queue(){
        head = NULL;
        size = 0;
    }

    void enqueue(H key){
        Node<H>* tmp = new Node<H>(key);
        if(!head)
            head = tmp;
        else{
            Node<H>* cursor = head;
            while(cursor->getNext()){
                cursor = cursor->getNext();
            }
            cursor->setNext(tmp);
        }
        size++;
    }
    H dequeue(){
        if(!head)
            return -1;
        H tmp = head->getKey();
        head = head->getNext();
        size--;
        return tmp;
    }

    bool isEmpity() { return size==0; }

    int getSize() { return size; }

    void printElements(){
        Node<H>* cursor = head;
        cout << endl;
        while(cursor){
            cout << cursor->getKey() << " ";
            cursor = cursor->getNext();
        }
    }
};

int main(){
    Queue<int> *p = new Queue<int>();
    p->enqueue(5);
    p->enqueue(6);
    p->enqueue(7);
    p->enqueue(8);
    p->enqueue(9);
    p->enqueue(10);
    cout << endl << "SIZE:" << p->getSize() << endl;
    p->dequeue();
    cout << endl << "SIZE:" << p->getSize() << endl;
    p->enqueue(11);
    p->printElements();
    return 0;
}