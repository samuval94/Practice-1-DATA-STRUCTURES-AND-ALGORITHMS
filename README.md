# Práctica I – Estructura de Datos y Algoritmos (C++)
### Samuel Valencia Montoya  - Juliana Sepúlveda Saldarriaga
**ST0245 - SI001 - Estructura de Datos y Algoritmos**  
Facultad de Ciencias Aplicadas e Ingeniería – Universidad Eafit
Docente: Alexander Narváez Berrío

---
## Descripción

Desarrolla un programa en C++ capaz de ordenar un gran conjunto de palabras utilizando tres estrategias algorítmicas diferentes, cada una basada en estructuras de datos distintas.

---
## Objetivo
El objetivo de este ejercicio es analizar cómo se comportan los distintos algoritmos y estructuras al trabajar con grandes volúmenes de datos.

---
## Estructura del proyecto

```
├── Main.cpp                  # Punto de entrada, cálculos de tiempo, análisis comparativo
├── Quicksort.h      # QuickSort header
├── Quicksort.cpp    # Implementación del quicksort
├── Heapsort.h                # HeapSort header
├── Heapsort.cpp              # Implementación del HeapSort
├── Tree.h                    # AVL Tree header
├── Tree.cpp                  #  Implementación del AVL Tree
└── dataset.txt               # 100,000 palabras seleccionadas aleatoriamente (input)
```

---
## Algorithms Implemented

### A) QuickSort — `std::vector<string>`
- Implementado desde cero, sin uso de std::sort.
- Estrategia de pivote: median-of-three (evita O(n²) en datos casi ordenados).
- Optimización tail-call: siempre recursa sobre la partición más pequeña primero.

### B) HeapSort — Binary Heap
- Implementado desde cero usando std::vector como estructura subyacente.
- Paso 1: construir un max-heap en O(n).
- Paso 2: extraer el máximo repetidamente en O(n log n).
- In-place:  no requiere estructuras adicionales.

### C) AVL Tree
- Cada nodo almacena: `key` (string), punteros `left` y `right`, campo `height`.
- Se rebalancea automáticamente en cada inserción mediante rotaciones.
- El resultado ordenado se obtiene mediante recorrido **inorder** almacenado en un vector.

---

## Ejemplo de Salida

```
Cargando palabras...
Total de palabras cargadas: 100000

Ordenando las palabras con Quicksort...
Finaliza el ordenamiento con exito.
Tiempo de ejecucion QuickSort: 309.32 ms
Memoria estimada QuickSort: 3125 KB
Guardando palabras ordenadas en 'dataset_ordenado.txt'...
Archivo guardado con exito.

Ordenando las palabras con HeapSort...
Finaliza el ordenamiento con exito.
Tiempo de ejecucion HeapSort:  513.264 ms
Memoria estimada HeapSort: 3125 KB

Insertando palabras en AVL Tree...
Finaliza el ordenamiento con exito.
Tiempo de ejecucion AVL Tree:  401.202 ms
Memoria estimada AVL: 5078 KB

ANALISIS COMPARATIVO
Algoritmo   Tiempo(ms)    Memoria(KB) Complejidad
------------------------------------------
QuickSort   309.32        3125        O(n log n)
HeapSort    513.264       3125        O(n log n)
AVL Tree    401.202       5078        O(n log n)
------------------------------------------
Ganador en velocidad: QuickSort
Ganador en memoria:   QuickSort

Process finished with exit code 0
```

---

## Análisis Comparativo

### 1. ¿Cuál algoritmo funciona mejor?

**QuickSort** obtuvo el mejor tiempo de ejecución y el menor uso de memoria. Su posición siempre fue constante en todas las ejecuciones.

| Posición | Algoritmo | Rango de Tiempo     | Memoria Usada  |
|------|-----------|----------|---------|
| 1°  | QuickSort | 120 - 335 ms   | 3125 KB |
| 2° | AVL Tree  | 158 - 389 ms   | 5078 KB |
| 3° | HeapSort  | 218 - 615 ms   | 3125 KB |

El tiempo de ejecución puede cambiar dependiendo de las condiciones en las cuales se ejecute el programa. Entre más aplicaciones abiertas a la vez, la CPU reparte su tiempo en todos los procesos.

### 2. Por qué la complejidad teórica difiere de los resultados prácticos?

Los tres algoritmos poseen la misma complejidad, **Big O — O(n log n) **, pero sus tiempos de ejecución difieren por la localidad del caché. Es decir, se diferencian en cómo acceder a los datos.
- **QuickSort** opera sobre un `std::vector` contiguo en memoria, por lo que los accesos son secuenciales. El prefetcher del CPU maneja esto eficientemente, generando muy pocos cache misses.
- **HeapSort** ccede a elementos en los índices `2i+1` y `2i+2`, lo que crea saltos no secuenciales en memoria. Estos saltos generan cache misses frecuentes, ralentizando la ejecución a pesar de tener la misma complejidad teórica.
- **AVL Tree** accede a nodos a través de punteros dispersos en el heap de memoria. Cada dereferenciacón de puntero puede causar un cache miss, sumado al overhead de las rotaciones necesarias para mantener el balance.

La notación Big O mide el número de operaciones pero ignora efectos del hardware y patrones de acceso a memoria, por esto los resultados prácticos pueden diferir sustancialmente de la teoría.

### 3. Ventajas y desventajas de cada estructura de datos

| Algoritmo | Ventaja | Desventajas |
|-----------|-----------|---------------|
| **QuickSort** | Rápido en la práctica, bajo uso de memoria, uso óptimo de caché | Peor caso O(n²) si el pivote es malo; no sirve para datos dinámicos |
| **HeapSort** | Peor caso garantizado O(n log n), ordenamiento in-place | Más lento en la práctica por cache misses de acceso no secuencial |
| **AVL Tree** | Búsqueda, inserción y eliminación O(log n) tras el ordenamiento; siempre balanceado | Usa dos veces más memoria (punteros + campo altura por nodo); overhead de rotaciones |

---

