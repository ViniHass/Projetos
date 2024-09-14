#ifndef BUSCA_H
#define BUSCA_H

#include <stdio.h>
#include <stdlib.h>

//Melhor Caso: O(1)
//Pior Caso: O(n)
int busca_sequencial(int lista[], int tamanho, int valor);

//Melhor Caso: O(1)
//Pior Caso: O(log n)
int busca_binaria(int lista[], int tamanho, int valor);

//Pior Caso: O(log3 n) 
int busca_ternaria(int lista[], int tamanho, int valor);

//Melhor Caso: O(1)
//Pior Caso: O(n) 
int busca_interpolar(int lista[], int tamanho, int valor);

//Melhor Caso: O(1)
//Pior Caso: O(log n)
int busca_exponencial(int lista[], int tamanho, int valor);

//busca binaria auxiliar para busca exponencial
int busca_bin(int lista[], int tamanho, int valor, int esquerda, int direita);

//Melhor Caso: O(1)
//Pior Caso: O(sqrt(n))
int busca_por_salto(int lista[], int tamanho, int valor);

#endif