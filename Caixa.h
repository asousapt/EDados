#ifndef CAIXA_H_INCLUDED
#define CAIXA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Funcionarios.h"
#include "ListaGenerica.h"
#include "funcoes.h"

typedef struct caixa {
    int numCaixa;
    int fechado; //1-fechado; 0-aberto
    float tempoEspera; //medio
    int contadorPessoas,contadorProdutos;
    FUNCIONARIO* func;
    FILAGENERICA* filaCaixa;
} CAIXA;

CAIXA* CriarCaixa(int numero );
void MostrarCaixa(void* F);
void DestruirCaixa(void *obj);
CAIXA* ProcurarCaixa(ListaGenerica *lg,int numero);
CAIXA* ProcurarCaixaAberta(ListaGenerica *lg,int numero);
<<<<<<< HEAD
void AbrirCaixa(ListaGenerica *lg);
void MostrarCaixasEstado(ListaGenerica *lg,int estado);
=======
void AbreFechaCaixa(ListaGenerica *lg);
>>>>>>> d0da29751b065e3e44ad55991571479a509a20c8

#endif // CAIXA_H_INCLUDED