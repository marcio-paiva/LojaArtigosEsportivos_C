#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intercalacao.h"

#define TAM_CIN 256 // Tamanho do buffer para o nome dos arquivos

// Função para abrir o próximo arquivo de partição e obter o arquivo e o buffer de produto
FILE* abreProximoArquivo(FILE **arquivos, const char *pasta_particoes, int *indice, int num_particoes) {
    if (*indice >= num_particoes) return NULL;

    char caminho[TAM_CIN];
    snprintf(caminho, TAM_CIN, "%s/particao%d.dat", pasta_particoes, *indice);

    FILE *arquivo = fopen(caminho, "rb");
    if (!arquivo) {
        perror("Erro ao abrir partição");
        exit(EXIT_FAILURE);
    }

    printf("Partição aberta: %s\n", caminho); // Mensagem de depuração
    (*indice)++;
    return arquivo;
}

// Função para encontrar o menor registro entre os arquivos abertos
int encontraMenorRegistro(FILE **arquivos, Produto *menor_registro, int num_arquivos) {
    int encontrou = 0;
    int indice_menor = -1;

    for (int i = 0; i < num_arquivos; i++) {
        if (feof(arquivos[i])) continue;

        Produto registro_atual;
        if (fread(&registro_atual, sizeof(Produto), 1, arquivos[i]) != 1) {
            continue;
        }

        printf("Lido do arquivo %d: %d\n", i, registro_atual.codigo); // Mensagem de depuração

        if (!encontrou || registro_atual.codigo < menor_registro->codigo) {
            *menor_registro = registro_atual;
            indice_menor = i;
            encontrou = 1;
        }
    }

    // Se algum registro foi encontrado, ler o próximo registro do arquivo com o menor registro
    if (encontrou && indice_menor != -1) {
        if (feof(arquivos[indice_menor])) {
            fclose(arquivos[indice_menor]);
            arquivos[indice_menor] = NULL;
            printf("Arquivo %d fechado porque está no final\n", indice_menor); // Mensagem de depuração
            num_arquivos--;
        }
    }

    return encontrou;
}

// Função para intercalação das partições
void intercalaParticoes(const char *pasta_particoes, int num_particoes, FILE *arq_saida) {
    FILE *arquivos[num_particoes];
    int num_arquivos_abertos = 0;
    int indice_particao = 0;

    // Inicializa os arquivos
    for (int i = 0; i < num_particoes; i++) {
        FILE *arquivo = abreProximoArquivo(arquivos, pasta_particoes, &indice_particao, num_particoes);
        if (arquivo) {
            arquivos[num_arquivos_abertos++] = arquivo;
        }
    }

    if (num_arquivos_abertos == 0) {
        printf("Nenhum arquivo de partição foi aberto.\n");
        return;
    }

    Produto menor_registro;
    while (encontraMenorRegistro(arquivos, &menor_registro, num_arquivos_abertos)) {
        printf("Escrevendo registro: %d\n", menor_registro.codigo); // Mensagem de depuração
        fwrite(&menor_registro, sizeof(Produto), 1, arq_saida);
    }

    // Fecha todos os arquivos restantes
    for (int i = 0; i < num_arquivos_abertos; i++) {
        if (arquivos[i]) {
            fclose(arquivos[i]);
        }
    }

    printf("Intercalacao concluida com sucesso.\n");
}
