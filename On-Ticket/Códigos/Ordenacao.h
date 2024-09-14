#ifndef ORDENACAO_H
#define ORDENACAO_H

#include <stdio.h>
#include <stdlib.h>

void bubbleSort (int vetor[], int n);

void bubbleSort_Otimizado (int vetor[], int n);

void selectionSort(int v[], int tam);

void insertionSort(int vetor[], int n);

// Função para realizar o Merge Sort
void merge(int vetor[], int inicio, int meio, int fim);

void mergeSort(int vetor[], int inicio, int fim);

// Função para trocar os valores de duas variáveis
void trocar(int* a, int* b);

// Função para particionar o vetor em torno de um pivô
int particionar(int vetor[], int inicio, int fim);

// Função do Quick Sort
void quickSort(int vetor[], int inicio, int fim);

// Função para encontrar o maior elemento no array
int findMax(int vetor[], int n);

// Função para realizar a contagem do dígito específico (exp) no array usando o Counting Sort
void countingSort_Radix(int vetor[], int n, int exp);

// Função para realizar o Radix Sort
void radixSort(int vetor[], int n);

void countingSort(int vetor[], int n);

// Função auxiliar para imprimir o vetor
void printVetor(int vetor[], int n);

#endif