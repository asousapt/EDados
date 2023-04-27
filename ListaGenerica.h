#ifndef LISTAGENERICA_H_INCLUDED
#define LISTAGENERICA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Fila.h"


typedef struct NOG{
    void *Info;
    struct NOG *Prox;
}NOG;

typedef struct{
    int NEL;
    NOG *Inicio;
}ListaGenerica;

typedef struct cliente {
    int cod;
    char* nome;
    // time_t entrada;
    // time_t saida;
    // int tempoEspera;
} CLIENTE;

typedef struct funcionario {
    int cod;
    char *nome;
} FUNCIONARIO;

typedef struct produto{
    int cod;
    char *designacao;
    float preco;
    float tempoCompra;
    float tempoCaixa;
} PRODUTO;

typedef struct caixa {
    int numCaixa;
    int fechado; //1-fechado; 0-aberto
    time_t tempoEspera; //medio
    int contadorPessoas,contadorProdutos;
    FUNCIONARIO func;
    Filagenerica* filaCaixa;
} CAIXA;

ListaGenerica * CriarLG();
PRODUTO* CriarProduto(char* codigo, char* designacao, char* preco, char* tempoCompra, char* tempoCaixa );
CLIENTE* CriarCliente(char* numeroCliente,char* NomeCliente);
FUNCIONARIO* CriarFuncionario(char* numeroFuncionario,char* nomeFuncionario);
void DestruirLG(ListaGenerica *lg, void (*fdest)(void *));
void ShowLG(ListaGenerica *lg, void (*f)(void *));
void AddBeginLG(ListaGenerica *lg, void *X);
int PertenceLG(ListaGenerica *lg, void *X, int (*fcomp)(void *, void *));

#endif // LISTAGENERICA_H_INCLUDED