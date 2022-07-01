#include <iostream>
using namespace std;

void merge(int* array, int start, int mid, int end){
    int dim = (end-start)+1;
    int tmp[dim];
    int i = start, k = mid+1, c = 0;
    while(i<=mid && k<=end){
        if(array[i]<array[k])
            tmp[c++] = array[i++];
        else
            tmp[c++] = array[k++];
        
    }
    while(i<=mid)
        tmp[c++] = array[i++];
    while(k<=end)
        tmp[c++] = array[k++];
    int s = start;
    for(int i = 0; i<dim; i++)
        array[s++] = tmp[i];
}

void mergesort(int* array, int start, int end){
    if(start<end){
        int mid = (end+start)/2;
        mergesort(array, start, mid);
        mergesort(array, mid+1, end);
        merge(array, start, mid, end);
    }
}


int main(){
    int *a = new int[12]{5,9,12,54,76,98,354,1,-865,34,21,-67};
    int dim = 12;
    for(int i = 0; i<dim; i++)
        cout << a[i] << " ";
    cout <<endl;
    mergesort(a, 0, 11);
    for(int i = 0; i<dim; i++)
        cout << a[i] << " ";
    cout <<endl;
    return 0;
}