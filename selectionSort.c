#include "selectionsort.h"
#include "loja.h"
#include <stdlib.h>
#include <stdio.h>

void selectionSortProdutos(FILE *arq, int tam) {
    int i, j, min_idx;
    Produto *fi, *fj, *fmin;

    for (i = 0; i < tam - 1; i++) {
        min_idx = i;

        // Lê o registro no índice i e assume que é o menor
        fseek(arq, i * tamanhoRegistroProduto(), SEEK_SET);
        fmin = leProduto(arq);

        if (fmin == NULL) {
            perror("Erro ao ler o registro no índice i");
            return;
        }

        for (j = i + 1; j < tam; j++) {
            fseek(arq, j * tamanhoRegistroProduto(), SEEK_SET);
            fj = leProduto(arq);

            if (fj == NULL) {
                perror("Erro ao ler o registro no índice j");
                free(fmin);
                return;
            }

            if (fj->codigo < fmin->codigo) {
                min_idx = j;
                free(fmin);
                fmin = fj;
            } else {
                free(fj);
            }
        }

        // Se min_idx não for o índice atual, trocamos os registros
        if (min_idx != i) {
            fseek(arq, i * tamanhoRegistroProduto(), SEEK_SET);
            fi = leProduto(arq);

            if (fi == NULL) {
                perror("Erro ao ler o registro no índice i para troca");
                free(fmin);
                return;
            }

            // Salva o menor valor na posição i
            fseek(arq, i * tamanhoRegistroProduto(), SEEK_SET);
            salvaProduto(fmin, arq);

            // Salva o valor original na posição min_idx
            fseek(arq, min_idx * tamanhoRegistroProduto(), SEEK_SET);
            salvaProduto(fi, arq);

            free(fi);
        }

        free(fmin);
    }

    // Descarrega o buffer para ter certeza que dados foram gravados
    fflush(arq);
}

void selectionSortClientes(FILE *arq, int tam) {
    int i, j, min_idx;
    Cliente *fi, *fj, *fmin;

    for (i = 0; i < tam - 1; i++) {
        min_idx = i;

        // Lê o registro no índice i e assume que é o menor
        fseek(arq, i * tamanhoRegistroCliente(), SEEK_SET);
        fmin = leCliente(arq);

        if (fmin == NULL) {
            perror("Erro ao ler o registro no índice i");
            return;
        }

        for (j = i + 1; j < tam; j++) {
            fseek(arq, j * tamanhoRegistroCliente(), SEEK_SET);
            fj = leCliente(arq);

            if (fj == NULL) {
                perror("Erro ao ler o registro no índice j");
                free(fmin);
                return;
            }

            if (fj->codigo < fmin->codigo) {
                min_idx = j;
                free(fmin);
                fmin = fj;
            } else {
                free(fj);
            }
        }

        // Se min_idx não for o índice atual, trocamos os registros
        if (min_idx != i) {
            fseek(arq, i * tamanhoRegistroCliente(), SEEK_SET);
            fi = leCliente(arq);

            if (fi == NULL) {
                perror("Erro ao ler o registro no índice i para troca");
                free(fmin);
                return;
            }

            // Salva o menor valor na posição i
            fseek(arq, i * tamanhoRegistroCliente(), SEEK_SET);
            salvaCliente(fmin, arq);

            // Salva o valor original na posição min_idx
            fseek(arq, min_idx * tamanhoRegistroCliente(), SEEK_SET);
            salvaCliente(fi, arq);

            free(fi);
        }

        free(fmin);
    }
    // Descarrega o buffer para ter certeza que dados foram gravados
    fflush(arq);
}

void selectionSortPedidos(FILE *arq, int tam) {
    int i, j, min_idx;
    Pedido *fi, *fj, *fmin;

    for (i = 0; i < tam - 1; i++) {
        min_idx = i;

        // Lê o registro no índice i e assume que é o menor
        fseek(arq, i * tamanhoRegistroPedido(), SEEK_SET);
        fmin = lePedido(arq);

        if (fmin == NULL) {
            perror("Erro ao ler o registro no índice i");
            return;
        }

        for (j = i + 1; j < tam; j++) {
            fseek(arq, j * tamanhoRegistroPedido(), SEEK_SET);
            fj = lePedido(arq);

            if (fj == NULL) {
                perror("Erro ao ler o registro no índice j");
                free(fmin);
                return;
            }

            if (fj->codigo < fmin->codigo) {
                min_idx = j;
                free(fmin);
                fmin = fj;
            } else {
                free(fj);
            }
        }

        // Se min_idx não for o índice atual, trocamos os registros
        if (min_idx != i) {
            fseek(arq, i * tamanhoRegistroPedido(), SEEK_SET);
            fi = lePedido(arq);

            if (fi == NULL) {
                perror("Erro ao ler o registro no índice i para troca");
                free(fmin);
                return;
            }

            fseek(arq, i * tamanhoRegistroPedido(), SEEK_SET);
            salvaPedido(fmin, arq);

            fseek(arq, min_idx * tamanhoRegistroPedido(), SEEK_SET);
            salvaPedido(fi, arq);

            free(fi);
        }

        free(fmin);
    }
    // Descarrega o buffer para ter certeza que dados foram gravados
    fflush(arq);
}