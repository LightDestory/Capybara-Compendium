#include <iostream>
#include <fstream>

using namespace std;

template <class H>
class MaxHeap{
    private:
    H* data;
    int size;
    int parent(int i) { return i>>1;}
    int left(int i) { return i<<1;}
    int right(int i) { return (i<<1)|1;}
    void swap(int i, int j){
        H tmp = data[i];
        data[i] = data[j];
        data[j] = tmp;
    }
    void heapify(int i){
        int max = i;
        int r = right(i);
        int l = left(i);
        if(l<=size && data[l]>data[max]) max = l;
        if(r<=size && data[r]>data[max]) max = r;
        if(max!=i){
            swap(max, i);
            heapify(max);
        }
    }
    public: 
    MaxHeap(H* data, int size){
        this->data = data;
        this->size = size;
    }
    void buildMaxHeap(){
        for(int i = size/2; i>0; i--)
            heapify(i);
    }
    void print(fstream& output){
        for(int i = 1; i<=size; i++)
            output << data[i] << " ";
    }
};

template <class H>
void runtime(fstream& input, fstream& output, int N, H proto){
    H* data = new H[N+1];
    for(int i = 1; i<=N; i++)
        input >> data[i];
    MaxHeap<H>* mh = new MaxHeap<H>(data, N);
    mh->buildMaxHeap();
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
    return 0;
}