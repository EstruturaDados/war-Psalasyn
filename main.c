#include <stdio.h>
#include <string.h>

/*
    Estrutura que representa um território do jogo.
    Agrupa informações relacionadas a um mesmo território.
*/
struct Territorio {
    char nome[30];   // Nome do território
    char cor[10];    // Cor do exército
    int tropas;      // Quantidade de tropas
};

int main() {

    // Vetor para armazenar 5 territórios
    struct Territorio territorios[5];

    // Cadastro dos territórios
    for (int i = 0; i < 5; i++) {

        printf("\nCadastro do Territorio %d\n", i + 1);

        printf("Digite o nome do territorio: ");
        scanf("%s", territorios[i].nome);

        printf("Digite a cor do exercito: ");
        scanf("%s", territorios[i].cor);

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    // Exibição do relatório final
    printf("\n===== RELATORIO DOS TERRITORIOS =====\n");

    for (int i = 0; i < 5; i++) {

        printf("\nTerritorio %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exercito: %s\n", territorios[i].cor);
        printf("Quantidade de tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}
