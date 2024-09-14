#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Tarvore.h"
#include "Menus.h"



NoArvore* criaNo( int valor, Monstro mons )
{
    NoArvore *novoNo = (NoArvore *)malloc(sizeof(NoArvore));
    novoNo->dado = valor;
    novoNo->Inimigo = mons;
    novoNo->pai = novoNo->esquerda = novoNo->meio = novoNo->direita = NULL;
    return novoNo;
}

NoArvore *preencheArvore(Monstro mons)
{
    NoArvore *raiz;

    raiz = criaNo( 1, mons );

    for (int i = 2; i <= ROOMS; i++)
    {
        NoArvore *atual = raiz;
        while (1)
        {
            int ramoAleatorio = rand() % 3;  // 0: esquerda, 1: meio, 2: direita

            if (ramoAleatorio == 0)
            {
                if (atual->esquerda == NULL)
                {
                    atual->esquerda = criaNo( i, mons );
                    atual->esquerda->pai = atual;
                    break;
                } else {
                    atual = atual->esquerda;
                }
            } else if (ramoAleatorio == 1)
            {
                if (atual->meio == NULL)
                {
                    atual->meio = criaNo( i, mons );
                    atual->meio->pai = atual;
                    break;
                } else
                {
                    atual = atual->meio;
                }
            } else
            {
                if (atual->direita == NULL)
                {
                    atual->direita = criaNo( i, mons );
                    atual->direita->pai = atual;
                    break;
                } else
                {
                    atual = atual->direita;
                }
            }
        }
    }

    return raiz;
}


void distribuiMonstros(NoArvore* raiz, int altura, Monstro rato, Monstro esqueleto,
 Monstro bird )
{
    if (raiz == NULL) {
        return;
    }

    if (altura == 1) {
        // Se a altura for 1, coloque um rato
        raiz->Inimigo = rato;
    } else if (altura == 2) {
        // Se a altura for 2, 75% de chance de rato, 25% de chance de esqueleto
        int chance = rand() % 100;
        if (chance < 75) {
            raiz->Inimigo = rato;
        } else {
            raiz->Inimigo = esqueleto;
        }
    } else if (altura == 3) {
        // Se a altura for 3, 25% de chance de rato, 75% de chance de esqueleto
        int chance = rand() % 100;
        if (chance < 25) {
            raiz->Inimigo = rato;
        } else {
            raiz->Inimigo = esqueleto;
        }
    } else if (altura == 4) {
        // Se a altura for 4, 25% de chance de bird, 75% de chance de esqueleto
        int chance = rand() % 100;
        if (chance < 25) {
            raiz->Inimigo = bird;
        } else {
            raiz->Inimigo = esqueleto;
        }
    } else if( altura > 4 ) {
        // Para alturas maiores que 4, sempre coloque um bird
        raiz->Inimigo = bird;
    }

    // Recursivamente distribui monstros nos filhos
    distribuiMonstros(raiz->esquerda, altura + 1, rato, esqueleto, bird);
    distribuiMonstros(raiz->meio, altura + 1, rato, esqueleto, bird);
    distribuiMonstros(raiz->direita, altura + 1, rato,esqueleto, bird);
}

void distribuiBoss(NoArvore* raiz, Monstro minotauro)
{
    if (raiz == NULL) return;

    if (raiz->esquerda == NULL && raiz->meio == NULL && raiz->direita == NULL)
    {
        raiz->Inimigo = minotauro;
        return;
    }

    int ramoAleatorio = rand() % 3;

    if (ramoAleatorio == 0 && raiz->esquerda != NULL) {
        distribuiBoss(raiz->esquerda, minotauro);
    } else if (ramoAleatorio == 1 && raiz->meio != NULL) {
        distribuiBoss(raiz->meio, minotauro);
    } else if (ramoAleatorio == 2 && raiz->direita != NULL) {
        distribuiBoss(raiz->direita, minotauro);
    } else {
        distribuiBoss(raiz, minotauro);
    }
}


NoArvore* andaArvore(NoArvore *raiz, TipoHeroi *player, Mapa *mapa)
{

    system(CLEAR_COMMAND);
    printf("\n============================================\n");
    printf("\n               UFG DUNGEON                  \n");
    printf("\n============================================\n\n");
    printf("Numero do andar: %.2d\n", raiz->dado);
    printf("---------------------------------------------\n");
    printaMapa( mapa );
    printf("---------------------------------------------\n");
    printf("\nEscolha uma porta:\n\n");

    if( raiz->meio!=NULL ) printf("1- Rota da Frente        -> andar %.2d\n", raiz->meio->dado);
    if( raiz->esquerda!=NULL ) printf("2- Rota da Esquerda      -> andar %.2d\n", raiz->esquerda->dado);
    if( raiz->direita!=NULL ) printf("3- Rota da Direita      -> andar %.2d\n", raiz->direita->dado);
    if( raiz->dado != 1) printf("4- Retornar              -> andar %.2d\n", raiz->pai->dado);
    printf("\nEscolha 0 para desistir do jogo e voltar a tela inicial\n");
    
    
    int n;
    while (scanf("%d", &n) != 1) 
    {
      while (getchar() != '\n');
      printf("Entrada inválida.\n\n Digite um número válido: ");
    }

    switch ( n )
    {
        case 0 :
            player->Hp = -1;
            return raiz;
            break;
        case 1 :
            if( raiz->meio == NULL )
            {
                printf("Nao existe porta nesta direcao!\n");
                return raiz;
            }
            return raiz->meio;
            break;

        case 2 :
            if( raiz->esquerda == NULL )
            {
                printf("Nao existe porta nesta direcao!\n");
                return raiz;
            }
            return raiz->esquerda;
            break;
    
        case 3 :
            if( raiz->direita == NULL )
            {
                printf("Nao existe porta nesta direcao!\n");
                return raiz;
            }      
            return raiz->direita;
            break;

        case 4 :
            if( raiz->pai == NULL ) return raiz;
            return raiz->pai;
            break;
      
        default :
            printf("\nNúmero inválido.\n\nAperte ENTER para digitar novamente...");
            getchar();
            getchar();
            return raiz;
    }

    return raiz;


    return raiz;
};

void imprimeArvore(NoArvore *raiz)
{
    if (raiz != NULL)
    {
        imprimeArvore(raiz->esquerda);
        printf("Dado: %d, Tipo de Inimigo: %d, HP: %d, Ataque: %d, Defesa: %d\n",
               raiz->dado, raiz->Inimigo.tipo, raiz->Inimigo.Hp, raiz->Inimigo.Atk, raiz->Inimigo.Def);
        imprimeArvore(raiz->meio);
        imprimeArvore(raiz->direita);
    }
};



// Função para criar um novo monstro
Monstro criarMonstro( int Hp, int Atk, int Def, TipoMonstro tipo) {
    Monstro novoMonstro;
    novoMonstro.Hp = Hp;
    novoMonstro.Atk = Atk;
    novoMonstro.Def = Def;
    novoMonstro.tipo = tipo;
    return novoMonstro;
}

void criarHeroi( TipoHeroi *player) {

    int atk = rand() % 6 + 5;
    int def = rand() % 6 + 5;
   

    player->Atk = atk;
    player->Def = def;
    player->Hp = VIDA_HEROI;
    


    printf("\nEscolha um nome para o seu Heroi:");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    // fgets(player->Name, sizeof(player->Name), stdin);
    scanf("%[^\n]", player->Name);

    printf("\nDigite o nível do guerreiro (1-10): ");
    scanf("%d", &player->nivel);


    printf("\nEscolha a classe do guerreiro:\n");
    printf("1. Mago\n");
    printf("2. Guerreiro\n");
    printf("3. Arqueiro\n");
    printf("Digite o número correspondente: ");
    int escolhaClasse;
    scanf("%d", &escolhaClasse);
    switch (escolhaClasse) {
        case 1:
            strcpy(player->classe, "Mago");
            break;
        case 2:
            strcpy(player->classe, "Guerreiro");
            break;
        case 3:
            strcpy(player->classe, "Arqueiro");
            break;
        default:
            printf("Opção inválida. Guerreiro selecionado por padrão.\n");
            strcpy(player->classe, "Guerreiro");
    }

    if (strcmp(player->classe, "Mago") == 0) {
        printf("\nEscolha o tipo de magia do mago:\n");
        printf("1. Fogo\n");
        printf("2. Gelo\n");
        printf("3. Raio\n");
        printf("Digite o número correspondente: ");
        int escolhaMagia;
        scanf("%d", &escolhaMagia);
        switch (escolhaMagia) {
            case 1:
                strcpy(player->tipoArma, "Varinha de Fogo");
                break;
            case 2:
                strcpy(player->tipoArma, "Cajado de Gelo");
                break;
            case 3:
                strcpy(player->tipoArma, "Orbe de Raio");
                break;
            default:
                printf("Opção inválida. Varinha de Fogo selecionada por padrão.\n");
                strcpy(player->tipoArma, "Varinha de Fogo");
        }
    } else if (strcmp(player->classe, "Guerreiro") == 0) {
        printf("\nEscolha o tipo de arma do guerreiro:\n");
        printf("1. Espada\n");
        printf("2. Machado\n");
        printf("3. Lança\n");
        printf("Digite o número correspondente: ");
        int escolhaArma;
        scanf("%d", &escolhaArma);
        switch (escolhaArma) {
            case 1:
                strcpy(player->tipoArma, "Espada");
                break;
            case 2:
                strcpy(player->tipoArma, "Machado");
                break;
            case 3:
                strcpy(player->tipoArma, "Lança");
                break;
            default:
                printf("Opção inválida. Espada selecionada por padrão.\n");
                strcpy(player->tipoArma, "Espada");
        }
    } else if (strcmp(player->classe, "Arqueiro") == 0) {
        printf("\nEscolha o tipo de arco do arqueiro:\n");
        printf("1. Curto\n");
        printf("2. Longo\n");
        printf("Digite o número correspondente: ");
        int escolhaArco;
        scanf("%d", &escolhaArco);
        switch (escolhaArco) {
            case 1:
                strcpy(player->tipoArma, "Arco Curto");
                break;
            case 2:
                strcpy(player->tipoArma, "Arco Longo");
                break;
            default:
                printf("Opção inválida. Arco Curto selecionado por padrão.\n");
                strcpy(player->tipoArma, "Arco Curto");
        }
    }

    printf("\nDigite a vida do guerreiro (50-200): ");
    scanf("%f", &player->vida);

    printf("\nDigite o valor de ataque do guerreiro (5.0-20.0): ");
    scanf("%f", &player->ataque);

    printf("\nDigite o valor de defesa do guerreiro (1.0-10.0): ");
    scanf("%f", &player->defesa);

    printf("\nEscolha o tipo de armadura do guerreiro:\n");
    printf("1. Leve\n");
    printf("2. Média\n");
    printf("3. Pesada\n");
    printf("Digite o número correspondente: ");
    int escolhaArmadura;
    scanf("%d", &escolhaArmadura);
    switch (escolhaArmadura) {
        case 1:
            strcpy(player->armadura, "Leve");
            break;
        case 2:
            strcpy(player->armadura, "Média");
            break;
        case 3:
            strcpy(player->armadura, "Pesada");
            break;
        default:
            printf("Opção inválida. Armadura leve selecionada por padrão.\n");
            strcpy(player->armadura, "Leve");
    }

    printf("\nDigite os pontos de experiência do guerreiro (0-100): ");
    scanf("%d", &player->pontosExperiencia);


    printf("\n\nPor fim suas características não nos interessa\n");
    printf("pressione ENTER se estiver preparado...\n\n");
    getchar();
    getchar();



}

int Combate(TipoHeroi *heroi, NoArvore *monstro) {
    int i;
    int result = 1;

    
    int ataqueHeroi = ((heroi->Atk + monstro->Inimigo.Def) / 2) * 3;
    int ataqueMonstro = ((monstro->Inimigo.Atk + heroi->Def) / 2) * 1.5;
    int dano = ataqueHeroi - ataqueMonstro;

    monstro->Inimigo.Hp = 0;

    heroi->Hp = heroi->Hp - dano;

   
   
    
    if (heroi->Hp <= 0) {
        system(CLEAR_COMMAND);
        printf("\n========================================================\n");
        printf("\n               QUE PENA, %s !                  \n",heroi->Name);
        printf("Você não foi pário para os desafios do labirinto,\n    espero te ver em breve \n");
        printf("\n========================================================\n\n");
        
        printf("Aperte ENTER para voltar para tela inicial\n");
        getchar();
        getchar();
        return result;

           
    } else {
        printf("Guerreiro venceu a batalha, mas teve um dano de %d hp\n", dano);
        printf("Pressione ENTER para prosseguir\n");
        if(monstro->Inimigo.tipo == MINOTAURO) {
            system(CLEAR_COMMAND);
            printf("\n===================================================\n");
            printf("\n               PARABÉNS, %s !                  \n",heroi->Name);
            printf("    você derrotou o minotauro e encontrou a saída\n");
            printf("\n====================================================\n\n");

            printf("Aperte ENTER para voltar para tela inicial\n");
            getchar();
            getchar();

            return result;
        }
        result = 0;
           
    }
   
    getchar();
    getchar();
    return result;
    
}
 
void liberaArvore(NoArvore *raiz)
{
    if (raiz == NULL) {
        free(raiz);
        return;
    }
   
    liberaArvore(raiz->esquerda);
    liberaArvore(raiz->meio);
    liberaArvore(raiz->direita); 
}


void iniciaMapa( Mapa *mapa, NoArvore *raiz )
{
    int i;

    for( i=0; i<ROOMS; i++)
    {
        mapa[i].atual = mapa[i].direita = mapa[i].esquerda = mapa[i].retorna = mapa[0].frente = 0;
    }

    mapa[0].atual = 1;

    if( raiz->direita != NULL ) mapa[0].direita = raiz->direita->dado;
    else mapa[0].direita = -1;
    
    if( raiz->esquerda != NULL ) mapa[0].esquerda = raiz->esquerda->dado;
    else mapa[0].esquerda = -1;
    
    if( raiz->meio != NULL ) mapa[0].frente = raiz->meio->dado;
    else mapa[0].frente = -1;

    mapa[0].retorna = -1;

};

void atualizaMapa( Mapa *mapa, NoArvore *raiz)
{
    int i = 0;
    while( mapa[i].atual != 0 )
    {
        if( mapa[i].atual == raiz->dado ) return;
        i++;
    }


    mapa[i].atual = raiz->dado;
    
    if( raiz->direita != NULL ) mapa[i].direita = raiz->direita->dado;
    else mapa[i].direita = -1;
    
    if( raiz->esquerda != NULL ) mapa[i].esquerda = raiz->esquerda->dado;
    else mapa[i].esquerda = -1;
    
    if( raiz->meio != NULL ) mapa[i].frente = raiz->meio->dado;
    else mapa[i].frente = -1;
    
    mapa[i].retorna = raiz->pai->dado;

};

void printaMapa( Mapa *mapa )
{
    int i = 0;

    printf("Mapa dos andares visitados:\n"); 

    while( mapa[i].atual != 0 )
    {
        printf("Andar: %.2d ->  ", mapa[i].atual);
        if( mapa[i].esquerda != -1 ) printf("Esq: %.2d  ", mapa[i].esquerda);
            else printf("Esq: X  ");
        if( mapa[i].frente != -1 ) printf("Fre: %.2d  ", mapa[i].frente);
            else printf("Fre: X  ");
        if( mapa[i].direita != -1 ) printf("Dir: %.2d  ", mapa[i].direita);
            else printf("Dir: X  ");
        if( mapa[i].retorna != -1 ) printf("Ret: %.2d  \n", mapa[i].retorna);
            else printf("Ret: X  \n");
        i++;
    }
};
