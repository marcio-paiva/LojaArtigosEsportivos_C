#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "intercalacao.h"
#include "loja.h"

void intercalacaoOtimaProdutos(int num_particoes) {
    // Abrir todas as partições
    FILE *particoes[num_particoes];
    char nome_particao[100];
    for (int i = 0; i < num_particoes; i++) {
        sprintf(nome_particao, "particoes/produtos/particao%d.dat", i);
        particoes[i] = fopen(nome_particao, "rb");
    }

    // Buffer para manter os produtos atualmente sendo comparados em cada partição
    Produto *buffer[num_particoes];
    for (int i = 0; i < num_particoes; i++) {
        buffer[i] = leProduto(particoes[i]);  // Ler o primeiro produto de cada partição
    }

    // Abrir arquivo final para gravar os produtos intercalados
    FILE *arquivo_final = fopen("produtos.dat", "wb");

    int menor_indice;
    Produto *menor_produto;

    // Intercalar até que todos os produtos sejam gravados
    while (1) {
        menor_produto = NULL;
        menor_indice = -1;

        // Encontrar o menor produto entre as partições
        for (int i = 0; i < num_particoes; i++) {
            if (buffer[i] != NULL) {
                if (menor_produto == NULL || buffer[i]->codigo < menor_produto->codigo) {
                    menor_produto = buffer[i];
                    menor_indice = i;
                }
            }
        }

        // Se não há mais registros para intercalar, sair do loop
        if (menor_produto == NULL) {
            break;
        }

        // Grava o menor produto no arquivo final
        salvaProduto(menor_produto, arquivo_final);
        free(menor_produto);  // Liberar o menor produto gravado

        // Ler o próximo produto da partição que tinha o menor produto
        buffer[menor_indice] = leProduto(particoes[menor_indice]);
    }

    // Fechar todas as partições e o arquivo final
    for (int i = 0; i < num_particoes; i++) {
        fclose(particoes[i]);
    }
    fclose(arquivo_final);

    printf("\nIntercalacao feita com suceso. %d particoes foram intercaladas.\n", num_particoes);
}

void intercalacaoOtimaClientes(int num_particoes) {
    // Abrir todas as partições
    FILE *particoes[num_particoes];
    char nome_particao[100];
    for (int i = 0; i < num_particoes; i++) {
        sprintf(nome_particao, "particoes/clientes/particao%d.dat", i);
        particoes[i] = fopen(nome_particao, "rb");
    }

    // Buffer para manter os clientes atualmente sendo comparados em cada partição
    Cliente *buffer[num_particoes];
    for (int i = 0; i < num_particoes; i++) {
        buffer[i] = leCliente(particoes[i]);  // Ler o primeiro cliente de cada partição
    }

    // Abrir arquivo final para gravar os clientes intercalados
    FILE *arquivo_final = fopen("clientes.dat", "wb");

    int menor_indice;
    Cliente *menor_cliente;

    // Intercalar até que todos os clientes sejam gravados
    while (1) {
        menor_cliente = NULL;
        menor_indice = -1;

        // Encontrar o menor cliente entre as partições
        for (int i = 0; i < num_particoes; i++) {
            if (buffer[i] != NULL) {
                if (menor_cliente == NULL || buffer[i]->codigo < menor_cliente->codigo) {
                    menor_cliente = buffer[i];
                    menor_indice = i;
                }
            }
        }

        // Se não há mais registros para intercalar, sair do loop
        if (menor_cliente == NULL) {
            break;
        }

        // Grava o menor cliente no arquivo final
        salvaCliente(menor_cliente, arquivo_final);
        free(menor_cliente);  // Liberar o menor cliente gravado

        // Ler o próximo cliente da partição que tinha o menor cliente
        buffer[menor_indice] = leCliente(particoes[menor_indice]);
    }

    // Fechar todas as partições e o arquivo final
    for (int i = 0; i < num_particoes; i++) {
        fclose(particoes[i]);
    }
    fclose(arquivo_final);

    printf("\nIntercalacao feita com suceso. %d particoes foram intercaladas.\n", num_particoes);
}

void intercalacaoOtimaPedidos(int num_particoes) {
    // Abrir todas as partições
    FILE *particoes[num_particoes];
    char nome_particao[100];
    for (int i = 0; i < num_particoes; i++) {
        sprintf(nome_particao, "particoes/pedidos/particao%d.dat", i);
        particoes[i] = fopen(nome_particao, "rb");
    }

    // Buffer para manter os pedidos atualmente sendo comparados em cada partição
    Pedido *buffer[num_particoes];
    for (int i = 0; i < num_particoes; i++) {
        buffer[i] = lePedido(particoes[i]);  // Ler o primeiro pedido de cada partição
    }

    // Abrir arquivo final para gravar os pedidos intercalados
    FILE *arquivo_final = fopen("pedidos.dat", "wb");

    int menor_indice;
    Pedido *menor_pedido;

    // Intercalar até que todos os pedidos sejam gravados
    while (1) {
        menor_pedido = NULL;
        menor_indice = -1;

        // Encontrar o menor pedido entre as partições
        for (int i = 0; i < num_particoes; i++) {
            if (buffer[i] != NULL) {
                if (menor_pedido == NULL || buffer[i]->codigo < menor_pedido->codigo) {
                    menor_pedido = buffer[i];
                    menor_indice = i;
                }
            }
        }

        // Se não há mais registros para intercalar, sair do loop
        if (menor_pedido == NULL) {
            break;
        }

        // Grava o menor pedido no arquivo final
        salvaPedido(menor_pedido, arquivo_final);
        free(menor_pedido);  // Liberar o menor pedido gravado

        // Ler o próximo pedido da partição que tinha o menor pedido
        buffer[menor_indice] = lePedido(particoes[menor_indice]);
    }

    // Fechar todas as partições e o arquivo final
    for (int i = 0; i < num_particoes; i++) {
        fclose(particoes[i]);
    }
    fclose(arquivo_final);

    printf("\nIntercalacao feita com suceso. %d particoes foram intercaladas.\n", num_particoes);
}
