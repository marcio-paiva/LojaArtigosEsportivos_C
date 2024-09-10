#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "selecaoNatural.h"

//Função para colocar o produto com menor código na primeira posição (selection sort simplificado - sem laço externo)
void colocaMenorNaPrimeiraPosicao(Produto **buffer, int tam) {
    int i, min_idx = 0;
    Produto *temp;

    // Encontra o menor elemento no array
    for (i = 1; i < tam; i++) {
        if (buffer[i]->codigo < buffer[min_idx]->codigo) {
            min_idx = i; // Atualiza o índice do menor produto
        }
    }

    // Troca o menor elemento encontrado com o primeiro elemento
    if (min_idx != 0) {
        temp = buffer[0];
        buffer[0] = buffer[min_idx];
        buffer[min_idx] = temp;
    }
}

int selecaoNatural(FILE *arq_prod, int M) {
    int qtd_particoes = 0, qtd_buffer = 0, qtd_reservatorio = 0, endereco_entrada = 0;
    Produto *buffer[M], *reservatorio[M], *produto_auxiliar;
    char nome_particao[100];

    rewind(arq_prod);
    for (endereco_entrada = 0; endereco_entrada < M; endereco_entrada++) { // Preenchendo o buffer inicial
        produto_auxiliar = leProduto(arq_prod);
        if (produto_auxiliar == NULL) {
            qtd_buffer = endereco_entrada;
            break;
        }
        buffer[endereco_entrada] = produto_auxiliar;
        qtd_buffer++;
    }

    colocaMenorNaPrimeiraPosicao(buffer, qtd_buffer);

    sprintf(nome_particao, "particoes/particao%d.dat", qtd_particoes++); // Cria uma nova partição para os registros ordenados
    FILE *particao_atual = fopen(nome_particao, "wb");

    salvaProduto(buffer[0], particao_atual); // Grava o registro com menor chave na partição
    free(buffer[0]); // Liberar o registro gravado

    for (int k = 1; k < qtd_buffer; k++) { // Movendo o restante dos registros no buffer para frente
        buffer[k - 1] = buffer[k];
    }
    qtd_buffer--; // Atualiza a quantidade de registros no buffer

    while ((produto_auxiliar = leProduto(arq_prod)) != NULL) { // Processamento dos registros restantes
        endereco_entrada++;

        if (produto_auxiliar->codigo < buffer[0]->codigo) {
            reservatorio[qtd_reservatorio++] = produto_auxiliar; // Adicionar ao reservatório
            if (qtd_reservatorio == M) { // Se o reservatório está cheio
                while (qtd_buffer > 0) {
                    colocaMenorNaPrimeiraPosicao(buffer, qtd_buffer);
                    salvaProduto(buffer[0], particao_atual);
                    free(buffer[0]); // Libera o registro que foi gravado

                    for (int k = 1; k < qtd_buffer; k++) { // Movendo o restante dos registros no buffer para frente
                        buffer[k - 1] = buffer[k];
                    }
                    qtd_buffer--;
                }
                fclose(particao_atual);
                
                for (int j = 0; j < qtd_reservatorio; j++) { // Passa registros do reservatório para o buffer
                    buffer[j] = reservatorio[j];
                    reservatorio[j] = NULL; // Limpa o reservatório
                }
                qtd_buffer = qtd_reservatorio;
                qtd_reservatorio = 0;
                
                sprintf(nome_particao, "particoes/particao%d.dat", qtd_particoes++); // Criar nova partição
                particao_atual = fopen(nome_particao, "wb");
            }
        } else {
            buffer[qtd_buffer] = produto_auxiliar;  // Adiciona ao final do buffer
            qtd_buffer++;
            colocaMenorNaPrimeiraPosicao(buffer, qtd_buffer); // Ordena o buffer
            salvaProduto(buffer[0], particao_atual); // Grava o menor registro
            free(buffer[0]); // Libera o registro gravado
            for (int k = 1; k < qtd_buffer; k++) { // Movendo o restante dos registros no buffer para frente
                buffer[k - 1] = buffer[k];
            }
            qtd_buffer--;
        }
    }

    // Grava o restante dos registros do buffer
    while (qtd_buffer > 0) {
        colocaMenorNaPrimeiraPosicao(buffer, qtd_buffer); // Ordena o buffer
        salvaProduto(buffer[0], particao_atual); // Grava o menor registro
        free(buffer[0]); // Libera o registro gravado
        for (int k = 1; k < qtd_buffer; k++) { // Movendo o restante dos registros no buffer para frente
            buffer[k - 1] = buffer[k];
        }
        qtd_buffer--;
    }

    // Grava o restante do reservatório na última partição
    if (qtd_reservatorio > 0) {
        fclose(particao_atual);
        sprintf(nome_particao, "particoes/particao%d.dat", qtd_particoes++);
        particao_atual = fopen(nome_particao, "wb");

        while(qtd_reservatorio > 0){
            colocaMenorNaPrimeiraPosicao(reservatorio, qtd_reservatorio);
            salvaProduto(reservatorio[0], particao_atual);
            free(reservatorio[0]); // Libera o registro gravado
            for (int k = 1; k < qtd_reservatorio; k++) {
                reservatorio[k - 1] = reservatorio[k];
            }
            qtd_reservatorio--;
        }
    }

    fclose(particao_atual);

    return qtd_particoes;
}

