#include "selectionsort.h"  
#include "loja.h"  
#include <stdlib.h>  // Inclui a biblioteca padrão para gerenciamento de memória e outras funções utilitárias
#include <stdio.h>  // Inclui a biblioteca padrão para operações de entrada e saída

void selectionSortProdutos(FILE *arq, int tam) {
    int i, j, min_idx;  // Declaração de variáveis para índices e posição do menor elemento
    Produto *fi, *fj, *fmin;  // Ponteiros para armazenar temporariamente os produtos durante a ordenação

    // Loop externo que percorre todos os elementos do arquivo
    for (i = 0; i < tam - 1; i++) {
        min_idx = i;  // Inicializa o índice do menor elemento com o índice atual

        // Lê o registro no índice i e assume que é o menor
        fseek(arq, i * tamanhoRegistroProduto(), SEEK_SET);  // Posiciona o ponteiro do arquivo no início do registro i
        fmin = leProduto(arq);  // Lê o produto do arquivo na posição i

        // Loop interno que percorre os elementos subsequentes ao índice i
        for (j = i + 1; j < tam; j++) {
            fseek(arq, j * tamanhoRegistroProduto(), SEEK_SET);  // Posiciona o ponteiro do arquivo no início do registro j
            fj = leProduto(arq);  // Lê o produto do arquivo na posição j

            // Compara os códigos dos produtos para encontrar o menor
            if (fj->codigo < fmin->codigo) {
                min_idx = j;  // Atualiza o índice do menor elemento
                free(fmin);  // Libera a memória do produto anteriormente considerado o menor
                fmin = fj;  // Atualiza o menor produto
            } else {
                free(fj);  // Libera a memória do produto fj se não for o menor
            }
        }

        // Se min_idx não for o índice atual, troca os registros
        if (min_idx != i) {
            fseek(arq, i * tamanhoRegistroProduto(), SEEK_SET);  // Posiciona o ponteiro do arquivo no início do registro i
            fi = leProduto(arq);  // Lê o produto do arquivo na posição i

            // Salva o menor valor na posição i
            fseek(arq, i * tamanhoRegistroProduto(), SEEK_SET);  // Posiciona o ponteiro do arquivo no início do registro i
            salvaProduto(fmin, arq);  // Salva o produto fmin na posição i

            // Salva o valor original na posição min_idx
            fseek(arq, min_idx * tamanhoRegistroProduto(), SEEK_SET);  // Posiciona o ponteiro do arquivo no início do registro min_idx
            salvaProduto(fi, arq);  // Salva o produto fi na posição min_idx

            free(fi);  // Libera a memória do produto fi
        }

        free(fmin);  // Libera a memória do menor produto
    }
    // Descarrega o buffer para ter certeza de que os dados foram gravados
    fflush(arq);  // Garante que todos os dados foram escritos no arquivo
}

void selectionSortClientes(FILE *arq, int tam) {
    int i, j, min_idx;  // Declaração de variáveis para índices e posição do menor elemento
    Cliente *fi, *fj, *fmin;  // Ponteiros para armazenar temporariamente os clientes durante a ordenação

    // Loop externo que percorre todos os elementos do arquivo
    for (i = 0; i < tam - 1; i++) {
        min_idx = i;  // Inicializa o índice do menor elemento com o índice atual

        // Lê o registro no índice i e assume que é o menor
        fseek(arq, i * tamanhoRegistroCliente(), SEEK_SET);  // Posiciona o ponteiro do arquivo no início do registro i
        fmin = leCliente(arq);  // Lê o cliente do arquivo na posição i

        // Loop interno que percorre os elementos subsequentes ao índice i
        for (j = i + 1; j < tam; j++) {
            fseek(arq, j * tamanhoRegistroCliente(), SEEK_SET);  // Posiciona o ponteiro do arquivo no início do registro j
            fj = leCliente(arq);  // Lê o cliente do arquivo na posição j

            // Compara os códigos dos clientes para encontrar o menor
            if (fj->codigo < fmin->codigo) {
                min_idx = j;  // Atualiza o índice do menor elemento
                free(fmin);  // Libera a memória do cliente anteriormente considerado o menor
                fmin = fj;  // Atualiza o menor cliente
            } else {
                free(fj);  // Libera a memória do cliente fj se não for o menor
            }
        }

        // Se min_idx não for o índice atual, troca os registros
        if (min_idx != i) {
            fseek(arq, i * tamanhoRegistroCliente(), SEEK_SET);  // Posiciona o ponteiro do arquivo no início do registro i
            fi = leCliente(arq);  // Lê o cliente do arquivo na posição i

            // Salva o menor valor na posição i
            fseek(arq, i * tamanhoRegistroCliente(), SEEK_SET);  // Posiciona o ponteiro do arquivo no início do registro i
            salvaCliente(fmin, arq);  // Salva o cliente fmin na posição i

            // Salva o valor original na posição min_idx
            fseek(arq, min_idx * tamanhoRegistroCliente(), SEEK_SET);  // Posiciona o ponteiro do arquivo no início do registro min_idx
            salvaCliente(fi, arq);  // Salva o cliente fi na posição min_idx

            free(fi);  // Libera a memória do cliente fi
        }

        free(fmin);  // Libera a memória do menor cliente
    }
    // Descarrega o buffer para ter certeza de que os dados foram gravados
    fflush(arq);  // Garante que todos os dados foram escritos no arquivo
}

void selectionSortPedidos(FILE *arq, int tam) {
    int i, j, min_idx;  // Declaração de variáveis para índices e posição do menor elemento
    Pedido *fi, *fj, *fmin;  // Ponteiros para armazenar temporariamente os pedidos durante a ordenação

    // Loop externo que percorre todos os elementos do arquivo
    for (i = 0; i < tam - 1; i++) {
        min_idx = i;  // Inicializa o índice do menor elemento com o índice atual

        // Lê o registro no índice i e assume que é o menor
        fseek(arq, i * tamanhoRegistroPedido(), SEEK_SET);  // Posiciona o ponteiro do arquivo no início do registro i
        fmin = lePedido(arq);  // Lê o pedido do arquivo na posição i

        // Loop interno que percorre os elementos subsequentes ao índice i
        for (j = i + 1; j < tam; j++) {
            fseek(arq, j * tamanhoRegistroPedido(), SEEK_SET);  // Posiciona o ponteiro do arquivo no início do registro j
            fj = lePedido(arq);  // Lê o pedido do arquivo na posição j

            // Compara os códigos dos pedidos para encontrar o menor
            if (fj->codigo < fmin->codigo) {
                min_idx = j;  // Atualiza o índice do menor elemento
                free(fmin);  // Libera a memória do pedido anteriormente considerado o menor
                fmin = fj;  // Atualiza o menor pedido
            } else {
                free(fj);  // Libera a memória do pedido fj se não for o menor
            }
        }

        // Se min_idx não for o índice atual, troca os registros
        if (min_idx != i) {
            fseek(arq, i * tamanhoRegistroPedido(), SEEK_SET);  // Posiciona o ponteiro do arquivo no início do registro i
            fi = lePedido(arq);  // Lê o pedido do arquivo na posição i

            // Salva o menor valor na posição i
            fseek(arq, i * tamanhoRegistroPedido(), SEEK_SET);  // Posiciona o ponteiro do arquivo no início do registro i
            salvaPedido(fmin, arq);  // Salva o pedido fmin na posição i

            // Salva o valor original na posição min_idx
            fseek(arq, min_idx * tamanhoRegistroPedido(), SEEK_SET);  // Posiciona o ponteiro do arquivo no início do registro min_idx
            salvaPedido(fi, arq);  // Salva o pedido fi na posição min_idx

            free(fi);  // Libera a memória do pedido fi
        }

        free(fmin);  // Libera a memória do menor pedido
    }
    // Descarrega o buffer para ter certeza de que os dados foram gravados
    fflush(arq);  // Garante que todos os dados foram escritos no arquivo
}
