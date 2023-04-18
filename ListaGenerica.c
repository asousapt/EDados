#include <stdio.h>
#include "ListaGenerica.h"
#include "Fila.h"

CLIENTE* CriarCliente(char* numeroCliente,char* nomeCliente){
  CLIENTE* NovoCliente = (CLIENTE *) malloc(sizeof(CLIENTE));
  
  NovoCliente->cod = atoi(numeroCliente);
  strcpy(NovoCliente->nome,nomeCliente);
  return NovoCliente;
}

ListaGenerica *CriarLG() {
  printf("\n <%s>\n", __FUNCTION__);
  ListaGenerica *L = (ListaGenerica *)malloc(sizeof(ListaGenerica));
  L->Inicio = NULL;
  L->NEL = 0;

  return L;
}

void DestruirLG(ListaGenerica *lg, void (*fdest)(void *)) {
  printf("\n <%s>\n", __FUNCTION__);
  if (!lg)
    return;
  NOG *P = lg->Inicio;
  NOG *Rafael;
  while (P) {
    Rafael = P->Prox;
    fdest(P->Info);
    free(P);
    P = Rafael;
  }
  free(lg);
}


void ShowLG(ListaGenerica *lg, void (*f)(void *)) {
  printf("\n<%s>\n", __FUNCTION__);
  if (!lg)
    return;
  NOG *P = lg->Inicio;
  while (P) {
    f(P->Info);
    P = P->Prox;
  }
}

void AddBeginLG(ListaGenerica *lg, void *X) {
  printf("\n<%s>\n", __FUNCTION__);
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