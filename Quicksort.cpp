//
// Created by valen on 17/03/2026.
#include "Practica_quicksort.h"
#include <vector>
#include <string>

using namespace std;

int particion(vector<string>& palabras, int bajo, int alto) {
    int medio = bajo + (alto - bajo) / 2;

    // Median-of-three: deja la mediana en palabras[alto]
    if (palabras[bajo]  > palabras[medio]) swap(palabras[bajo],  palabras[medio]);
    if (palabras[medio] > palabras[alto])  swap(palabras[medio], palabras[alto]);
    if (palabras[bajo]  > palabras[medio]) swap(palabras[bajo],  palabras[medio]);
    // Ahora palabras[medio] es la mediana → la movemos a alto como pivote
    swap(palabras[medio], palabras[alto]);

    const string pivote = palabras[alto];
    int i = bajo - 1;

    for (int j = bajo; j < alto; j++) {
        if (palabras[j] <= pivote) {
            i++;
            swap(palabras[i], palabras[j]);
        }
    }
    swap(palabras[i + 1], palabras[alto]);
    return i + 1;
}

void quicksort(vector<string>& palabras, int bajo, int alto) {
    while (bajo < alto) {
        int p = particion(palabras, bajo, alto);

        // Optimizacion: procesamos primero la parte mas pequeña
        if (p - bajo < alto - p) {
            quicksort(palabras, bajo, p - 1);
            bajo = p + 1;
        } else {
            quicksort(palabras, p + 1, alto);
            alto = p - 1;
        }
    }
}