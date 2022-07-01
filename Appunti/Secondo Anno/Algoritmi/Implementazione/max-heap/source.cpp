#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
template<class H>
class MaxHeap{
    private:
    H* data;
    int arraySize, size, counter;
    int parent(int i) { return i>>1;}
    int left(int i) { return i<<1;}
    int right(int i) { return (i<<1)|1;}
    void swap(int i, int j){
        H tmp = data[i];
        data[i] = data[j];
        data[j] = tmp;
    }
    void heapify(int i){
        counter++;
        int max = i;
        int l = left(i);
        int r = right(i);
        if(l<=size && data[l]>data[max]) max = l;
        if(r<=size && data[r]>data[max]) max = r;
        if(max!=i){
            swap(max, i);
            heapify(max);
        }
    }
    public:
    MaxHeap(int arraySize){
        this->arraySize = arraySize;
        data = new H[arraySize+1];
        counter = 0;
        size = 0;
    }

    void enqueue(H item){
        data[++size] = item;
        int position = size;
        while(parent(position)>0 && data[parent(position)]<data[position]){
            swap(parent(position), position);
            position = parent(position);
        }
    }

    H extract(){
        H tmp = data[1];
        data[1] = data[size--];
        if(size>0)
            heapify(1);
        return tmp;
    }

    void print(fstream& output){
        output << counter << " ";
        for(int i = 1; i<=size; i++)
            output << data[i] << " ";
    }
};
template <class H>
void runtime(fstream& input, fstream& output, int N, H proto){
    MaxHeap<H>* mh = new MaxHeap<H>(N);
    char c;
    string tmp;
    for(int i = 0; i<N; i++){
        input >> c >> c;
        if(c=='x'){
            mh->extract();
            input >> tmp;
        }
        else{
            input >> proto;
            mh->enqueue(proto);
        }
    }
    mh->print(output);
}
int main(){
    fstream input("input.txt", ios::in), output("output.txt", ios::out);
    string type;
    int N;
    for(int i =0; i<100; i++){
        input >> type >> N;
        if(type=="char")
            runtime(input, output, N, char());
        else
            runtime(input, output, N, double());
        output << endl;
    }
}