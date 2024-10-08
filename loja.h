#ifndef ARTIGOS_ESPORTIVOS_H
#define ARTIGOS_ESPORTIVOS_H

#include <stdio.h>

// Definindo a estrutura do Produto
typedef struct {
    int codigo;
    char nome[50];
    double preco;
    int quantidade;
} Produto;

// Definindo a estrutura do Cliente
typedef struct {
    int codigo;
    char nome[50];
    char cpf[15];
    char endereco[100];
} Cliente;

// Definindo a estrutura do Pedido
typedef struct {
    int codigo;
    int codigo_cliente;
    int codigo_produto;
    int quantidade;
    double total;
} Pedido;

// Funcoes relacionadas ao Produto
Produto* criaProduto(int codigo, char *nome, double preco, int quantidade);
int codigoExisteProd(int codigo, FILE* arq_prod);
void salvaProduto(Produto *prod, FILE *out);
Produto* leProduto(FILE *in);
void imprimeProduto(Produto *prod);
void removeProduto(int codigo, FILE *arquivo);
void imprimirBaseProdutos(FILE *out);
int tamanhoArquivoProdutos(FILE *arq);
void criarBaseProdutos(FILE *out, int tam);

// Funcoes relacionadas ao Cliente
Cliente* criaCliente(int codigo, char *nome, char *cpf, char *endereco);
int codigoExisteCli(int codigo, FILE* arq_cli);
void salvaCliente(Cliente *cli, FILE *out);
Cliente* leCliente(FILE *in);
void imprimeCliente(Cliente *cli);
void removeCliente(int codigo, FILE *arquivo);
void imprimirBaseCliente(FILE *out);
int tamanhoArquivoClientes(FILE *arq);
void criarBaseClientes(FILE *out, int tam);
void gerarCPF(char* cpf);
void gerarEndereco(char* endereco);

// Funcoes relacionadas ao Pedido
Pedido* criaPedido(int codigo, int codigo_cliente, int codigo_produto, int quantidade, double total);
int codigoExistePed(int chave, FILE* arq_ped);
void salvaPedido(Pedido *ped, FILE *out);
Pedido* lePedido(FILE *in);
void imprimePedido(Pedido *ped);
void removePedido(int codigo, FILE *arquivo);
void imprimirBasePedido(FILE *out);
int tamanhoArquivoPedidos(FILE *arq);
void criarBasePedidos(FILE *out, int tam);

// Funcoes auxiliares
int tamanhoRegistroProduto();
int tamanhoRegistroCliente();
int tamanhoRegistroPedido();
int qtdRegistros(FILE *arq, int tamanho_registro);
void embaralha(int *array, int n);

#endif // ARTIGOS_ESPORTIVOS_H