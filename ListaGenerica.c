#include <stdio.h>
#include "ListaGenerica.h"
#include "Fila.h"

CLIENTE* CriarCliente(char* numeroCliente,char* nomeCliente){
  CLIENTE* NovoCliente = (CLIENTE *) malloc(sizeof(CLIENTE));
 

  NovoCliente->cod = atoi(numeroCliente);
   NovoCliente->nome = (char*) malloc(strlen(nomeCliente) + 1);
    strcpy(NovoCliente->nome, nomeCliente);

  return NovoCliente;
}

//Cria um novo objecto funcionario 
FUNCIONARIO* CriarFuncionario(char* numeroFuncionario,char* nomeFuncionario) {
  FUNCIONARIO* novoFuncionario = (FUNCIONARIO *) malloc(sizeof(FUNCIONARIO));
 
  novoFuncionario->cod = atoi(numeroFuncionario);
  novoFuncionario->nome = (char*) malloc(strlen(nomeFuncionario) + 1);
  strcpy(novoFuncionario->nome, nomeFuncionario);

  return novoFuncionario;
}

// cria um novo objecto produto 
PRODUTO* CriarProduto(char* codigo, char* designacao, char* preco, char* tempoCompra, char* tempoCaixa ){
  PRODUTO* novoProduto = (PRODUTO *) malloc(sizeof(PRODUTO));

  novoProduto->cod = atoi(codigo); 
  novoProduto->designacao = (char*) malloc(strlen(designacao) + 1);
  strcpy(novoProduto->designacao, designacao);
  novoProduto->preco = atof(preco); 
  novoProduto->tempoCaixa = atof(tempoCaixa);
  novoProduto->tempoCompra = atof(tempoCompra);

  return novoProduto;
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
  NOG *Pproximo;
  while (P) {
    Pproximo = P->Prox;
    fdest(P->Info);
    free(P);
    P = Pproximo;
  }
  free(lg);
}

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