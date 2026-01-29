#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
    Estrutura que representa um território do jogo.
*/
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

/*
    Função responsável por cadastrar os territórios.
    Recebe o mapa (vetor dinâmico) e o total de territórios.
*/
void cadastrarTerritorios(Territorio* mapa, int total) {

    for (int i = 0; i < total; i++) {

        printf("\nCadastro do Territorio %d\n", i);

        printf("Nome: ");
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do exercito: ");
        fgets(mapa[i].cor, 10, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // limpa o '\n' deixado pelo scanf
    }
}

/*
    Função responsável por exibir todos os territórios.
*/
void exibirTerritorios(Territorio* mapa, int total) {

    printf("\n===== MAPA ATUAL =====\n");

    for (int i = 0; i < total; i++) {
        printf("[%d] %s | Cor: %s | Tropas: %d\n",
               i,
               mapa[i].nome,
               mapa[i].cor,
               mapa[i].tropas);
    }
}

/*
    Função que simula o ataque entre dois territórios.
    Utiliza números aleatórios como dados de batalha.
*/
void atacar(Territorio* atacante, Territorio* defensor) {

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\nDado do atacante (%s): %d", atacante->nome, dadoAtacante);
    printf("\nDado do defensor (%s): %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {

        printf("O atacante venceu a batalha!\n");

        // Defensor muda de cor
        strcpy(defensor->cor, atacante->cor);

        // Transferência de tropas (metade do atacante)
        int tropasTransferidas = atacante->tropas / 2;
        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;

    } else {

        printf("O defensor resistiu ao ataque!\n");

        // Atacante perde uma tropa (se possível)
        if (atacante->tropas > 0) {
            atacante->tropas--;
        }
    }
}

/*
    Função responsável por liberar a memória alocada dinamicamente.
*/
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

/*
    Função principal do programa.
*/
int main() {

    int totalTerritorios;
    int indiceAtacante;
    int indiceDefensor;

    Territorio* mapa;

    // Inicializa a semente dos números aleatórios
    srand(time(NULL));

    printf("Informe o numero de territorios: ");
    scanf("%d", &totalTerritorios);
    getchar(); // limpa o '\n'

    // Alocação dinâmica do mapa
    mapa = (Territorio*) calloc(totalTerritorios, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    // Cadastro dos territórios
    cadastrarTerritorios(mapa, totalTerritorios);

    // Exibição inicial
    exibirTerritorios(mapa, totalTerritorios);

    // Escolha do atacante
    printf("\nEscolha o indice do territorio atacante: ");
    scanf("%d", &indiceAtacante);

    // Escolha do defensor
    printf("Escolha o indice do territorio defensor: ");
    scanf("%d", &indiceDefensor);

    // Validação dos índices
    if (indiceAtacante < 0 || indiceAtacante >= totalTerritorios ||
        indiceDefensor < 0 || indiceDefensor >= totalTerritorios) {

        printf("Indice invalido.\n");
        liberarMemoria(mapa);
        return 1;
    }

    // Validação de cores (não pode atacar território da mesma cor)
    if (strcmp(mapa[indiceAtacante].cor, mapa[indiceDefensor].cor) == 0) {
        printf("Ataque invalido: territorios da mesma cor.\n");
        liberarMemoria(mapa);
        return 1;
    }

    // Execução do ataque
    atacar(&mapa[indiceAtacante], &mapa[indiceDefensor]);

    // Exibição pós-ataque
    exibirTerritorios(mapa, totalTerritorios);

    // Liberação da memória
    liberarMemoria(mapa);

    return 0;
}

