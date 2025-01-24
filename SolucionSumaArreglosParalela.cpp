// SolucionSumaArreglosParalela.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <chrono>               //Se agrego la libreria para medir el tiempo de ejecución.

#ifdef _OPENMP
#include <omp.h>
#else
#define omp_get_thread_num() 0
#endif

#define N 10000
#define chunk 500
#define mostrar 100

void imprimeArreglo(float* d);

int main()
{
    std::cout << "Sumando Arreglos en Paralelo!\n";
    float a[N], b[N], c[N];
    int i;

    for (i = 0; i < N; i++)
    {
        a[i] = i * 10;
        b[i] = (i + 3) * 3;
    }
    int pedazos = chunk;

    auto start = std::chrono::high_resolution_clock::now();

    #pragma omp parallel for \
    shared(a, b, c, pedazos) private(i) \
    schedule(static, pedazos)

    for (i = 0; i < N; i++)
        c[i] = a[i] + b[i];

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Tiempo de ejecucion del calculo paralelo: " << duration.count() << " segundos\n";

    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << std::endl;
    imprimeArreglo(a);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << std::endl;
    imprimeArreglo(b);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << std::endl;
    imprimeArreglo(c);
}

void imprimeArreglo(float* d)
{
    for (int x = 0; x < mostrar; x++)
        std::cout << d[x] << " - ";
    std::cout << std::endl;
}
