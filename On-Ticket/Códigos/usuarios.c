#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include "usuarios.h"
#include "menus.h"
#include "cadastro.h"

// Função para desabilitar o eco do teclado
void disable_echo() {
    struct termios term;
    tcgetattr(0, &term);
    term.c_lflag &= ~ECHO;
    tcsetattr(0, TCSANOW, &term);
}

// Função para habilitar o eco do teclado novamente
void enable_echo() {
    struct termios term;
    tcgetattr(0, &term);
    term.c_lflag |= ECHO;
    tcsetattr(0, TCSANOW, &term);
}

// inicializacao da lista de usuarios
void iniciaListaUsuarios(ListaUsers *lista)
{
    lista->ptr_primeiro = (TipoUser) malloc(sizeof(Users));
    lista->ptr_ultimo = lista->ptr_primeiro;
    lista->ptr_primeiro->ptr_prox = NULL;
}

//confere se a lista está vazia e retorna 1 em caso positivo, 0 caso negativo
int listaUsuariosVazia(ListaUsers *lista)
{
    return (lista->ptr_ultimo == lista->ptr_primeiro) ? 1 : 0;
}

//busca o numero do CPF e retorna os dados do usuario caso seja encontrado
TipoUser buscaCPF(char cpf[], ListaUsers *lista)
{
    TipoUser aux = lista->ptr_primeiro;
    while (aux != NULL)
    {
        if (strcmp(cpf, aux->usuario.cpf) == 0)
        {
            //printf("CPF encontrado.\n");
            return aux;
        }
        aux = aux->ptr_prox;
    }

    return NULL;
};

//busca o numero do Id e retorna os dados do usuario caso seja encontrado
TipoUser buscaId(int Id, ListaUsers *lista)
{
    TipoUser aux = lista->ptr_primeiro;
    while (aux != NULL)
    {
        if ( Id == aux->usuario.Id)
        {
            printf("CPF encontrado.\n");
            return aux;
        }
        aux = aux->ptr_prox;
    }

    return NULL;
};

//compara se o cpf já está na lista de usuarios
// retorna valor 1 caso o usuario já possua conta e 0 caso contrario
int checaCPFCadastrado(char cpf[], ListaUsers *lista)
{
    TipoUser verifica = NULL;
    if(listaUsuariosVazia( lista )) return 0;

    verifica = buscaCPF(cpf, lista);
    if (verifica != NULL)
    {
        printf("Este Login ja possui cadastro no sitema.\n");
        printf("Entre em contato com o suporte para recuperar sua conta\n");
        return 1;
    }
    return 0;
}

int maiorId(ListaUsers *lista)
{
    TipoUser aux = lista->ptr_primeiro;
    int maior = 0;
    while(aux!=NULL)
    {
        if(aux->usuario.Id > maior) maior = aux->usuario.Id;
        aux = aux->ptr_prox;
    }
    return maior;
}

//cadastra novos usuarios ao sistema
//A função confere se o CPF já está cadastrado no sistema
//retorna 1 caso não seja possivel realizar o cadastro
//retorna 0 caso o cadastro tenha sido realizado com sucesso
int cadastraUsuarios( ListaUsers *lista )
{
    system("clear");
    printf("\n============================================\n");
    printf("\n             TELA DE CADASTRO             \n\n");
    printf("==============================================\n");
    TipoUser novo = (TipoUser) malloc(sizeof(Users));
    if (novo == NULL) {
        printf("Erro de alocação de memória.\n");
        return 1;
    }
    printf("\nDigite o numero do Login:");
    scanf("%11s%*c", novo->usuario.cpf);
    
    if(checaCPFCadastrado(novo->usuario.cpf, lista))
    {
        return 1;
    };

    printf("Digite uma senha:");
    scanf("%11s%*c", novo->usuario.senha);
    printf("Digite o seu nome completo:");
    scanf("%31[^\n]%*c", novo->usuario.nome);
    if(listaUsuariosVazia (lista)) novo->usuario.Id = 1;
    else
    {
        novo->usuario.Id = maiorId(lista) + 1;
    }
    novo->usuario.privilegio = 0;

    int i;
    for(i=0;i<N_RES_USER;i++)
    {
        novo->usuario.meusIngressos[i].codigoIngresso = 0;
        novo->usuario.meusIngressos[i].codigoReserva = 0;
        novo->usuario.meusIngressos[i].Status = 0;
    }
    
    novo->ptr_prox = NULL;
    lista->ptr_ultimo->ptr_prox = novo;
    lista->ptr_ultimo = novo;
    printf("Cadastro realizado com sucesso.\n\n");
    printf("Seja bem-vindo, %s!\n", novo->usuario.nome);
    printf("\nAperte Enter para continuar...");
    getchar();  // Captura o Enter pressionados
   
    return 0;
};


//função para fazer login no sistema
TipoUser fazerLogin(ListaUsers *lista1, ListaUsers *lista2)
{
    system("clear");
    printf("\n============================================\n");
    printf("\n               TELA DE LOGIN            \n\n");
    printf("============================================\n");  
    int tentativa = 0;
    Dados novo;
    printf("\nDigite o numero do Login:");
    scanf("%s", novo.cpf);

    TipoUser usuarioEncontrado = buscaCPF(novo.cpf, lista2);
    if (usuarioEncontrado == NULL)
    {
        usuarioEncontrado = buscaCPF(novo.cpf, lista1);
    }

    while(tentativa<3)
    {
        if( usuarioEncontrado == NULL )
        {
            printf("\nLogin nao encontrado, faça cadastro para prosseguir.\n\n");
            printf("Aperte ENTER para retornar...");
            getchar();
            getchar();
            break;
        }
        if (usuarioEncontrado)
        {
            printf("Digite uma senha:");
            disable_echo(); // Desabilita o eco do teclado
            scanf("%s", novo.senha);
            enable_echo(); // Habilita o eco do teclado novamente

            if (strcmp(novo.senha, usuarioEncontrado->usuario.senha) == 0)
            {
                printf("\n\nLogin realizado com sucesso!\n\n");
                printf("Seja bem-vindo, %s!\n\n", usuarioEncontrado->usuario.nome);
                printf("\nAperte Enter para continuar...");
                getchar();  // Captura o Enter pressionado
                getchar();  // Pausa até o Enter ser pressionado novamente
                return usuarioEncontrado;
            }
            else
            {
                printf("\n\nFalha no Login -> Senha Incorreta.\n");
                printf("\nDigite a senha novamente\n\n");
            }
        }
        tentativa++;
    }
    if(tentativa == 3)
    {
        printf("Errou a senha 3 vezes.\n");
        printf("\nAperte Enter para continuar...");
        getchar();  // Captura o Enter pressionado
        getchar();  // Pausa até o Enter ser pressionado novamente
    }
    return NULL;
}

// função para separar os dados de um usuário por um caracter especial '$'
void salvarDadosUsuarios(ListaUsers *lista, FILE *arquivo)
{
    TipoUser atual = lista->ptr_primeiro->ptr_prox;

    while (atual != NULL)
    {
        fprintf(arquivo, "%s$%s$%s$%d$%d\n",
         atual->usuario.cpf, atual->usuario.senha, atual->usuario.nome,
          atual->usuario.Id, atual->usuario.privilegio);
        atual = atual->ptr_prox;
    }
}


//função para liberar memoria ao fechar programa
void liberarListaUsuarios(ListaUsers *lista)
{
    TipoUser atual = lista->ptr_primeiro->ptr_prox;
    TipoUser proximo;

    while (atual != NULL)
    {
        proximo = atual->ptr_prox;
        free(atual);
        atual = proximo;
    }

    lista->ptr_primeiro = NULL;
    lista->ptr_ultimo = NULL;
}

//função de teste que imprime a lista de usuarios
void Imprime(ListaUsers *lista)
{
    TipoUser Aux;
    Aux = lista->ptr_primeiro->ptr_prox;
    while (Aux != NULL)
    {
        printf("\n%s\n", Aux->usuario.cpf);
        printf("%s\n", Aux->usuario.senha);
        printf("%s\n", Aux->usuario.nome);
        printf("%d\n", Aux->usuario.Id);
        Aux = Aux->ptr_prox;
    }
}

// função para carregar os dados dos usuários a partir do arquivo separados pelo caracter especial '$'
void carregarDadosUsuarios(ListaUsers *lista1, ListaUsers *lista2, FILE *arquivo)
{
    char line[100];

    while (fgets(line, sizeof(line), arquivo) != NULL)
    {
        char cpf[12];
        char senha[12];
        char nome[32];
        int id;
        int privilegio;

        if (sscanf(line, "%11[^$]$%11[^$]$%31[^$]$%d$%d",
         cpf, senha, nome, &id, &privilegio) == 5)
        {
            TipoUser novo = (TipoUser)malloc(sizeof(Users));
            if (novo == NULL)
            {
                printf("Erro de alocação de memória.\n");
                return;
            }

            strcpy(novo->usuario.cpf, cpf);
            strcpy(novo->usuario.senha, senha);
            strcpy(novo->usuario.nome, nome);
            novo->usuario.Id = id;
            novo->usuario.privilegio = privilegio;

            if (novo->usuario.privilegio == 0)
            {
                novo->ptr_prox = NULL;
                lista1->ptr_ultimo->ptr_prox = novo;
                lista1->ptr_ultimo = novo;
            }
            else
            {
                novo->ptr_prox = NULL;
                lista2->ptr_ultimo->ptr_prox = novo;
                lista2->ptr_ultimo = novo;
            }
        }
        else
        {
            printf("Erro ao ler linha do arquivo.\n");
        }
    }
}



void alteraNome( TipoUser *usuario )
{
    char nome[32];
    printf("\nDigite o novo nome do usuario:");
    scanf(" %[^\n]%*c", nome);
    strcpy( (*usuario)->usuario.nome, nome);
    printf("\n\n>>> Nome alterado com sucesso <<<\n\nAperte ENTER para retornar...");
    getchar();
    
};

void alteraSenha( TipoUser *usuario )
{
    char senha[12];
    printf("\nDigite a nova senha:");
    scanf("%s", senha);
    strcpy( (*usuario)->usuario.senha, senha);
    printf("\n\n>>> Senha alterada com sucesso <<<\n\nAperte ENTER para retornar...");
    getchar();
    getchar();
};

int numUser( ListaUsers *lista )
{
    int num = 0;
    TipoUser aux = lista->ptr_primeiro;

    while( aux != NULL )
    {
        num++;
        aux = aux->ptr_prox;
    }
    return num;
}

void inicializar_vetor( int **vetor, ListaUsers *lista ) 
{
    int n = numUser( lista );
    *vetor = (int *)malloc(n * sizeof(int));
    if (*vetor == NULL)
    {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        (*vetor)[i] = 0;
    }
}

void descarregaVetor( int id[], ListaUsers *lista)
{
    int i;
    int MAX_USERS = numUser(lista);
    for(i=0;i<MAX_USERS;i++) id[i] = 0;
    TipoUser usuario = lista->ptr_primeiro;
    if(usuario == NULL)
    {
        printf("Nao ha usuarios cadastrados para ordenar.\n");
        return;
    }

    i = 0;
    while( usuario != NULL)
    {
        id[i] = usuario->usuario.Id;
        i++;
        usuario = usuario->ptr_prox;
    }
};

void copiaVetor(int origem[], int destino[], ListaUsers *lista) 
{
    int i;
    int MAX_USERS = numUser(lista);
    for (i = 0; i < MAX_USERS; i++) 
    {
        destino[i] = origem[i];
    }
}


void printVetorOrdenado(int vetor[], ListaUsers *lista)
{
    int i, numReservas;
    TipoUser aux;
    printf("\n");
    int n = numUser(lista);
    for (i = 0; i < n; i++)
    {
        aux = lista->ptr_primeiro;
        numReservas = 0;

        if( vetor[i] == 0) continue;

        while(aux!=NULL)
        {
            if(aux->usuario.Id == vetor[i])
            {
                while(aux->usuario.meusIngressos[numReservas].codigoIngresso != 0)
                {
                    numReservas++;
                }
                printf("Id: %d, Nome: %s, Quantidade de Reservas: %d\n",
                 aux->usuario.Id, aux->usuario.nome, numReservas);
            }
            aux = aux->ptr_prox;
        }

    }
}

void printNumEscolhido(int vetor[], int n, ListaUsers *lista)
{
    int i, numReservas;
    TipoUser aux;
    printf("\n");

    aux = lista->ptr_primeiro;
    numReservas = 0;

    if( n == -1 )
    {
        printf("Usuario nao encontrado!");
        return;
    }

    while(aux!=NULL)
    {
        if(aux->usuario.Id == vetor[n])
        {
            while(aux->usuario.meusIngressos[numReservas].codigoIngresso != 0)
            {
                numReservas++;
            }
            printf("Id: %d, Nome: %s, Quantidade de Reservas: %d\n",
             aux->usuario.Id, aux->usuario.nome, numReservas);
            break;
        }
        aux = aux->ptr_prox;
    }
}