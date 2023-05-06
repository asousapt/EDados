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

PRODUTO* CriarProduto(char* codigo, char* designacao, char* preco, char* tempoCompra, char* tempoCaixa );
void MostrarProduto(void* P);
void DestruirProduto(void* P);
PRODUTO* ProcurarProdutos(ListaGenerica *lg,int codProduto);

#endif // PRODUTOS_H_INCLUDED