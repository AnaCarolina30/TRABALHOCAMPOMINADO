#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* todas as celulas começam fechadas
pra cada posição que o usuario jogar, 
precisamos saber se esta fechada ou aberta 
se é uma bomba ou não
quantas bombas tem na vizinhança*/

/* com uma matriz de inteiros (ex: int jogo [10][10;]) 
poderiamos verificar se as celulas estao abertas ou fechadas, usando 0 para fechadas e 1 para abertas 
não tem como verficar se se é uma bomba ou não e quantas bombas tem na vizinhança*/

/* CELULA - estrutura 
eBomba 0 ou 1 
estaAberta 0 ou 1
vizinhos 0 a 4
*/

typedef struct {
    int eBomba;
    int estaAberta;
    int vizinhos;
} Celula;

// variaveis globais
// int + nome da matriz + quantas linhas e colunas tem 
Celula jogo[10][10];
int linha, coluna, tam = 10;

// percorrer a matriz dizendo que todas as posiçoes estao fechadas, nao sao bombas e tem zero bombas na vizinhança

//procedimento para inicializar a matriz no jogo

void inicializarJogo() {
    for (linha = 0; linha < tam; linha++) {
        for (coluna = 0; coluna < tam; coluna++) {
            jogo[linha][coluna].eBomba = 0;
            jogo[linha][coluna].estaAberta = 0;
            jogo[linha][coluna].vizinhos = 0;  //inicializando o jogo, primeira ação que precisa tomar no jogo
        }
    }
}

/* procedimento para sortear n bombas 
usamos void porque esse procedimento nao vai retornar nada 
podemos perguntar ao usuario quantas bombas ele vai querer ou definir um padrao definido
int n = quantas bombas vao ser sorteadas*/ 

void sortearBombas(int n) {
    int i;
    srand(time(NULL));  //semente pro rand
    for (i = 1; i <= n; i++) {
        linha = rand() % tam;
        coluna = rand() % tam;  //nesse caso nosso tam é igual a 10. usaremos o resto da divisao
        if (jogo[linha][coluna].eBomba == 0) // verficiar se tem repetição de bombas no mesmo lugar 
            jogo[linha][coluna].eBomba = 1;
        else
            i--; // decrementa um elemento pra que ocorra a quantidade de vezes desejadas 
    } // garantimos que serão sorteadas n bombas 
}

/* função pra dizer se um par de coordenadas é valido ou não
garantir que os indices de linha e coluna nao ultrapassem o limite do int tam 
*/

int coordenadaEhValida(int linha, int coluna) {
    return (linha >= 0 && linha < tam && coluna >= 0 && coluna < tam);
}

/* função que retorna a quantidade de bombas na vizinhança de l e c (linha e coluna)
n - quantidade de bombas 
*/

/* verificação das casas vizinhas:
1- linha de cima: linha - 1 e c 
2- linha de baixo: linha + 1 e c
3- linha da direita: linha e coluna + 1
4- linha da esquerda: linha e coluna - 1  
*/

int quantidadeBombasVizinhas(int linha, int coluna) {
    int quantidade = 0;  //// se a coordenada for valida, precismaos ver se tem uma bomba la 
    if (coordenadaEhValida(linha - 1, coluna) && jogo[linha - 1][coluna].eBomba)
        quantidade++; //// se for verdadeiro, a gente incrementa 1, porque o 1 significa verdadeiro
    if (coordenadaEhValida(linha + 1, coluna) && jogo[linha + 1][coluna].eBomba)
        quantidade++;
    if (coordenadaEhValida(linha, coluna + 1) && jogo[linha][coluna + 1].eBomba)
        quantidade++;
    if (coordenadaEhValida(linha, coluna - 1) && jogo[linha][coluna - 1].eBomba)
        quantidade++;
    return quantidade;
}

// procedimento para contar as bombas vizinhas 

void contarBombas() {
    for (linha = 0; linha < tam; linha++) {
        for (coluna = 0; coluna < tam; coluna++)
            jogo[linha][coluna].vizinhos = quantidadeBombasVizinhas(linha, coluna);
    }
}

/* procedimento para imprimir o jogo
para imprimir, primeiro precisamos percorrer a matriz completa do jogo, entao vamos usar as estruturas de repetição for de novo
*/

void imprimir() {
    printf("\n\n\t   ");  // iniciar saltando duas linhas, tabulação do espaço
    for (linha = 0; linha < tam; linha++)  // inserir os indices das colunas
        printf("  %d ", linha);  // ate aqui sao os indices das colunas 
    printf("\n\n\t   -----------------------------------------\n");

    for (linha = 0; linha < tam; linha++) {
        printf("\t%d  |", linha); // antes de imprimir qualquer item da linha precisamos ja de uma barra, por isso fazemos antes do for; o "%d" é pra imprimir os indices das linhas
        for (coluna = 0; coluna < tam; coluna++) {
            if (jogo[linha][coluna].estaAberta) {
                if (jogo[linha][coluna].eBomba)  // ver se a posição que foi aberta é uma bomba
                    printf(" * ");  // se for uma bomba, imprime um *
                else
                    printf(" %d ", jogo[linha][coluna].vizinhos); // se a posição estiver aberta vai mostrar o numero de bombas vizinhas 
            } else
                printf("   "); // se estiver fechada, vamos imprimir um espaço porque não podemos revelar o que tem ali
            printf("|");
        }
        printf("\n\t   -----------------------------------------\n");
    }
}

//procedimento para abrir a coordenada digitada pelo usuario
void abrirCelula(int linha, int coluna) {
    if (coordenadaEhValida(linha, coluna) && !jogo[linha][coluna].estaAberta) { //garante que as coordenadas sao validas e que as celular nao foram abertas 
        jogo[linha][coluna].estaAberta = 1;
        if (jogo[linha][coluna].vizinhos == 0) {
            abrirCelula(linha - 1, coluna);
            abrirCelula(linha + 1, coluna);
            abrirCelula(linha, coluna + 1);
            abrirCelula(linha, coluna - 1);
        }
    }
}

/* função para verificar vitoria
1 - ganhou
2- nao ganhou ainda

precisamos percoorer toda a matriz procurando por celulas fechadas que nao sejam bombas, porque so assim o usuario ganha 
*/

int ganhou() {
    int quantidade = 0;  //quantidade de posiçoes fechadas 
    for (linha = 0; linha < tam; linha++) {
        for (coluna = 0; coluna < tam; coluna++) {
            if (!jogo[linha][coluna].estaAberta && !jogo[linha][coluna].eBomba) //verfica se esta fechada e se nao é bomba
                quantidade++;
        }
    }
    return quantidade;  //se o usuario ganhou retorna zero, se perdeu retorna tambem a quantidade de celulas fechadas e que nao sao bombas
}

// procedimento jogar que faz a leitura das coordenadas 
void jogar() {
    int linhas, colunas;
    do {
        imprimir(); //o imprimir fica aqui porque queremos que toda vez seja jogado, o programa imprima um novo tabuleiro
        do {
            printf("\nDigite as coordenadas de linha e coluna: "); // pedir pro usuario as coordenadas desejadas
            scanf("%d%d", &linhas, &colunas);

            if (!coordenadaEhValida(linhas, colunas))
                printf("\nCoordenada invalida!");
        } while (!coordenadaEhValida(linhas, colunas) || jogo[linhas][colunas].estaAberta); //garantir que a coordenada é valida e a posição esta fechada

        abrirCelula(linhas, colunas);
    } while (ganhou() != 0 && !jogo[linhas][colunas].eBomba); //queremos que ele repita o processo de abrir celulas enquanto o usuario nao ganhar

    if (jogo[linhas][colunas].eBomba)
        printf("\n\tQue pena! Voce perdeu!\n"); //ve se abriu uma bomba e perdeu ou se nao abriu e ganhou
    else
        printf("\n\tPARABENS VOCE GANHOU!\n");
}

int main() {
    int opcao;  //perguntar pro usuario se ele quer jogar de novo
    do {
        inicializarJogo();
        sortearBombas(10);
        contarBombas();
        printf("\n\t\t\tCAMPO MINADO\n");
        jogar();

        printf("\nDigite 1 para jogar novamente: ");
        scanf("%d", &opcao);
    } while (opcao == 1);

    return 0;
}
