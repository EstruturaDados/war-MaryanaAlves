#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

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

//Função para simular o ataque entre dois territorios
void atacar(Territorio *atacante, Territorio *defensor){
    //Gerador de numeros aleatorios para rolar os "dados"
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("O atacante %s rolou um dado e tirou: %d\n", atacante->nome, dadoAtacante);
    printf("O defensor %s rolou um dado e tirou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("VITORIA DO ATAQUE! O defensor perdeu metade das tropas e o territorio foi conquistado.\n");
        
        int tropasTransferidas = defensor->tropas / 2;
        atacante->tropas += tropasTransferidas;
        defensor->tropas -= tropasTransferidas;
        
        strcpy(defensor->cor, atacante->cor);
    } 
    else if (dadoAtacante < dadoDefensor) {
        printf("VITORIA DA DEFESA! O atacante perdeu 1 tropa.\n");
        atacante->tropas--;
        defensor->tropas++;
    } 
    else {
        printf("EMPATE! Nenhum territorio perdeu tropas.");
    }
    //Caso o territorio seja conquistado (perdeu todas as tropas), exibe a mensagem de conquista
    if (atacante->tropas == 0) {
        printf("CONQUISTA! o territorio %s foi dominado pelo Exercito %s!", atacante->nome, defensor->cor);
    } 
    else if (defensor->tropas == 0) {
        printf("CONQUISTA! o territorio %s foi dominado pelo Exercito %s!", defensor->nome, atacante->cor);
    }
}

// Função para cadastrar territorios
void cadastrarTerritorios(Territorio *territorios, unsigned int numTerritorios) {
    printf("\n===============================\n");
    printf("  WAR ESTRUTURADO - %u CADASTROS INICIAIS  \n", numTerritorios);
    printf("===============================\n");

    for (int i = 0; i < (int)numTerritorios; i++) {
        printf("\n--- Cadastrando Territorio %d ---\n", i + 1);

        printf("Nome do territorio: ");
        fgets(territorios[i].nome, 30, stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

        printf("Cor do territorio (ex: Vermelho, Roxo): ");
        fgets(territorios[i].cor, 10, stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';

        printf("Numero de tropas: ");
        scanf("%d", &territorios[i].tropas);
        limparBufferEntrada();
    }

    printf("\nTerritorios cadastrados com sucesso!\n");
}

void exibirMapa(Territorio *territorios, unsigned int numTerritorios) {
    printf("\n===============================");
    printf("\n   MAPA DO MUNDO - ESTADO ATUAL   ");
    printf("\n===============================\n");

    for (int i = 0; i < (int)numTerritorios; i++) {
        printf("\n%d. %s (Exercito %s, Tropas: %d)", i + 1, territorios[i].nome, territorios[i].cor, territorios[i].tropas);
    }
    printf("\n");
}

void liberarMemoria(Territorio *territorios) {
    free(territorios);
}

int main() {
    srand((unsigned int)time(NULL));
    bool encerrarJogo = false;
    unsigned int numTerritorios, escolhaAtacante, escolhaDefensor;

    do {
        printf("\nQuantos territorios iniciais voce gostaria de ter?: ");
        scanf("%u", &numTerritorios);
        limparBufferEntrada();
        
        if (numTerritorios == 0 || numTerritorios > 100) {
            printf("O numero de territorios deve ser maior que zero e menor ou igual a 100. Tente novamente.\n");
        }
    } while (numTerritorios == 0 || numTerritorios > 100);

    //Criacao do ponteiro de territorios e alocacao dinamica com o numero de territorios escolhido pelo usuario
    Territorio *territorios = calloc((size_t)numTerritorios, sizeof(Territorio));

    cadastrarTerritorios(territorios, numTerritorios);
    printf("\n\nPressione enter para continuar...");
    getchar();

    exibirMapa(territorios, numTerritorios);
    
    do {
        //Fase que simula o ataque entre territorios
        printf("\n\n --- FASE DE ATAQUE ---\n");
        printf("Escolha o territorio atacante (1 a %u, ou 0 para sair): ", numTerritorios);
        scanf("%u", &escolhaAtacante);
        limparBufferEntrada();

        if (escolhaAtacante == 0){
            printf("Encerrando o jogo. Obrigado por jogar!\n");
            encerrarJogo = true;
            break;    
        } 
        if (escolhaAtacante < 1 || escolhaAtacante > numTerritorios || territorios[escolhaAtacante - 1].tropas == 0) {
            printf("Escolha invalida. Territorio inexistente ou sem tropas.\n");
            continue;
        }

        printf("Escolha o territorio defensor (1 a %u): ", numTerritorios);
        scanf("%u", &escolhaDefensor);
        limparBufferEntrada();

        if (escolhaDefensor < 1 || escolhaDefensor > numTerritorios || escolhaDefensor == escolhaAtacante || strcmp(territorios[escolhaAtacante - 1].cor, territorios[escolhaDefensor - 1].cor) == 0 || territorios[escolhaDefensor - 1].tropas == 0) {
            printf("Escolha invalida! Defensor inexistente, sem tropas ou de mesma cor do atacante.\n");
            continue;
        }

        printf("\n--- RESULTADO DA BATALHA ---\n");
            
        //Ataque e exibição do resultado da batalha
        atacar(&territorios[escolhaAtacante - 1], &territorios[escolhaDefensor - 1]);
        printf("\n\nPressione enter para continuar...");
        getchar();

        //Exibição do mapa atualizado
        exibirMapa(territorios, numTerritorios);

    } while (encerrarJogo == false);

    liberarMemoria(territorios);
    return 0;
}
