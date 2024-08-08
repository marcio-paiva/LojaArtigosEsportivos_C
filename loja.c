#include "loja.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Fun��es relacionadas ao Produto
Produto* criaProduto(int codigo, char *nome, double preco, int quantidade) {
    Produto *prod = (Produto *) malloc(sizeof(Produto));
    if (prod) {
        prod->codigo = codigo;
        strcpy(prod->nome, nome);
        prod->preco = preco;
        prod->quantidade = quantidade;
    }
    return prod;
}

void salvaProduto(Produto *prod, FILE *out) {
    fwrite(&prod->codigo, sizeof(int), 1, out);
    fwrite(prod->nome, sizeof(char), sizeof(prod->nome), out);
    fwrite(&prod->preco, sizeof(double), 1, out);
    fwrite(&prod->quantidade, sizeof(int), 1, out);
}

Produto* leProduto(FILE *in) {
    Produto *prod = (Produto *) malloc(sizeof(Produto));
    if (0 >= fread(&prod->codigo, sizeof(int), 1, in)) {
        free(prod);
        return NULL;
    }
    fread(prod->nome, sizeof(char), sizeof(prod->nome), in);
    fread(&prod->preco, sizeof(double), 1, in);
    fread(&prod->quantidade, sizeof(int), 1, in);
    return prod;
}

void imprimeProduto(Produto *prod) {
    printf("**********************************************");
    printf("\nProduto de codigo %d", prod->codigo);
    printf("\nNome: %s", prod->nome);
    printf("\nPreco: %.2f", prod->preco);
    printf("\nQuantidade: %d", prod->quantidade);
    printf("\n**********************************************");
}

// Função para remover um produto pelo código
void removeProduto(int codigo, FILE *arquivo) {
    FILE *temp = fopen("temp.dat", "wb");
    if (!temp) {
        perror("Não foi possível abrir o arquivo temporário para escrita");
        return;
    }

    Produto *prod;
    int found = 0;

    fseek(arquivo, 0, SEEK_SET); // Posiciona o ponteiro no início do arquivo

    while ((prod = leProduto(arquivo)) != NULL) {
        if (prod->codigo == codigo) {
            found = 1;
            free(prod);
        } else {
            salvaProduto(prod, temp);
            free(prod);
        }
    }

    fclose(temp);

    if (found) {
        fclose(arquivo);
        remove("produtos.dat");          // Remove o arquivo original
        rename("temp.dat", "produtos.dat"); // Renomeia o arquivo temporário
        printf("Produto com codigo %d removido com sucesso.\n", codigo);
    } else {
        remove("temp.dat");              // Remove o arquivo temporário
        printf("Produto com codigo %d não encontrado.\n", codigo);
    }
}

void imprimirBaseProdutos(FILE *out) {
    printf("\nImprimindo a base de dados...\n");

    rewind(out);
    void *item;

    while ((item = leProduto(out)) != NULL) {
        imprimeProduto(item);
        free(item);
    }
}

// Funcoes relacionadas ao Cliente
Cliente* criaCliente(int codigo, char *nome, char *cpf, char *endereco) {
    Cliente *cli = (Cliente *) malloc(sizeof(Cliente));
    if (cli) {
        cli->codigo = codigo;
        strcpy(cli->nome, nome);
        strcpy(cli->cpf, cpf);
        strcpy(cli->endereco, endereco);
    }
    return cli;
}

void salvaCliente(Cliente *cli, FILE *out) {
    fwrite(&cli->codigo, sizeof(int), 1, out);
    fwrite(cli->nome, sizeof(char), sizeof(cli->nome), out);
    fwrite(cli->cpf, sizeof(char), sizeof(cli->cpf), out);
    fwrite(cli->endereco, sizeof(char), sizeof(cli->endereco), out);
}

Cliente* leCliente(FILE *in) {
    Cliente *cli = (Cliente *) malloc(sizeof(Cliente));
    if (0 >= fread(&cli->codigo, sizeof(int), 1, in)) {
        free(cli);
        return NULL;
    }
    fread(cli->nome, sizeof(char), sizeof(cli->nome), in);
    fread(cli->cpf, sizeof(char), sizeof(cli->cpf), in);
    fread(cli->endereco, sizeof(char), sizeof(cli->endereco), in);
    return cli;
}

void imprimeCliente(Cliente *cli) {
    printf("**********************************************");
    printf("\nCliente de codigo %d", cli->codigo);
    printf("\nNome: %s", cli->nome);
    printf("\nCPF: %s", cli->cpf);
    printf("\nEndereco: %s", cli->endereco);
    printf("\n**********************************************");
}

void removeCliente(int codigo, FILE *arquivo) {
    FILE *temp = fopen("temp.dat", "wb");
    if (!temp) {
        perror("Não foi possível abrir o arquivo temporário para escrita");
        return;
    }

    Cliente *cli;
    int found = 0;

    fseek(arquivo, 0, SEEK_SET); // Posiciona o ponteiro no início do arquivo

    while ((cli = leCliente(arquivo)) != NULL) {
        if (cli->codigo == codigo) {
            found = 1;
            free(cli);
        } else {
            salvaCliente(cli, temp);
            free(cli);
        }
    }

    fclose(temp);

    if (found) {
        fclose(arquivo);
        remove("clientes.dat");          // Remove o arquivo original
        rename("temp.dat", "clientes.dat"); // Renomeia o arquivo temporário
        printf("Cliente com codigo %d removido com sucesso.\n", codigo);
    } else {
        remove("temp.dat");              // Remove o arquivo temporário
        printf("Cliente com codigo %d não encontrado.\n", codigo);
    }
}

void imprimirBaseCliente(FILE *out){
        printf("\nImprimindo a base de dados...\n");

    rewind(out);
    void *item;

    while ((item = leCliente(out)) != NULL) {
        imprimeCliente(item);
        free(item);
    }
}

// Fun��es relacionadas ao Pedido
Pedido* criaPedido(int codigo, int codigo_cliente, int codigo_produto, int quantidade, double total) {
    Pedido *ped = (Pedido *) malloc(sizeof(Pedido));
    if (ped) {
        ped->codigo = codigo;
        ped->codigo_cliente = codigo_cliente;
        ped->codigo_produto = codigo_produto;
        ped->quantidade = quantidade;
        ped->total = total;
    }
    return ped;
}

void salvaPedido(Pedido *ped, FILE *out) {
    fwrite(&ped->codigo, sizeof(int), 1, out);
    fwrite(&ped->codigo_cliente, sizeof(int), 1, out);
    fwrite(&ped->codigo_produto, sizeof(int), 1, out);
    fwrite(&ped->quantidade, sizeof(int), 1, out);
    fwrite(&ped->total, sizeof(double), 1, out);
}

Pedido* lePedido(FILE *in) {
    Pedido *ped = (Pedido *) malloc(sizeof(Pedido));
    if (0 >= fread(&ped->codigo, sizeof(int), 1, in)) {
        free(ped);
        return NULL;
    }
    fread(&ped->codigo_cliente, sizeof(int), 1, in);
    fread(&ped->codigo_produto, sizeof(int), 1, in);
    fread(&ped->quantidade, sizeof(int), 1, in);
    fread(&ped->total, sizeof(double), 1, in);
    return ped;
}

void imprimePedido(Pedido *ped) {
    printf("**********************************************");
    printf("\nPedido de codigo %d", ped->codigo);
    printf("\nCodigo do Cliente: %d", ped->codigo_cliente);
    printf("\nCodigo do Produto: %d", ped->codigo_produto);
    printf("\nQuantidade: %d", ped->quantidade);
    printf("\nTotal: %.2f", ped->total);
    printf("\n**********************************************");
}

// Fun��es auxiliares
int tamanhoRegistroProduto() {
    return sizeof(int)         // c�digo
           + sizeof(char) * 50 // nome
           + sizeof(double)    // pre�o
           + sizeof(int);      // quantidade
}

int tamanhoRegistroCliente() {
    return sizeof(int)         // c�digo
           + sizeof(char) * 50 // nome
           + sizeof(char) * 15 // cpf
           + sizeof(char) * 100; // endere�o
}

int tamanhoRegistroPedido() {
    return sizeof(int)         // c�digo
           + sizeof(int)       // c�digo_cliente
           + sizeof(int)       // c�digo_produto
           + sizeof(int)       // quantidade
           + sizeof(double);   // total
}

int qtdRegistros(FILE *arq, int tamanho_registro) {
    fseek(arq, 0, SEEK_END);
    return (int)(ftell(arq) / tamanho_registro);
}

// Função para embaralhar um vetor
void embaralha(int *array, int n) {
    if (n > 1) {
        srand(time(NULL));
        for (int i = 0; i < n - 1; i++) {
            int j = i + rand() / (RAND_MAX / (n - i) + 1);
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

void criarBaseProdutos(FILE *out, int tam) {
    int ids[tam];
    for (int i = 0; i < tam; i++) {
        ids[i] = i + 1;
    }

    // Embaralha os IDs para criar produtos em ordem aleatória
    embaralha(ids, tam);

    Produto *p;
    for (int i = 0; i < tam; i++) {
        p = criaProduto(ids[i], "Produto", 10.0 * (ids[i]), tam - i);
        salvaProduto(p, out);
        free(p);
    }
    printf("\n\nBase criada com sucesso\n\n");
}

void criarBaseClientes(FILE *out, int tam) {
    int ids[tam];
    for (int i = 0; i < tam; i++) {
        ids[i] = i + 1;
    }

    // Embaralha os IDs para criar clientes em ordem aleatória
    embaralha(ids, tam);
    Cliente *c;
    for (int i = 0; i < tam; i++) {
        c = criaCliente(ids[i], "Cliente", "000.000.000-00", "Endereco");
        salvaCliente(c, out);
        free(c);
    }
}

void criarBasePedidos(FILE *out, int tam) {
    Pedido *ped;
    for (int i = 0; i < tam; i++) {
        ped = criaPedido(i + 1, (i % 10) + 1, (i % 10) + 1, 1, 10.0 * (i + 1));
        salvaPedido(ped, out);
         free(ped);
    }
}


