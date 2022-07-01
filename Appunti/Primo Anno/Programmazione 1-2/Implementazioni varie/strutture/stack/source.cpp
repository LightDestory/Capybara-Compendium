#include <iostream>

using namespace std;
template<typename H>
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

template<typename H>
class Stack{
private:
    int size;
    Node<H>* head;
public:
    Stack(){
        size = 0;
        head = NULL;
    }

    void push(H key){
        Node<H>* tmp = new Node<H>(key);
        if(!head){
            head = tmp;
        } else{
            tmp->setNext(head);
            head = tmp;
        }
        size++;
    }

    H pop(){
        if(!head)
            return -1;
        H tmp = head->getKey();
        head = head->getNext();
        size--;
        return tmp;
    }

    int getSize() { return size; }

    void printElements(){
        Node<H>* cursor = head;
        while(cursor){
            cout << cursor->getKey() << " ";
            cursor = cursor->getNext();
        }
        cout << endl;
    }
};

int main(){
    Stack<int> *s = new Stack<int>();
    s->push(5);
    s->push(6);
    s->push(7);
    s->push(8);
    s->push(9);
    s->pop();
    s->push(10);
    s->printElements();
    return 0;
}