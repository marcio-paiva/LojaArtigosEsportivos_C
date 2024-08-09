#include "selectionsort.h"
#include "loja.h"
#include <stdlib.h>
#include <stdio.h>

void selectionSortProdutos(FILE *arq, int tam) {
    int i, j, min_idx;
    Produto *fi, *fj, *fmin;

    for (i = 0; i < tam - 1; i++) {
        min_idx = i; // Assume o índice atual como o menor

        fseek(arq, i * tamanhoRegistroProduto(), SEEK_SET); // Posiciona o ponteiro no início do índice i
        fmin = leProduto(arq); // Lê o produto no índice i

        for (j = i + 1; j < tam; j++) {
            fseek(arq, j * tamanhoRegistroProduto(), SEEK_SET); // Posiciona o ponteiro no índice j
            fj = leProduto(arq); // Lê o produto no índice j

            if (fj->codigo < fmin->codigo) { // Verifica se o produto no índice j é menor
                min_idx = j; // Atualiza o índice do menor produto
                free(fmin); // Libera o produto anterior
                fmin = fj; // Atualiza o menor produto
            } else {
                free(fj); // Libera o produto que não é menor
            }
        }

        if (min_idx != i) {
            fseek(arq, i * tamanhoRegistroProduto(), SEEK_SET); // Posiciona o ponteiro no início do índice i
            fi = leProduto(arq); // Lê o produto no índice i para troca

            fseek(arq, i * tamanhoRegistroProduto(), SEEK_SET); // Posiciona o ponteiro no índice i
            salvaProduto(fmin, arq); // Salva o menor produto na posição i

            fseek(arq, min_idx * tamanhoRegistroProduto(), SEEK_SET); // Posiciona o ponteiro no índice min_idx
            salvaProduto(fi, arq); // Salva o produto original na posição min_idx

            free(fi); // Libera o produto que foi substituído
        }

        free(fmin); // Libera o menor produto
    }

    fflush(arq); // Descarrega o buffer para garantir que os dados foram gravados
}

void selectionSortClientes(FILE *arq, int tam) {
    int i, j, min_idx;
    Cliente *fi, *fj, *fmin;

    for (i = 0; i < tam - 1; i++) {
        min_idx = i; // Assume o índice atual como o menor

        fseek(arq, i * tamanhoRegistroCliente(), SEEK_SET); // Posiciona o ponteiro no início do índice i
        fmin = leCliente(arq); // Lê o cliente no índice i

        for (j = i + 1; j < tam; j++) {
            fseek(arq, j * tamanhoRegistroCliente(), SEEK_SET); // Posiciona o ponteiro no índice j
            fj = leCliente(arq); // Lê o cliente no índice j

            if (fj->codigo < fmin->codigo) { // Verifica se o cliente no índice j é menor
                min_idx = j; // Atualiza o índice do menor cliente
                free(fmin); // Libera o cliente anterior
                fmin = fj; // Atualiza o menor cliente
            } else {
                free(fj); // Libera o cliente que não é menor
            }
        }

        if (min_idx != i) {
            fseek(arq, i * tamanhoRegistroCliente(), SEEK_SET); // Posiciona o ponteiro no início do índice i
            fi = leCliente(arq); // Lê o cliente no índice i para troca

            fseek(arq, i * tamanhoRegistroCliente(), SEEK_SET); // Posiciona o ponteiro no índice i
            salvaCliente(fmin, arq); // Salva o menor cliente na posição i

            fseek(arq, min_idx * tamanhoRegistroCliente(), SEEK_SET); // Posiciona o ponteiro no índice min_idx
            salvaCliente(fi, arq); // Salva o cliente original na posição min_idx

            free(fi); // Libera o cliente que foi substituído
        }

        free(fmin); // Libera o menor cliente
    }

    fflush(arq); // Descarrega o buffer para garantir que os dados foram gravados
}

void selectionSortPedidos(FILE *arq, int tam) {
    int i, j, min_idx;
    Pedido *fi, *fj, *fmin;

    for (i = 0; i < tam - 1; i++) {
        min_idx = i; // Assume o índice atual como o menor

        fseek(arq, i * tamanhoRegistroPedido(), SEEK_SET); // Posiciona o ponteiro no início do índice i
        fmin = lePedido(arq); // Lê o pedido no índice i

        for (j = i + 1; j < tam; j++) {
            fseek(arq, j * tamanhoRegistroPedido(), SEEK_SET); // Posiciona o ponteiro no índice j
            fj = lePedido(arq); // Lê o pedido no índice j

            if (fj->codigo < fmin->codigo) { // Verifica se o pedido no índice j é menor
                min_idx = j; // Atualiza o índice do menor pedido
                free(fmin); // Libera o pedido anterior
                fmin = fj; // Atualiza o menor pedido
            } else {
                free(fj); // Libera o pedido que não é menor
            }
        }

        if (min_idx != i) {
            fseek(arq, i * tamanhoRegistroPedido(), SEEK_SET); // Posiciona o ponteiro no início do índice i
            fi = lePedido(arq); // Lê o pedido no índice i para troca

            fseek(arq, i * tamanhoRegistroPedido(), SEEK_SET); // Posiciona o ponteiro no índice i
            salvaPedido(fmin, arq); // Salva o menor pedido na posição i

            fseek(arq, min_idx * tamanhoRegistroPedido(), SEEK_SET); // Posiciona o ponteiro no índice min_idx
            salvaPedido(fi, arq); // Salva o pedido original na posição min_idx

            free(fi); // Libera o pedido que foi substituído
        }

        free(fmin); // Libera o menor pedido
    }

    fflush(arq); // Descarrega o buffer para garantir que os dados foram gravados
}