#ifndef SELECAONATURAL_H
#define SELECAONATURAL_H

#include <stdio.h>
#include "loja.h"
#include "selectionsort.h"

// Função principal para ordenar um arquivo usando o algoritmo de Seleção Natural
int selecaoNatural(FILE *arquivo_entrada, const char *pasta_particoes, int M);

#endif // SELECAONATURAL_H
