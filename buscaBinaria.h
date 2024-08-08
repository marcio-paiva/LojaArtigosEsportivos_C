#ifndef BUSCA_BINARIA_H
#define BUSCA_BINARIA_H

#include <stdio.h>
#include "loja.h"

// Protótipo da função de busca binária
Produto *buscaBinariaProduto(int chave, FILE *in, int tam);
Cliente *buscaBinariaCliente(int chave, FILE *in, int tam);
Pedido *buscaBinariaPedido(int chave, FILE *in, int tam);

#endif // BUSCA_BINARIA_H
