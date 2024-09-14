#include "usuarios.h"
#include "menus.h"
#include "cadastro.h"
#include "reserva.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void iniciaListaShows(ListaShows *lista)
{
    lista->ptr_primeiro = NULL;
    lista->ptr_ultimo = NULL;
}

void iniciaListaIngressos(ListaIngressos *lista)
{
    lista->ptr_primeiro = NULL;
    lista->ptr_ultimo = NULL;
}

void adicionarShow(ListaShows *lista, Show show)
{
    PonteiroShow novo = (PonteiroShow)malloc(sizeof(struct Show));
    if (novo == NULL)
    {
        printf("Erro de alocação de memória.\n");
        return;
    }

    novo->codShow = 0;
    strcpy(novo->artista, show.artista);
    novo->dia = show.dia;
    strcpy(novo->local, show.local);
    novo->ptr_prox = NULL;

    for (int i = 0; i < 10; i++)
    {
        novo->codigoIngresso[i] = 0;
    }

    if (lista->ptr_primeiro == NULL)
    {
        novo->codShow = 1;
        lista->ptr_primeiro = novo;
        lista->ptr_ultimo = novo;
    }
    else
    {
        novo->codShow = 1 + lista->ptr_ultimo->codShow;
        lista->ptr_ultimo->ptr_prox = novo;
        lista->ptr_ultimo = novo;
    }

    printf("\n\n>>> Show cadastrado com sucesso <<<\n\nAperte ENTER para retornar...");
    getchar();
    
}

PonteiroIngressos adicionarIngresso(ListaIngressos *lista, ListaShows *shows)
{
  system("clear");
  printf("\n================================================\n");
  printf("\n             CADASTRO DE INGRESSOS              \n");
  printf("\n================================================\n");

  if(shows->ptr_primeiro == NULL) {
    printf("\nNão há Shows cadastrados.\n\nAperte enter para retornar...");
    getchar();
    getchar();
    return NULL;
  }
    PonteiroIngressos novo = (PonteiroIngressos)malloc(sizeof(struct Ingressos));
    if (novo == NULL)
    {
        printf("Erro de alocação de memória.\n");
        return NULL;
    }

    PonteiroShow show = escolherShow(shows);
    if( show==NULL )
    {
        printf("numero escolhido inválido\n");
        printf("\nOpcao invalida, aperte ENTER para retornar...");
        getchar();
        getchar();
        return NULL;
    }

    novo->show = show;

    if(show == NULL) {
      printf("\nShow não encontrado, aperte ENTER para escolher novamente...");
      getchar();
      getchar();
    }

    Ingressos ingresso = lerIngresso();

    novo->codIngresso = 0;
    strcpy(novo->tipo, ingresso.tipo);
    novo->preco = ingresso.preco;
    novo->ptr_prox = NULL;

    if (lista->ptr_primeiro == NULL)
    {
        novo->codIngresso = 1;
        lista->ptr_primeiro = novo;
        lista->ptr_ultimo = novo;
    }
    else
    {
        novo->codIngresso = lista->ptr_ultimo->codIngresso + 1;
        lista->ptr_ultimo->ptr_prox = novo;
        lista->ptr_ultimo = novo;
    }

   

    int i;
    if(show->codigoIngresso[9]!=0)
    {
        printf("Não é possivel cadastrar mais ingressos!\n");
        return NULL;
    } else
    {
        for(i=0; i<10; i++)
        {
            if(show->codigoIngresso[i]==0)
            {
                show->codigoIngresso[i] = novo->codIngresso;
                break;
            }
        }
    }

    printf("\n\n>>> Ingresso cadastrado com sucesso <<<\n\nAperte ENTER para retornar...");
    getchar();
    
    return lista->ptr_ultimo;
    
}

void imprimirShows(ListaShows *lista, ListaIngressos *listaingressos)
{
  system("clear");
  printf("\n============================================\n");
  printf("\n             TELA DE SHOWS             \n\n");
  printf("============================================\n\n");
    PonteiroShow atual = lista->ptr_primeiro;

    if (atual == NULL)
    {
        printf("\nNão há shows cadastrados.\n");
        return;
    }

    while (atual != NULL)
    {
        printf("Código do Show: %d\n", atual->codShow);
        printf("Artista: %s\n", atual->artista);
        printf("Data: %02d/%02d/%d\n", atual->dia.dia, atual->dia.mes, atual->dia.ano);
        printf("Local: %s\n", atual->local);

        int ingressoEncontrado = 0;
        for (int i = 0; i < 10; i++)
        {
            if (atual->codigoIngresso[i] != 0)
            {
                ingressoEncontrado = 1;
                break;
            }
        }

        if (ingressoEncontrado)
        {
            printf("Ingressos:\n");
            imprimirIngressos(listaingressos, atual->codigoIngresso);
            printf("--------------------------------------------\n");
        }
        else
        {
            printf("Este show não possui ingressos cadastrados.\n");
            printf("--------------------------------------------\n");
        }

        printf("\n");
        atual = atual->ptr_prox;
    }
}

void imprimirIngressos(ListaIngressos *lista, int codigoIngresso[10])
{
    PonteiroIngressos ingresso_atual = lista->ptr_primeiro;

    if (ingresso_atual == NULL)
    {
        printf("\nNão há ingressos cadastrados para este show\n");
        printf("Aperte ENTER para escolher novamente...");
        getchar();
        getchar();
        return;
    }

    for (int i = 0; i < 10; i++)
    {
        if (codigoIngresso[i] == 0)
            break;

        while (ingresso_atual != NULL && ingresso_atual->codIngresso != codigoIngresso[i])
        {
            ingresso_atual = ingresso_atual->ptr_prox;
        }

        if (ingresso_atual != NULL)
        {
            printf("%d. Tipo: %s, Preço: %.2lf\n",
               ingresso_atual->codIngresso, ingresso_atual->tipo, ingresso_atual->preco);
        }
    }
}


void liberarListasShows(ListaShows *lista, ListaIngressos *lista2)
{

    PonteiroIngressos atual2 = lista2->ptr_primeiro;
    PonteiroIngressos proximo2;
    while (atual2 != NULL)
    {
        proximo2 = atual2->ptr_prox;
        free(atual2);
        atual2 = proximo2;
    }

    lista2->ptr_primeiro = NULL;
    lista2->ptr_ultimo = NULL;

    PonteiroShow atual = lista->ptr_primeiro;
    PonteiroShow proximo;
    while (atual != NULL)
    {
        proximo = atual->ptr_prox;
        free(atual);
        atual = proximo;
    }

    lista->ptr_primeiro = NULL;
    lista->ptr_ultimo = NULL;
}

void lerData(Dia *data)
{
    int dia;
    int mes;
    int ano;
    int erro = 0;

    printf("Digite a data no formato dd/mm/aaaa: ");
    scanf("%d/%d/%d", &dia, &mes, &ano);

    int bissexto = (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0));
    int dias_por_mes[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


    while (ano < 2023 || mes < 1 || mes > 12 || dia < 1 || (mes == 2 && (bissexto ? dia > 29 : dia > 28)) || dia > dias_por_mes[mes]) {
    if (!erro) {
        printf("\n[ERRO] Data inválida, pressione ENTER para digitar uma nova data\n");
        erro = 1; // Indica que a mensagem de erro já foi exibida
    }
    getchar();
    if (getchar() == '\n') {
        printf("Digite a data no formato dd/mm/aaaa: ");
        scanf("%2d/%2d/%4d", &dia, &mes, &ano);
        erro = 0; // Reset da variável de controle de erro após a tentativa de correção
    }
    bissexto = (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0));
    }

    data->dia = dia;
    data->mes = mes;
    data->ano = ano;
}

Show lerShow()
{
    Show novo;

    printf("\nDigite o nome do artista: ");
    scanf(" %19[^\n]%*c", novo.artista);

    lerData(&(novo.dia));

    printf("Digite o local do show: ");
    scanf(" %31[^\n]%*c", novo.local);

    return novo;
}

Ingressos lerIngresso()
{
    Ingressos novo;

    printf("\nDigite o tipo de ingresso: ");
    scanf("%11s%*c", novo.tipo);

    printf("Digite o preço do ingresso: ");
    scanf("%lf%*c", &(novo.preco));

    novo.ptr_prox = NULL;

    return novo;
}

PonteiroShow escolherShow(ListaShows *lista)
{
    int opcao;

    PonteiroShow atual = lista->ptr_primeiro;

    if(atual == NULL)
    {
        printf("\nNão há shows cadastrados, aperte ENTER para escolher novamente...");
        getchar();
        getchar();
        return NULL;
    }
    // Exibe a lista de shows cadastrados
    printf("\nLista de Shows:\n\n");
    printf("\033[0m");
    while (atual != NULL)
    {
        printf("\033[3;4;31m%d. %s - %02d/%02d/%d\033[0m\n",
         atual->codShow, atual->artista, atual->dia.dia, atual->dia.mes, atual->dia.ano);
        atual = atual->ptr_prox;
    }
    printf("\033[3;36m");
    // Solicita a escolha do show ao usuário
    printf("\nEscolha o número do show: ");

    while (scanf("%d", &opcao) != 1) 
    {
        while (getchar() != '\n');
        printf("Entrada inválida. Digite um número válido: ");
    }

    // Percorre a lista até o show escolhido
    atual = lista->ptr_primeiro;
    while (atual != NULL && opcao != atual->codShow)
    {
        atual = atual->ptr_prox;
    }

    if (atual == NULL)
    {
      
        return NULL;
    }
    else
    {
        return atual;
    }
}

PonteiroIngressos escolherIngresso(ListaIngressos *Ingressos, ListaShows *Shows)
{

    PonteiroShow showEscolhido = escolherShow(Shows);

    if(showEscolhido == NULL) return NULL;

    int codigoEscolhido;
    printf("-------------------------------------------------\n");
    printf("\nLista de ingressos disponíveis:\n\n");


    printf("\033[0m");
    printf("\033[3;4;31m");
    imprimirIngressos(Ingressos, showEscolhido->codigoIngresso);
    printf("\033[0m");
    printf("\033[3;36m");
    
    printf("\nSelecione o código do tipo desejado:");

    while (scanf("%d", &codigoEscolhido) != 1) 
    {
      while (getchar() != '\n');
      printf("Entrada inválida. Digite um número válido: ");
    }

    int i,flag=0;
    for(i=0;i<10;i++)
    {
        if (showEscolhido->codigoIngresso[i] == codigoEscolhido )
        { 
            flag = 1;
            break;
        }
    }
    if( flag == 0 )
    {
        printf("\nO código do ingresso escolhido não corresponde a um ingresso válido para o show selecionado.\n");
        printf("\nAperte ENTER para retornar...\n");
        getchar();
        getchar();
        return  NULL;
    }

    //percorrer a lista de ingressos para encontar o ingresso escolhido pelo usuario e o retornar
    PonteiroIngressos atual = Ingressos->ptr_primeiro;


    while (atual != NULL) {
      if(atual->codIngresso == codigoEscolhido) {
        return atual;
      }
      atual = atual->ptr_prox;
    }

      printf("\nIngresso não encontrado, aperte ENTER para voltar...");
      getchar();
      getchar();

    return NULL;
}

