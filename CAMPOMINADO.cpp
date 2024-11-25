#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
    int eBomba;       // Indica se a célula contém uma bomba (1: sim, 0: não)
    int estaAberta;   // Indica se a célula foi aberta (1: sim, 0: não)
    int vizinhos;     // Número de bombas nas células vizinhas
} Celula;

#define TAM 10 // Tamanho do tabuleiro
Celula jogo[TAM][TAM];

// Função para inicializar o tabuleiro
void inicializarJogo() {
    for (int linha = 0; linha < TAM; linha++) {
        for (int coluna = 0; coluna < TAM; coluna++) {
            jogo[linha][coluna].eBomba = 0;
            jogo[linha][coluna].estaAberta = 0;
            jogo[linha][coluna].vizinhos = 0;
        }
    }
}

// Sorteia bombas aleatoriamente no tabuleiro
void sortearBombas(int n) {
    int i = 0;
    srand(time(NULL));
    while (i < n) {
        int linha = rand() % TAM;
        int coluna = rand() % TAM;
        if (jogo[linha][coluna].eBomba == 0) {
            jogo[linha][coluna].eBomba = 1;
            i++;
        }
    }
}

// Verifica se uma coordenada está dentro dos limites do tabuleiro
int coordenadaEhValida(int linha, int coluna) {
    return (linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM);
}

// Calcula o número de bombas nas células vizinhas
int quantidadeBombasVizinhas(int linha, int coluna) {
    int quantidade = 0;
    int direcoes[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},         {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };

    for (int i = 0; i < 8; i++) {
        int novaLinha = linha + direcoes[i][0];
        int novaColuna = coluna + direcoes[i][1];
        if (coordenadaEhValida(novaLinha, novaColuna) && jogo[novaLinha][novaColuna].eBomba) {
            quantidade++;
        }
    }

    return quantidade;
}

// Atualiza o número de bombas vizinhas para todas as células
void contarBombas() {
    for (int linha = 0; linha < TAM; linha++) {
        for (int coluna = 0; coluna < TAM; coluna++) {
            jogo[linha][coluna].vizinhos = quantidadeBombasVizinhas(linha, coluna);
        }
    }
}

// Exibe o tabuleiro no console
void imprimir() {
    printf("\n\n\t   ");
    for (int coluna = 0; coluna < TAM; coluna++) {
        printf("  %d ", coluna);
    }
    printf("\n\t   -----------------------------------------\n");

    for (int linha = 0; linha < TAM; linha++) {
        printf("\t%d  |", linha);
        for (int coluna = 0; coluna < TAM; coluna++) {
            if (jogo[linha][coluna].estaAberta) {
                if (jogo[linha][coluna].eBomba) {
                    printf(" * "); // Bomba
                } else {
                    printf(" %d ", jogo[linha][coluna].vizinhos); // Número de bombas vizinhas
                }
            } else {
                printf("   "); // Célula fechada
            }
            printf("|");
        }
        printf("\n\t   -----------------------------------------\n");
    }
}

// Abre uma célula e suas vizinhas se aplicável
void abrirCelula(int linha, int coluna) {
    if (coordenadaEhValida(linha, coluna) && !jogo[linha][coluna].estaAberta) {
        jogo[linha][coluna].estaAberta = 1;
        if (jogo[linha][coluna].vizinhos == 0 && !jogo[linha][coluna].eBomba) {
            // Abre células vizinhas recursivamente
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    abrirCelula(linha + i, coluna + j);
                }
            }
        }
    }
}

// Verifica se o jogador venceu (todas as células não-bombas foram abertas)
int ganhou() {
    for (int linha = 0; linha < TAM; linha++) {
        for (int coluna = 0; coluna < TAM; coluna++) {
            if (!jogo[linha][coluna].estaAberta && !jogo[linha][coluna].eBomba) {
                return 0; // Ainda há células não abertas
            }
        }
    }
    return 1; // Vitória
}

// Função principal do jogo
void jogar(int nivel) {
    int numBombas = nivel * 5; // Ajuste a dificuldade multiplicando bombas
    inicializarJogo();
    sortearBombas(numBombas);
    contarBombas();

    int linha, coluna;
    while (!ganhou()) {
        imprimir();
        printf("\nDigite linha e coluna para abrir (ex: 3 4): ");
        scanf("%d %d", &linha, &coluna);

        if (!coordenadaEhValida(linha, coluna)) {
            printf("\nCoordenadas inválidas!\n");
        } else if (jogo[linha][coluna].eBomba) {
            printf("\nVocê perdeu! Bomba encontrada.\n");
            imprimir();https://github.com/AnaCarolina30/TRABALHOCAMPOMINADO
            return;
        } else {
            abrirCelula(linha, coluna);
        }
    }

    printf("\nParabéns! Você venceu o jogo.\n");
    imprimir();
}

// Função principal
int main() {
    int nivel;
    printf("Bem-vindo ao Campo Minado!\n");
    printf("Escolha o nível de dificuldade (1 a 5): ");
    scanf("%d", &nivel);
    if (nivel < 1 || nivel > 5) {
        printf("Nível inválido. Tente novamente.\n");
        return 1;
    }

    jogar(nivel);
    return 0;
}


