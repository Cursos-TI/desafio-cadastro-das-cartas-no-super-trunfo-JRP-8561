#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ESTADOS 8
#define MAX_CIDADES 4

typedef struct {
    char codigo[5];
    int populacao;
    float area;
    float pib;
    int pontos_turisticos;
    float densidade_populacional;
    float pib_per_capita;
} Carta;

void calcular_propriedades(Carta *carta) {
    if (carta->area > 0) {
        carta->densidade_populacional = carta->populacao / carta->area;
    } else {
        carta->densidade_populacional = 0;
    }
    if (carta->populacao > 0) {
        carta->pib_per_capita = carta->pib / carta->populacao;
    } else {
        carta->pib_per_capita = 0;
    }
}

void entrada_automatica(Carta cartas[MAX_ESTADOS][MAX_CIDADES]) {
    srand(time(NULL));
    for (int i = 0; i < MAX_ESTADOS; i++) {
        for (int j = 0; j < MAX_CIDADES; j++) {
            sprintf(cartas[i][j].codigo, "%c%02d", 'A' + i, j + 1);
            cartas[i][j].populacao = rand() % 1000000 + 10000; // Entre 10k e 1M
            cartas[i][j].area = (rand() % 5000 + 100) / 10.0;   // Entre 10.0 e 500.0 km²
            cartas[i][j].pib = (rand() % 100000 + 1000) / 10.0; // Entre 100.0 e 10k milhões
            cartas[i][j].pontos_turisticos = rand() % 20 + 1;   // Entre 1 e 20
            calcular_propriedades(&cartas[i][j]);
        }
    }
    printf("Dados gerados automaticamente com sucesso!\n");
}

void entrada_manual(Carta cartas[MAX_ESTADOS][MAX_CIDADES]) {
    for (int i = 0; i < MAX_ESTADOS; i++) {
        for (int j = 0; j < MAX_CIDADES; j++) {
            sprintf(cartas[i][j].codigo, "%c%02d", 'A' + i, j + 1);
            printf("\nCadastro da cidade %s:\n", cartas[i][j].codigo);

            printf("População (valor positivo): ");
            while (scanf("%d", &cartas[i][j].populacao) != 1 || cartas[i][j].populacao <= 0) {
                printf("Entrada inválida! Insira um valor positivo para a população: ");
                while (getchar() != '\n'); // Limpa o buffer do stdin
            }

            printf("Área (km², valor positivo): ");
            while (scanf("%f", &cartas[i][j].area) != 1 || cartas[i][j].area <= 0) {
                printf("Entrada inválida! Insira um valor positivo para a área: ");
                while (getchar() != '\n'); // Limpa o buffer do stdin
            }

            printf("PIB (em milhões, valor positivo): ");
            while (scanf("%f", &cartas[i][j].pib) != 1 || cartas[i][j].pib <= 0) {
                printf("Entrada inválida! Insira um valor positivo para o PIB: ");
                while (getchar() != '\n'); // Limpa o buffer do stdin
            }

            printf("Número de pontos turísticos (valor entre 1 e 100): ");
            while (scanf("%d", &cartas[i][j].pontos_turisticos) != 1 ||
                   cartas[i][j].pontos_turisticos <= 0 || cartas[i][j].pontos_turisticos > 100) {
                printf("Entrada inválida! Insira um valor entre 1 e 100 para os pontos turísticos: ");
                while (getchar() != '\n'); // Limpa o buffer do stdin
            }

            calcular_propriedades(&cartas[i][j]);
        }
    }
}

void exibir_cartas(Carta cartas[MAX_ESTADOS][MAX_CIDADES], char *pais) {
    printf("\nDados do país: %s\n", pais);
    for (int i = 0; i < MAX_ESTADOS; i++) {
        for (int j = 0; j < MAX_CIDADES; j++) {
            printf("\nCidade %s (%s):\n", cartas[i][j].codigo, pais);
            printf("População: %d\n", cartas[i][j].populacao);
            printf("Área: %.2f km²\n", cartas[i][j].area);
            printf("PIB: %.2f milhões\n", cartas[i][j].pib);
            printf("Pontos turísticos: %d\n", cartas[i][j].pontos_turisticos);
            printf("Densidade Populacional: %.2f hab/km²\n", cartas[i][j].densidade_populacional);
            printf("PIB per Capita: %.2f milhões/hab\n", cartas[i][j].pib_per_capita);
        }
    }
}

int main() {
    Carta cartas[MAX_ESTADOS][MAX_CIDADES];
    char pais[50];
    int opcao, continuar;

    do {
        printf("Bem-vindo ao sistema Super Trunfo - Países!\n");
        printf("Insira o nome do país: ");
        while (getchar() != '\n'); // Limpa o buffer do stdin
        fgets(pais, 50, stdin);
        pais[strcspn(pais, "\n")] = '\0'; // Remove o caractere de nova linha

        printf("\nEscolha o método de entrada de dados:\n");
        printf("1 - Entrada manual\n");
        printf("2 - Entrada automática (aleatória)\n");
        printf("Opção: ");
        
        while (scanf("%d", &opcao) != 1 || (opcao != 1 && opcao != 2)) {
            printf("Entrada inválida! Escolha 1 para manual ou 2 para automática: ");
            while (getchar() != '\n'); // Limpa o buffer do stdin
        }

        if (opcao == 1) {
            entrada_manual(cartas);
        } else {
            entrada_automatica(cartas);
        }

        exibir_cartas(cartas, pais);

        printf("\nDeseja cadastrar outro país? (1 - Sim, 0 - Não): ");
        while (scanf("%d", &continuar) != 1 || (continuar != 0 && continuar != 1)) {
            printf("Entrada inválida! Escolha 1 para Sim ou 0 para Não: ");
            while (getchar() != '\n'); // Limpa o buffer do stdin
        }

    } while (continuar == 1);

    printf("Encerrando o programa. Obrigado!\n");
    return 0;
}