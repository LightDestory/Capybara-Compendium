#include <iostream>
#include <ctime>
using namespace std;

template <typename H>
class ListNode{
    private:
    H* key;
    ListNode<H> *next, *prev;
    public:
    ListNode(H key, ListNode<H>* next = NULL, ListNode<H>* prev = NULL){
        this->key = new H(key);
        this->next = next;
        this->prev = prev;
    }

    ListNode(){
        key = NULL;
        next = NULL;
        prev = NULL;
    }

    H getKey() { return *key; }

    void setKey(H key) { *this->key = key; }

    ListNode<H>* getNext() { return next; }

    void setNext(ListNode<H>* next) { this->next = next; }

    ListNode<H>* getPrev() { return prev; }

    void setPrev(ListNode<H>* prev) { this->prev = prev; }

};
template <typename H>
class OrderedDLinkedList{
    private:
    int size;
    ListNode<H> *header, *tailer, *iterator;
    public:
    OrderedDLinkedList(){
        size = 0;
        header = new ListNode<H>();
        tailer = new ListNode<H>();
        header->setNext(tailer);
        tailer->setPrev(header);
        iterator = NULL;
    }

    int getSize() { return size; }

    void reset() { iterator = header->getNext(); }

    bool hasNext() { return iterator!=tailer;}

    H next() {
        H tmp = iterator->getKey();
        iterator = iterator->getNext();
        return tmp;
    }

    ListNode<H>* find(H key){
        ListNode<H>* cursor = header->getNext();
        while(cursor!=tailer){
            if(cursor->getKey()==key)
                return cursor;
            cursor= cursor->getNext();
        }
        return NULL;
    }

    void insert(H key){
        ListNode<H>* cursor = header->getNext();
        while(cursor!=tailer && cursor->getKey()<key)
            cursor = cursor->getNext();
        ListNode<H>* prev = cursor->getPrev();
        ListNode<H>* tmp = new ListNode<H>(key, cursor, prev);
        prev->setNext(tmp);
        cursor->setPrev(tmp);
    }

    void canc(int key){
        ListNode<H>* s = find(key);
        if(s){
            ListNode<H>* prev = s->getPrev();
            ListNode<H>* next = s->getNext();
            prev->setNext(next);
            next->setPrev(prev);
        }
    }
};

int main(){
    srand(time(NULL));
    auto list = new OrderedDLinkedList<int>();
    for(int i = 0; i<20; i++)
        list->insert(rand()%45);
    cout << endl;
    list->reset();
    while(list->hasNext()){
        cout << list->next() << " ";
    }
    cout << endl;
    if(list->find(3)) cout << "TROVATO" << endl;
    else cout << "NON TROVATO" << endl;
    if(list->find(13)) cout << "TROVATO" << endl;
    else cout << "NON TROVATO" << endl;
    for(int i = 0; i<20; i++)
        list->canc(rand()%45);
    cout << endl;
    list->reset();
    while(list->hasNext()){
        cout << list->next() << " ";
    }
    return 0;
}