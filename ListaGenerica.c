#include <stdio.h>
#include "ListaGenerica.h"
#include "Fila.h"


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
  NOG *Pproximo;
  while (P) {
    Pproximo = P->Prox;
    fdest(P->Info);
    free(P);
    P = Pproximo;
  }
  free(lg);
}

<<<<<<< HEAD
void DestruirCliente(void *obj){
  CLIENTE *cliente = (CLIENTE *) obj;
  free(cliente->nome);
}

void DestruirFuncionario(void *obj){
  FUNCIONARIO *funcionario = (FUNCIONARIO *) obj;
  free(funcionario->nome);
}

void DestruirProduto(void *obj){
  PRODUTO *produto = (PRODUTO *) obj;
  free(produto->designacao);
}

void DestruirCaixa(void *obj){
  CAIXA *caixa = (CAIXA *) obj;
  free(caixa->func);
  //Destruir Fila na caixas
}

=======
>>>>>>> ccaab5cb81d227b08d1254c9cc10845951113dbf
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