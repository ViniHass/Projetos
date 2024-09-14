#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <termios.h>
#include "Tarvore.h"
#include "Menus.h"



void generateDotFile( NoArvore *root, FILE *dotFile) {
    if (root != NULL) {
        if (root->esquerda != NULL) {
            fprintf(dotFile, "%d -> %d;\n", root->dado, root->esquerda->dado);
            generateDotFile(root->esquerda, dotFile);
        }
        if (root->meio != NULL) {
            fprintf(dotFile, "%d -> %d;\n", root->dado, root->meio->dado);
            generateDotFile(root->meio, dotFile);
        }
        if (root->direita != NULL) {
            fprintf(dotFile, "%d -> %d;\n", root->dado, root->direita->dado);
            generateDotFile(root->direita, dotFile);
        }
    }
}



int main()
{
    int opc;
    srand(time(NULL));
    Monstro empty = criarMonstro( 0, 0, 0, EMPTY);
    Monstro rato = criarMonstro( 2, 3, 3, RATO);
    Monstro esqueleto = criarMonstro( 3, 4, 6, ESQUELETO);
    Monstro bird = criarMonstro( 4, 6, 7, BIRD);
    Monstro minotauro = criarMonstro( 5, 8, 9, MINOTAURO);

    
    TipoHeroi *player = (TipoHeroi*) malloc( sizeof(TipoHeroi));


    do {
        NoArvore *raiz = preencheArvore( empty );
        distribuiMonstros( raiz, 0, rato, esqueleto, bird);
        distribuiBoss( raiz, minotauro );
        opc = jogo( raiz, player);
       
        liberaArvore(raiz);

        FILE *dotFile = fopen("tree.dot", "w");
        if (dotFile == NULL) {
            perror("Erro ao criar o arquivo DOT");
            exit(EXIT_FAILURE);
        }

        fprintf(dotFile, "digraph TernaryTree {\n");
        generateDotFile(raiz, dotFile);
        fprintf(dotFile, "}\n");

        fclose(dotFile);
        
    } while( opc != 1);
    

    return 0;
}