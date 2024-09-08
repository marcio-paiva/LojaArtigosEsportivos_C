#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "selecaoNatural.h"

// Função para comparar dois produtos (usada para ordenação)
int compararProdutos(const void *a, const void *b) {
    Produto *produtoA = (Produto *)a;
    Produto *produtoB = (Produto *)b;
    return produtoA->codigo - produtoB->codigo; // Comparar pelo código
}

// Função para criar o caminho completo para o arquivo de partição
char* criaCaminhoParticao(const char *pasta, int numero_particao) {
    char *caminho = malloc(256); // Tamanho aumentado para garantir espaço suficiente
    if (!caminho) {
        perror("Erro ao alocar memória para o caminho da partição");
        exit(EXIT_FAILURE);
    }
    snprintf(caminho, 256, "%s/particao%d.bin", pasta, numero_particao);
    return caminho;
}

// Função para criar uma nova partição com extensão .dat
void criaParticao(const char *pasta, int numero_particao) {
    char *caminho = criaCaminhoParticao(pasta, numero_particao);
    
    FILE *arquivo = fopen(caminho, "wb");
    if (!arquivo) {
        perror("Erro ao criar partição");
        free(caminho);
        exit(EXIT_FAILURE);
    }
    fclose(arquivo);
    
    free(caminho);
}

// Função para gravar registros em uma partição com extensão .dat
void gravaEmParticao(Produto *produtos, int num_produtos, const char *pasta, int numero_particao) {
    char *caminho = criaCaminhoParticao(pasta, numero_particao);
    
    FILE *arquivo = fopen(caminho, "ab");
    if (!arquivo) {
        perror("Erro ao abrir partição para gravação");
        free(caminho);
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < num_produtos; i++) {
        salvaProduto(&produtos[i], arquivo);
    }
    fclose(arquivo);
    
    free(caminho);
}

// Função para processar e armazenar registros usando o algoritmo de Seleção Natural
void selecaoNatural(FILE *arq_prod, const char *pasta_particoes, int M) {
    int numero_particao = 0;
    Produto *buffer = malloc(M * sizeof(Produto));
    Produto *reservatorio = malloc(M * sizeof(Produto));
    if (!buffer || !reservatorio) {
        perror("Erro ao alocar memória");
        exit(EXIT_FAILURE);
    }

    int num_reservatorio = 0; // Contador para o número de registros no reservatório
    int num_buffer = 0; // Contador para o número de registros no buffer

    // Primeiro, leia M registros do arquivo de entrada para o buffer
    while (1) {
        num_buffer = fread(buffer, sizeof(Produto), M, arq_prod);
        if (num_buffer == 0) {
            // Se o arquivo de entrada acabou e ainda há registros no reservatório, grave-os
            if (num_reservatorio > 0) {
                criaParticao(pasta_particoes, numero_particao);
                gravaEmParticao(reservatorio, num_reservatorio, pasta_particoes, numero_particao);
                numero_particao++;
            }
            break;
        }

        // Ordena o buffer com base na chave do produto
        qsort(buffer, num_buffer, sizeof(Produto), compararProdutos);

        // Processa registros do buffer
        for (int i = 0; i < num_buffer; i++) {
            Produto *r = &buffer[i];

            // Caso o reservatório esteja cheio, grave-o e inicie um novo
            if (num_reservatorio >= M) {
                criaParticao(pasta_particoes, numero_particao);
                gravaEmParticao(reservatorio, num_reservatorio, pasta_particoes, numero_particao);
                numero_particao++;
                num_reservatorio = 0; // Esvazia o reservatório
            }

            // Grava o registro com a menor chave na partição
            criaParticao(pasta_particoes, numero_particao);
            gravaEmParticao(r, 1, pasta_particoes, numero_particao);
            
            // Lê o próximo registro do arquivo
            Produto proximo;
            size_t lidos = fread(&proximo, sizeof(Produto), 1, arq_prod);
            if (lidos == 1 && proximo.codigo < r->codigo) {
                // Se o próximo registro tem uma chave menor, adicione-o ao reservatório
                reservatorio[num_reservatorio++] = proximo;
            }
        }
    }
    
    // Se houver registros restantes no reservatório, grave-os
    if (num_reservatorio > 0) {
        criaParticao(pasta_particoes, numero_particao);
        gravaEmParticao(reservatorio, num_reservatorio, pasta_particoes, numero_particao);
    }

    printf("Selecao Natural concluida com sucesso.\n");

    free(buffer); // Libera a memória alocada para o buffer
    free(reservatorio); // Libera a memória alocada para o reservatório
}
