#include "reserva.h"
#include "cadastro.h"
#include "usuarios.h"
#include <stdlib.h>
#include <stdio.h>

void inicializaReserva(ReservasUser *reserva)
{
    int i;
    for (i = 0; i < MAX_NUM_RESERVA; i++)
    {
        reserva->reservas[i].id = 0;
        reserva->reservas[i].codigoreserva = 0;

    }
    reserva->comeco = -1;
    reserva->fim = reserva->comeco;
    reserva->codIngresso = 0;
    reserva->totalIngressos = 0;
}



void StartReserva(ReservasUser reserva[], PonteiroIngressos ingresso)
{
    if (ingresso == NULL)
        return;

    int i, j;
    for (i = 0; i < TAM_LISTA; i++)
    {
        if (reserva[i].codIngresso == 0)
        {
            reserva[i].codIngresso = ingresso->codIngresso;
            for ( j = 0; j < MAX_NUM_RESERVA; j++)
            {
                reserva[i].reservas[j].id = 0;
            }
            break;
        }
    }

    
}


void obterReserva(ReservasUser reserva[], TipoUser usuario, ListaIngressos *ingressos, ListaShows *shows)
{
    system("clear");
    printf("\n============================================\n");
    printf("\n            OBTENÇÃO DE RESERVAS            \n");
    printf("\n============================================\n");
    if (shows->ptr_primeiro == NULL)
    {
        printf("\nNão há shows cadastrados.\n");
        printf("\nAperte ENTER para retornar...\n");
        getchar();
        getchar();
        return;
    }
    int codigoEscolhido;
    PonteiroIngressos ingressoEscolhido = escolherIngresso(ingressos, shows);
    PonteiroShow aux = shows->ptr_primeiro;

    if (ingressoEscolhido == NULL || ingressoEscolhido->show->codShow != shows->ptr_primeiro->codShow) 
    {
        while( aux != NULL )
        {
            if(ingressoEscolhido->show->codShow!=aux->codShow )
                break;

            aux = aux->ptr_prox;
        }
        if( aux == NULL )
        {
            printf("\nO código do ingresso escolhido não corresponde a um ingresso válido para o show selecionado.\n");
            printf("\nAperte ENTER para retornar...\n");
            getchar();
            getchar();
            return;
        }
    }

    if (( reserva[ingressoEscolhido->codIngresso].fim + 1 ) % MAX_NUM_RESERVA 
        == reserva[ingressoEscolhido->codIngresso].comeco)
    {
        printf("\n>> Nao e possivel fazer reserva! <<\n\nAperte ENTER para retornar...");
        getchar();
        getchar();
        return; // Inserção falhou
    }

    if( reserva[ingressoEscolhido->codIngresso].comeco == -1 )
    {
        reserva[ingressoEscolhido->codIngresso].comeco = 0;
    }

    int i;
    int codI = ingressoEscolhido->codIngresso;
    int end = reserva[ingressoEscolhido->codIngresso].fim;
    int codRes = reserva[codI].totalIngressos + 1;

    reserva[codI].fim = (end + 1) % MAX_NUM_RESERVA;
    
    end = reserva[ingressoEscolhido->codIngresso].fim;
    
    reserva[codI].reservas[end].id = usuario->usuario.Id;
    reserva[codI].reservas[end].codigoreserva =  codRes;

    for (i = 0; i < N_RES_USER; i++)
    {
        if (usuario->usuario.meusIngressos[i].codigoIngresso == 0)
        {
            usuario->usuario.meusIngressos[i].codigoIngresso = ingressoEscolhido->codIngresso;
            usuario->usuario.meusIngressos[i].codigoReserva = reserva[codI].reservas[end].codigoreserva;
            usuario->usuario.meusIngressos[i].Status = -1;
            break;
        }
        if ( i == N_RES_USER - 1)
        {
            printf("\nAlcançou o limite de reservas!\n");
        }
    }

    reserva[codI].totalIngressos++;

    printf("\n>> Reserva obtida com sucesso <<\n\nAperte ENTER para retornar...");
    getchar();
    getchar();
}



void imprimirReservas(ReservasUser reservas[], ListaIngressos *ingressos , TipoUser usuario)
{
    system("clear");
    printf("\n============================================\n");
    printf("\n              RESERVAS OBTIDAS              \n");
    printf("\n============================================\n");
    int i = 0;
    int k = 1;

    if (usuario->usuario.meusIngressos[0].codigoIngresso == 0)
    {
        printf("\nVocê ainda não realizou nenhuma reserva :(\n");
        printf("\nAperte ENTER para retornar...\n");
        getchar();
        getchar();
        return;
    }

    PonteiroIngressos aux =  ingressos->ptr_primeiro;

    for(i=0;i<N_RES_USER;i++)
    {
        aux =  ingressos->ptr_primeiro;
        int codRes = usuario->usuario.meusIngressos[i].codigoReserva;
        int codIngresso = usuario->usuario.meusIngressos[i].codigoIngresso;

        if( codRes == 0 ) break;


        while( aux != NULL && aux->codIngresso != codIngresso )
        {
            aux = aux->ptr_prox;
        }

        if ( aux !=NULL )
        {
            printf("\nReserva %d\n",k);
            printf("Artista: %s\n", aux->show->artista);
            printf("Local: %s\n", aux->show->local);
            printf("Tipo do Ingresso: %s\n", aux->tipo);
            printf("Preço do ingresso: R$ %.2f\n", aux->preco);
            printf("Data: %02d/%02d/%d\n",
                   aux->show->dia.dia,
                   aux->show->dia.mes,
                   aux->show->dia.ano);
            printf("Codigo da Reserva: %d\n", usuario->usuario.meusIngressos[i].codigoReserva);
            if( usuario->usuario.meusIngressos[i].Status == -1) printf("Aguardando aprovacao\n");
            else if( usuario->usuario.meusIngressos[i].Status == 1) printf("Ingresso aprovado\n");
            printf("------------------------------------------------------\n");
            k++;
        }
        
    }

    printf("\nPressione ENTER para voltar...\n");
    getchar();
    getchar();
}



void imprimirTodasReservas(ReservasUser reservas[], ListaIngressos *ingressos, ListaShows *Shows, ListaUsers *lista)
{
    system("clear");
    printf("\n============================================\n");
    printf("\n             LISTA DE RESERVAS              \n");
    printf("\n============================================\n");
    int i;

    PonteiroIngressos ingresso = escolherIngresso(ingressos, Shows);
    if(ingresso == NULL) return;
    
    for(i=0;i<TAM_LISTA;i++)
    {
        if( ingresso->codIngresso == reservas[i].codIngresso ) break;
    }
  
    int codIngresso = reservas[i].codIngresso;

    printf("Artista: %s\n", ingresso->show->artista);
    printf("Local: %s\n", ingresso->show->local);
    printf("Tipo do Ingresso: %s\n", ingresso->tipo);
    printf("Preço do ingresso: R$ %.2f\n", ingresso->preco);
    printf("Data: %02d/%02d/%d\n",
       ingresso->show->dia.dia,
       ingresso->show->dia.mes,
       ingresso->show->dia.ano);
    printf("------------------------------------------------------\n");

    TipoUser aux;

    printf("\n");

    int start = reservas[ingresso->codIngresso].comeco;
    int end = reservas[ingresso->codIngresso].fim;

    int index = start;

    for (int i = start; ; i++) 
    {
        int index = i % MAX_NUM_RESERVA;
        if (index > end) break;
    
        aux = lista->ptr_primeiro;
        while (aux != NULL)
        {
            if (reservas[codIngresso].reservas[index].id == aux->usuario.Id) 
            {
                printf("Id: %d, Nome: %s\n", aux->usuario.Id, aux->usuario.nome);
                break;
            }

            aux = aux->ptr_prox;
        }

        if (index == end) break;            
    }

    printf("\nPressione enter para voltar...\n");
    getchar();
    getchar();
    return;
}

void cancelaReserva(ReservasUser reservas[], TipoUser usuario, ListaIngressos *ingressos, ListaShows *shows)
{
    system("clear");
    printf("\n============================================\n");
    printf("\n          Cancelamento de Reservas          \n");
    printf("\n============================================\n");
    if (usuario->usuario.meusIngressos[0].codigoIngresso == 0)
    {
        printf("\nVocê não possui ingressos cadastrados.\n");
        printf("\nAperte ENTER para retornar...\n");
        getchar();
        getchar();
        return;
    }
    
    int opcao, k = 1;
    PonteiroIngressos aux = ingressos->ptr_primeiro;

    for (int i = 0; i < N_RES_USER; i++)
    {
        aux = ingressos->ptr_primeiro;
        int codIngresso = usuario->usuario.meusIngressos[i].codigoIngresso;
        int codReserva = usuario->usuario.meusIngressos[i].codigoReserva;

        if (codIngresso == 0 || codReserva == 0)
            break;

        while (aux != NULL && aux->codIngresso != codIngresso)
        {
            aux = aux->ptr_prox;
        }

        if (aux != NULL)
        {
            printf("\nReserva %d\n", k);
            printf("Artista: %s\n", aux->show->artista);
            printf("Local: %s\n", aux->show->local);
            printf("Tipo do Ingresso: %s\n", aux->tipo);
            printf("Preço do ingresso: R$ %.2f\n", aux->preco);
            printf("Data: %02d/%02d/%d\n",
                   aux->show->dia.dia,
                   aux->show->dia.mes,
                   aux->show->dia.ano);
            if (usuario->usuario.meusIngressos[i].Status == -1)
                printf("Aguardando aprovação\n");
            else if (usuario->usuario.meusIngressos[i].Status == 1)
                printf("Ingresso aprovado\n");
            k++;
        }
    }
    printf("Digite %d para cancelar a operação\n", k);

    while (scanf("%d", &opcao) != 1 || opcao < 1 || opcao > k)
    {
        while (getchar() != '\n');
        printf("Entrada inválida. Digite um número válido: ");
    }

    if( usuario->usuario.meusIngressos[opcao-1].Status == 1)
    {
        printf("A reserva selecionada já foi aceita pelo sistema.\n");
        printf("Para cancela-la entre em contato com o suporte.\n");
        printf("\nPressione ENTER para voltar...\n");
        getchar();
        getchar();
        return;
    }

    if (opcao == k)
        return;
    
    // Obter o índice correto da reserva escolhida
    int indexReserva = opcao - 1;
    int codIngresso = usuario->usuario.meusIngressos[indexReserva].codigoIngresso;
    int codReserva = usuario->usuario.meusIngressos[indexReserva].codigoReserva;

    int start = reservas[codIngresso].comeco;
    int end = reservas[codIngresso].fim;

    for (int i = start; ; i++)
    {
        int index = i % MAX_NUM_RESERVA;
        if (index > end)
            break;

        if (reservas[codIngresso].reservas[index].codigoreserva == codReserva)
        {
            // Remover a reserva e ajustar os índices
            for (int j = index; j < end; j++)
            {
                int next = (j + 1) % MAX_NUM_RESERVA;
                reservas[codIngresso].reservas[j] = reservas[codIngresso].reservas[next];
            }

            // Atualizar novo fim da lista
            end = (end - 1 + MAX_NUM_RESERVA) % MAX_NUM_RESERVA;

            // Atualizar começo da lista se necessário
            if (index == start)
            {
                start = (start + 1) % MAX_NUM_RESERVA;
                reservas[codIngresso].comeco = start;
            }

            // Atualizar o fim da lista
            reservas[codIngresso].fim = end;

            // Ajustar os dados do usuário
            usuario->usuario.meusIngressos[indexReserva].codigoIngresso = 0;
            usuario->usuario.meusIngressos[indexReserva].codigoReserva = 0;
            usuario->usuario.meusIngressos[indexReserva].Status = 0;
        }

        if (index == end)
            break;
    }

    for (int i = opcao - 1; i < N_RES_USER - 1; i++)
    {
        usuario->usuario.meusIngressos[i] = usuario->usuario.meusIngressos[i + 1];
    }
    // Atualizar último elemento após a remoção
    usuario->usuario.meusIngressos[N_RES_USER - 1].codigoIngresso = 0;
    usuario->usuario.meusIngressos[N_RES_USER - 1].codigoReserva = 0;
    usuario->usuario.meusIngressos[N_RES_USER - 1].Status = 0;


    printf("Reserva cancelada com sucesso.\n");
    printf("\nPressione ENTER para voltar...\n");
    getchar();
    getchar();
    return;
}


void distribuirReservas(ReservasUser reservas[], ListaIngressos *ingressos, ListaShows *Shows, ListaUsers *lista)
{
    system("clear");
    printf("\n============================================\n");
    printf("\n           DISPONIBILIZA RESERVAS           \n");
    printf("\n============================================\n");
    int i, j, k;

    PonteiroIngressos ingresso = escolherIngresso(ingressos, Shows);
    if(ingresso == NULL) return;
    
    for(i=0;i<TAM_LISTA;i++)
    {
        if( ingresso->codIngresso == reservas[i].codIngresso ) break;
    }
  
    int codIngresso = reservas[i].codIngresso;

    printf("Artista: %s\n", ingresso->show->artista);
    printf("Local: %s\n", ingresso->show->local);
    printf("Tipo do Ingresso: %s\n", ingresso->tipo);
    printf("Preço do ingresso: R$ %.2f\n", ingresso->preco);
    printf("Data: %02d/%02d/%d\n",
       ingresso->show->dia.dia,
       ingresso->show->dia.mes,
       ingresso->show->dia.ano);
    printf("------------------------------------------------------\n");

    int qte;
    printf("Quantos ingressos deseja disponibilizar? Max = %d\n", MAX_NUM_RESERVA);
    while (scanf("%d", &qte) != 1 || qte < 0 || qte > MAX_NUM_RESERVA) {
        while (getchar() != '\n'); // Limpa o buffer do teclado
        printf("Entrada inválida. Digite um número válido: ");
    }

    TipoUser aux = lista->ptr_primeiro;

    printf("\n");

    int start; 
    int end;
    start = reservas[codIngresso].comeco;
    end = reservas[codIngresso].fim;

    i = 0;
    j = start;
    while( i < qte )
    {
  
        int index = j % MAX_NUM_RESERVA;
        if (index > end) break;
        aux = lista->ptr_primeiro;

        while (aux != NULL)
        {
            for( k = 0; k < N_RES_USER; k++ )
            {
                if( aux->usuario.meusIngressos[k].codigoReserva == reservas[codIngresso].reservas[index].codigoreserva)
                {
                    aux->usuario.meusIngressos[k].Status = 1;
                    reservas[codIngresso].comeco++;
                    i++;
                    break;
                }
            };

            aux = aux->ptr_prox;
        }
        j++;
        if (index == end) break;        
    }
    

    printf("\nPressione enter para voltar...\n");
    getchar();
    getchar();
    return;
}