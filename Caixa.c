#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Caixa.h"

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

// Faz print de uma caixa 
void MostrarCaixa(void* F){
  CAIXA* objCaixa = (CAIXA *) F;
  printf("\n === Caixa ===");
  printf("\n Numero: %d", objCaixa->numCaixa);
  printf("\n Nome: %s", objCaixa->NomeCaixa);
  printf("\n Fechado: %d\n", objCaixa->fechado);
}

void AbrirCaixa(ListaGenerica *lg){
  int numero = validarInt("Número Caixa:",0,100);
    
  if (!lg) return;
  CAIXA *cx;
  NOG *P = lg->Inicio;
  while (P) {
    cx = P->Info;
    if (cx->numCaixa == numero) {
      cx->fechado = 0;
    }
    P = P->Prox;
  }
}