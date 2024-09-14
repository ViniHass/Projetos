
#include <stdio.h>
#include <stdlib.h>
#include "Ordenacao.h"

void bubbleSort (int vetor[], int n) {
    int k, j, aux;


    for (k = 1; k < n; k++) {

        for (j = 0; j < n - 1; j++) {

            if (vetor[j] > vetor[j + 1]) {
                aux          = vetor[j];
                vetor[j]     = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}

void bubbleSort_Otimizado (int vetor[], int n) {

    int k, j, aux;
    int rep;

    rep = (n/3+1);

    for (k = 0; k < rep; k++) 
    {
        //segue ordenando os vetores
        for (j = 0 + k; j < n - 1 - k; j++) 
        {
            if (vetor[j] > vetor[j + 1]) 
            {
                aux          = vetor[j];
                vetor[j]     = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }

        //passa voltando pelos vetores
        for (j = n - 1 - k; j > 0 + k; j--)
        {
            if (vetor[j] < vetor[j - 1]) 
            {
                aux          = vetor[j];
                vetor[j]     = vetor[j - 1];
                vetor[j - 1] = aux;
            }
        }
        
    }
}

void selectionSort(int v[], int tam)
{
    int i, j;
    int comp;
    for (i = 0; i < tam - 1; i++)
    {
        comp = v[i];
        for (j = i + 1; j < tam; j++)
        {
            if (v[j] < comp)
            {
                comp = v[j];
                v[j] = v[i];
                v[i] = comp;
            }
        }
    }
}

void insertionSort(int vetor[], int n) {
    int i, chave, j;
    for (i = 1; i < n; i++) {
        chave = vetor[i];
        j = i - 1;

        // Mover os elementos do array que são maiores que a chave para uma posição à frente
        while (j >= 0 && vetor[j] > chave) {
            vetor[j + 1] = vetor[j];
            j = j - 1;
        }
        vetor[j + 1] = chave;
    }
}

// Função para realizar o Merge Sort
void merge(int vetor[], int inicio, int meio, int fim) {
    int tamanhoEsquerdo = meio - inicio + 1;
    int tamanhoDireito = fim - meio;

    // Cria vetores temporários para armazenar as sublistas da esquerda e da direita
    int* esquerdo = (int*)malloc(tamanhoEsquerdo * sizeof(int));
    int* direito = (int*)malloc(tamanhoDireito * sizeof(int));

    // Copia os elementos para os vetores temporários
    for (int i = 0; i < tamanhoEsquerdo; i++) {
        esquerdo[i] = vetor[inicio + i];
    }
    for (int j = 0; j < tamanhoDireito; j++) {
        direito[j] = vetor[meio + 1 + j];
    }

    // Merge das sublistas temporárias para o vetor original
    // Índice para a sublista esquerda
    int i = 0; 
    // Índice para a sublista direita
    int j = 0;
    // Índice para o vetor original
    int k = inicio; 

    while (i < tamanhoEsquerdo && j < tamanhoDireito) {
        if (esquerdo[i] <= direito[j]) {
            vetor[k] = esquerdo[i];
            i++;
        } else {
            vetor[k] = direito[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes, se houver, da sublista esquerda
    while (i < tamanhoEsquerdo) {
        vetor[k] = esquerdo[i];
        i++;
        k++;
    }

    // Copia os elementos restantes, se houver, da sublista direita
    while (j < tamanhoDireito) {
        vetor[k] = direito[j];
        j++;
        k++;
    }

    // Libera a memória dos vetores temporários
    free(esquerdo);
    free(direito);
}

void mergeSort(int vetor[], int inicio, int fim) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;

        // Divide o vetor em duas metades e chama recursivamente o mergeSort para cada metade
        mergeSort(vetor, inicio, meio);
        mergeSort(vetor, meio + 1, fim);

        // Une as duas metades ordenadas usando o merge
        merge(vetor, inicio, meio, fim);
    }
}

// Função para trocar os valores de duas variáveis
void trocar(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função para particionar o vetor em torno de um pivô
int particionar(int vetor[], int inicio, int fim) {
    // Pivô é o último elemento do vetor
    int pivô = vetor[fim]; 
    // Índice do menor elemento
    int i = inicio - 1; 

    // Percorre o vetor, colocando os elementos menores que o pivô à esquerda dele
    for (int j = inicio; j < fim; j++) {
        if (vetor[j] <= pivô) {
            i++;
            trocar(&vetor[i], &vetor[j]);
        }
    }

    trocar(&vetor[i + 1], &vetor[fim]); // Coloca o pivô em sua posição correta
    // Retorna a posição do pivô
    return i + 1; 
}

// Função do Quick Sort
void quickSort(int vetor[], int inicio, int fim) {
    if (inicio < fim) {
        int p = particionar(vetor, inicio, fim);

        // Chama o quickSort recursivamente para as duas metades do vetor
        quickSort(vetor, inicio, p - 1);
        quickSort(vetor, p + 1, fim);
    }
}

// Função para encontrar o maior elemento no array
int findMax(int vetor[], int n) {
    int max = vetor[0];
    for (int i = 1; i < n; i++) {
        if (vetor[i] > max) {
            max = vetor[i];
        }
    }
    return max;
}

// Função para realizar a contagem do dígito específico (exp) no array usando o Counting Sort
void countingSort_Radix(int vetor[], int n, int exp) {
    int output[n];
    int count[10] = {0};

    // Contar o número de ocorrências de cada dígito
    for (int i = 0; i < n; i++) {
        count[(vetor[i] / exp) % 10]++;
    }

    // Atualizar o array de contagem para conter as posições corretas
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Construir o array de saída
    for (int i = n - 1; i >= 0; i--) {
        output[count[(vetor[i] / exp) % 10] - 1] = vetor[i];
        count[(vetor[i] / exp) % 10]--;
    }

    // Copiar o array de saída para o array original
    for (int i = 0; i < n; i++) {
        vetor[i] = output[i];
    }
}

// Função para realizar o Radix Sort
void radixSort(int vetor[], int n) {
    // Encontrar o valor máximo para determinar o número de dígitos
    int max = findMax(vetor, n);

    // Realizar o Counting Sort para cada dígito, começando pelo dígito menos significativo (1)
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSort_Radix(vetor, n, exp);
    }
}

void countingSort(int vetor[], int n) {
    // Encontrar o valor máximo no array para determinar o tamanho do array de contagem
    int max = vetor[0];
    for (int i = 1; i < n; i++) {
        if (vetor[i] > max) {
            max = vetor[i];
        }
    }

    // Criar o array de contagem e inicializá-lo com zeros
    int* count = (int*)calloc(max + 1, sizeof(int));

    // Contar o número de ocorrências de cada elemento
    for (int i = 0; i < n; i++) {
        count[vetor[i]]++;
    }

    // Atualizar o array de contagem para conter as posições corretas
    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }

    // Construir o array de saída
    int* output = (int*)malloc(n * sizeof(int));
    for (int i = n - 1; i >= 0; i--) {
        output[count[vetor[i]] - 1] = vetor[i];
        count[vetor[i]]--;
    }

    // Copiar o array de saída para o array original
    for (int i = 0; i < n; i++) {
        vetor[i] = output[i];
    }

    // Liberar a memória alocada
    free(count);
    free(output);
}

// Função auxiliar para imprimir o vetor
void printVetor(int vetor[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}
