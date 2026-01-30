#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

/* Limpa o buffer de entrada */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* Cadastro dos territórios */
void cadastrarTerritorios(Territorio* mapa, int total) {
    for (int i = 0; i < total; i++) {

        printf("\nCadastro do Territorio %d\n", i + 1);

        printf("Nome: ");
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do exercito: ");
        fgets(mapa[i].cor, 10, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        limparBuffer();
    }
}

/* Exibe o mapa */
void exibirTerritorios(Territorio* mapa, int total) {
    printf("\n===== MAPA ATUAL =====\n");
    for (int i = 0; i < total; i++) {
        printf("[%d] %s | Cor: %s | Tropas: %d\n",
               i + 1,
               mapa[i].nome,
               mapa[i].cor,
               mapa[i].tropas);
    }
}

/* Sorteio da missão */
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

/* Verificação da missão */
int verificarMissao(char* missao, Territorio* mapa, int total) {
    if (strstr(missao, "vermelha") != NULL) {
        for (int i = 0; i < total; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0) {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

/* Ataque */
void atacar(Territorio* atacante, Territorio* defensor) {

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\nDado do atacante (%s): %d\n", atacante->nome, dadoAtacante);
    printf("Dado do defensor (%s): %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {

        printf("O atacante venceu!\n");

        strcpy(defensor->cor, atacante->cor);

        int tropasTransferidas = atacante->tropas / 2;
        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;

    } else {

        printf("O defensor resistiu!\n");
        if (atacante->tropas > 0) {
            atacante->tropas--;
        }
    }
}

/* Liberação de memória */
void liberarMemoria(Territorio* mapa, char* missao) {
    free(mapa);
    free(missao);
}

int main() {

    srand(time(NULL));

    int totalTerritorios;
    int atacante, defensor;

    char* missoes[] = {
        "Conquistar pelo menos 3 territorios",
        "Eliminar todos os territorios da cor vermelha",
        "Controlar mais da metade do mapa",
        "Reduzir um inimigo a zero tropas",
        "Conquistar qualquer territorio com mais de 5 tropas"
    };

    char* missaoJogador = malloc(101);
    if (!missaoJogador) return 1;

    printf("Informe o numero de territorios: ");
    scanf("%d", &totalTerritorios);
    limparBuffer();

    Territorio* mapa = calloc(totalTerritorios, sizeof(Territorio));
    if (!mapa) {
        free(missaoJogador);
        return 1;
    }

    cadastrarTerritorios(mapa, totalTerritorios);
    exibirTerritorios(mapa, totalTerritorios);

    atribuirMissao(missaoJogador, missoes, 5);

    printf("\n===== SUA MISSAO =====\n%s\n", missaoJogador);

    printf("\nEscolha o territorio atacante (1 a %d): ", totalTerritorios);
    scanf("%d", &atacante);
    limparBuffer();
    atacante--;

    printf("Escolha o territorio defensor (1 a %d): ", totalTerritorios);
    scanf("%d", &defensor);
    limparBuffer();
    defensor--;

    if (atacante < 0 || atacante >= totalTerritorios ||
        defensor < 0 || defensor >= totalTerritorios ||
        strcmp(mapa[atacante].cor, mapa[defensor].cor) == 0) {

        printf("Ataque invalido.\n");
        liberarMemoria(mapa, missaoJogador);
        return 1;
    }

    atacar(&mapa[atacante], &mapa[defensor]);
    exibirTerritorios(mapa, totalTerritorios);

    if (verificarMissao(missaoJogador, mapa, totalTerritorios)) {
        printf("\n🏆 MISSAO CUMPRIDA! VOCE VENCEU! 🏆\n");
    }

    liberarMemoria(mapa, missaoJogador);
    return 0;
}
