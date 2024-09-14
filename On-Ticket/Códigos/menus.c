#include <stdio.h>
#include <stdlib.h>
#include "menus.h"
#include "cadastro.h"
#include "usuarios.h"
#include "reserva.h"
#include "Ordenacao.h"
#include "Busca.h"


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


void clear()
{
  system(CLEAR_COMMAND);
}

void printLogin()
{
  printf("\n============================================\n");
  printf("\n                 On-Ticket                  \n");
  printf("\n============================================\n");
  printf("\nSelecione uma opção:\n\n");
  printf("1- Fazer Login.\n");
  printf("2- Realizar cadastro.\n");
  printf("3- ENCERRAR o programa.\n");
}

int login( ListaUsers *users, ListaUsers *admins, TipoUser *usuario )
{
  system("clear");
  printLogin();
  int n;
  while (scanf("%d", &n) != 1) 
  {
    while (getchar() != '\n');
    printf("Entrada inválida.\n\n Digite um número válido: ");
  }
  switch ( n )
  {
    case 1 :
      *usuario = fazerLogin( users, admins );
      break;    
    case 2 :
      cadastraUsuarios( users );
      break;
    case 3 :
      return 1;
      break;
    default :
      printf("\nNúmero inválido.\n\nAperte ENTER para digitar novamente...");
      getchar();
      getchar();
      return 0;
  }
  return 0;
}


void printMenuUsuario()
{
  printf("\nSelecione uma opção:\n\n");
  printf("1- Visualizar shows.\n");
  printf("2- Realizar reserva.\n");
  printf("3- Minhas reservas.\n");
  printf("4- Cancelar reserva.\n");
  printf("5- Alterar dados cadastrais\n");
  printf("6- Logoff.\n");
}

int MenuUsuario( TipoUser *usuario, ListaShows *shows, ListaIngressos *ingressos, ReservasUser reservas[])
{
  system("clear");
  int n;
  printf("\n============================================\n");
  printf("\n          Logado como %s!              \n\n",(*usuario)->usuario.nome);
  printf("============================================\n");
  //printf("Logado como %s\n\n", (*usuario)->usuario.nome);
  printMenuUsuario();


  while(scanf("%d", &n) != 4) {
      switch ( n )
      {
        case 1 :
        imprimirShows( shows, ingressos );
        printf("\nAperte Enter para retornar...");
        getchar();  // Captura o Enter pressionado
        getchar();  // Pausa até o Enter ser pressionado novamente
          
          break;

        case 2 :
          obterReserva(reservas,*usuario,ingressos, shows);
          break;

        case 3 :
          imprimirReservas(reservas, ingressos, *usuario);
          break;

        case 4 :
          cancelaReserva(reservas, *usuario, ingressos, shows);
          break;

        case 5 :
          MenuAlteraDados( usuario );
          break;

        case 6 :
          *usuario = NULL;
          break;

        default :
          printf("\nOpcao invalida, aperte ENTER para escolher novamente...");
          getchar();
          getchar();
        }      
    return 0;
  }
  
 return 0;
}

void printMenuAlteraDados()
{
  printf("\n============================================\n");
  printf("\n             RESERVAS OBTIDAS              \n");
  printf("\n============================================\n");
  printf("\nSelecione uma opção\n\n");
  printf("1: Alterar o nome\n");
  printf("2: Mudar Senha\n");
  printf("3: Retornar\n");
};

void MenuAlteraDados( TipoUser *usuario )
{
  system("clear");
  printMenuAlteraDados();
  int n;
  while (scanf("%d", &n) != 1) 
  {
    while (getchar() != '\n');
    printf("Entrada inválida. Digite um número válido: ");
  }
  switch ( n )
  {
    case 1 :
    alteraNome( usuario );
    break;

    case 2 :
    alteraSenha( usuario );
    break;

    case 3 :
    return;

    default :
    printf("\nOpcao invalida, aperte ENTER para escolher novamente...");
    getchar();
    getchar();
    return;
  }
}

void printMenuAdmin()
{
  printf("\nMenu de Administração:\n\n");
  printf("1: Visualizar shows.\n");
  printf("2: Cadastrar shows.\n");
  printf("3: Disponibilizar ingressos.\n");
  printf("4: Apresentar Banco de dados.\n");
  printf("5: Buscar Usuario.\n");
  printf("6: Ver Lista de Reservas.\n");
  printf("7. Vender ingressos.\n");
  printf("8: Logoff.\n");
};

int MenuAdmin( TipoUser *usuario, ListaUsers *users ,ListaShows *shows, ListaIngressos *ingressos, ReservasUser reserva[])
{
  system("clear");
  int n;
  PonteiroIngressos newingresso = NULL;
  printf("\n============================================\n");
  printf("\nLogado como %s!              \n\n",(*usuario)->usuario.nome);
  printf("============================================\n\n");
  //printf("Logado como %s\n\n", (*usuario)->usuario.nome);
  printMenuAdmin();
  while (scanf("%d", &n) != 1) 
  {
    while (getchar() != '\n');
    printf("Entrada inválida. Digite um número válido: ");
  }
  switch ( n )
  {
    case 1 :
      imprimirShows( shows, ingressos );
      printf("\nAperte Enter para retornar...");
      getchar();  // Captura o Enter pressionado
      getchar();  // Pausa até o Enter ser pressionado novamente
      break;
      break;

    case 2 :
      MenuCadastraShow( usuario, shows, ingressos );
      break;

    case 3 :
      newingresso = adicionarIngresso( ingressos, shows);
      StartReserva( reserva, newingresso );
      break;

    case 4 :
      MenuOrdenacao( users );
      break;

    case 5 :
      MenuBusca( users );
      break;

    case 6 :
      imprimirTodasReservas( reserva,  ingressos, shows, users);
      break;

    case 7 :
      distribuirReservas( reserva, ingressos, shows, users);
      break;

    case 8 :
      *usuario = NULL;
      break;

    default :
      printf("\nOpcao invalida, aperte ENTER para escolher novamente...");
      getchar();
      getchar();
      return 0;
  }
  return 0;
}

void printMenuCadastraShow()
{
  printf("\n============================================\n");
  printf("\n             CADASTRO DE SHOWS               \n");
  printf("\n============================================\n");
  printf("\nSelecione uma opcao\n");
  printf("\n1- Novo Show\n");
  printf("2- Retornar\n");
};

void MenuCadastraShow( TipoUser *usuario , ListaShows *shows, ListaIngressos *ingressos)
{
  system("clear");
  
  printMenuCadastraShow();
  Show show;
  int n;
  while (scanf("%d", &n) != 1) 
  {
    while (getchar() != '\n');
    printf("Entrada inválida. Digite um número válido: ");
  }
  switch ( n )
  {
    case 1 :
      show = lerShow();
      adicionarShow( shows, show);
    break;

    case 2 :
      return;

    default :
      printf("\nOpcao invalida, aperte ENTER para escolher novamente...");
      getchar();
      getchar();
    return;
  }
}

void printMenuOrdenacao()
{
  printf("\n============================================\n");
  printf("\n              Banco de Dados                \n");
  printf("\n============================================\n");
  printf("\nSelecione uma opcao de ordenação para apresentar o banco de dados\n");
  printf("\n0- Imprimir sem ordenar\n");
  printf("1- BubbleSort\n");
  printf("2- BubbleSort Otimizado\n");
  printf("3- SelectionSort\n");
  printf("4- InsertionSort\n");
  printf("5- MergeSort\n");
  printf("6- QuickSort\n");
  printf("7- RadixSort\n");
  printf("8- CountingSort\n");
  printf("9- Retornar\n");
};

void MenuOrdenacao( ListaUsers *users )
{
  system("clear");
  int *id;
  inicializar_vetor( &id , users );
  descarregaVetor( id, users);

  int MAX_USERS = numUser(users);
  
  printMenuOrdenacao();
  int n;
  int *copia;
  inicializar_vetor( &copia , users );

  while (scanf("%d", &n) != 1) 
  {
    while (getchar() != '\n');
    printf("Entrada inválida. Digite um número válido: ");
  }
  switch ( n )
  {
    case 0 :
    copiaVetor( id, copia, users);
    printVetorOrdenado(copia, users);
    free(copia);
    free(id);
    printf("\nAperte ENTER para continuar...");
    getchar();
    getchar();
    break;

    case 1 :
    copiaVetor( id, copia, users);
    bubbleSort(copia, MAX_USERS);
    printVetorOrdenado(copia, users);
    free(copia);
    free(id);
    printf("\nAperte ENTER para continuar...");
    getchar();
    getchar();
    return;

    case 2 :
    copiaVetor( id, copia, users);
    bubbleSort_Otimizado(copia, MAX_USERS);
    printVetorOrdenado(copia, users);
    free(copia);
    free(id);
    printf("\nAperte ENTER para continuar...");
    getchar();
    getchar();    
    return;

    case 3 :
    copiaVetor( id, copia, users);
    selectionSort(copia, MAX_USERS);
    printVetorOrdenado(copia, users);
    free(copia);
    free(id);
    printf("\nAperte ENTER para continuar...");
    getchar();
    getchar();    
    return;

    case 4 :
    copiaVetor( id, copia, users);
    insertionSort(copia, MAX_USERS);
    printVetorOrdenado(copia, users);
    free(copia);
    free(id);
    printf("\nAperte ENTER para continuar...");
    getchar();
    getchar();    
    return;

    case 5 :
    copiaVetor( id, copia, users);
    mergeSort(copia,0 , MAX_USERS -1);
    printVetorOrdenado(copia, users);
    free(copia);
    free(id);
    printf("\nAperte ENTER para continuar...");
    getchar();
    getchar();    
    return;

    case 6 :
    copiaVetor( id, copia, users);
    quickSort(copia,0 , MAX_USERS -1);
    printVetorOrdenado(copia, users);
    free(copia);
    free(id);
    printf("\nAperte ENTER para continuar...");
    getchar();
    getchar();    
    return;

    case 7 :
    copiaVetor( id, copia, users);
    radixSort(copia, MAX_USERS);
    printVetorOrdenado(copia, users);
    free(copia);
    free(id);
    printf("\nAperte ENTER para continuar...");
    getchar();
    getchar();    
    return;

    case 8 :
    copiaVetor( id, copia, users);
    countingSort(copia, MAX_USERS);
    printVetorOrdenado(copia, users);
    free(copia);
    free(id);
    printf("\nAperte ENTER para continuar...");
    getchar();
    getchar();    
    return;

    case 9 :    
    return;

    default :
    printf("\nOpcao invalida, aperte ENTER para escolher novamente...");
    getchar();
    getchar();
    return;
  }
}


void printMenuBusca()
{
  system("clear");
  printf("\n============================================\n");
  printf("\n               Busca Usuario                \n");
  printf("\n============================================\n");
  printf("\nSelecione uma opcao de busca\n");
  printf("1- Busca Sequencial\n");
  printf("2- Busca Binaria\n");
  printf("3- Busca Ternaria\n");
  printf("4- Busca Interpolar\n");
  printf("5- Busca Exponencial\n");
  printf("6- Busca Por Salto\n");
  printf("7- Retornar\n");
};

void MenuBusca( ListaUsers *users )
{
  system("clear");

  int *id;
  inicializar_vetor( &id , users );
  descarregaVetor( id, users);

  int MAX_USERS = numUser(users);

  int *copia;
  inicializar_vetor( &copia , users );
  
  printMenuBusca();
  int n;
  int find, pos;

  while (scanf("%d", &n) != 1) 
  {
    while (getchar() != '\n');
    printf("Entrada inválida. Digite um número válido: ");
  }
  switch ( n )
  {
    case 1 :
    copiaVetor( id, copia, users);
    bubbleSort_Otimizado(copia, MAX_USERS);
    printf("\nDigite o Id que deseja buscar.\n");
    while (scanf("%d", &find) != 1) 
    {
      while (getchar() != '\n');
      printf("Entrada inválida. Digite um número válido: ");
    }
    pos = busca_sequencial(copia, MAX_USERS, find);
    printNumEscolhido(copia, pos, users);
    free(copia);
    free(id);
    printf("\nAperte ENTER para continuar...");
    getchar();
    getchar();
    return;

    case 2 :
    copiaVetor( id, copia, users);
    bubbleSort_Otimizado(copia, MAX_USERS);
    printf("\nDigite o Id que deseja buscar.\n");
    while (scanf("%d", &find) != 1) 
    {
      while (getchar() != '\n');
      printf("Entrada inválida. Digite um número válido: ");
    }
    pos = busca_binaria(copia, MAX_USERS, find);
    printNumEscolhido(copia, pos, users);
    free(copia);
    free(id);
    printf("\nAperte ENTER para continuar...");
    getchar();
    getchar();
    return;

    case 3 :
    copiaVetor( id, copia, users);
    bubbleSort_Otimizado(copia, MAX_USERS);
    printf("\nDigite o Id que deseja buscar.\n");
    while (scanf("%d", &find) != 1) 
    {
      while (getchar() != '\n');
      printf("Entrada inválida. Digite um número válido: ");
    }
    pos = busca_ternaria(copia, MAX_USERS, find);
    printNumEscolhido(copia, pos, users);
    free(copia);
    free(id);
    printf("\nAperte ENTER para continuar...");
    getchar();
    getchar();
    return;

    case 4 :
    copiaVetor( id, copia, users);
    bubbleSort_Otimizado(copia, MAX_USERS);
    printf("\nDigite o Id que deseja buscar.\n");
    while (scanf("%d", &find) != 1) 
    {
      while (getchar() != '\n');
      printf("Entrada inválida. Digite um número válido: ");
    }
    pos = busca_interpolar(copia, MAX_USERS, find);
    printNumEscolhido(copia, pos, users);
    free(copia);
    free(id);
    printf("\nAperte ENTER para continuar...");
    getchar();
    getchar();
    return;

    case 5 :
    copiaVetor( id, copia, users);
    bubbleSort_Otimizado(copia, MAX_USERS);
    printf("\nDigite o Id que deseja buscar.\n");
    while (scanf("%d", &find) != 1) 
    {
      while (getchar() != '\n');
      printf("Entrada inválida. Digite um número válido: ");
    }
    pos = busca_exponencial(copia, MAX_USERS, find);
    printNumEscolhido(copia, pos, users);
    free(copia);
    free(id);
    printf("\nAperte ENTER para continuar...");
    getchar();
    getchar();
    return;

    case 6 :
    copiaVetor( id, copia, users);
    bubbleSort_Otimizado(copia, MAX_USERS);
    printf("\nDigite o Id que deseja buscar.\n");
    while (scanf("%d", &find) != 1) 
    {
      while (getchar() != '\n');
      printf("Entrada inválida. Digite um número válido: ");
    }
    pos = busca_por_salto(copia, MAX_USERS, find);
    printNumEscolhido(copia, pos, users);
    free(copia);
    free(id);
    printf("\nAperte ENTER para continuar...");
    getchar();
    getchar();
    return;

    case 7 :    
    return;

    default :
    printf("\nOpcao invalida, aperte ENTER para escolher novamente...");
    getchar();
    getchar();
    return;
  }
}
