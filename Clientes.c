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

int VerificaClienteAsCompras (SUPERMERCADO *S,int codigoCliente){
  CLIENTE *cl;
  NOG *P = S->ClientesAsCompras->Inicio;
  int retorna = 0;
  while (P) {
    cl = P->Info;
    if (cl->cod == codigoCliente) {
      retorna = 1;//encontrou
    }
    P = P->Prox;
  }

  //1->Encontrou cliente as compras
  //0->Não encontrou cliente as compras
  return retorna;
}

CLIENTEASCOMPRAS* ProcurarClienteAsCompras (ListaGenerica *lg,int codigoCliente){
  CLIENTEASCOMPRAS *cl,*clR;
  NOG *P = lg->Inicio;
  while (P) {
    cl = P->Info;
    if (cl->cliente->cod == codigoCliente) {
      clR = cl;
    }
    P = P->Prox;
  }
  return clR;
}

void AdicionarClienteAsCompras(SUPERMERCADO *S){
  int altCliente = 0,skip = 0,icr = 1;
  CLIENTE *cl;

  while (skip == 0){
    altCliente = aleatorio(1,1000);
    
    NOG *P = S->Clientes->Inicio;
    while (P) {
      if (icr == altCliente) {
        CLIENTE *temp = P->Info;
        int codigo = temp->cod;
        if (VerificaClienteAsCompras(S,codigo) == 0){
          skip = 1;
          cl = P->Info;
        }
        break;
      }
      P = P->Prox;
      icr++;
    }
  }
  
  int nProd = aleatorio(5,40); 
  CLIENTEASCOMPRAS* NovoCliente = (CLIENTEASCOMPRAS *) malloc(sizeof(CLIENTEASCOMPRAS));
  NovoCliente->cliente = cl;
  NovoCliente->nProdutos = nProd;
  NovoCliente->Produtos = CriarLG(); 
  AddBeginLG(S->ClientesAsCompras,NovoCliente);
}

void MostrarClientesAsCompras(void* C){
  CLIENTEASCOMPRAS* objClienteCompras = (CLIENTEASCOMPRAS *) C;
  CLIENTE* objCliente = objClienteCompras->cliente;
  printf("\n === Cliente No Supermercado ===");
  printf("\n Numero: %d", objCliente->cod);
  printf("\n Nome: %s", objCliente->nome);
  printf("\n === Produtos do Cliente ===");

  ShowLG(objClienteCompras->Produtos,MostrarProduto);
}

void AdicionarProdutoAoCliente(SUPERMERCADO *S,int codigo){
  int icr = 1, altProd = aleatorio(1,1000);

  CLIENTEASCOMPRAS *CC = ProcurarClienteAsCompras(S->ClientesAsCompras,numero);
  if (!CC) return;

  PRODUTO *Prod;
  NOG *P = S->Produtos->Inicio;
  while (P) {
    if (icr == altProd) {
        Prod = P->Info;
      break;
    }
    P = P->Prox;
    icr++;
  }

  AddBeginLG(CC->Produtos,Prod);
}

