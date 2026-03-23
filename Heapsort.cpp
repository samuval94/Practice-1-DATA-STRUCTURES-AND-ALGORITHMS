//
// Created by valen on 18/03/2026.
//

#include "heapsort.h"
#include <algorithm>
using namespace std;

void heapify(vector<string>& palabras, int n, int i) {
    int mayor = i;
    int izq = 2 * i + 1;
    int der = 2 * i + 2;

    if (izq < n && palabras[izq] > palabras[mayor]) mayor = izq;
    if (der < n && palabras[der] > palabras[mayor]) mayor = der;

    if (mayor != i) {
        swap(palabras[i], palabras[mayor]);
        heapify(palabras, n, mayor); // sigue bajando hasta restaurar el heap
    }
}

// Paso 1: construir el Max-Heap — O(n)
// Paso 2: extraer el mayor repetidamente — O(n log n)
void heapSort(vector<string>& palabras) {
    int n = palabras.size();

    // Construir heap: empieza desde el último nodo con hijos
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(palabras, n, i);

    // Extraer el mayor (posición 0) y mandarlo al final
    for (int i = n - 1; i > 0; i--) {
        swap(palabras[0], palabras[i]);  // mayor al final
        heapify(palabras, i, 0);         // restaurar heap
    }
}

// El heap vive dentro del mismo vector, no necesita estructuras adicionales
long long memoriaEstimadaHeap(int n) {
    return sizeof(string) * n;
}