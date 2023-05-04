#ifndef LISTAGENERICA_H_INCLUDED
#define LISTAGENERICA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Fila.h"
#include "Caixa.h"


typedef struct NOG{
    void *Info;
    struct NOG *Prox;
}NOG;

typedef struct{
    int NEL;
    NOG *Inicio;
}ListaGenerica;


typedef struct produto{
    int cod;
    char *designacao;
    float preco;
    float tempoCompra;
    float tempoCaixa;
} PRODUTO;


ListaGenerica * CriarLG();
PRODUTO* CriarProduto(char* codigo, char* designacao, char* preco, char* tempoCompra, char* tempoCaixa );
void DestruirLG(ListaGenerica *lg, void (*fdest)(void *));
void DestruirCliente(void *obj);
void DestruirFuncionario(void *obj);
void DestruirProduto(void *obj);
void DestruirCaixa(void *obj);
void ShowLG(ListaGenerica *lg, void (*f)(void *));
void AddBeginLG(ListaGenerica *lg, void *X);
int PertenceLG(ListaGenerica *lg, void *X, int (*fcomp)(void *, void *));

#endif // LISTAGENERICA_H_INCLUDED