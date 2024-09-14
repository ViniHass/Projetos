#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tarvore.h"
#include "Menus.h"



void exibirHistoria() {
    system(CLEAR_COMMAND);
    printf("\n========================================================\n");
    printf("\n               Bem vindo ao Labirinto da Decisão                \n");
    printf("\n=========================================================\n\n");
    printf("Em uma terra distante, envolta por sombras e mistérios, ergue-se o lendário Labirinto da Decisao.\n");
    printf("Contam as lendas que, em seu cerne, repousa o Minotauro, uma criatura de mitos que guarda tesouros inimagináveis.\n\n");

    printf("Ao cruzar os portoes sombrios do labirinto, depara-se com uma bifurcacao.\n");
    printf("Diante de voce, tres caminhos se estendem em direcoes desconhecidas.\n");
    printf("Cada escolha que fizer moldara seu destino.\n\n");

    printf("Seu objetivo é alcançar as profundezas do labirinto, onde o lendário Minotauro o aguarda.\n");
    printf("Será que conseguirá fazer escolhas sábias, superar os obstaculos e enfrentar o terrivel guardião para reivindicar as riquezas que la aguardam?\n\n");

    printf("Pressione ENTER para começar o desafio...");
    getchar();
    
}



void printMenuInical() {
  system(CLEAR_COMMAND);
  printf("\n============================================\n");
  printf("\n               UFG DUNGEON                  \n");
  printf("\n============================================\n\n");
  printf("\nSelecione uma opção:\n\n");
  printf("1- Start Game\n");
  printf("2- Fechar Programa\n");
}



int jogo( NoArvore* raiz, TipoHeroi* player)
{
  system(CLEAR_COMMAND);
  printMenuInical();
  int n, result;
  int aux;
  while (scanf("%d", &n) != 1) 
  {
    while (getchar() != '\n');
    printf("Entrada inválida.\n\n Digite um número válido: ");
  }

  switch ( n )
  {
    case 1 :
    
      criarHeroi( player );
      exibirHistoria();
     
      NoArvore* atual = raiz;

      Mapa mapa[ROOMS];

      iniciaMapa( mapa, raiz );

      while(1)
      {

        atualizaMapa( mapa, atual);

        atual = andaArvore( atual, player, mapa );

        //caso o player tenha escolhido encerar o jogo o hp do heroi é setado em -1
        if( player->Hp == -1 ) break;
       
        //Verifica se existe inimigo vivo no andar, em caso afirmativo há um combate
        if( atual->Inimigo.Hp > 0 )
        {
          printDecideCombate( atual, player );

          //função para escolher entre duas opções e descartar qualquer outra entrada
          while (scanf("%d", &n) != 1) 
          {
            while (getchar() != '\n');
            printf("Entrada inválida.\n\n Digite um número válido: ");
          }

          // O player pode decidir se recua ao escolher a opção 2
          // Caso escolha 1 ira combater
          // Caso o player morra no combate irá cancelar o jogo
          if( n == 2 ) atual = atual->pai;
          else {

            // Combate retorna 0 em caso de vitoria e 1 em caso de derrota
            if( Combate( player, atual ) ) {
              break;
            }
          }
        }

      }
      break;

    case 2 :
      return 1;
      
    default :
      printf("\nNúmero inválido.\n\nAperte ENTER para digitar novamente...");
      getchar();
      getchar();
      return 0;
  }

  return 0;
};

void menuHeroi() {
  printf("Vamos costumizar seu herói\n\n");
  printf("Selecione um nome para o seu guerreiro:");
  printf("Pressione ENTER para retornar");
}


int MenuCaminho( NoArvore* raiz )
{
  system(CLEAR_COMMAND);
  printf("\n============================================\n");
  printf("\n               UFG DUNGEON                  \n");
  printf("\n============================================\n\n");
  printf("\nEscolha uma porta:\n\n");

  if( raiz->meio!=NULL ) printf("1- Frente\n");
  if( raiz->esquerda!=NULL ) printf("2- Porta Esquerda\n");
  if( raiz->direita!=NULL ) printf("3- Direita\n");
  printf("4- Retornar\n");


  int n;
  while (scanf("%d", &n) != 1) 
  {
    while (getchar() != '\n');
    printf("Entrada inválida.\n\n Digite um número válido: ");
  }
  switch ( n )
  {
    case 1 :
      if( raiz->meio == NULL )
      {
        printf("Nao existe porta nesta direcao!\n");
        return 1;
      }
      raiz = raiz->meio;
      return 0;
      break;

    case 2 :
      if( raiz->esquerda == NULL )
      {
        printf("Nao existe porta nesta direcao!\n");
        return 1;
      }
      raiz = raiz->esquerda;
      return 0;
      break;
    
    case 3 :
      if( raiz->direita == NULL )
      {
        printf("Nao existe porta nesta direcao!\n");
        return 1;
      }      
      raiz = raiz->direita;
      return 0;
      break;

    case 4 :
      raiz = raiz->pai;
      return 1;
      break;
      
    default :
      printf("\nNúmero inválido.\n\nAperte ENTER para digitar novamente...");
      getchar();
      getchar();
      return 1;
  }

  return 1;
};

void MenuCombate( NoArvore* raiz, TipoHeroi *player )
{
  system(CLEAR_COMMAND);
  printf("\n============================================\n");
  printf("\n               UFG DUNGEON                  \n");
  printf("\n============================================\n\n");
  if(raiz->Inimigo.tipo == 1 ) printRat();
  if(raiz->Inimigo.tipo == 2 ) printEsqueleto();
  if(raiz->Inimigo.tipo == 3 ) printBird();
  if(raiz->Inimigo.tipo == 4 ) printMinotauro();
  printf("---------------------------------------------\n");
  printf("Status Inimigo\n");
  printf("Atk: %d   Def: %d\n",  raiz->Inimigo.Atk, raiz->Inimigo.Def);
  printf("---------------------------------------------\n");
  printf("Status %s\n", player->Name);
  printf("Hp: %d   Atk: %d   Def: %d\n", player->Hp ,player->Atk, player->Def);
  printf("---------------------------------------------\n");
};

void printDecideCombate( NoArvore* raiz, TipoHeroi *heroi )
{
  system(CLEAR_COMMAND);
  printf("\n============================================\n");
  printf("\n               UFG DUNGEON                  \n");
  printf("\n============================================\n\n");
  if(raiz->Inimigo.tipo == 1 ) printRat();
  if(raiz->Inimigo.tipo == 2 ) printEsqueleto();
  if(raiz->Inimigo.tipo == 3 ) printBird();
  if(raiz->Inimigo.tipo == 4 ) printMinotauro();
  printf("---------------------------------------------\n");
  printf("Status Inimigo\n");
  printf("Atk: %d   Def: %d\n", raiz->Inimigo.Atk, raiz->Inimigo.Def);
  printf("---------------------------------------------\n");
  printf("Status Do Herói\n");
  printf("Hp: %d   Atk: %d   Def: %d\n", heroi->Hp, heroi->Atk, heroi->Def);
  printf("---------------------------------------------\n");
  printf("Selecione uma opcao\n");
  printf("1- Lutar\n");
  printf("2- Recuar\n");
};


void printRat()
{

  printf("        __             _,-\"~^\"-.\n");
  printf("      _// )      _,-\"~`         `.\n");
  printf("    .\" ( /`\"-,-\"`                 ;\n");
  printf("   / 6                             ;\n");
  printf("  /           ,             ,-\"     ;\n");
  printf(" (,__.--.      \\           /        ;\n");
  printf("  //'   /`-\\   |          |        `._________\n");
  printf("    _.-'_/`  )  )--...,,,___\\     \\-----------,)\n");
  printf("  (((\"` _.-'.-'           __`-.   )         //\n");
  printf("       (((`\"             (((---~\"`         //\n");
  printf("                                            ((________________\n");
  printf("                                            `----\"\"\"\"~~~~^^^```\n");

}

void printEsqueleto()
{
  printf("      .-.\n");
  printf("     (o.o)\n");
  printf("      |=|\n");
  printf("     __|__\n");
  printf("   //.=|=.\\\\\n");
  printf("  // .=|=. \\\\\n");
  printf("  \\\\ .=|=. //\n");
  printf("   \\\\(_=_)//\n");
  printf("    (:| |:)\n");
  printf("     || ||\n");
  printf("     () ()\n");
  printf("     || ||\n");
  printf("     || ||\n");
  printf("    ==' '==\n");
}

void printBird()
{
  printf("      __             __\n");
  printf("   .-'.'     .-.     '.'-.\n");
  printf(" .'.((      ( ^ `>     )).'.\n");
  printf("/`'- \\'.______\\ (_____.'/ -'`\\\n");
  printf("|-''`.'------' '------'.`''-|\n");
  printf("|.-'`.'.'.`/ | | \\`.'.'.`'-.|\n");
  printf("\\ .' . /  | | | |  \\ . '. /\n");
  printf(" '._. :  _|_| |_|_  : ._.'\n");
  printf("    ````` /T\"Y\"T\\ `````\n");
  printf("          / | | | \\\n");
  printf("       `'`'`'`'`'`'`'`\n");
}


void printMinotauro()
{
  printf("     .      .\n");
  printf("     |\\____/|\n");
  printf("    (\\|----|/)\n");
  printf("     \\ 0  0 /\n");
  printf("      |    |\n");
  printf("   ___/\\../\\____\n");
  printf("  /     --       \\\n");
  printf(" /  \\         /   \\\n");
  printf("|    \\___/___/(   |\n");
  printf("\\   /|  }{   | \\  )\n");
  printf(" \\  ||__}{__|  |  |\n");
  printf("  \\  |;;;;;;;/  / \n");
  printf("   \\ /;;;;;;;;| [,,[|======'\n");
  printf("     |;;;;;;/ |     /\n");
  printf("     ||;;|\\   |\n");
  printf("     ||;;/|   /\n");
  printf("     \\_|:||__|\n");
  printf("      \\ ;||  /\n");
  printf("      |= || =|\n");
  printf("      |= /\\ =|\n");
  printf("      /_/  \\_\\ \n");
}