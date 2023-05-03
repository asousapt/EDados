#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    void *Dados;
    struct NOFILA *Prox;
} NOFILA;

typedef struct Filagenerica {
    NOFILA *cabeca;
    NOFILA *cauda;
    int tamanho;
} FILAGENERICA;

#endif FILA_H_INCLUDED
