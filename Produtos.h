#ifndef PRODUTOS_H_INCLUDED
#define PRODUTOS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Produtos.h"

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


PRODUTO* CriarProduto(char* codigo, char* designacao, char* preco, char* tempoCompra, char* tempoCaixa );
void MostrarProduto(void* P);
void DestruirProduto(void* P);
PRODUTO* ProcurarProdutos(ListaGenerica *lg,int codProduto);
int validaProduto(void *elem1, void *elem2);

#endif // PRODUTOS_H_INCLUDED