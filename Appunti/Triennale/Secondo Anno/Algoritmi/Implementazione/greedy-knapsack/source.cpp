#include <iostream>
#include <fstream>
#include <list>
using namespace std;

int knapsack(fstream& input, fstream& out, int N, int sack_size){
    list<int>* l = new list<int>();
    int sum = 0, tmp;
    for(int i = 0; i<N;i++){
        input >> tmp;
        l->push_back(tmp);
    }
    l->sort();
    for(int i = 0; i<sack_size; i++){
        sum+=l->back();
        l->pop_back();
    }
    return sum;
}

int main(){
    fstream input("input.txt", ios::in), output("output.txt", ios::out);
    int N, sack_size;
    for(int i = 0; i<100; i++){
        input >> N >> sack_size;
        output << knapsack(input, output, N, sack_size) << endl;
    }
}