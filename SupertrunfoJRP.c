#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ESTADOS 8
#define MAX_CIDADES 4
#define MAX_PAÍSES 10
#define MAX_JOGADORES 2

typedef struct {
    char codigo[5];
    int populacao;
    float area;
    float pib;
    int pontos_turisticos;
    float densidade_populacional;
    float pib_per_capita;
} Carta;

typedef struct {
    char nome[50];
    Carta cartas[MAX_ESTADOS][MAX_CIDADES];
} Pais;

typedef struct {
    char nome[50];
    Carta carta_escolhida;
    float super_poder;
} Jogador;

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
}

void entrada_manual(Carta cartas[MAX_ESTADOS][MAX_CIDADES]) {
    for (int i = 0; i < MAX_ESTADOS; i++) {
        for (int j = 0; j < MAX_CIDADES; j++) {
            sprintf(cartas[i][j].codigo, "%c%02d", 'A' + i, j + 1);
            printf("\nCarta %s:\n", cartas[i][j].codigo);

            printf("População: ");
            while (scanf("%d", &cartas[i][j].populacao) != 1 || cartas[i][j].populacao < 0) {
                printf("Entrada inválida! Insira um valor válido para população: ");
                while (getchar() != '\n');
            }

            printf("Área (em km²): ");
            while (scanf("%f", &cartas[i][j].area) != 1 || cartas[i][j].area <= 0) {
                printf("Entrada inválida! Insira um valor válido para área: ");
                while (getchar() != '\n');
            }

            printf("PIB (em milhões): ");
            while (scanf("%f", &cartas[i][j].pib) != 1 || cartas[i][j].pib < 0) {
                printf("Entrada inválida! Insira um valor válido para PIB: ");
                while (getchar() != '\n');
            }

            printf("Número de pontos turísticos: ");
            while (scanf("%d", &cartas[i][j].pontos_turisticos) != 1 || cartas[i][j].pontos_turisticos < 0) {
                printf("Entrada inválida! Insira um valor válido para pontos turísticos: ");
                while (getchar() != '\n');
            }

            calcular_propriedades(&cartas[i][j]);
        }
    }
}

void exibir_cartas(Carta cartas[MAX_ESTADOS][MAX_CIDADES], char *pais) {
    printf("\nCartas disponíveis para o país: %s\n", pais);
    for (int i = 0; i < MAX_ESTADOS; i++) {
        for (int j = 0; j < MAX_CIDADES; j++) {
            printf("Cidade %s - População: %d, Área: %.2f km², PIB: %.2f milhões, Pontos Turísticos: %d\n",
                   cartas[i][j].codigo, cartas[i][j].populacao, cartas[i][j].area,
                   cartas[i][j].pib, cartas[i][j].pontos_turisticos);
        }
    }
}

float calcular_super_poder(Carta carta) {
    return carta.populacao + carta.area + carta.pib + carta.pontos_turisticos;
}

int main() {
    Pais paises[MAX_PAÍSES];
    int total_paises = 0, opcao;

    printf("Bem-vindo ao Super Trunfo - Países!\n");

    // Cadastro inicial dos países
    do {
        printf("\nInsira o nome do país: ");
        while (getchar() != '\n'); // Limpa o buffer do stdin
        fgets(paises[total_paises].nome, 50, stdin);
        paises[total_paises].nome[strcspn(paises[total_paises].nome, "\n")] = '\0'; // Remove o caractere de nova linha

        printf("\nEscolha o método de entrada de dados:\n");
        printf("1 - Entrada manual\n");
        printf("2 - Entrada automática (aleatória)\n");
        printf("Opção: ");
        while (scanf("%d", &opcao) != 1 || (opcao != 1 && opcao != 2)) {
            printf("Entrada inválida! Escolha 1 para manual ou 2 para automática: ");
            while (getchar() != '\n');
        }

        if (opcao == 1) {
            entrada_manual(paises[total_paises].cartas);
        } else {
            entrada_automatica(paises[total_paises].cartas);
        }

        exibir_cartas(paises[total_paises].cartas, paises[total_paises].nome);
        total_paises++;

        printf("\nDeseja cadastrar outro país? (1 - Sim, 0 - Não): ");
        while (scanf("%d", &opcao) != 1 || (opcao != 0 && opcao != 1)) {
            printf("Entrada inválida! Escolha 1 para Sim ou 0 para Não: ");
            while (getchar() != '\n');
        }

    } while (opcao == 1 && total_paises < MAX_PAÍSES);

    // Configuração do jogo com 2 jogadores
    Jogador jogadores[MAX_JOGADORES];
    for (int i = 0; i < MAX_JOGADORES; i++) {
        printf("\nJogador_%d, insira seu nome: ", i + 1);
        while (getchar() != '\n');
        fgets(jogadores[i].nome, 50, stdin);
        jogadores[i].nome[strcspn(jogadores[i].nome, "\n")] = '\0';

        printf("\n%s, escolha um país:\n", jogadores[i].nome);
        for (int j = 0; j < total_paises; j++) {
            printf("%d - %s\n", j + 1, paises[j].nome);
        }

        int pais_escolhido;
        printf("Opção: ");
        while (scanf("%d", &pais_escolhido) != 1 || pais_escolhido < 1 || pais_escolhido > total_paises) {
            printf("Entrada inválida! Escolha um número entre 1 e %d: ", total_paises);
            while (getchar() != '\n');
        }

        printf("Escolha um estado de A a H: ");
        char estado;
        while (scanf(" %c", &estado) != 1 || estado < 'A' || estado > 'H') {
            printf("Entrada inválida! Escolha um estado de A a H: ");
            while (getchar() != '\n');
        }

        int estado_index = estado - 'A';

        printf("Escolha uma cidade (1 a 4): ");
        int cidade;
        while (scanf("%d", &cidade) != 1 || cidade < 1 || cidade > 4) {
            printf("Entrada inválida! Escolha uma cidade de 1 a 4: ");
            while (getchar() != '\n');
        }

        int cidade_index = cidade - 1;
        jogadores[i].carta_escolhida = paises[pais_escolhido - 1].cartas[estado_index][cidade_index];
        jogadores[i].super_poder = calcular_super_poder(jogadores[i].carta_escolhida);
        printf("\nVocê escolheu a carta: %s\n", jogadores[i].carta_escolhida.codigo);
    }

    // Determinar o vencedor
    int vencedor = (jogadores[0].super_poder > jogadores[1].super_poder) ? 0 : 1;
    printf("\nO vencedor é %s com a carta %s e um Super Poder de %.2f!\n",
           jogadores[vencedor].nome, jogadores[vencedor].carta_escolhida.codigo, jogadores[vencedor].super_poder);

    return 0;
}
