#ifndef BUSCASEQUENCIAL_H_INCLUDED
#define BUSCASEQUENCIAL_H_INCLUDED

#include <stdio.h>
#include "loja.h"

//Realiza uma busca sequencial por um funcionario na base de dados

Produto *buscaSequencialProduto(int chave, FILE *in);
Cliente *buscaSequencialCliente(int chave, FILE *in);


#endif // BUSCASEQUENCIAL_H_INCLUDED