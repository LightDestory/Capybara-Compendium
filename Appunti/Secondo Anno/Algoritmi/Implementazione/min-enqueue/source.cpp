#include <iostream>
#include <fstream>
using namespace std;
template <class H>
class MinHeap{
    private:
    H* data;
    int arraySize, size;
    int parent(int i) { return i>>1;}
    int left(int i) { return i<<1;}
    int right(int i){ return (i<<1)|1;}
    void swap(int i, int j){
        H tmp = data[i];
        data[i] = data[j];
        data[j]= tmp;
    }
    public:
    MinHeap(int arraySize){
        this->arraySize = arraySize;
        data = new H[arraySize+1];
        size = 0;
    }
    void enqueue(H item){
        data[++size] = item;
        int position = size;
        while(parent(position)>0 && data[parent(position)]>data[position]){
            swap(parent(position), position);
            position = parent(position);
        }
    }

    void print(fstream& output){
        for(int i=1; i<=size; i++){
            output << data[i] << " ";
        }
    }
};
template <class H>
void runtime(fstream& input, fstream& output, int N, H proto){
    MinHeap<H> *mh = new MinHeap<H>(N);
    for(int i = 0; i<N; i++){
        input >> proto;
        mh->enqueue(proto);
    }
    mh->print(output);
}

int main(){
    fstream input("input.txt", ios::in), output("output.txt", ios::out);
    int N;
    string type;
    for(int i = 0; i<100; i++){
        input >> type >> N;
        if(type=="char")
            runtime(input, output, N, char());
        else
            runtime(input, output, N, double());
        output << endl;
    }
}