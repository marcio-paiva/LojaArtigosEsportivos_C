#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "loja.h"
#include "buscaSequencial.h"

//Realiza uma busca sequencial por um produto na base de dados
Produto *buscaSequencialProduto(int chave, FILE *in){

    Produto *f;
    int achou = 0;
    rewind(in);

    while ((f = leProduto(in)) != NULL){

        if(f->codigo == chave){
           achou = 1;
           break;
        }
    }
        if(achou == 1)
            return f;
        else printf("\nProduto nao encontrado");

    free(f);
    return NULL; // Retorna NULL se não encontrar
}

//Realiza uma busca sequencial por um cliente na base de dados
Cliente *buscaSequencialCliente(int chave, FILE *in){

    Cliente *f;
    int achou = 0;
    rewind(in);

    while ((f = leCliente(in)) != NULL){

        if(f->codigo == chave){
           achou = 1;
           break;
        }
    }
        if(achou == 1)
            return f;
        else printf("\nCliente nao encontrado");

    free(f);
    return NULL; // Retorna NULL se não encontrar
}