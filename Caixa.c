#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Fila.h"
#include "Caixa.h"


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

// Faz print de uma caixa 
void MostrarCaixa(void* F){
  CAIXA* objCaixa = (CAIXA *) F;
  char *nome = (char *)malloc(10);
  sprintf(nome,"%s %d", "Caixa", objCaixa->numCaixa);
  printf("\n === Caixa ===");
  printf("\n Numero: %d", objCaixa->numCaixa);
  printf("\n Nome: %s", nome);
  printf("\n Fechado: %d\n", objCaixa->fechado);
}


void DestruirCaixa(void* F){
  CAIXA* objCaixa = (CAIXA *) F;
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

void AbreFechaCaixa(ListaGenerica *lg){
  if (!lg) return;
  int numero = validarInt("Número Caixa:",0,100);
    
  CAIXA *cx = ProcurarCaixa(lg,numero);
  if (cx){
    cx->fechado = !(cx->fechado);
  }
}

// Retorna o ponteiro com a caixa mais rapida
CAIXA* caixaComMenorTempo(ListaGenerica* lista) {
    NOG* atual = lista->Inicio;
    CAIXA* caixaMenorTempoEsperaReal = NULL;
    float menorTempo = 999999; 

    while (atual != NULL) {
        CAIXA* caixaAtual = (CAIXA*)atual->Info;
        
        float tempoProdutos = 0;
        if (caixaAtual->filaCaixa->tamanho > 0) {
          tempoProdutos =calcularTempoTotalCompra(caixaAtual->filaCaixa);
        }

        if ((caixaAtual->tempoEsperaReal+tempoProdutos) < menorTempo) {
            menorTempo = caixaAtual->tempoEsperaReal+tempoProdutos;
            caixaMenorTempoEsperaReal = caixaAtual;
        }
        

        atual = atual->Prox;
    }

    return caixaMenorTempoEsperaReal;
}
