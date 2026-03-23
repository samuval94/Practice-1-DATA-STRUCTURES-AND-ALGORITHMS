#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <random>
#include "Practica_quicksort.h"
#include "Tree.h"
#include "heapsort.h"

using namespace std;

int main() {
    vector<string> palabras;
    string palabra;

    // 1. Lectura del archivo
    ifstream archivo("dataset.txt");
    if (!archivo.is_open()) {
        cout << "Error: No se encontro dataset.txt en cmake-build-debug" << endl;
        return 1;
    }

    cout << "Cargando palabras..." << endl;
    while (archivo >> palabra && palabras.size() < 100000) {
        palabras.push_back(palabra);
    }
    archivo.close();
    cout << "Total de palabras cargadas: " << palabras.size() << endl;

    if (!palabras.empty()) {

        // Mezclamos el vector ANTES de copiar y FUERA del chrono
        // Asi los tres algoritmos reciben datos aleatorios y no medimos el shuffle
        mt19937 rng(42);
        shuffle(palabras.begin(), palabras.end(), rng);

        // ─────────────────────────────────────────
        // QUICKSORT
        // ─────────────────────────────────────────
        vector<string> palabrasQS = palabras; // copia del vector ya mezclado

        cout << "\nOrdenando las palabras con Quicksort"
                "..." << endl;
        auto inicio = chrono::high_resolution_clock::now();
        quicksort(palabrasQS, 0, (int)palabrasQS.size() - 1);
        auto fin = chrono::high_resolution_clock::now();

        chrono::duration<double, milli> tiempo = fin - inicio;
        cout << "Finaliza el ordenamiento con exito." << endl;
        cout << "Tiempo de ejecucion QuickSort: " << tiempo.count() << " ms" << endl;
        cout << "Memoria estimada QuickSort: "
     << (sizeof(string) * palabrasQS.size()) / 1024 << " KB" << endl;

        // Guardar resultado QuickSort en archivo
        ofstream archivoSalida("dataset_ordenado.txt");
        if (archivoSalida.is_open()) {
            cout << "Guardando palabras ordenadas en 'dataset_ordenado.txt'..." << endl;
            for (const string& p : palabrasQS) {
                archivoSalida << p << "\n";
            }
            archivoSalida.close();
            cout << "Archivo guardado con exito." << endl;
        } else {
            cout << "Error al crear el archivo de salida." << endl;
        }

        // ─────────────────────────────────────────
        // HEAPSORT
        // ─────────────────────────────────────────
        vector<string> palabrasHS = palabras; // copia del vector mezclado

        cout << "\nOrdenando las palabras con HeapSort..." << endl;
        auto inicioHS = chrono::high_resolution_clock::now();
        heapSort(palabrasHS);
        auto finHS = chrono::high_resolution_clock::now();

        chrono::duration<double, milli> tiempoHS = finHS - inicioHS;
        cout << "Finaliza el ordenamiento con exito." << endl;
        cout << "Tiempo de ejecucion HeapSort:  " << tiempoHS.count() << " ms" << endl;
        cout << "Memoria estimada HeapSort: "
             << memoriaEstimadaHeap(palabras.size()) / 1024 << " KB" << endl;

        // ─────────────────────────────────────────
        // AVL TREE
        // ─────────────────────────────────────────
        AVLTree arbol;
        Node* raiz = nullptr;

        cout << "\nInsertando palabras en AVL Tree..." << endl;
        auto inicioAVL = chrono::high_resolution_clock::now();
        for (const string& p : palabras) {
            raiz = arbol.insert(raiz, p);
        }
        vector<string> resultadoAVL;
        arbol.inorderToVector(raiz, resultadoAVL);
        auto finAVL = chrono::high_resolution_clock::now();

        chrono::duration<double, milli> tiempoAVL = finAVL - inicioAVL;
        cout << "Finaliza el ordenamiento con exito." << endl;
        cout << "Tiempo de ejecucion AVL Tree:  " << tiempoAVL.count() << " ms" << endl;
        cout << "Memoria estimada AVL: "
             << arbol.memoriaEstimada(palabras.size()) / 1024 << " KB" << endl;

        // ─────────────────────────────────────────
        // ANALISIS COMPARATIVO
        // ─────────────────────────────────────────
        long long memQS  = sizeof(string) * palabras.size();
        long long memHS  = memoriaEstimadaHeap(palabras.size());
        long long memAVL = arbol.memoriaEstimada(palabras.size());

        // Ganador en velocidad
        string ganadorVelocidad = "QuickSort";
        if (tiempoHS.count() < tiempo.count() && tiempoHS.count() < tiempoAVL.count())
            ganadorVelocidad = "HeapSort";
        else if (tiempoAVL.count() < tiempo.count() && tiempoAVL.count() < tiempoHS.count())
            ganadorVelocidad = "AVL Tree";

        // Ganador en memoria
        string ganadorMemoria = "QuickSort";
        if (memHS < memQS && memHS < memAVL)
            ganadorMemoria = "HeapSort";
        else if (memAVL < memQS && memAVL < memHS)
            ganadorMemoria = "AVL Tree";

        cout << "\nANALISIS COMPARATIVO" << endl;
        cout << left
             << setw(12) << "Algoritmo"
             << setw(14) << "Tiempo(ms)"
             << setw(12) << "Memoria(KB)"
             << setw(15) << "Complejidad" << endl;
        cout << "------------------------------------------" << endl;
        cout << left
             << setw(12) << "QuickSort"
             << setw(14) << tiempo.count()
             << setw(12) << memQS  / 1024
             << setw(15) << "O(n log n)" << endl;
        cout << left
             << setw(12) << "HeapSort"
             << setw(14) << tiempoHS.count()
             << setw(12) << memHS  / 1024
             << setw(15) << "O(n log n)" << endl;
        cout << left
             << setw(12) << "AVL Tree"
             << setw(14) << tiempoAVL.count()
             << setw(12) << memAVL / 1024
             << setw(15) << "O(n log n)" << endl;
        cout << "------------------------------------------" << endl;
        cout << "Ganador en velocidad: " << ganadorVelocidad << endl;
        cout << "Ganador en memoria:   " << ganadorMemoria   << endl;
    }


    return 0;
}