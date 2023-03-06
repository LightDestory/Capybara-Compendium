#include <iostream>

using namespace std;

/*
 * Descrizione:
 * Un algoritmo di ordinamento basato sul confronto degli elementi a 2 a 2
 * Caratteristiche:
 * In-place: agisce sull'array fornito, modificandolo e non allocando ulteriore memoria (copia dell'array).
 * Stabile: l'ordinamento cronologico degli elementi con la stessa chiave viene preservato.
 * Complessità:
 * - O(n^2) : sia nel caso medio che peggiore[array ordinato in modo decrescente),
 *            ogni n elemento deve essere confrontato con gli altri n-1 elementi;
 * - O(n) : nel caso migliore, ovvero quando l'array è già ordinato
 */

template <typename H>
void bubblesort(H *array, int dim){
    for(int i = dim; i>1; i--){
        for(int j = 0; j<i-1; j++){
            if(array[j]> array[j+1]){
            H tmp = array[j];
            array[j] = array[j+1];
            array[j+1] = tmp;
        }
        }
    }
}
template <typename H>
void bubblesort_recursive(H* array, int dim){
    if(dim<=1)
        return;
    for(int i = 0; i<dim-1; i++){
        if(array[i] > array[i+1]){
            H tmp = array[i];
            array[i] = array[i+1];
            array[i+1] = tmp;
        }
    }
    bubblesort_recursive(array, dim-1);
}

int main(){
    int *A = new int[9] {54,32,7,4,3,88,3,11,2};
    for(int i = 0; i<9; i++)
        cout << A[i] << " ";
    cout << endl;
    bubblesort_recursive(A, 9);
    for(int i = 0; i<9; i++)
        cout << A[i] << " ";
    return 0;
}