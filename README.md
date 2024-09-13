# LOJA DE ARTIGOS ESPORTIVOS

Este projeto é uma aplicação de linha de comando para gerenciar produtos, clientes e pedidos de uma loja. Ele oferece várias funcionalidades para manutenção e interação com esses conjuntos de dados.

## BIBLIOTECAS UTILIZADAS

- `stdio.h`: https://www.ibm.com/docs/pt-br/i/7.5?topic=files-stdioh
  - Fornece funções para operações de entrada e saída padrão, como printf, scanf, fopen, fclose, fread, e fwrite. É fundamental para a comunicação com o usuário e manipulação de arquivos.
- `stdlib.h`: https://www.ibm.com/docs/pt-br/i/7.5?topic=files-stdlibh
  - Contém funções para gerenciamento de memória, controle de processos e conversão de tipos, como malloc, free, exit, atoi, e qsort. É usada para operações de alocação dinâmica e controle de execução do programa.
- `string.h`: https://www.ibm.com/docs/pt-br/i/7.5?topic=files-stringh
  - Oferece funções para manipulação de strings e arrays de caracteres, como strcpy, strlen, strcmp, e strcat. É essencial para trabalhar com cadeias de caracteres e realizar operações básicas sobre elas.
- `time.h`: https://www.ibm.com/docs/pt-br/i/7.5?topic=files-timeh
  - Fornece funções para manipulação de data e hora, como time, localtime, strftime, e clock. É usado para obter e formatar informações sobre o tempo e realizar medições de duração.
- `stdbool.h`: https://www.ibm.com/docs/pt-br/i/7.5?topic=files-stdboolh
  - Fornece definições para o tipo booleano e os valores lógicos true e false. É utilizada para melhorar a legibilidade do código ao trabalhar com condições lógicas e valores booleanos.

## Funcionalidades

### Gerenciamento de Produtos
O menu de produtos oferece as seguintes funcionalidades:

1. **Gerar Produtos Aleatórios**: Gerar produtos aleatórios e adicioná-los à lista de produtos.
2. **Ler Arquivo**: Exibir o conteúdo do arquivo de produtos.
3. **Ordenar Produtos**: Ordenar a lista de produtos pelo código do produto.
4. **Busca Sequencial**: Procurar um produto usando busca sequencial pelo seu código.
5. **Busca Binária**: Procurar um produto usando busca binária pelo seu código.
6. **Adicionar Produto**: Adicionar um novo produto à lista de produtos da loja.
7. **Remover Produto**: Remover um produto da lista de produtos pelo seu código.
8. **Selecao Natural**: Divide a base de produtos em partições ordenadas pelo seu código.
9. **Intercalaçao**: Intercala partições de produtos, ordenando-as pelo seu código e gravando-as no arquivo final.

### Gerenciamento de Clientes
O menu de clientes oferece as seguintes funcionalidades:

1. **Gerar Clientes Aleatórios**: Gerar dados de clientes aleatórios e adicioná-los à lista de clientes.
2. **Ler Lista de Clientes**: Exibir o conteúdo do arquivo de clientes.
3. **Ordenar Clientes**: Ordenar a lista de produtos pelo código do cliente.
4. **Busca Sequencial**: Procurar um cliente usando busca sequencial pelo seu código.
5. **Busca Binária**: Procurar um cliente usando busca binária pelo seu código.
6. **Adicionar Cliente**: Adicionar um novo cliente à lista de clientes.
7. **Remover Cliente**: Remover um cliente da lista de clientes pelo seu código.
8. **Selecao Natural**: Divide a base de clientes em partições ordenadas pelo seu código.
9. **Intercalaçao**: Intercala partições de clientes, ordenando-as pelo seu código e gravando-as no arquivo final.

### Gerenciamento de Pedidos
O menu de pedidos oferece as seguintes funcionalidades:

1. **Gerar Pedidos Aleatórios**: Gerar dados de pedidos aleatórios e adicioná-los à lista de pedidos.
2. **Imprimir Lista de Pedidos**: Exibir o conteúdo do arquivo de pedidos.
3. **Ordenar por Código de Pedido**: Ordenar a lista de pedidos pelo código do pedido.
4. **Busca Sequencial**: Procurar um pedido usando busca sequencial pelo seu código.
5. **Busca Binária**: Procurar um pedido usando busca binária pelo seu código.
6. **Adicionar Pedido**: Realizar um pedido de um produto especificando o codigo do produto e do cliente e quantidade.
7. **Remover Pedido**: Remover um pedido da lista de pedidos pelo seu código.
8. **Selecao Natural**: Divide a base de pedidos em partições ordenadas pelo seu código.
9. **Intercalaçao**: Intercala partições de pedidos, ordenando-as pelo seu código e gravando-as no arquivo final.

## Como Executar

Para executar a aplicação, siga estas etapas:
1. Certifique-se de ter um compilador C instalado
2. Salve o código C em um arquivo
3. Abra um terminal ou prompt de comando, navegue até o diretório onde o código foi salvo e compile o código usando o compilador C com o seguinte comando: 
    ```bash
    gcc loja.h loja.c main.c selectionSort.c selectionSort.h buscaBinaria.c buscaBinaria.h buscaSequencial.c buscaSequencial.h selecaoNatural.h selecaoNatural.c intercalacao.h intercalacao.c -o main.exe
    ```
4. Execute o programa pelo `main.exe`

## Manipulação de Dados

### A aplicação armazena e manipula todos os  dados diretamente em disco.

- `produtos.dat` para dados de produtos.
- `clientes.dat` para dados de clientes.
- `pedidos.dat` para dados de pedidos.

* As partições da Seleção Natural são criadas nos seguintes diretórios:
  - `particoes/produtos/`
  - `particoes/clientes/`
  - `particoes/pedidos/`
- Certifique-se de que estas pastas existam nos arquivos do programa para o correto funcionamento.