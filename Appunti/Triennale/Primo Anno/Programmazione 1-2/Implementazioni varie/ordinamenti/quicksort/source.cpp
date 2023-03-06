#include <iostream>
using namespace std;

int partition(int* a, int start, int end){
    int pivot = a[end];
    int left = start, right = end-1;
    do{
        while(a[left]<pivot)
            left++;
        while(a[right]>pivot)
            right--;
        if(left<right){
            int tmp = a[left];
            a[left] = a[right];
            a[right] = tmp;
        }
    } while(left<right);
    a[end] = a[left];
    a[left] = pivot;
    return left;
}

void quicksort(int* a, int start, int end){
    if(start<end){
        int p = partition(a, start, end);
        quicksort(a, start, p-1);
        quicksort(a, p+1, end);
    }
}


int main(){
    int *a = new int[12]{5,9,12,54,76,98,354,1,-865,34,21,-67};
    int dim = 12;
    for(int i = 0; i<dim; i++)
        cout << a[i] << " ";
    cout <<endl;
    quicksort(a, 0, 11);
    for(int i = 0; i<dim; i++)
        cout << a[i] << " ";
    cout <<endl;
    return 0;
}