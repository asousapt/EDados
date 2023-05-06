#include <stdio.h>
#include "ListaGenerica.h"
#include "Fila.h"


ListaGenerica *CriarLG() {
  ListaGenerica *L = (ListaGenerica *)malloc(sizeof(ListaGenerica));
  L->Inicio = NULL;
  L->NEL = 0;

  return L;
}

void DestruirLG(ListaGenerica *lg, void (*fdest)(void *)) {
  if (!lg)
    return;
  NOG *P = lg->Inicio;
  NOG *Pproximo;
  while (P) {
    Pproximo = P->Prox;
    fdest(P->Info);
    free(P);
    P = Pproximo;
  }
  free(lg);
}

void ShowLG(ListaGenerica *lg, void (*f)(void *)) {
  if (!lg)
    return;
  NOG *P = lg->Inicio;
  while (P) {
    f(P->Info);
    P = P->Prox;
  }
}

void AddBeginLG(ListaGenerica *lg, void *X) {
  //printf("\n<%s>\n", __FUNCTION__);
  if (!lg || !X)
    return;
  NOG *novono = (NOG *)malloc(sizeof(NOG));
  novono->Prox = lg->Inicio;
  novono->Info = X;
  lg->Inicio = novono;
  lg->NEL++;
}
int PertenceLG(ListaGenerica *lg, void *X, int (*fcomp)(void *, void *)) {
  printf("\n <%s>\n", __FUNCTION__);
  if (!lg || !X)
    return 0;
  NOG *P = lg->Inicio;
  while (P) {
    if (fcomp(P->Info, X) == 1)
      return 1;
    P = P->Prox;
  }
  return 0;
}