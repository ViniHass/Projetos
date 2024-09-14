#ifndef MENUS_H
#define MENUS_H

#include "Tarvore.h"

#ifdef _WIN32
  #define CLEAR_COMMAND "cls"
#elif defined __linux__
  #define CLEAR_COMMAND "clear"
#elif defined __APPLE__
  #define CLEAR_COMMAND "clear"
#elif defined __unix__
  #define CLEAR_COMMAND "clear"
#else
  #define CLEAR_COMMAND ""
#endif

void menuInical();


void exibirHistoria();


int jogo( NoArvore* raiz, TipoHeroi *player);

void menuHeroi();

void MenuCombate( NoArvore* raiz, TipoHeroi *player );

void printDecideCombate( NoArvore* raiz, TipoHeroi *heroi);

void printRat();

void printEsqueleto();

void printBird();

void printMinotauro();

#endif