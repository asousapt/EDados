#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Caixa.h"
#include "Funcionarios.h"

// Criar objecto caixa
CAIXA* CriarCaixa(int numero){
  CAIXA* novaCaixa = (CAIXA *) malloc(sizeof(CAIXA));
  FILAGENERICA *filaCaixa = CriarFila();

  novaCaixa->numCaixa = numero; 
  novaCaixa->contadorPessoas = 0;
  novaCaixa->contadorProdutos = 0;
  novaCaixa->fechado = 1;
  novaCaixa->filaCaixa = filaCaixa;
  novaCaixa->func = NULL;
  novaCaixa->tempoEsperaReal = 0;
  novaCaixa->tempoEsperaMed = 0;
  novaCaixa->tempoTotal = 0;

  return novaCaixa;
}


void listarCaixas(ListaGenerica* listaCaixas) {
  printf("*****Caixas ******\n"); 
  printf("No | Caixa  | Estado  | Operador\n");
  ShowLG(listaCaixas, MostrarCaixa);
}

void MostrarCaixa(void* F){
  CAIXA* objCaixa = (CAIXA *) F;
  FUNCIONARIO* funcionario1 = objCaixa->func;
  char *nome = (char *)malloc(10);
  sprintf(nome,"%s %d", "Caixa ", objCaixa->numCaixa);
 if (objCaixa->func != NULL) {
  printf("%d - %s * %d * %s \n", objCaixa->numCaixa, nome, !objCaixa->fechado, funcionario1->nome);
 } else {
  printf("%d - %s * %d  \n", objCaixa->numCaixa, nome, !objCaixa->fechado);
 }

  free(nome);
  }


// Faz print de uma caixa aberta
void MostrarCaixaAberta(void* F){
  CAIXA* objCaixa = (CAIXA *) F;
  char *nome = (char *)malloc(10);
  sprintf(nome,"%s %d", "Caixa ", objCaixa->numCaixa);
  if (objCaixa->fechado == 0) {
    printf("%d - %s\n", objCaixa->numCaixa, nome);
  }
}

void MostrarCaixaFechada(void* F){
  CAIXA* objCaixa = (CAIXA *) F;
  char *nome = (char *)malloc(10);
  sprintf(nome,"%s %d", "Caixa ", objCaixa->numCaixa);
  if (objCaixa->fechado == 1) {
    printf("%d - %s\n", objCaixa->numCaixa, nome);
  }
}


void DestruirCaixa(void* F){
  CAIXA* objCaixa = (CAIXA *) F;
  DestruirFuncionario(objCaixa->func);
  //DestruirFila(objCaixa->filaCaixa, DestruirFuncionario); adicionar depois a funcao destruir
  free(objCaixa);
}

CAIXA* ProcurarCaixa(ListaGenerica *lg,int numero){
  CAIXA *cx,*cxR;
  NOG *P = lg->Inicio;
  while (P) {
    cx = P->Info;
    if (cx->numCaixa == numero) {
      cxR = cx;
    }
    P = P->Prox;
  }
  return cxR;
}


CAIXA* ProcurarCaixaAberta(ListaGenerica *lg,int numero){
  CAIXA *cx,*cxR;
  NOG *P = lg->Inicio;
  while (P) {
    cx = P->Info;
    if (cx->numCaixa == numero && cx->fechado == 0) {
      cxR = cx;
    }
    P = P->Prox;
  }
  return cxR;
}

// Funcao que abre e fecha caixas.
// Param Numero :
//        0 - Operacao manual feita pelo utilizador
//        <> numero de caixa passado automaticamente 
// Param operacao : 
//        0 - Fechar caixa 
//        1 - abrir caixa
void AbreFechaCaixa(SUPERMERCADO *super, int numero, int operacao){
  ListaGenerica * lg = (ListaGenerica *) super->Caixas;
  CAIXA* caixaEscolhida = (CAIXA *) malloc(sizeof(CAIXA));

  if (!lg) return;
  if (numero == 0  && operacao == 0) {
    printf("\n***** Caixas -> Fechar *****\n");
    ShowLG(super->Caixas, MostrarCaixaAberta);
    do
    {
      printf("Introduza o numero da caixa a fechar\n"); 
      scanf("%d", &numero); 
      
      caixaEscolhida = ProcurarCaixa(super->Caixas, numero); 

    } while (!caixaEscolhida || caixaEscolhida->fechado < 0 || caixaEscolhida->fechado >=1);
    
  }

  if (numero == 0 && operacao == 1) {
    printf("\n***** Caixas -> Abrir *****\n");
    ShowLG(super->Caixas, MostrarCaixaFechada);
    do
    {
      printf("Introduza o numero da caixa a abrir\n"); 
      scanf("%d", &numero); 
      caixaEscolhida = ProcurarCaixa(super->Caixas, numero); 
    } while (!caixaEscolhida || caixaEscolhida->fechado <= 0 || caixaEscolhida->fechado >1);
  }
   
  if (operacao == 0) {
    caixaEscolhida->fechado = 1;
    caixaEscolhida->func = NULL;
  } 
  else {
    caixaEscolhida->fechado = 0; 
    FUNCIONARIO* funcionarioAtribuir =  encontrarFuncionarioLivre(super->Funcionarios, super->Caixas);
    caixaEscolhida->func = funcionarioAtribuir;
  }
}

// Retorna o ponteiro com a caixa mais rapida ja contando com os clientes que estao na fila
CAIXA* caixaComMenorTempo(ListaGenerica* lista) {
  NOG* atual = lista->Inicio;
  CAIXA* caixaMenorTempoEsperaReal = NULL;
  float menorTempo = 999999; 

  while (atual != NULL) {
    CAIXA* caixaAtual = (CAIXA*)atual->Info;
    if (caixaAtual->fechado == 0) {
      if (caixaAtual->filaCaixa->tamanho > 0) { 
        if ((caixaAtual->tempoEsperaReal) < menorTempo) {
          menorTempo = caixaAtual->tempoEsperaReal;
          caixaMenorTempoEsperaReal = caixaAtual;
        }
      } else {
        return caixaAtual;   
      }     
  }
  atual = atual->Prox;
}
  return caixaMenorTempoEsperaReal;
}
