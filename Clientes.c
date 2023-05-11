#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Clientes.h"

CLIENTE* CriarCliente(char* numeroCliente,char* nomeCliente){
  CLIENTE* NovoCliente = (CLIENTE *) malloc(sizeof(CLIENTE));
 
  NovoCliente->cod = atoi(numeroCliente);
   NovoCliente->nome = (char*) malloc(strlen(nomeCliente) + 1);
    strcpy(NovoCliente->nome, nomeCliente);

  return NovoCliente;
}

// Funcao que faz a validacao se o cliente ja existe na lista 
int validaCliente(void *elem1, void *elem2) {
  CLIENTE* cliente1 = (CLIENTE *) elem1;
  CLIENTE* cliente2 = (CLIENTE *) elem2;

  if (cliente1->cod == cliente2->cod) return 1; 
  
  return 0;
}

// Faz print de um cliente 
void MostrarCliente(void* C){
  CLIENTE* objCliente = (CLIENTE *) C;
  printf("\n === Cliente ===");
  printf("\n Numero: %d", objCliente->cod);
  printf("\n Nome: %s", objCliente->nome);
}

//funcao que limpa da memoria o cliente 
void DestruirCliente(void* C){
  CLIENTE* objCliente = (CLIENTE *) C;
  free(objCliente);
}

CLIENTE* ProcurarCliente (ListaGenerica *lg,int codigoCliente){
  CLIENTE *cl,*clR;
  NOG *P = lg->Inicio;
  while (P) {
    cl = P->Info;
    if (cl->cod == codigoCliente) {
      clR = cl;
    }
    P = P->Prox;
  }
  return clR;
}

// void AdicionarClienteCaixa(ListaGenerica *lgCx,ListaGenerica *lgCl,int numeroCaixa,int codigoCliente){
//   if (!lgCx || !lgCl) return;
//   CAIXA *cx = ProcurarCaixaAberta(lgCx,numeroCaixa);
//   CLIENTE *cl ;
// }