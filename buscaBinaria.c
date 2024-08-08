#include "buscaBinaria.h"
#include "loja.h"
#include <stdio.h>
#include <stdlib.h>

Produto *buscaBinariaProduto(int chave, FILE *in, int tam) {
    int esq = 0;
    int dir = tam - 1;
    Produto *f = NULL;
    
    while (esq <= dir) {
        int meio = (esq + dir) / 2;

        // Move o ponteiro do arquivo para o meio
        fseek(in, meio * tamanhoRegistroProduto(), SEEK_SET);
        f = leProduto(in);

        if (f->codigo == chave) {
            return f;
        } else if (f->codigo < chave) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }

        free(f); // Libera o registro lido
    }

    return NULL; // Retorna NULL se não encontrar
}

Cliente *buscaBinariaCliente(int chave, FILE *in, int tam) {
    int esq = 0;
    int dir = tam - 1;
    Cliente *f = NULL;
    
    while (esq <= dir) {
        int meio = (esq + dir) / 2;
        // Move o ponteiro do arquivo para o meio
        fseek(in, meio * tamanhoRegistroCliente(), SEEK_SET);
        f = leCliente(in);

        if (f->codigo == chave) {
            return f;
        } else if (f->codigo < chave) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }

        free(f); // Libera o registro lido
    }

    return NULL; // Retorna NULL se não encontrar
}