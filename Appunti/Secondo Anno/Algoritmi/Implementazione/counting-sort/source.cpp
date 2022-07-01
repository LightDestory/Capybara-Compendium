#include <iostream>
#include <fstream>
using namespace std;

void counting_sort(fstream& input, fstream& output, int N){
    int *unsorted = new int[N];
    int *sorted = new int[N];
    for(int i = 0; i<N; i++){
        input >> unsorted[i];
    }
    int max = unsorted[0];
    int min = unsorted[0];
    for(int i = 1; i<N; i++){
        if(unsorted[i]>max) max = unsorted[i];
        if(unsorted[i]<min) min = unsorted[i];
    }
    int range = max-min+1;
    int *C = new int[range] {0};
    for(int i = 0; i<N; i++){
        C[unsorted[i]-min]++;
    }
    for(int i = 1; i<range; i++)
        C[i] = C[i]+C[i-1];
    for(int i = 0;i<N; i++){
        int tmp_pos = unsorted[i]-min;
        int out_pos = C[tmp_pos]-1;
        sorted[out_pos] = unsorted[i];
        C[tmp_pos]--;
    }
    for(int i = 0; i<range; i++)
        output << C[i] << " ";
    for(int i = 0; i<N; i++)
        output << sorted[i] << " ";
}

int main(){
    fstream input("input.txt", ios::in), output("output.txt", ios::out);
    int N;
    for(int i = 0; i<100; i++){
        input >> N;
        counting_sort(input, output, N);
        output << endl;
    }
    return 0;
}