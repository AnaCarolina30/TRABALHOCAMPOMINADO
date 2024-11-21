#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int eBomba; 
    int estaAberta;
    int vizinhos;
} Celula;

Celula jogo[10][10];
int linha, coluna, tam = 10;
int score = 0;  // Variável para armazenar a pontuação

void inicializarJogo() {
    for (linha = 0; linha < tam; linha++) {
        for (coluna = 0; coluna < tam; coluna++) {
            jogo[linha][coluna].eBomba = 0;
            jogo[linha][coluna].estaAberta = 0;
            jogo[linha][coluna].vizinhos = 0;
        }
    }
}

void sortearBombas(int n) {
    int i;
    srand(time(NULL));
    for (i = 1; i <= n; i++) {
        linha = rand() % tam;
        coluna = rand() % tam;
        if (jogo[linha][coluna].eBomba == 0)
            jogo[linha][coluna].eBomba = 1;
        else
            i--;
    }
}

int coordenadaEhValida(int linha, int coluna) {
    return (linha >= 0 && linha < tam && coluna >= 0 && coluna < tam);
}

int quantidadeBombasVizinhas(int linha, int coluna) {
    int quantidade = 0;
    if (coordenadaEhValida(linha - 1, coluna) && jogo[linha - 1][coluna].eBomba)
        quantidade++;
    if (coordenadaEhValida(linha + 1, coluna) && jogo[linha + 1][coluna].eBomba)
        quantidade++;
    if (coordenadaEhValida(linha, coluna + 1) && jogo[linha][coluna + 1].eBomba)
        quantidade++;
    if (coordenadaEhValida(linha, coluna - 1) && jogo[linha][coluna - 1].eBomba)
        quantidade++;
    return quantidade;
}

void contarBombas() {
    for (linha = 0; linha < tam; linha++) {
        for (coluna = 0; coluna < tam; coluna++)
            jogo[linha][coluna].vizinhos = quantidadeBombasVizinhas(linha, coluna);
    }
}

void imprimir() {
    printf("\n\n\t   ");
    for (linha = 0; linha < tam; linha++)
        printf("  %d ", linha);
    printf("\n\n\t   -----------------------------------------\n");

    for (linha = 0; linha < tam; linha++) {
        printf("\t%d  |", linha);
        for (coluna = 0; coluna < tam; coluna++) {
            if (jogo[linha][coluna].estaAberta) {
                if (jogo[linha][coluna].eBomba)
                    printf(" * ");
                else
                    printf(" %d ", jogo[linha][coluna].vizinhos);
            } else
                printf("   ");
            printf("|");
        }
        printf("\n\t   -----------------------------------------\n");
    }
}

void abrirCelula(int linha, int coluna) {
    if (coordenadaEhValida(linha, coluna) && !jogo[linha][coluna].estaAberta) {
        jogo[linha][coluna].estaAberta = 1;
        if (jogo[linha][coluna].vizinhos == 0) {
            abrirCelula(linha - 1, coluna);
            abrirCelula(linha + 1, coluna);
            abrirCelula(linha, coluna + 1);
            abrirCelula(linha, coluna - 1);
        }
    }
}

int ganhou() {
    int quantidade = 0;
    for (linha = 0; linha < tam; linha++) {
        for (coluna = 0; coluna < tam; coluna++) {
            if (!jogo[linha][coluna].estaAberta && !jogo[linha][coluna].eBomba)
                quantidade++;
        }
    }
    return quantidade;
}

void jogar() {
    int linhas, colunas;
    do {
        imprimir();
        do {
            printf("\nDigite as coordenadas de linha e coluna: ");
            scanf("%d%d", &linhas, &colunas);

            if (!coordenadaEhValida(linhas, colunas))
                printf("\nCoordenada invalida!");
        } while (!coordenadaEhValida(linhas, colunas) || jogo[linhas][colunas].estaAberta);

        abrirCelula(linhas, colunas);
    } while (ganhou() != 0 && !jogo[linhas][colunas].eBomba);

    if (jogo[linhas][colunas].eBomba) {
        printf("\n\tQue pena! Voce perdeu!\n");
    } else {
        printf("\n\tPARABENS VOCE GANHOU!\n");
        score++;  // Incrementa o score ao vencer
    }
}

void mostrarScore() {
    printf("\nScore atual: %d\n", score);
}

int main() {
    int opcao;
    do {
        printf("\n\t\t\tMENU INICIAL\n");
        printf("\n1. Jogar\n2. Ver Score\n3. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inicializarJogo();
                sortearBombas(10);
                contarBombas();
                jogar();
                break;
            case 2:
                mostrarScore();
                break;
            case 3:
                printf("Saindo do jogo. Ate logo!\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    } while (opcao != 3);

    return 0;
}
