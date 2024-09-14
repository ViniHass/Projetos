#ifndef TARVORE_H
#define TARVORE_H

#define ROOMS 45

#define VIDA_HEROI 150

// Enumeração para representar o tipo de monstro
typedef enum
{
    EMPTY,
    RATO,
    ESQUELETO,
    BIRD,
    MINOTAURO,
} TipoMonstro;

// Estrutura para representar um monstro
typedef struct {
    int Hp;
    int Atk;
    int Def;
    TipoMonstro tipo;
} Monstro;

typedef struct NoArvore {
    int dado;
    Monstro Inimigo;
    struct NoArvore *pai;
    struct NoArvore *esquerda;
    struct NoArvore *meio;
    struct NoArvore *direita;
} NoArvore;


// Estrutura para representar o herói

typedef struct Heroi {
    int Hp;
    int Atk;
    int Def;
    char Name[30];
    int nivel;
    char classe[30];
    float vida;
    float ataque;
    float defesa;
    char tipoArma[20];
    char armadura[20];
    int pontosExperiencia;
} TipoHeroi;


typedef struct Lista {
    int atual;
    int retorna;
    int esquerda;
    int direita;
    int frente;
} Mapa;


NoArvore* criaNo( int valor, Monstro mons); // função que cria um novo monstro

NoArvore *preencheArvore( Monstro mons ); // adiciona um monstro a um nó da árvore

void distribuiMonstros(NoArvore* raiz, int altura, Monstro rato, Monstro esqueleto,
Monstro bird); 

void distribuiBoss(NoArvore* raiz, Monstro minotaruro);

NoArvore* andaArvore(NoArvore *raiz, TipoHeroi *player, Mapa *mapa);

void imprimeArvore(NoArvore *raiz);


// Função para criar um novo monstro
Monstro criarMonstro( int Hp, int Atk, int Def, TipoMonstro tipo);

// Função para criar un novo heroi

void criarHeroi( TipoHeroi *player );


// Função que executa o combate por nó
//return 1 -> guerreiro venceu
// return 2 -> guerreiro abatido
int Combate(TipoHeroi *heroi, NoArvore *monstro);

void liberaArvore(NoArvore *raiz);

void iniciaMapa( Mapa *mapa, NoArvore *raiz );

void atualizaMapa( Mapa *mapa, NoArvore *raiz);

void printaMapa( Mapa *mapa );

#endif