#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Clientes.h"
#include "supermercado.h"
#include "Produtos.h"

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
  free(objCliente->nome);
  free(objCliente);
}

CLIENTE* ProcurarCliente(ListaGenerica *lg,int codigoCliente){
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

int VerificaClienteAsCompras(SUPERMERCADO *S,int codigoCliente){
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

CLIENTEASCOMPRAS* ProcurarClienteAsCompras(ListaGenerica *lg,int codigoCliente){
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

void AdicionarClienteAsCompras(SUPERMERCADO *S,RELOGIO *R){
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

  int nProd = aleatorio(1,5); 
  CLIENTEASCOMPRAS* NovoCliente = (CLIENTEASCOMPRAS *) malloc(sizeof(CLIENTEASCOMPRAS));
  NovoCliente->cliente = cl;
  NovoCliente->nProdutos = nProd;
  NovoCliente->ProdutosClientes = CriarLG();
  NovoCliente->horaEntradaSuper = VerTimeRelogio(R);
  AddBeginLG(S->ClientesAsCompras,NovoCliente);

  AdicionarTodosOsProdutosAosClientes(S,NovoCliente,R);
} 

void MostrarClientesAsCompras(void* C){
  CLIENTEASCOMPRAS* objClienteCompras = (CLIENTEASCOMPRAS *) C;
  CLIENTE* objCliente = objClienteCompras->cliente;
  printf("\n === Cliente No Supermercado ===");
  printf("\n Numero: %d", objCliente->cod);
  printf("\n Nome: %s", objCliente->nome);
  printf(" Nº de Produtos: %d", objClienteCompras->nProdutos);
  
  struct tm *tmp = localtime(&objClienteCompras->horaEntradaSuper);
  printf("\n Entrada Supermercado: %dh%dm", tmp->tm_hour,tmp->tm_min);

  tmp = localtime(&objClienteCompras->horaEntradaFila);
  printf("\n Entrada Caixa: %dh%dm%ds", tmp->tm_hour,tmp->tm_min,tmp->tm_sec);
  printf("\n\n === Produtos do Cliente ===");

  ShowLG(objClienteCompras->ProdutosClientes,MostrarProdutoCliente);
}

void AdicionarVariosClientesAsCompras(SUPERMERCADO *S,RELOGIO *R){
  int numClientesSM = S->ClientesAsCompras->NEL;
  int numVerificacao = (S->nmrClientesSupermercado) - numClientesSM;
  int numClientes = aleatorio(1,numVerificacao);

  for (int i = 1; i<=numClientes; i++){
    AdicionarClienteAsCompras(S,R);
  }
}

void VerificaTempoEntradaCaixa(SUPERMERCADO *S,RELOGIO * R){
  time_t horaAtual = VerTimeRelogio(R);
  struct tm *tmp = localtime(&horaAtual);
  CLIENTEASCOMPRAS * CC;
  NOG * noTratar = NULL;

  NOG *P = S->ClientesAsCompras->Inicio;
  int retorna = 0;
  while (P) {
    noTratar = NULL;
    CC = P->Info;

    time_t HoraCaixa = CC->horaEntradaFila;
    struct tm *strHoraCaixa = localtime(&HoraCaixa);
    if (strHoraCaixa->tm_hour < tmp->tm_hour){
      //Verifica qual a caixa mais rapida 
      CAIXA* caixaAtual = caixaComMenorTempo(S->Caixas);
      //Adiciona o cesto do cliente na fila da caixa
      adicionarClienteComprasFila(caixaAtual, CC);
      
      noTratar = P;      
    }else if (strHoraCaixa->tm_hour == tmp->tm_hour && strHoraCaixa->tm_min < tmp->tm_min){
      CAIXA* caixaAtual = caixaComMenorTempo(S->Caixas);
      adicionarClienteComprasFila(caixaAtual, CC);
      noTratar = P;
    }else if (strHoraCaixa->tm_hour == tmp->tm_hour && strHoraCaixa->tm_min == tmp->tm_min && strHoraCaixa->tm_sec <= tmp->tm_sec){
      CAIXA* caixaAtual = caixaComMenorTempo(S->Caixas);
      adicionarClienteComprasFila(caixaAtual, CC);
      noTratar = P;
    }
    P = P->Prox;
    if (noTratar != NULL) {
      
      removerNoLG(S->ClientesAsCompras,noTratar);
    }
  }
}

void DestruirClienteAsCompras(void *obj){
  CLIENTEASCOMPRAS *x = obj;
  DestruirCliente(x->cliente);
  //DestruirLG(x->ProdutosClientes,);
}