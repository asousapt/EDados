#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Relogio.h"
#include "ListaGenerica.h"

typedef struct NOFILA{
    void *Dados;
    struct NOFILA *Prox;
} NOFILA;

typedef struct Filagenerica {
    NOFILA *cabeca;
    NOFILA *cauda;
    int tamanho;
} FILAGENERICA;

FILAGENERICA *CriarFila();
int FilaVazia(FILAGENERICA *fila);
void AdicionaAFila(FILAGENERICA *fila, void *dados);
void *RetirarDaFilaInicio(FILAGENERICA *fila);
void *RetirarDaFila(FILAGENERICA *fila, int (comp)(void *, void *), void *dadosRemover);
void MostrarFila(FILAGENERICA *Fila, void (*f)(void *));
void DestruirFila(FILAGENERICA *fila, void (*f)(void *));

#endif
