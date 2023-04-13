#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

#include <stdio.h>
#include "ListaGenerica.h"

typedef struct NOFila{
    CLIENTE   *Info;
    struct NO *Prox;
} NOFILA;

typedef struct FilaEspera {
    NOFILA *Inicio;
    NOFILA *Fim;
    int NEL;
} FILAESPERA;

#endif // FILA_H_INCLUDED