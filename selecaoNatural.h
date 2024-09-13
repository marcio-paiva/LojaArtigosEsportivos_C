#ifndef SELECAONATURAL_H
#define SELECAONATURAL_H

#include <stdio.h>
#include "loja.h"

// Função principal para ordenar um arquivo usando o algoritmo de Seleção Natural
int selecaoNaturalProdutos(FILE *arquivo_entrada, int M);

int selecaoNaturalClientes(FILE *arquivo_entrada, int M);

int selecaoNaturalPedidos(FILE *arquivo_entrada, int M);

#endif // SELECAONATURAL_H
