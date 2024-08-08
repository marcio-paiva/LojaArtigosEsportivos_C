#include "loja.h"
#include <stdio.h>
#include "selectionsort.h"
#include "buscaBinaria.h"
#include "buscaSequencial.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main() {

    clock_t start_time, end_time; double time;
    int TAM_PRODUTOS = 1000; //ALTERAR TAMANHO DA BASE DE PRODUTOS AQUI
    int TAM_CLIENTES = 1000; //ALTERAR TAMANHO DA BASE DE CLIENTES AQUI

    FILE *arq_prod = fopen("produtos.dat", "wb+");
    FILE *arq_cli = fopen("clientes.dat", "wb+");
    FILE *arq_ped = fopen("pedidos.dat", "wb+");

    if (!arq_prod || !arq_cli || !arq_ped) {
        perror("Erro ao abrir arquivo");
        return EXIT_FAILURE;
    }
    
    int opcao;
    int codigo; char nome[100]; double preco; int quantidade; //Utilizadas para adicionar produto/cliente
    int chave;
    do {
        printf("\nMenu de Produtos:\n");
        printf("1. Gerar Base de Produtos\n");
        printf("2. Ler Arquivo dos Produtos\n");
        printf("3. Busca Sequencial\n");
        printf("4. Busca Binaria\n");
        printf("5. Ordenar Produtos\n");
        printf("6. Adicionar Produto\n");
        printf("7. Remover Produto\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        switch (opcao){
            case 1:
                //CRIA BASE DE PRODUTOS
                criarBaseProdutos(arq_prod, TAM_PRODUTOS);
                break;

            case 2:
                //IMPRIME BASE DE PRODUTOS
                imprimirBaseProdutos(arq_prod);
                break;

            case 3:
                //BUSCA SEQUENCIAL NA BASE DE PRODUTOS
                printf("\n\nDigite o codigo do produto para buscar: ");
                scanf("%d", &chave);
                Produto *resultado_prod = buscaSequencialProduto(chave, arq_prod);
                if (resultado_prod != NULL) {
                    imprimeProduto(resultado_prod);
                    free(resultado_prod);
                }
                break;

            case 4:
                //BUSCA BINARIA NA BASE DE PRODUTOS
                printf("\n\nDigite o codigo do produto para buscar: ");
                scanf("%d", &chave);
                selectionSortProdutos(arq_prod, TAM_PRODUTOS);
                resultado_prod = buscaBinariaProduto(chave, arq_prod, TAM_PRODUTOS);
                if (resultado_prod != NULL) {
                    imprimeProduto(resultado_prod);
                    free(resultado_prod);
                }else{
                    printf("\nProduto nao encontrado.\n\n");
                }
                break;

            case 5:
                //ORDENA BASE DE PRODUTOS - SELECTION SORT (Retorna tempo de execução)
                start_time = clock();
                selectionSortProdutos(arq_prod, TAM_PRODUTOS);
                end_time = clock();
                time = (end_time - start_time) / 1000.0;
                printf("\nTempo de execucao da ordenacao dos produtos: %.6f segundos\n", time);
                break;

            case 6:
                //ADICIONAR PRODUTO NA BASE
                printf("Informe o codigo do produto: ");
                scanf("%d", &codigo);
                getchar();
                printf("Informe o nome do produto: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0'; // Remove a nova linha do final da string, se presente
                printf("Informe o preco do produto: ");
                scanf("%lf", &preco);
                printf("Informe a quantidade do produto: ");
                scanf("%d", &quantidade);
                TAM_PRODUTOS += 1;
                Produto* produto = criaProduto(codigo, nome, preco, quantidade);
                salvaProduto(produto, arq_prod);
                imprimeProduto(produto);
                printf("\nCriado com sucesso!");
                break;

            case 7:
                printf("Informe o codigo do produto: ");
                scanf("%d", &codigo);
                removeProduto(codigo, arq_prod);    
                TAM_PRODUTOS -= 1;
                break;

            case 0:
                printf("Voltando...\n");
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }
    }while (opcao != 0);

    char cpf[14], endereco[100];
    do {
        printf("\nMenu de Clientes:\n");
        printf("1. Gerar Base de Clientes\n");
        printf("2. Ler Arquivo de Clientes\n");
        printf("3. Busca Sequencial\n");
        printf("4. Busca Binaria\n");
        printf("5. Ordenar Clientes\n");
        printf("6. Adicionar Clientes\n");
        printf("7. Remover Clientes\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        switch (opcao){
            case 1:
                //CRIA BASE DE CLIENTES
                criarBaseClientes(arq_cli, TAM_CLIENTES);
                break;

            case 2:
                //IMPRIME BASE DE CLIENTES
                imprimirBaseCliente(arq_cli);
                break;

            case 3:
                //BUSCA SEQUENCIAL NA BASE DE CLIENTES
                printf("\n\nDigite o codigo do cliente para buscar: ");
                scanf("%d", &chave);
                Cliente *resultado_cli = buscaSequencialCliente(chave, arq_cli);
                if (resultado_cli != NULL) {
                    imprimeCliente(resultado_cli);
                    free(resultado_cli);
                }
                break;

            case 4:
                //BUSCA BINARIA NA BASE DE CLIENTES
                printf("\n\nDigite o codigo do produto para buscar: ");
                scanf("%d", &chave);
                selectionSortClientes(arq_cli, TAM_CLIENTES); // ORDENAR ANTES
                resultado_cli = buscaBinariaCliente(chave, arq_cli, TAM_CLIENTES);
                if (resultado_cli != NULL) {
                    imprimeCliente(resultado_cli);
                    free(resultado_cli);
                }else{
                    printf("\nCliente nao encontrado.\n\n");
                }
                break;

            case 5:
                //ORDENA BASE DE CLIENTES - SELECTION SORT (Retorna tempo de execução)
                start_time = clock();
                selectionSortClientes(arq_cli, TAM_CLIENTES);
                end_time = clock();
                time = (end_time - start_time) / 1000.0;
                printf("\nTempo de execucao da ordenacao dos clientes: %.6f segundos\n", time);
                break;

            case 6:
                //ADICIONAR CLIENTE NA BASE
                printf("Informe o codigo do cliente: ");
                scanf("%d", &codigo);
                getchar(); //captura o /n
                printf("Informe o nome do cliente: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0'; // Remove a nova linha do final da string, se presente
                printf("Informe o cpf do cliente: ");
                fgets(cpf, sizeof(cpf), stdin);
                cpf[strcspn(cpf, "\n")] = '\0'; // Remove a nova linha do final da string, se presente
                printf("Informe o endereco do cliente: ");
                fgets(endereco, sizeof(endereco), stdin);
                endereco[strcspn(endereco, "\n")] = '\0'; // Remove a nova linha do final da string, se presente
                TAM_CLIENTES += 1;
                Cliente* cliente = criaCliente(codigo, nome, cpf, endereco);
                salvaCliente(cliente, arq_cli);
                imprimeCliente(cliente);
                printf("\nCriado com sucesso!");
                break;

            case 7:
                printf("Informe o codigo do cliente: ");
                scanf("%d", &codigo);
                removeCliente(codigo, arq_cli);    
                TAM_CLIENTES -= 1;
                break;

            case 0:
                printf("Voltando...\n");
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }
    }while (opcao != 0);

    do {
        printf("\n=== MENU DE PEDIDOS ===");
        printf("1. Adicionar Pedido");
        printf("2. Remover Pedido");
        printf("3. Ler Arquivo de Pedidos");
        printf("4. Busca Sequencial");
        printf("5. Busca Binaria");
        printf("6. Ordenar Base de Pedidos");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        switch (opcao){
            case 1:
                //ADICIONAR PEDIDO NA BASE
                printf("Informe o codigo do cliente: ");
                scanf("%d", &codigo);
                getchar(); //captura o /n
                printf("Informe o nome do cliente: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0'; // Remove a nova linha do final da string, se presente
                printf("Informe o cpf do cliente: ");
                fgets(cpf, sizeof(cpf), stdin);
                cpf[strcspn(cpf, "\n")] = '\0'; // Remove a nova linha do final da string, se presente
                printf("Informe o endereco do cliente: ");
                fgets(endereco, sizeof(endereco), stdin);
                endereco[strcspn(endereco, "\n")] = '\0'; // Remove a nova linha do final da string, se presente
                TAM_CLIENTES += 1;
                Cliente* cliente = criaCliente(codigo, nome, cpf, endereco);
                salvaCliente(cliente, arq_cli);
                imprimeCliente(cliente);
                printf("\nCriado com sucesso!");
                break;

            case 2:
                //IMPRIME BASE DE CLIENTES
                imprimirBaseCliente(arq_cli);
                break;

            case 3:
                //BUSCA SEQUENCIAL NA BASE DE CLIENTES
                printf("\n\nDigite o codigo do cliente para buscar: ");
                scanf("%d", &chave);
                Cliente *resultado_cli = buscaSequencialCliente(chave, arq_cli);
                if (resultado_cli != NULL) {
                    imprimeCliente(resultado_cli);
                    free(resultado_cli);
                }
                break;

            case 4:
                //BUSCA BINARIA NA BASE DE CLIENTES
                printf("\n\nDigite o codigo do produto para buscar: ");
                scanf("%d", &chave);
                selectionSortClientes(arq_cli, TAM_CLIENTES); // ORDENAR ANTES
                resultado_cli = buscaBinariaCliente(chave, arq_cli, TAM_CLIENTES);
                if (resultado_cli != NULL) {
                    imprimeCliente(resultado_cli);
                    free(resultado_cli);
                }else{
                    printf("\nCliente nao encontrado.\n\n");
                }
                break;

            case 5:
                //ORDENA BASE DE CLIENTES - SELECTION SORT (Retorna tempo de execução)
                start_time = clock();
                selectionSortClientes(arq_cli, TAM_CLIENTES);
                end_time = clock();
                time = (end_time - start_time) / 1000.0;
                printf("\nTempo de execucao da ordenacao dos clientes: %.6f segundos\n", time);
                break;

            case 6:
                //ADICIONAR CLIENTE NA BASE
                printf("Informe o codigo do cliente: ");
                scanf("%d", &codigo);
                getchar(); //captura o /n
                printf("Informe o nome do cliente: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0'; // Remove a nova linha do final da string, se presente
                printf("Informe o cpf do cliente: ");
                fgets(cpf, sizeof(cpf), stdin);
                cpf[strcspn(cpf, "\n")] = '\0'; // Remove a nova linha do final da string, se presente
                printf("Informe o endereco do cliente: ");
                fgets(endereco, sizeof(endereco), stdin);
                endereco[strcspn(endereco, "\n")] = '\0'; // Remove a nova linha do final da string, se presente
                TAM_CLIENTES += 1;
                Cliente* cliente = criaCliente(codigo, nome, cpf, endereco);
                salvaCliente(cliente, arq_cli);
                imprimeCliente(cliente);
                printf("\nCriado com sucesso!");
                break;

            case 7:
                printf("Informe o codigo do cliente: ");
                scanf("%d", &codigo);
                removeCliente(codigo, arq_cli);    
                TAM_CLIENTES -= 1;
                break;

            case 0:
                printf("Voltando...\n");
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }
    }while (opcao != 0);

    system("\n\npause");

    fclose(arq_prod);
    fclose(arq_cli);
    fclose(arq_ped);

    return EXIT_SUCCESS;
}