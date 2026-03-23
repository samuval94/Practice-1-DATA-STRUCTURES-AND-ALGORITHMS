//
// Created by valen on 18/03/2026.
//

#ifndef C___ESTRUCTURAS_DE_DATOS_HEAPSORT_H
#define C___ESTRUCTURAS_DE_DATOS_HEAPSORT_H

#include <string>
#include <vector>
using namespace std;

// Restaura la propiedad del heap en el subárbol con raíz en i
void heapify(vector<string>& palabras, int n, int i);

// Ordena el vector completo usando HeapSort
void heapSort(vector<string>& palabras);

// Estimación de memoria usada por el heap
long long memoriaEstimadaHeap(int n);

#endif //C___ESTRUCTURAS_DE_DATOS_HEAPSORT_H