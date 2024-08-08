#include "buscaBinaria.h"
#include "loja.h"
#include <stdio.h>
#include <stdlib.h>

Produto* buscaBinariaProduto(int chave, FILE *in, int tam) {
    int comparacoes = 0; // Inicializa o contador de comparações
    int esq = 0;
    int dir = tam - 1;
    Produto *f = NULL;
    
    while (esq <= dir) {
        int meio = (esq + dir) / 2;

        // Move o ponteiro do arquivo para o meio
        fseek(in, meio * tamanhoRegistroProduto(), SEEK_SET);
        f = leProduto(in);

        comparacoes++; // Conta a comparação realizada

        if (f->codigo == chave) {
            free(f); // Libera o registro lido
            printf("Número de comparacoes: %d\n", comparacoes); // Imprime o número de comparações
            return f;
        } else if (f->codigo < chave) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }

        free(f); // Libera o registro lido
    }

    printf("Numero de comparacees: %d\n", comparacoes); // Imprime o número de comparações se não encontrar
    return NULL; // Retorna NULL se não encontrar
}

Cliente* buscaBinariaCliente(int chave, FILE *in, int tam) {
    int comparacoes = 0; // Inicializa o contador de comparações
    int esq = 0;
    int dir = tam - 1;
    Cliente *f = NULL;
    
    while (esq <= dir) {
        int meio = (esq + dir) / 2;
        // Move o ponteiro do arquivo para o meio
        fseek(in, meio * tamanhoRegistroCliente(), SEEK_SET);
        f = leCliente(in);

        comparacoes++; // Conta a comparação realizada

        if (f->codigo == chave) {
            free(f); // Libera o registro lido
            printf("Numero de comparacoes: %d\n", comparacoes); // Imprime o número de comparações
            return f;
        } else if (f->codigo < chave) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }

        free(f); // Libera o registro lido
    }

    printf("Número de comparacees: %d\n", comparacoes); 
    return NULL; 
}