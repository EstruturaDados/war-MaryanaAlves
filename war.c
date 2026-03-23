#include <stdio.h>
#include <string.h>

#define MAX_TERRITORIOS 5

//Estrutura dos territorios
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

//Função para limpar os 'lixos' indesejados do buffer de entrada
void limparBufferEntrada(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    //Criacao do vetor de territorios
    Territorio territorios[MAX_TERRITORIOS];

    printf("===============================\n");
    printf("Vamos cadastrar os 5 territorios iniciais do nosso mundo\n");

    //Cadastro dos 5 territorios em loop
    for(int i=0; i<MAX_TERRITORIOS; i++) {
        printf("--- Cadastrando Territorio %d ---\n", i+1);

        printf("Nome do territorio: ");
        fgets(territorios[i].nome, 30, stdin);

        printf("Cor do territorio (ex: Vermelho, Roxo): ");
        fgets(territorios[i].cor, 10, stdin);

        //Removendo o '\n' enter do final das strings por '\0' nulo
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';
        
        printf("Numero de tropas: ");
        scanf("%d", &territorios[i].tropas);
        limparBufferEntrada();    
    }

    printf("\nTerritorios cadastrados com sucesso!");

    printf("\n\n===============================");
    printf("\n   MAPA DO MUNDO - ESTADO ATUAL   ");
    printf("\n===============================\n");

    //Exibicao dos territorios cadastrados
    for(int i=0; i<MAX_TERRITORIOS; i++) {
        printf("\nTERRITORIO %d:", i+1);
        printf("\n  - Nome: %s", territorios[i].nome);
        printf("\n  - Dominado por: Exercito %s", territorios[i].cor);
        printf("\n  - Tropas: %d\n\n", territorios[i].tropas);
    }

    return 0;
}
