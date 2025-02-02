#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_ESTADOS 8
#define MAX_CIDADES 4
#define MAX_PAISES 10

typedef struct {
    char nome_pais[50];
    char nome_estado[3];
    char codigo_cidade[3];
    int populacao;
    float area;
    float pib;
    int pontos_turisticos;
} Dados;

void gerar_dados_aleatorios(Dados matriz_dados[MAX_ESTADOS][MAX_CIDADES], const char* nome_pais) {
    for (int est = 0; est < MAX_ESTADOS; est++) {
        for (int cid = 0; cid < MAX_CIDADES; cid++) {
            strcpy(matriz_dados[est][cid].nome_pais, nome_pais);
            matriz_dados[est][cid].populacao = 100000 + rand() % 900000;
            matriz_dados[est][cid].area = (100000 + rand() % 900000) / 100.0;
            matriz_dados[est][cid].pib = (100000 + rand() % 900000) / 100.0;
            matriz_dados[est][cid].pontos_turisticos = 100000 + rand() % 900000;
        }
        sprintf(matriz_dados[est][0].nome_estado, "%c", 'A' + est);
    }
}

void exibir_dados(Dados paises[][MAX_ESTADOS][MAX_CIDADES], int total_paises) {
    for (int p = 0; p < total_paises; p++) {
        printf("Dados do país: %s\n", paises[p][0][0].nome_pais);
        for (int est = 0; est < MAX_ESTADOS; est++) {
            for (int cid = 0; cid < MAX_CIDADES; cid++) {
                printf("%s_%s%02d: Populacao: %d, Area: %.2f, PIB: %.2f, Pontos Turisticos: %d\n", 
                    paises[p][est][cid].nome_pais, paises[p][est][0].nome_estado, cid + 1,
                    paises[p][est][cid].populacao, paises[p][est][cid].area,
                    paises[p][est][cid].pib, paises[p][est][cid].pontos_turisticos);
            }
        }
        printf("\n");
    }
}

char obter_resposta(const char* mensagem) {
    char resposta;
    while (1) {
        printf("%s (Y/N): ", mensagem);
        getchar(); // Limpar o buffer
        scanf("%c", &resposta);
        resposta = toupper(resposta);
        if (resposta == 'Y' || resposta == 'N') {
            return resposta;
        } else {
            printf("Você deve responder apenas Y/N. Deseja tentar novamente? (Y/N): ");
            getchar(); // Limpar o buffer
            scanf("%c", &resposta);
            resposta = toupper(resposta);
            if (resposta == 'N') {
                exit(1); // Sai do programa se o usuário não quiser tentar novamente
            }
        }
    }
}

int main() {
    Dados paises[MAX_PAISES][MAX_ESTADOS][MAX_CIDADES];
    int total_paises = 0;
    char continuar = 'Y';

    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    while (continuar == 'Y' && total_paises < MAX_PAISES) {
        // Entrada de dados do nome do país
        printf("Digite o nome do país: ");
        scanf("%s", paises[total_paises][0][0].nome_pais);

        // Pergunta se o preenchimento deve ser automático para todos os dados
        char resposta_automatica = obter_resposta("Deseja preenchimento automático para o país");

        if (resposta_automatica == 'Y') {
            gerar_dados_aleatorios(paises[total_paises], paises[total_paises][0][0].nome_pais);
        } else {
            // Loop para os estados de A a H
            for (int est = 0; est < MAX_ESTADOS; est++) {
                sprintf(paises[total_paises][est][0].nome_estado, "%c", 'A' + est);

                // Loop para as cidades de 1 a 4
                for (int cid = 0; cid < MAX_CIDADES; cid++) {
                    sprintf(paises[total_paises][est][cid].codigo_cidade, "%1d", cid + 1);

                    // Solicita dados adicionais ao usuário para cada cidade
                    printf("Digite a populacao da cidade %s_%s%02d: ",
                           paises[total_paises][0][0].nome_pais, paises[total_paises][est][0].nome_estado, cid + 1);
                    scanf("%d", &paises[total_paises][est][cid].populacao);

                    printf("Digite a area da cidade %s_%s%02d: ",
                           paises[total_paises][0][0].nome_pais, paises[total_paises][est][0].nome_estado, cid + 1);
                    scanf("%f", &paises[total_paises][est][cid].area);

                    printf("Digite o PIB da cidade %s_%s%02d: ",
                           paises[total_paises][0][0].nome_pais, paises[total_paises][est][0].nome_estado, cid + 1);
                    scanf("%f", &paises[total_paises][est][cid].pib);

                    printf("Digite o numero de pontos turisticos da cidade %s_%s%02d: ",
                           paises[total_paises][0][0].nome_pais, paises[total_paises][est][0].nome_estado, cid + 1);
                    scanf("%d", &paises[total_paises][est][cid].pontos_turisticos);
                }
            }
        }

        // Incrementa o total de países cadastrados
        total_paises++;

        // Pergunta se deseja cadastrar mais
        continuar = obter_resposta("Deseja cadastrar mais alguma entrada");

        // Se o usuário responder "N", exibe todos os dados
        if (continuar == 'N') {
            exibir_dados(paises, total_paises);
        }
    }

    return 0;
}
