#include<stdio.h>
#include<string.h>

void criarMapa(int x,int y) {
    char espaco[x][y];
    memset(espaco,'#', sizeof(espaco));
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            printf("%c", espaco[j][i]);
        }
        printf("\n");
    }
    
} 

void criarBomba() {
    
}

int main(){
    criarMapa(6, 8);
}