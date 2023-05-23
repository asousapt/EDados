#ifndef CAIXA_H_INCLUDED
#define CAIXA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "supermercado.h"
#include "Fila.h"
#include "Funcionarios.h"
#include "ListaGenerica.h"
#include "funcoes.h"
#include "Clientes.h"

typedef struct caixa {
    int numCaixa;
    int fechado; //1-fechado; 0-aberto
    float tempoTotal;
    float tempoEsperaMed; //medio
    float tempoEsperaReal;
    int contadorPessoas,contadorProdutos;
    FUNCIONARIO* func;
    FILAGENERICA* filaCaixa;
} CAIXA;

int tempoEsperaMin(void* C);
CAIXA* CriarCaixa(int numero);
void MostrarCaixaAberta(void* F);
void MostrarCaixaFechada(void* F);
void DestruirCaixa(void *obj);
CAIXA* ProcurarCaixa(ListaGenerica *lg,int numero);
CAIXA* ProcurarCaixaAberta(ListaGenerica *lg,int numero);
void AbrirCaixa(ListaGenerica *lg);
void MostrarCaixasEstado(ListaGenerica *lg,int estado);
CAIXA* caixaComMenorTempo(ListaGenerica* lista);
void AbreFechaCaixa(SUPERMERCADO *super, int numero, int operacao);
void MostrarCaixa(void* F); 
void listarCaixas(ListaGenerica* listaCaixas); 

#endif // CAIXA_H_INCLUDED