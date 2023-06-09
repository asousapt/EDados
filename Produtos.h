#ifndef PRODUTOS_H_INCLUDED
#define PRODUTOS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "supermercado.h"
#include "Clientes.h"
#include "Relogio.h"

typedef struct produto{
    int cod;
    char *designacao;
    float preco;
    float tempoCompra;
    float tempoCaixa;
} PRODUTO;

typedef struct produtoscliente{
    PRODUTO *produtoCL;
    int quantidade;
} PRODUTOCLIENTE;

PRODUTO* CriarProduto(char* codigo, char* designacao, char* preco, char* tempoCompra, char* tempoCaixa);
void MostrarProduto(void* P);
void DestruirProduto(void* P);
PRODUTO* ProcurarProdutos(ListaGenerica *lg,int codProduto);
int validaProduto(void *elem1, void *elem2);

//FUNCOES: PRODUTOCLIENTE
int GetQuantidadeProdutoCliente(ListaGenerica *lg, PRODUTO *P);
PRODUTOCLIENTE *GetProdutoCliente(ListaGenerica *lg, PRODUTO *P);
void AdicionarProdutoAoCliente(SUPERMERCADO *S,CLIENTEASCOMPRAS *CC, RELOGIO* R);
void AdicionarTodosOsProdutosAosClientes(SUPERMERCADO *S,CLIENTEASCOMPRAS *CC,RELOGIO *R);
void MostrarProdutoCliente(void* P);
void DestruirProdutoCliente(void *x);
int ofereceProduto(SUPERMERCADO * S, float tempoEsparaNaFila);
PRODUTO* produtoMaisBarato(CLIENTEASCOMPRAS* CC);
float tempoProcessarProdutosCaixa(CLIENTEASCOMPRAS* CC);
float totalValorProdutosOferecidos(ListaGenerica* lg);

#endif // PRODUTOS_H_INCLUDED