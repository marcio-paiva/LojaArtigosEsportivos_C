#include "loja.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Funcoes relacionadas ao Produto
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

int codigoExiste(int codigo, FILE* arq_prod) {
    rewind(arq_prod); // Volta ao início do arquivo
    Produto* prod;
    while ((prod = leProduto(arq_prod)) != NULL) {
        if (prod->codigo == codigo) {
            free(prod);
            return 1; // Código já existe
        }
        free(prod);
    }
    return 0; // Código não existe
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

void imprimeProduto(Produto *prod) {
    printf("**********************************************");
    printf("\nProduto de codigo %d", prod->codigo);
    printf("\nNome: %s", prod->nome);
    printf("\nPreco: %.2f", prod->preco);
    printf("\nQuantidade: %d", prod->quantidade);
    printf("\n**********************************************");
}

void removeProduto(int codigo, FILE *arquivo) {
    FILE *temp = fopen("temp.dat", "wb");
    if (!temp) {
        perror("Nao foi possivel abrir o arquivo temporario para escrita");
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
        printf("\nProduto com codigo %d removido com sucesso.\n", codigo);
    } else {
        remove("temp.dat");              // Remove o arquivo temporário
        printf("\nProduto com codigo %d nao encontrado.\n", codigo);
    }
     arquivo = fopen("produtos.dat", "rb");
        if (!arquivo) {
            perror("Nao foi possivel reabrir o arquivo produtos.dat");
            return;
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
        perror("Nao foi possivel abrir o arquivo temporario para escrita");
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
    arquivo = fopen("clientes.dat", "rb");
    if (!arquivo) {
        perror("Nao foi possivel reabrir o arquivo clientes.dat");
        return;
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

// Funcoes relacionadas ao Pedido
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

void criarBasePedidos(FILE *out, int tam) {
    int ids[tam];
    for (int i = 0; i < tam; i++) {
        ids[i] = i + 1;
    }

    // Embaralha os IDs para criar clientes em ordem aleatória
    embaralha(ids, tam);
    Pedido *ped;
    for (int i = 0; i < tam; i++) {
        ped = criaPedido(ids[i], (i % 10) + 1, (i % 10) + 1, 1, 10.0 * (i + 1));
        salvaPedido(ped, out);
         free(ped);
    }
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

void removePedido(int codigo, FILE *arquivo){
    FILE *temp = fopen("temp.dat", "wb");
    if (!temp) {
        perror("Nao foi possivel abrir o arquivo temporario para escrita");
        return;
    }

    Pedido *ped;
    int found = 0;

    fseek(arquivo, 0, SEEK_SET); // Posiciona o ponteiro no início do arquivo

    while ((ped = lePedido(arquivo)) != NULL) {
        if (ped->codigo == codigo) {
            found = 1;
            free(ped);
        } else {
            salvaPedido(ped, temp);
            free(ped);
        }
    }
    fclose(temp);

    if (found) {
        fclose(arquivo);
        remove("pedidos.dat");          // Remove o arquivo original
        rename("temp.dat", "pedidos.dat"); // Renomeia o arquivo temporário
        printf("Pedido com codigo %d removido com sucesso.\n", codigo);
    } else {
        remove("temp.dat");              // Remove o arquivo temporário
        printf("Pedido com codigo %d nao encontrado.\n", codigo);
    }
    arquivo = fopen("pedidos.dat", "rb");
    if (!arquivo) {
        perror("Nao foi possivel reabrir o arquivo pedidos.dat");
        return;
    } 
}

void imprimirBasePedido(FILE *out){
    printf("\nImprimindo a base de dados...\n");

    rewind(out);
    void *item;

    while ((item = lePedido(out)) != NULL) {
        imprimePedido(item);
        free(item);
    }
}

// Funcoes auxiliares
int tamanhoRegistroProduto() {
    return sizeof(int)         // codigo
           + sizeof(char) * 50 // nome
           + sizeof(double)    // preco
           + sizeof(int);      // quantidade
}

int tamanhoRegistroCliente() {
    return sizeof(int)         // codigo
           + sizeof(char) * 50 // nome
           + sizeof(char) * 15 // cpf
           + sizeof(char) * 100; // endereco
}

int tamanhoRegistroPedido() {
    return sizeof(int)         // codigo
           + sizeof(int)       // codigo_cliente
           + sizeof(int)       // codigo_produto
           + sizeof(int)       // quantidade
           + sizeof(double);   // total
}

int qtdRegistros(FILE *arq, int tamanho_registro) {
    fseek(arq, 0, SEEK_END);
    return (int)(ftell(arq) / tamanho_registro);
}

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