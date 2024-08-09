#include "loja.h"
#include <stdio.h>
#include "selectionsort.h"
#include "buscaBinaria.h"
#include "buscaSequencial.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define TAM_PRODUTOS 1000 //ALTERAR TAMANHO DA BASE DE PEDIDOS AQUI 
#define TAM_CLIENTES 1000 //ALTERAR TAMANHO DA BASE DE PEDIDOS AQUI 
#define TAM_PEDIDOS 10 //ALTERAR TAMANHO DA BASE DE PEDIDOS AQUI 

int main() {
    FILE *arq_prod = fopen("produtos.dat", "wb+");
    FILE *arq_cli = fopen("clientes.dat", "wb+");
    FILE *arq_ped = fopen("pedidos.dat", "wb+");

    if (!arq_prod || !arq_cli || !arq_ped) {
        perror("Erro ao abrir arquivo");
        return EXIT_FAILURE;
    }

    clock_t start_time, end_time; double time;
    int opcao_geral; //Utilizada para controlar switch case externo (menu geral)
    do{
        printf("\n=== Menu de Geral ===\n");
        printf("1. Menu de Produtos\n");
        printf("2. Menu de Clientes\n");
        printf("3. Menu de Pedidos\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao_geral);
        
        int codigo; //Utilizada para adicionar produto/cliente
        char nome[100]; double preco; int quantidade; //Utilizadas para adicionar produto
        int chave; //Utilizada para fazer buscas
        char cpf[15], endereco[100]; //Utilizadas para adicionar cliente
        int codigo_cli; int codigo_prod; double total; //Utilizadas para adicionar pedido

        int opcao; //Utilizada para controlar switch case interno de cada menu
        switch (opcao_geral){
        case 1:
            do {
                printf("\n=== Menu de Produtos ===\n");
                printf("1. Gerar Base de Produtos Desordenada\n");
                printf("2. Imprimir Estoque\n");
                printf("3. Ordenar Base de Produtos\n");
                printf("4. Busca Sequencial\n");
                printf("5. Busca Binaria\n");
                printf("6. Cadastrar Produto no Estoque\n");
                printf("7. Remover Produto do Estoque\n");
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
                        //ORDENA BASE DE PRODUTOS - SELECTION SORT (Retorna tempo de execução)
                        start_time = clock();
                        selectionSortProdutos(arq_prod, tamanhoArquivoProdutos(arq_prod));
                        end_time = clock();
                        time = (end_time - start_time) / 1000.0;
                        printf("\nTempo de execucao da ordenacao dos produtos: %.6f segundos\n", time);
                        break;

                    case 4:
                        //BUSCA SEQUENCIAL NA BASE DE PRODUTOS
                        printf("\n\nDigite o codigo do produto para buscar: ");
                        scanf("%d", &chave);
                        start_time = clock();
                        Produto *resultado_prod = buscaSequencialProduto(chave, arq_prod);
                        end_time = clock();
                        time = (end_time - start_time) / 1000.0;
                        if (resultado_prod != NULL) {
                            imprimeProduto(resultado_prod);
                            printf("\nTempo de execucao da busca sequencial dos produtos: %.6f segundos\n", time);
                            free(resultado_prod);
                        }
                        break;

                    case 5:
                        //BUSCA BINARIA NA BASE DE PRODUTOS
                        printf("\n\nDigite o codigo do produto para buscar: ");
                        scanf("%d", &chave);
                        start_time = clock();
                        selectionSortProdutos(arq_prod, tamanhoArquivoProdutos(arq_prod));
                        end_time = clock();
                        time = (end_time - start_time) / 1000.0;
                        printf("\nTempo de execucao da ordenacao dos produtos: %.6f segundos\n", time);
                        start_time = clock();
                        resultado_prod = buscaBinariaProduto(chave, arq_prod, tamanhoArquivoProdutos(arq_prod));
                        end_time = clock();
                        time = (end_time - start_time) / 1000.0;
                        if (resultado_prod != NULL) {
                            imprimeProduto(resultado_prod);
                            printf("\nTempo de execucao da busca binaria dos produtos: %.6f segundos\n", time);
                            free(resultado_prod);
                        }
                        break;

                    case 6:
                        //ADICIONAR PRODUTO NA BASE
                        printf("Informe o codigo do produto: ");
                        scanf("%d", &codigo);
                        if(codigoExisteProd(codigo, arq_prod)){
                            printf("\nErro: Codigo do produto ja existe!\n\n");
                            break;
                        }
                        getchar();
                        printf("Informe o nome do produto: ");
                        fgets(nome, sizeof(nome), stdin);
                        nome[strcspn(nome, "\n")] = '\0'; // Remove a nova linha do final da string, se presente
                        printf("Informe o preco do produto: ");
                        scanf("%lf", &preco);
                        printf("Informe a quantidade do produto: ");
                        scanf("%d", &quantidade);
                        Produto* produto = criaProduto(codigo, nome, preco, quantidade);
                        salvaProduto(produto, arq_prod);
                        imprimeProduto(produto);
                        printf("\nCriado com sucesso!");
                        break;

                    case 7:
                        printf("Informe o codigo do produto: ");
                        scanf("%d", &codigo);
                        removeProduto(codigo, arq_prod);
                        break;

                    case 0:
                        printf("Voltando...\n");
                        break;

                    default:
                        printf("Opcao invalida!\n");
                        break;
                }
            }while (opcao != 0);
            break;

        case 2:
            do {
                printf("\n=== Menu de Clientes ===\n");
                printf("1. Gerar Base de Clientes Desordenada\n");
                printf("2. Imprimir Clientes\n");
                printf("3. Ordenar Base de Clientes\n");
                printf("4. Busca Sequencial\n");
                printf("5. Busca Binaria\n");
                printf("6. Cadastrar Cliente\n");
                printf("7. Remover Cliente\n");
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
                        //ORDENA BASE DE CLIENTES - SELECTION SORT (Retorna tempo de execução)
                        start_time = clock();
                        selectionSortClientes(arq_cli, tamanhoArquivoClientes(arq_cli));
                        end_time = clock();
                        time = (end_time - start_time) / 1000.0;
                        printf("\nTempo de execucao da ordenacao dos clientes: %.6f segundos\n", time);
                        break;

                    case 4:
                        //BUSCA SEQUENCIAL NA BASE DE CLIENTES
                        printf("\n\nDigite o codigo do cliente para buscar: ");
                        scanf("%d", &chave);
                        start_time = clock();
                        Cliente *resultado_cli = buscaSequencialCliente(chave, arq_cli);
                        end_time = clock();
                        time = (end_time - start_time) / 1000.0;
                        if (resultado_cli != NULL) {
                            imprimeCliente(resultado_cli);
                            printf("\nTempo de execucao da busca sequencial dos clientes: %.6f segundos\n", time);
                            free(resultado_cli);
                        }
                        break;

                    case 5:
                        //BUSCA BINARIA NA BASE DE CLIENTES
                        printf("\n\nDigite o codigo do cliente para buscar: ");
                        scanf("%d", &chave);
                        start_time = clock();
                        selectionSortClientes(arq_cli, tamanhoArquivoClientes(arq_cli)); // ORDENAR ANTES
                        end_time = clock();
                        time = (end_time - start_time) / 1000.0;
                        printf("\nTempo de execucao da ordenacao dos clientes: %.6f segundos\n", time);
                        start_time = clock();
                        resultado_cli = buscaBinariaCliente(chave, arq_cli, tamanhoArquivoClientes(arq_cli));
                        end_time = clock();
                        time = (end_time - start_time) / 1000.0;
                        if (resultado_cli != NULL) {
                            imprimeCliente(resultado_cli);
                            printf("\nTempo de execucao da busca binaria dos clientes: %.6f segundos\n", time);
                            free(resultado_cli);
                        }
                        break;

                    case 6:
                        //ADICIONAR CLIENTE NA BASE
                        printf("Informe o codigo do cliente: ");
                        scanf("%d", &codigo);
                        if(codigoExisteCli(codigo, arq_cli)){
                            printf("\nErro: Codigo do Cliente ja existe!\n\n");
                            break;
                        }
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
                        Cliente* cliente = criaCliente(codigo, nome, cpf, endereco);
                        salvaCliente(cliente, arq_cli);
                        imprimeCliente(cliente);
                        printf("\nCriado com sucesso!");
                        break;

                    case 7:
                        printf("Informe o codigo do cliente: ");
                        scanf("%d", &codigo);
                        removeCliente(codigo, arq_cli);
                        break;

                    case 0:
                        printf("Voltando...\n");
                        break;

                    default:
                        printf("Opcao invalida!\n");
                        break;
                }
            }while (opcao != 0);
            break;

        case 3:
            do {
        printf("\n=== MENU DE PEDIDOS ===\n");
        printf("1. Criar Base de Pedidos Desordenada\n");
        printf("2. Imprimir Pedidos\n");
        printf("3. Ordenar Base de Pedidos\n");
        printf("4. Busca Sequencial\n");
        printf("5. Busca Binaria\n");
        printf("6. Adicionar Pedido\n");
        printf("7. Remover Pedido\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        switch (opcao){
            case 1:
                //CRIA BASE DE PEDIDOS
                criarBasePedidos(arq_ped, TAM_PEDIDOS);
                break;
            case 2:
                //IMPRIME BASE DE PEDIDOS
                imprimirBasePedido(arq_ped);
                break;
            
            case 3:
                //ORDENA BASE DE Pedidos - SELECTION SORT (Retorna tempo de execução)
                start_time = clock();
                selectionSortPedidos(arq_ped, tamanhoArquivoPedidos(arq_ped));
                end_time = clock();
                time = (end_time - start_time) / 1000.0;
                printf("\nTempo de execucao da ordenacao dos pedidos: %.6f segundos\n", time);
                break;

            case 4:
                //BUSCA SEQUENCIAL NA BASE DE PEDIDOS
                printf("\n\nDigite o codigo do pedido para buscar: ");
                scanf("%d", &chave);
                start_time = clock();
                Pedido *resultado_ped = buscaSequencialPedido(chave, arq_ped);
                end_time = clock();
                time = (end_time - start_time) / 1000.0;
                if (resultado_ped != NULL) {
                    imprimePedido(resultado_ped);
                    printf("\nTempo de execucao da busca sequencial dos pedidos: %.6f segundos\n", time);
                    free(resultado_ped);
                }
                break;

            case 5:
                //BUSCA BINARIA NA BASE DE PEDIDOS
                printf("\n\nDigite o codigo do pedido para buscar: ");
                scanf("%d", &chave);
                start_time = clock();
                selectionSortPedidos(arq_ped, tamanhoArquivoPedidos(arq_ped)); // ORDENAR ANTES
                end_time = clock();
                time = (end_time - start_time) / 1000.0;
                printf("\nTempo de execucao da ordenacao dos pedidos: %.6f segundos\n", time);
                start_time = clock();
                resultado_ped = buscaBinariaPedido(chave, arq_ped, tamanhoArquivoPedidos(arq_ped));
                end_time = clock();
                time = (end_time - start_time) / 1000.0;
                if (resultado_ped != NULL) {
                    imprimePedido(resultado_ped);
                    printf("\nTempo de execucao da busca binaria dos pedidos: %.6f segundos\n", time);
                    free(resultado_ped);
                }
                break;

            case 6:
                //ADICIONAR PEDIDO NA BASE
                printf("Informe o codigo do pedido: ");
                scanf("%d", &codigo);
                if(codigoExistePed(codigo, arq_ped)){
                    printf("\nErro: Codigo do Pedido ja existe!\n\n");
                    break;
                }
                //VINCULA PEDIDO AO CLIENTE
                printf("Informe o codigo do cliente: ");
                scanf("%d", &codigo_cli);
                Cliente* cliente_atual;
                if(codigoExisteCli(codigo_cli, arq_cli)){
                    printf("\nOrdenando base para buscar cliente, ");
                    selectionSortClientes(arq_cli, tamanhoArquivoClientes(arq_cli));
                    cliente_atual = buscaBinariaCliente(codigo_cli, arq_cli, tamanhoArquivoClientes(arq_cli));
                    imprimeCliente(cliente_atual);
                    free(cliente_atual);
                }else{
                    printf("\nErro: O codigo nao esta vinculado a nenhum cliente!\n\n");
                    break;
                }
                //VINCULA PEDIDO AO PRODUTO
                printf("\nInforme o codigo do produto: ");
                scanf("%d", &codigo_prod);
                Produto* prod_comprado;
                if(codigoExisteProd(codigo_prod, arq_prod)){
                    printf("\nOrdenando base para buscar produto, ");
                    selectionSortProdutos(arq_prod, tamanhoArquivoProdutos(arq_prod));
                    prod_comprado = buscaBinariaProduto(codigo_prod, arq_prod, tamanhoArquivoProdutos(arq_prod));
                    imprimeProduto(prod_comprado);
                    printf("\nInforme a quantidade: ");
                    scanf("%d", &quantidade);
                    if (prod_comprado->quantidade >= quantidade) {
                        total = (prod_comprado->preco * quantidade);
                        printf("Valor total do pedido: %lf", total);
                        Pedido *pedido = criaPedido(codigo, codigo_cli, codigo_prod, quantidade, total);
                        salvaPedido(pedido, arq_ped);
                        printf("\n\nPedido adicionado com sucesso:\n");
                        imprimePedido(pedido);
                        free(pedido);
                    }else{
                        printf("\nErro: Quantidade solicitada indisponivel no estoque!\n\n");
                    }
                free(prod_comprado);
                }else{
                    printf("\nErro: O codigo nao esta vinculado a nenhum produto!\n\n");
                    break;
                }
                break;

            case 7:
                printf("Informe o codigo do pedido: ");
                scanf("%d", &codigo);
                removePedido(codigo, arq_ped);    
                break;

            case 0:
                printf("Voltando...\n");
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }
            }while (opcao != 0);
            break;

        case 0:
            printf("Voltando...\n");
            break;

        default:
            printf("Opcao invalida!\n");
            break;
        }
    } while (opcao_geral != 0);

    fclose(arq_prod);
    fclose(arq_cli);
    fclose(arq_ped);

    return EXIT_SUCCESS;
}