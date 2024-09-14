#ifndef RESERVA_H
#define RESERVA_H

#define TAM_LISTA 10
#define MAX_NUM_RESERVA 10

#include <stdio.h>
#include <stdlib.h>
#include "cadastro.h"
#include "usuarios.h"

typedef struct reserva
{
    int id;
    int codigoreserva;
}TipoReserva;

typedef struct reservaUser{
    int codIngresso;
    int comeco, fim;
    int totalIngressos;
    TipoReserva reservas[MAX_NUM_RESERVA];
}ReservasUser;


void inicializaReserva(ReservasUser *reserva);

void StartReserva( ReservasUser reserva[], PonteiroIngressos ingresso);

void obterReserva(ReservasUser reserva[], TipoUser usuario, ListaIngressos *ingressos, ListaShows *shows);

void imprimirReservas(ReservasUser reservas[], ListaIngressos *ingressos , TipoUser usuario);

void imprimirTodasReservas(ReservasUser reservas[], ListaIngressos *ingressos, ListaShows *Shows, ListaUsers *lista);

void cancelaReserva(ReservasUser reservas[], TipoUser usuario, ListaIngressos *ingressos, ListaShows *shows);

void distribuirReservas(ReservasUser reservas[], ListaIngressos *ingressos, ListaShows *Shows, ListaUsers *lista);

#endif