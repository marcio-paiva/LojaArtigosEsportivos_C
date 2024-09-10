#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "intercalacao.h"
#include "loja.h"

void intercalacaoOtima(int num_particoes, int M) {
    // Abrir todas as partições
    FILE *particoes[num_particoes];
    char nome_particao[100];
    for (int i = 0; i < num_particoes; i++) {
        sprintf(nome_particao, "particoes/particao%d.dat", i);
        particoes[i] = fopen(nome_particao, "rb");
    }

    // Buffer para manter os produtos atualmente sendo comparados em cada partição
    Produto *buffer[num_particoes];
    for (int i = 0; i < num_particoes; i++) {
        buffer[i] = leProduto(particoes[i]);  // Ler o primeiro produto de cada partição
    }

    // Abrir arquivo final para gravar os produtos intercalados
    FILE *arquivo_final = fopen("produtos.dat", "wb");

    int menor_indice;
    Produto *menor_produto;

    // Intercalar até que todos os produtos sejam gravados
    while (1) {
        menor_produto = NULL;
        menor_indice = -1;

        // Encontrar o menor produto entre as partições
        for (int i = 0; i < num_particoes; i++) {
            if (buffer[i] != NULL) {
                if (menor_produto == NULL || buffer[i]->codigo < menor_produto->codigo) {
                    menor_produto = buffer[i];
                    menor_indice = i;
                }
            }
        }

        // Se não há mais registros para intercalar, sair do loop
        if (menor_produto == NULL) {
            break;
        }

        // Grava o menor produto no arquivo final
        salvaProduto(menor_produto, arquivo_final);
        free(menor_produto);  // Liberar o menor produto gravado

        // Ler o próximo produto da partição que tinha o menor produto
        buffer[menor_indice] = leProduto(particoes[menor_indice]);
    }

    // Fechar todas as partições e o arquivo final
    for (int i = 0; i < num_particoes; i++) {
        fclose(particoes[i]);
    }
    fclose(arquivo_final);
}
