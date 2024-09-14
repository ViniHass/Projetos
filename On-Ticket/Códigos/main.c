#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuarios.h"
#include "menus.h"
#include "cadastro.h"
#include "reserva.h"

#include <unistd.h>

#define MATRIX_COLUMNS 81

void print_matrix(int matrix[MATRIX_COLUMNS])
{
  for (int j = 0; j < MATRIX_COLUMNS; j++) {
    if (matrix[j] == 1)
      printf("\033[7;36m \033[0;m");
    else
      printf(" ");
  }
  putchar('\n');
}

void run_Intro()
{
  int matrix[MATRIX_COLUMNS];
  int i, p;
  
  printf("\n");
  system("clear");
  // Inicialmente, preenchemos a matriz com espaços em branco
  for (int j = 0; j < MATRIX_COLUMNS; j++) {
      matrix[j] = 1;
  }

  for (i = 0; i < 20; i++)
      print_matrix(matrix);
  i = 0;

  while (i < 120) {
      p = MATRIX_COLUMNS / 2;
      if (i < MATRIX_COLUMNS) {
          matrix[p + i / 2] = 0;
          matrix[p - i / 2] = 0;
      }
      i++;
      print_matrix(matrix);
      usleep(20000); // Adjust this value to control the rising speed (microseconds)
  }
  system("clear");
}


int main()
{
  FILE *arquivoUsuarios;
  ListaUsers users;
  ListaUsers admins;
  TipoUser usuario = NULL;
  ReservasUser reservas[TAM_LISTA];
  

  iniciaListaUsuarios(&users);
  iniciaListaUsuarios(&admins);

  int i;
  for(i=0;i<10;i++)
    inicializaReserva(&(reservas[i]));
  

  ListaShows shows;
  ListaIngressos ingressos;
  iniciaListaShows(&shows);
  iniciaListaIngressos(&ingressos);


  arquivoUsuarios = fopen("usuarios.txt", "r+");
  if (arquivoUsuarios == NULL)
  {
    // Se o arquivo de usuários não existir, criar um novo arquivo vazio
    arquivoUsuarios = fopen("usuarios.txt", "w+");
    if (arquivoUsuarios == NULL)
    {
      printf("Erro ao criar o arquivo de usuários.\n");
      return 1;
    }
  }
  else
  {
    carregarDadosUsuarios(&users, &admins, arquivoUsuarios);
  }

  run_Intro();
  
  printf("\033[3;36m");
  //Corpo da função principal do programa
  while (1)
  {
    //pede login de um usuario
    if (usuario == NULL)
    {
      if (login(&users, &admins, &usuario))
        break;
    }
    //entra no programa como um usuario
    if (usuario != NULL && usuario->usuario.privilegio==0)
    {
      if (MenuUsuario(&usuario, &shows, &ingressos, reservas))
        break;
    }
    //entra no programa como um administrador
    if (usuario != NULL && usuario->usuario.privilegio==1)
    {
      if (MenuAdmin( &usuario, &users ,&shows, &ingressos, reservas) )
        break;
    }
  }

  liberarListasShows(&shows, &ingressos);

  // Posicionar o ponteiro do arquivo no início
  rewind(arquivoUsuarios);
  // Salvar as alterações no arquivo de usuários
  salvarDadosUsuarios(&admins, arquivoUsuarios);
  salvarDadosUsuarios(&users, arquivoUsuarios);
  fclose(arquivoUsuarios);

  liberarListaUsuarios(&users);

  return 0;
}