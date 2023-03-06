#include<iostream>

using namespace std;

/*
 * Descrizione:
 * Un algoritmo di ordinamento basato creare una parte ordinata all'interno dell'array ordinando l'elemento subito
 * successivo alla parte ordinata
 * Caratteristiche:
 * In-place: agisce sull'array fornito, modificandolo e non allocando ulteriore memoria (copia dell'array).
 * Complessità:
 * - O(n) : nel caso ottimale, quando l'array è già ordinato in ogni iterazione il primo elemento della sotto-sequenza
 *          non ordinata viene confrontato solo con l'ultimo della sotto-sequenza ordinata.
 * - O(n^2) : nel caso peggiore, quando l'array è ordinato in modo decrescente, ogni iterazione
 *            dovrà scorrere e spostare ogni elemento della sotto-sequenza ordinata prima di poter inserire il primo elemento della
 *            sotto-sequenza non ordinata.
 */

template <typename H>
void insertionSort(H *array, int dim){
    for(int i = 1; i<dim; i++) {
        int j = i;
        while(j>=1 && array[j]<array[j-1]){
            H tmp = array[j];
            array[j] = array[j-1];
            array[j-1] = tmp;
            j--;
        }
    }
}

int main(){
    int *a = new int[7] {8,-6654,32,235654,676,2,1};
    for(int i = 0; i<7; i++)
        cout << a[i] << " ";
    cout << endl;
    insertionSort(a, 7);
    for(int i = 0; i<7; i++)
        cout << a[i] << " ";
    return 0;
}