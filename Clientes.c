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