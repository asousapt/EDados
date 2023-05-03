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

// Criar objecto caixa
CAIXA* CriarCaixa(int numero ){
  CAIXA* novaCaixa = (CAIXA *) malloc(sizeof(CAIXA));
  char nome[10];
  sprintf(nome, "Caixa %d", numero);

  novaCaixa->numCaixa = numero; 
  novaCaixa->contadorPessoas = 0;
  novaCaixa->contadorProdutos = 0;
  novaCaixa->fechado = 1;
  // novaCaixa->filaCaixa
  novaCaixa->func = NULL;
  novaCaixa->tempoEspera = 0;
  novaCaixa->NomeCaixa = (char*) malloc(strlen(nome) + 1);
  strcpy(novaCaixa->NomeCaixa, nome);

  return novaCaixa;
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