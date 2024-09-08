#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "loja.h"
#include "buscaSequencial.h"

Produto* buscaSequencialProduto(int chave, FILE *in) {
    Produto *f;
    int comparacoes = 0; // Inicializa o contador de comparações
    int achou = 0;
    rewind(in);

    while ((f = leProduto(in)) != NULL) {
        comparacoes++; // Conta a comparação realizada

        if (f->codigo == chave) {
            achou = 1;
            break;
        }
    }

    if (achou == 1) {
        printf("\nNumero de comparacoes: %d\n", comparacoes); // Imprime o número de comparações
        return f;
    } else {
        printf("\nProduto nao encontrado\n\n");
        printf("\nNumero de comparacoes: %d\n", comparacoes); // Imprime o número de comparações se não encontrar
    }

    free(f);
    return NULL; // Retorna NULL se não encontrar
}

Cliente* buscaSequencialCliente(int chave, FILE *in) {
    Cliente *f;
    int comparacoes = 0; // Inicializa o contador de comparações
    int achou = 0;
    rewind(in);

    while ((f = leCliente(in)) != NULL) {
        comparacoes++; // Conta a comparação realizada

        if (f->codigo == chave) {
            achou = 1;
            break;
        }
    }

    if (achou == 1) {
        printf("\nNumero de comparacoes: %d\n", comparacoes); // Imprime o número de comparações
        return f;
    } else {
        printf("\nCliente nao encontrado\n\n");
        printf("\nNumero de comparacoes: %d\n", comparacoes); 
    }

    free(f);
    return NULL; // Retorna NULL se não encontrar
}

Pedido* buscaSequencialPedido(int chave, FILE *in) {
    Pedido *f;
    int comparacoes = 0; // Inicializa o contador de comparações
    int achou = 0;
    rewind(in);

    while ((f = lePedido(in)) != NULL) {
        comparacoes++; // Conta a comparação realizada

        if (f->codigo == chave) {
            achou = 1;
            break;
        }
    }

    if (achou == 1) {
        printf("\nNumero de comparacoes: %d\n", comparacoes); // Imprime o número de comparações
        return f;
    } else {
        printf("\nPedido nao encontrado\n\n");
        printf("\nNumero de comparacoes: %d\n", comparacoes); 
    }

    free(f);
    return NULL; // Retorna NULL se não encontrar
}