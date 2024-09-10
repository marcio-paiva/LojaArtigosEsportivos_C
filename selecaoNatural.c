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
    snprintf(caminho, 256, "%s/particao%d.dat", pasta, numero_particao);
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
int selecaoNatural(FILE *arq_prod, const char *pasta_particoes, int M) {
    rewind(arq_prod);
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
                gravaEmParticao(reservatorio, num_reservatorio, pasta_particoes, numero_particao);
            }
            break;
        }

        // Ordena o buffer com base na chave do produto
        qsort(buffer, num_buffer, sizeof(Produto), compararProdutos);

        // Cria uma nova partição para os registros ordenados
        criaParticao(pasta_particoes, numero_particao++);
        
        // Processa registros do buffer
        for (int i = 0; i < num_buffer; i++) {
            Produto *r = &buffer[i];

            // Grava o registro com a menor chave na partição
            gravaEmParticao(r, 1, pasta_particoes, numero_particao - 1);

            // Lê o próximo registro do arquivo
            Produto proximo;
            size_t lidos = fread(&proximo, sizeof(Produto), 1, arq_prod);
            if (lidos == 1) {
                if (proximo.codigo < r->codigo) {
                    // Se o próximo registro tem uma chave menor, adicione-o ao reservatório
                    if (num_reservatorio < M) {
                        reservatorio[num_reservatorio++] = proximo;
                    }
                } else {
                    // Substitui o registro r no buffer pelo próximo registro
                    buffer[i] = proximo;
                }
            }
        }

        // Se o reservatório estiver cheio, grave-o e substitua o buffer
        if (num_reservatorio >= M) {
            // Grave os registros restantes do buffer na partição de saída
            for (int i = 0; i < num_buffer; i++) {
                gravaEmParticao(&buffer[i], 1, pasta_particoes, numero_particao - 1);
            }

            // Copia os registros do reservatório para o buffer
            int num_para_buffer = num_reservatorio;
            if (num_para_buffer > M) num_para_buffer = M; // Limita ao tamanho do buffer
            memcpy(buffer, reservatorio, num_para_buffer * sizeof(Produto));

            // Atualiza o número de registros no buffer
            num_buffer = num_para_buffer;

            // Esvazia o reservatório
            num_reservatorio = 0;

            // Cria uma nova partição para os registros ordenados
            criaParticao(pasta_particoes, numero_particao++);
        }
    }

    // Se houver registros restantes no reservatório, grave-os
    if (num_reservatorio > 0) {
        gravaEmParticao(reservatorio, num_reservatorio, pasta_particoes, numero_particao);
    }

    printf("Selecao Natural concluída com sucesso.\n");

    free(buffer); // Libera a memória alocada para o buffer
    free(reservatorio); // Libera a memória alocada para o reservatório

    return numero_particao;
}

