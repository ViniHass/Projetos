#ifndef CADASTRO_H
#define CADASTRO_H

#include <stdio.h>
#include <stdlib.h>


typedef struct Dia
{
    int dia;
    int mes;
    int ano;
} Dia;

//lista para os shows
typedef struct Show *PonteiroShow;

typedef struct Show
{
    int codShow;
    char artista[20];
    Dia dia;
    char local[32];
    int codigoIngresso[10];
    PonteiroShow ptr_prox;
} Show;

typedef struct ListaShows
{
    PonteiroShow ptr_primeiro;
    PonteiroShow ptr_ultimo;
} ListaShows;

//lista para os tipos de ingresso
typedef struct Ingressos *PonteiroIngressos;

typedef struct Ingressos
{
    PonteiroShow show;
    int codIngresso;
    char tipo[12];
    double preco;
    PonteiroIngressos ptr_prox;
} Ingressos;

typedef struct ListaIngressos
{
    PonteiroIngressos ptr_primeiro;
    PonteiroIngressos ptr_ultimo;
} ListaIngressos;




void iniciaListaShows(ListaShows *lista);

void iniciaListaIngressos(ListaIngressos *lista);

void adicionarShow(ListaShows *lista, Show show);

PonteiroIngressos adicionarIngresso(ListaIngressos *lista, ListaShows *shows);

void imprimirShows(ListaShows *lista, ListaIngressos *listaingressoss);

void imprimirIngressos(ListaIngressos *lista, int codigoIngresso[10]);

void liberarListasShows(ListaShows *lista, ListaIngressos *lista2);

void lerData(Dia *data);

Show lerShow();

Ingressos lerIngresso();

PonteiroShow escolherShow(ListaShows *lista);

PonteiroIngressos escolherIngresso(ListaIngressos *Ingressos, ListaShows *Shows);


#endif