#ifndef LISTAGENERICA_H
#define LISTAGENERICA_H
#include <stdio.h>
#include <stdlib.h>

typedef struct NOG
{
    void *Info;
    struct NOG *Prox;
}NOG;

typedef struct 
{
    int NEL;
    NOG *Inicio;
}ListaGenerica;

ListaGenerica * CriarLG();
void DestruirLG(ListaGenerica *lg, void (*fdest)(void *));
void ShowLG(ListaGenerica *lg, void (*f)(void *));
void AddBeginLG(ListaGenerica *lg, void *X);
int PertenceLG(ListaGenerica *lg, void *X, int (*fcomp)(void *, void *));

#endif 