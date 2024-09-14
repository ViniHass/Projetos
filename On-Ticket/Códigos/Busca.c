#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Busca.h"

int busca_sequencial(int lista[], int tamanho, int valor) {
    for (int i = 0; i < tamanho; i++) {
        if (lista[i] == valor) {
            return i; // Retorna o índice do elemento encontrado
        }
    }
    return -1; // Retorna -1 se o valor não estiver na lista
}

int busca_binaria(int lista[], int tamanho, int valor) {
    int esquerda = 0;
    int direita = tamanho - 1;

    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        if (lista[meio] == valor) {
            return meio; // Retorna o índice do elemento encontrado
        } else if (lista[meio] < valor) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }

    return -1; // Retorna -1 se o valor não estiver na lista
}

int busca_ternaria(int lista[], int tamanho, int valor) {
    int esquerda = 0;
    int direita = tamanho - 1;

    while (esquerda <= direita) {
        int um_terco = esquerda + (direita - esquerda) / 3;
        int dois_tercos = esquerda + 2 * (direita - esquerda) / 3;

        if (lista[um_terco] == valor) {
            return um_terco;
        } else if (lista[dois_tercos] == valor) {
            return dois_tercos;
        } else if (lista[um_terco] > valor) {
            direita = um_terco - 1;
        } else if (lista[dois_tercos] < valor) {
            esquerda = dois_tercos + 1;
        } else {
            esquerda = um_terco + 1;
            direita = dois_tercos - 1;
        }
    }

    return -1;
}

int busca_interpolar(int lista[], int tamanho, int valor) {
    int esquerda = 0;
    int direita = tamanho - 1;

    while (esquerda <= direita && lista[esquerda] <= valor && lista[direita] >= valor) {
        // Interpolação linear para estimar a posição do elemento
        int pos = esquerda + ((valor - lista[esquerda]) * (direita - esquerda)) / (lista[direita] - lista[esquerda]);

        if (lista[pos] == valor) {
            return pos;
        } else if (lista[pos] < valor) {
            esquerda = pos + 1;
        } else {
            direita = pos - 1;
        }
    }

    return -1;
}


int busca_exponencial(int lista[], int tamanho, int valor) {
    int indice = 1;

    if (lista[0] == valor) {
        return 0;
    }

    while (indice < tamanho && lista[indice] <= valor) {
        indice *= 2;
    }

    return busca_bin(lista, tamanho, valor, indice / 2, (indice < tamanho) ? indice : tamanho);
}

int busca_bin(int lista[], int tamanho, int valor, int esquerda, int direita) {
    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        if (lista[meio] == valor) {
            return meio;
        } else if (lista[meio] < valor) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }

    return -1;
}

int busca_por_salto(int lista[], int tamanho, int valor) {
    int salto = sqrt(tamanho);
    int anterior = 0;

    while (lista[(int)fmin(salto, tamanho) - 1] < valor) {
        anterior = salto;
        salto += sqrt(tamanho);
        if (anterior >= tamanho) {
            return -1;
        }
    }

    while (lista[anterior] < valor) {
        anterior++;
        if (anterior == fmin(salto, tamanho)) {
            return -1;
        }
    }

    if (lista[anterior] == valor) {
        return anterior;
    }
    return -1;
}
