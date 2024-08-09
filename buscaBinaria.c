#include "buscaBinaria.h"
#include "loja.h"
#include <stdio.h>
#include <stdlib.h>

Produto* buscaBinariaProduto(int chave, FILE *in, int tam) {
    int achou = 0;
    int comparacoes = 0; 
    int esq = 0;
    int dir = tam - 1;
    Produto *f = NULL;
    
    while (esq <= dir) {
        int meio = (esq + dir) / 2;

        fseek(in, meio * tamanhoRegistroProduto(), SEEK_SET); // Move o ponteiro do arquivo para o meio
        f = leProduto(in);
        comparacoes++; 

        if (f->codigo == chave) {
            achou = 1;
            printf("Numero de comparacoes: %d\n", comparacoes); 
            return f;
        } else if (f->codigo < chave) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }

        free(f); // Libera o registro lido
    } 
     if(achou == 0){
        printf("Produto com codigo %d nao encontrado.\n", chave);
        printf("Numero de comparacoes: %d\n", comparacoes); 
        return NULL; // Retorna NULL se não encontrar
    
     }

    printf("Numero de comparacoes: %d\n", comparacoes); 
    return NULL; // Retorna NULL se não encontrar
}

Cliente* buscaBinariaCliente(int chave, FILE *in, int tam) {
    int achou = 0;
    int comparacoes = 0; 
    int esq = 0;
    int dir = tam - 1;
    Cliente *f = NULL;
    
    while (esq <= dir) {
        int meio = (esq + dir) / 2;
        
        fseek(in, meio * tamanhoRegistroCliente(), SEEK_SET); // Move o ponteiro do arquivo para o meio
        f = leCliente(in);
        comparacoes++;

        if (f->codigo == chave) {
            achou = 1;
            printf("Numero de comparacoes: %d\n", comparacoes); 
            return f;
        } else if (f->codigo < chave) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }

        free(f); // Libera o registro lido
    }
    if(achou == 0){
        printf("Produto com codigo %d nao encontrado.\n", chave);
        printf("Numero de comparacoes: %d\n", comparacoes); 
        return NULL; // Retorna NULL se não encontrar
    
     }

    printf("Numero de comparacoes: %d\n", comparacoes); 
    return NULL; 
}

Pedido* buscaBinariaPedido(int chave, FILE *in, int tam) {
    int achou = 0;
    int comparacoes = 0; 
    int esq = 0;
    int dir = tam - 1;
    Pedido *f = NULL;
    
    while (esq <= dir) {
        int meio = (esq + dir) / 2;
        
        fseek(in, meio * tamanhoRegistroPedido(), SEEK_SET); // Move o ponteiro do arquivo para o meio
        f = lePedido(in);
        comparacoes++; 

        if (f->codigo == chave) {
            achou = 1;
            printf("Numero de comparacoes: %d\n", comparacoes);
            return f;
        } else if (f->codigo < chave) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }

        free(f); // Libera o registro lido
    }
    if(achou == 0){
        printf("Produto com codigo %d nao encontrado.\n", chave);
        printf("Numero de comparacoes: %d\n", comparacoes); 
        return NULL; // Retorna NULL se não encontrar
    }

    printf("Numero de comparacoes: %d\n", comparacoes); 
    return NULL; 
}