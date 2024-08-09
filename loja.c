#include "loja.h"
#include <stdlib.h>   //alocação de memória, controle de processos e conversões de tipos, como malloc, free, exit e atoi.
#include <string.h>   //manipulação de strings, como strcpy, strlen, strcat e strcmp.
#include <time.h>     //tempo: time, clock, difftime e geração de números aleatórios, como srand e rand.
#include <math.h>     //funções matemáticas, como sqrt, pow, sin, cos e log.

// Funcoes relacionadas ao Produto
Produto* criaProduto(int codigo, char *nome, double preco, int quantidade) {
    Produto *prod = (Produto *) malloc(sizeof(Produto)); // Aloca memória para um novo Produto
    if (prod) { // Verifica se a alocação foi bem-sucedida
        prod->codigo = codigo; 
        strcpy(prod->nome, nome); 
        prod->preco = preco; 
        prod->quantidade = quantidade; 
    }
    return prod; // Retorna o ponteiro para o novo produto
}

int codigoExisteProd(int codigo, FILE* arq_prod) {
    rewind(arq_prod); // Volta ao início do arquivo
    Produto* prod;
    while ((prod = leProduto(arq_prod)) != NULL) { // Lê produtos do arquivo até o final
        if (prod->codigo == codigo) { // Verifica se o código do produto corresponde ao código buscado
            free(prod); // Libera a memória do produto
            return 1; // Código já existe
        }
        free(prod); // Libera a memória do produto
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
    Produto *prod = (Produto *) malloc(sizeof(Produto)); // Aloca memória para um novo Produto
    if (0 >= fread(&prod->codigo, sizeof(int), 1, in)) { // Lê o código do produto e verifica se a leitura foi bem-sucedida
        free(prod); // Libera a memória alocada se a leitura falhar
        return NULL; // Retorna NULL se não for possível ler o produto
    }
    fread(prod->nome, sizeof(char), sizeof(prod->nome), in); 
    fread(&prod->preco, sizeof(double), 1, in); 
    fread(&prod->quantidade, sizeof(int), 1, in); 
    return prod; // Retorna o ponteiro para o produto lido
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
    FILE *temp = fopen("temp.dat", "wb"); // Abre um arquivo temporário para escrita binária
    if (!temp) {
        perror("Nao foi possivel abrir o arquivo temporario para escrita");
        return;
    }

    Produto *prod;
    int found = 0;
    fseek(arquivo, 0, SEEK_SET); // Posiciona o ponteiro do arquivo original no início

    while ((prod = leProduto(arquivo)) != NULL) { // Lê produtos do arquivo original até o final
        if (prod->codigo == codigo) { // Verifica se o código do produto corresponde ao código a ser removido
            found = 1;  // Marca que o produto foi encontrado
            free(prod); // Libera a memória alocada para o produto
        } else {
            salvaProduto(prod, temp); // Salva o produto não removido no arquivo temporário
            free(prod); // Libera a memória alocada para o produto
        }
    }

    fclose(temp); // Fecha o arquivo temporário após a escrita

    if (found) {
        fclose(arquivo); // Fecha o arquivo original após a leitura
        remove("produtos.dat"); // Remove o arquivo original
        rename("temp.dat", "produtos.dat"); // Renomeia o arquivo temporário para o nome do arquivo original
        printf("\nProduto com codigo %d removido com sucesso.\n", codigo);
    } else {
        remove("temp.dat"); // Remove o arquivo temporário se o produto não foi encontrado
        printf("\nProduto com codigo %d nao encontrado.\n", codigo);
    }

    arquivo = fopen("produtos.dat", "rb"); // Reabre o arquivo original para leitura binária
    if (!arquivo) {
        perror("Nao foi possivel reabrir o arquivo produtos.dat");
        return;
    }   
}

void imprimirBaseProdutos(FILE *out) {
    printf("\nImprimindo a base de dados...\n");

    rewind(out); //Início do arquivo
    void *item;

    while ((item = leProduto(out)) != NULL) {
        imprimeProduto(item);
        free(item);
    }
}

int tamanhoArquivoProdutos(FILE *arq) {
    fseek(arq, 0, SEEK_END); // Move o ponteiro do arquivo para o final
    int tam = trunc(ftell(arq) / tamanhoRegistroProduto()); // Calcula o número de registros no arquivo, convertendo o resultado para inteiro
    return tam;
}

void criarBaseProdutos(FILE *out, int tam) {
    int ids[tam];
    for (int i = 0; i < tam; i++) {
        ids[i] = i + 1;
    }
    embaralha(ids, tam); // Embaralha os IDs para criar produtos em ordem aleatória
    Produto *p;
    for (int i = 0; i < tam; i++) {
        p = criaProduto(ids[i], "Produto", 10.0 * (ids[i]), tam - i);
        salvaProduto(p, out);
        free(p);
    }
    printf("\n\nBase criada com sucesso\n\n");
}

// Funcoes relacionadas ao Cliente
Cliente* criaCliente(int codigo, char *nome, char *cpf, char *endereco) {
    Cliente *cli = (Cliente *) malloc(sizeof(Cliente)); // Aloca memória para um novo Cliente
    if (cli) { // Verifica se a alocação foi bem-sucedida
        cli->codigo = codigo; 
        strcpy(cli->nome, nome); 
        strcpy(cli->cpf, cpf); 
        strcpy(cli->endereco, endereco); 
    }
    return cli; // Retorna o ponteiro para o novo cliente
}

int codigoExisteCli(int codigo, FILE* arq_cli) {
    rewind(arq_cli); // Volta ao início do arquivo
    Cliente* cli;
    while ((cli = leCliente(arq_cli)) != NULL) {
        if (cli->codigo == codigo) {
            free(cli);
            return 1; // Código já existe
        }
        free(cli);
    }
    return 0; // Código não existe
}

void salvaCliente(Cliente *cli, FILE *out) {
    fwrite(&cli->codigo, sizeof(int), 1, out);
    fwrite(cli->nome, sizeof(char), sizeof(cli->nome), out);
    fwrite(cli->cpf, sizeof(char), sizeof(cli->cpf), out);
    fwrite(cli->endereco, sizeof(char), sizeof(cli->endereco), out);
}

Cliente* leCliente(FILE *in) {
    Cliente *cli = (Cliente *) malloc(sizeof(Cliente)); // Aloca memória para um novo Cliente
    if (0 >= fread(&cli->codigo, sizeof(int), 1, in)) { // Lê o código do cliente e verifica se a leitura foi bem-sucedida
        free(cli); // Libera a memória alocada se a leitura falhar
        return NULL; // Retorna NULL se não for possível ler o cliente
    }
    fread(cli->nome, sizeof(char), sizeof(cli->nome), in); 
    fread(cli->cpf, sizeof(char), sizeof(cli->cpf), in); 
    fread(cli->endereco, sizeof(char), sizeof(cli->endereco), in); 
    return cli; // Retorna o ponteiro para o cliente lido
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
    FILE *temp = fopen("temp.dat", "wb"); // Abre um arquivo temporário para escrita binária
    if (!temp) { // Verifica se o arquivo temporário foi aberto com sucesso
        perror("Nao foi possivel abrir o arquivo temporario para escrita"); 
        return; 
    }

    Cliente *cli;
    int found = 0;
    fseek(arquivo, 0, SEEK_SET); // Posiciona o ponteiro no início do arquivo

    while ((cli = leCliente(arquivo)) != NULL) { // Lê clientes do arquivo até o final
        if (cli->codigo == codigo) { // Verifica se o código do cliente corresponde ao código a ser removido
            found = 1; // Marca que o cliente foi encontrado
            free(cli); // Libera a memória do cliente
        } else {
            salvaCliente(cli, temp); // Salva o cliente não removido no arquivo temporário
            free(cli); // Libera a memória do cliente
        }
    }

    fclose(temp); // Fecha o arquivo temporário após a escrita

    if (found) { 
        fclose(arquivo); // Fecha o arquivo original
        remove("clientes.dat"); // Remove o arquivo original
        rename("temp.dat", "clientes.dat"); // Renomeia o arquivo temporário para o nome do arquivo original
        printf("Cliente com codigo %d removido com sucesso.\n", codigo); 
    } else {
        remove("temp.dat"); // Remove o arquivo temporário se o cliente não foi encontrado
        printf("Cliente com codigo %d não encontrado.\n", codigo); 
    }
    arquivo = fopen("clientes.dat", "rb"); // Reabre o arquivo original para leitura binária
    if (!arquivo) { // Verifica se o arquivo foi reaberto com sucesso
        perror("Nao foi possivel reabrir o arquivo clientes.dat"); 
        return; 
    }   
}

void imprimirBaseCliente(FILE *out){
        printf("\nImprimindo a base de dados...\n");

    rewind(out); //Início do arquivo
    void *item;

    while ((item = leCliente(out)) != NULL) {
        imprimeCliente(item);
        free(item);
    }
}

int tamanhoArquivoClientes(FILE *arq) {
    fseek(arq, 0, SEEK_END); // Move o ponteiro do arquivo para o final
    int tam = trunc(ftell(arq) / tamanhoRegistroCliente()); // Calcula o número de registros no arquivo, convertendo o resultado para inteiro
    return tam;
}

void criarBaseClientes(FILE *out, int tam) {
    int ids[tam];
    for (int i = 0; i < tam; i++) {
        ids[i] = i + 1;
    }

    embaralha(ids, tam); // Embaralha os IDs para criar clientes em ordem aleatória
    char cpf[15];
    char endereco[100];
    Cliente *c;
    for (int i = 0; i < tam; i++) {
        gerarCPF(cpf);
        gerarEndereco(endereco);
        c = criaCliente(ids[i], "Cliente", cpf, endereco);
        salvaCliente(c, out);
        free(c);
    }
}

void gerarCPF(char* cpf) {
    int n1 = rand() % 1000;
    int n2 = rand() % 1000;
    int n3 = rand() % 1000;
    int n4 = rand() % 100;
    snprintf(cpf, 15, "%03d.%03d.%03d-%02d", n1, n2, n3, n4); // Formata e armazena o CPF gerado na string `cpf`
}

void gerarEndereco(char* endereco) {
    const char* ruas[] = {"Rua A", "Avenida B", "Travessa C", "Rua D", "Alameda E"};
    const char* bairros[] = {"Centro", "Jardins", "Bela Vista", "Morumbi", "Vila Madalena"};
    const char* cidades[] = {"São Paulo", "Rio de Janeiro", "Belo Horizonte", "Curitiba", "Porto Alegre"};
    
    int numero = rand() % 1000 + 1; // // Gerando um número de casa aleatório, gera um número de 1 a 1000
    // Selecionando uma rua, bairro e cidade aleatórios
    const char* rua = ruas[rand() % (sizeof(ruas) / sizeof(ruas[0]))];
    const char* bairro = bairros[rand() % (sizeof(bairros) / sizeof(bairros[0]))];
    const char* cidade = cidades[rand() % (sizeof(cidades) / sizeof(cidades[0]))];

    snprintf(endereco, 100, "%s, Numero %d, Bairro %s, %s", rua, numero, bairro, cidade); // Formatando o endereço
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

int codigoExistePed(int codigo, FILE* arq_ped) {
    rewind(arq_ped); // Volta ao início do arquivo
    Pedido* ped;
    while ((ped = lePedido(arq_ped)) != NULL) {
        if (ped->codigo == codigo) {
            free(ped);
            return 1; // Código já existe
        }
        free(ped);
    }
    return 0; // Código não existe
}

void salvaPedido(Pedido *ped, FILE *out) {
    fwrite(&ped->codigo, sizeof(int), 1, out);
    fwrite(&ped->codigo_cliente, sizeof(int), 1, out);
    fwrite(&ped->codigo_produto, sizeof(int), 1, out);
    fwrite(&ped->quantidade, sizeof(int), 1, out);
    fwrite(&ped->total, sizeof(double), 1, out);
}

Pedido* lePedido(FILE *in) {
    Pedido *ped = (Pedido *) malloc(sizeof(Pedido)); // Aloca memória para um novo Pedido
    if (0 >= fread(&ped->codigo, sizeof(int), 1, in)) { // Lê o código do pedido e verifica se a leitura foi bem-sucedida
        free(ped); // Libera a memória alocada se a leitura falhar
        return NULL; // Retorna NULL se não for possível ler o pedido
    }
    fread(&ped->codigo_cliente, sizeof(int), 1, in); 
    fread(&ped->codigo_produto, sizeof(int), 1, in); 
    fread(&ped->quantidade, sizeof(int), 1, in); 
    fread(&ped->total, sizeof(double), 1, in); 
    return ped; // Retorna o ponteiro para o pedido lido
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

void removePedido(int codigo, FILE *arquivo) {
    FILE *temp = fopen("temp.dat", "wb"); // Abre um arquivo temporário para escrita binária
    if (!temp) { // Verifica se o arquivo temporário foi aberto com sucesso
        perror("Nao foi possivel abrir o arquivo temporario para escrita");
        return; 
    }

    Pedido *ped;
    int found = 0; 
    fseek(arquivo, 0, SEEK_SET); // Posiciona o ponteiro no início do arquivo

    while ((ped = lePedido(arquivo)) != NULL) { // Lê pedidos do arquivo até o final
        if (ped->codigo == codigo) { // Verifica se o código do pedido corresponde ao código a ser removido
            found = 1; // Marca que o pedido foi encontrado
            free(ped); // Libera a memória do pedido
        } else {
            salvaPedido(ped, temp); // Salva o pedido não removido no arquivo temporário
            free(ped); // Libera a memória do pedido
        }
    }
    fclose(temp); // Fecha o arquivo temporário após a escrita

    if (found) { 
        fclose(arquivo); // Fecha o arquivo original
        remove("pedidos.dat"); // Remove o arquivo original
        rename("temp.dat", "pedidos.dat"); // Renomeia o arquivo temporário para o nome do arquivo original
        printf("Pedido com codigo %d removido com sucesso.\n", codigo); 
    } else {
        remove("temp.dat"); // Remove o arquivo temporário se o pedido não foi encontrado
        printf("Pedido com codigo %d nao encontrado.\n", codigo); 
    }
    arquivo = fopen("pedidos.dat", "rb"); // Reabre o arquivo original para leitura binária
    if (!arquivo) { // Verifica se o arquivo foi reaberto com sucesso
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

int tamanhoArquivoPedidos(FILE *arq) {
    fseek(arq, 0, SEEK_END); // Move o ponteiro do arquivo para o final
    int tam = trunc(ftell(arq) / tamanhoRegistroPedido()); // Calcula o número de registros no arquivo, convertendo o resultado para inteiro
    return tam;
}

void criarBasePedidos(FILE *out, int tam) {
    int ids[tam];
    for (int i = 0; i < tam; i++) {
        ids[i] = i + 1;
    }

    embaralha(ids, tam); // Embaralha os IDs para criar clientes em ordem aleatória
    Pedido *ped;
    for (int i = 0; i < tam; i++) {
        ped = criaPedido(ids[i], (i % 10) + 1, (i % 10) + 1, 1, 10.0 * (i + 1));
        salvaPedido(ped, out);
         free(ped);
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
    fseek(arq, 0, SEEK_END); // Move o ponteiro do arquivo para o final para obter o tamanho total do arquivo
    return (int)(ftell(arq) / tamanho_registro); // Calcula o número de registros com base no tamanho do registro e retorna como inteiro
}

void embaralha(int *array, int n) {
    if (n > 1) { 
        srand(time(NULL)); // Inicializa o gerador de números aleatórios com a hora atual
        for (int i = 0; i < n - 1; i++) { 
            int j = i + rand() / (RAND_MAX / (n - i) + 1); // Calcula um índice aleatório j para trocar
            int t = array[j]; 
            array[j] = array[i]; // Substitui o valor no índice j pelo valor no índice i
            array[i] = t; // Substitui o valor no índice i pelo valor armazenado em t
        }
    }
}