#include <iostream>

using namespace std;

/*
 * Descrizione:
 * Un algoritmo di ordinamento basato sul individuare il minimo e inserirlo
 * all'i-nesima posizione dell'array, creando una parte ordinata.
 * Caratteristiche:
 * In-place: agisce sull'array fornito, modificandolo e non allocando ulteriore memoria (copia dell'array).
 * Complessità:
 * - O(n^2) : sia nel caso medio che peggiore, quando vi è un effettivo ordinamento;
 * - O(n)   : quando l'array è già ordinato;
 */

template <typename H>
void selection_sort(H* array, int dim){
    for(int i = 0; i<dim-1; i++){
        int min = i;
        for(int j = i+1; j<dim; j++)
            if(array[min]>array[j])
                min = j;
        if(min!=i){
            H tmp = array[i];
            array[i] = array[min];
            array[min] = tmp;
        }        
    }
}

template <typename H>
void selection_sort_recursive(H* array, int dim){
    if(dim<=1)
        return;
    int min = 0;
    for(int i = 1; i<dim; i++)
        if(array[min]>array[i])
            min = i;
    if(min!=0){
        H tmp = array[0];
        array[0] = array[min];
        array[min] = tmp;
    }
    selection_sort_recursive(array+1, dim-1);
}

int main(){
    int a[10] = {1,32,43,12,54,122,-144,21,2,4};
    for(int i = 0; i<10; i++)
    cout << a[i] << " ";
    cout << endl;
    selection_sort_recursive(a, 10);
    for(int i = 0; i<10; i++)
    cout << a[i] << " ";
}