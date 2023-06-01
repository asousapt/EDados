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


void EscreveLG(ListaGenerica *lg, FILE *ficheiro, void (*f)(void *, FILE *)) {
  if (!lg || !ficheiro)
    return;
  NOG *P = lg->Inicio;
  while (P) {
    f(P->Info, ficheiro);
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
  //printf("\n <%s>\n", __FUNCTION__);
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

void removerNoLG(ListaGenerica* lg, NOG* noRemover) {
    if (lg->Inicio == NULL || noRemover == NULL) {
        return; // Lista vazia ou nó inválido
    }

    // Caso especial: o nó a ser removido é o primeiro da lista
    if (lg->Inicio == noRemover) {
        lg->Inicio = noRemover->Prox;
        free(noRemover);
        lg->NEL--;
        return;
    }

    // Procurar o nó anterior ao nó a ser removido
    NOG* anterior = lg->Inicio;
    while (anterior != NULL && anterior->Prox != noRemover) {
        anterior = anterior->Prox;
    }

    // Se não encontrarmos o nó anterior, o nó a ser removido não está presente na lista
    if (anterior == NULL) {
        return;
    }

    // reconectar os nos
    anterior->Prox = noRemover->Prox;
    free(noRemover);
    lg->NEL--;
    
}

//Devolve o maior elemento da Lista lg com o metodo de comparacao fcomp
void *Maior(ListaGenerica *lg, int (*fcomp)(void *, void *)){
  NOG *no = lg->Inicio;
  void *maior = no->Info;
  while(no){
    if(fcomp(no->Info,maior)>0){
      maior = no->Info;
    }
    no = no->Prox;
  }
  return maior;
}

//Devolve o menor elemento da Lista lg com o metodo de comparacao fcomp
void *Menor(ListaGenerica *lg, int (*fcomp)(void *, void *)){
  NOG *no = lg->Inicio;
  void *menor = no->Info;
  while(no){
    if(fcomp(no->Info,menor)<0){
      menor = no->Info;
    }
    no = no->Prox;
  }
  return menor;
}

//Recebe uma lista de ints e devolve a media de todos os elementos
float media(ListaGenerica *lg){
  float media;
  NOG *P = lg->Inicio;
  while(P){
    media += (int)P->Info;
    P = P->Prox;
  }
  return media;
}

c{
}