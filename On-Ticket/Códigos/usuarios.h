#ifndef USUARIOS_H
#define USUARIOS_H
#include "cadastro.h"
#include <stdio.h>
#include <stdlib.h>

#define N_RES_USER 10


//Status 0 = não cadastrado, -1 = aguardando, 1 = aceito
typedef struct meusIngressos
{
    int codigoIngresso;
    int Status;
    int codigoReserva;
}meusIngressos;

//dados para fazer login
//receberá dados de CPF uma senha para acesso ao sistema e o nome do usuario
//Id será uma lista numerica ordenada para ser utilizada no sistema
//usuarios recebem privilegio 0, enquanto funcionarios 1
typedef struct Dados
{
    char cpf[12];
    char senha[12];
    char nome[32];
    int Id;
    int privilegio;

    meusIngressos meusIngressos[N_RES_USER];

}Dados;

//Cria as celulas para o tipo lista
typedef struct Users
{
    Dados usuario;
    struct Users *ptr_prox;
}Users;

//ponteiro para o tipo lista
typedef struct Users *TipoUser;

//estrutura da lista que receberá os dados dos usuários;
typedef struct
{
    TipoUser ptr_primeiro, ptr_ultimo;
} ListaUsers;


// inicializacao da lista de usuarios
void iniciaListaUsuarios(ListaUsers *lista);

//confere se a lista está vazia e retorna 1 em caso positivo, 0 caso negativo
int listaUsuariosVazia(ListaUsers *lista);

//busca o numero do CPF e retorna os dados do usuario caso seja encontrado
TipoUser buscaCPF(char cpf[], ListaUsers *lista);

//busca o numero do Id e retorna os dados do usuario caso seja encontrado
TipoUser buscaId(int Id, ListaUsers *lista);

//compara se o cpf já está na lista de usuarios
// retorna valor 1 caso o usuario já possua conta e 0 caso contrario
int checaCPFCadastrado(char cpf[], ListaUsers *lista);

//cadastra novos usuarios ao sistema
//A função confere se o CPF já está cadastrado no sistema
//retorna 1 caso não seja possivel realizar o cadastro
//retorna 0 caso o cadastro tenha sido realizado com sucesso
int cadastraUsuarios( ListaUsers *lista );;

//função para fazer login no sistema
TipoUser fazerLogin(ListaUsers *lista1, ListaUsers *lista2);

//função para salvar os dados dos usuarios no banco de dados
void salvarDadosUsuarios(ListaUsers *lista, FILE *arquivo);

//função para limpar memoria e fechar o programa
void liberarListaUsuarios(ListaUsers *lista);

//função de teste que imprime a lista de usuarios
void Imprime(ListaUsers *lista);

// função para passar os dados do arquivo para a lista
void carregarDadosUsuarios(ListaUsers *lista1, ListaUsers *lista2, FILE *arquivo);

void alteraNome( TipoUser *usuario );

void alteraSenha( TipoUser *usuario );

int numUser( ListaUsers *lista );

void inicializar_vetor( int **vetor, ListaUsers *lista );

void descarregaVetor( int id[], ListaUsers *lista);

void copiaVetor(int origem[], int destino[], ListaUsers *lista);

void printVetorOrdenado(int vetor[], ListaUsers *lista);

void printNumEscolhido(int vetor[], int n, ListaUsers *lista);

#endif