#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Log.h"
#include "Produtos.h"
#include "ListaGenerica.h"
#include "Clientes.h"

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

// Faz print de um produto 
void MostrarProduto(void* P){
  PRODUTO* objProduto = (PRODUTO *) P;

  printf("\n === Produto ===");
  printf("\n Numero: %d", objProduto->cod);
  printf("\n Descricao: %s", objProduto->designacao);
  printf("\n Preco: %f", objProduto->preco);
  printf("\n Tempo Compra: %f", objProduto->tempoCompra);
  printf("\n Tempo Caixa: %f", objProduto->tempoCaixa);

}

void DestruirProduto(void* P){
  PRODUTO* objProduto = (PRODUTO *) P;
  free(objProduto->designacao);
  free(objProduto);
}

PRODUTO* ProcurarProdutos(ListaGenerica *lg,int codProduto){
  PRODUTO *prd,*prdR;
  NOG *P = lg->Inicio;
  while (P) {
    prd = P->Info;
    if (prd->cod == codProduto) {
      prdR = prd;
    }
    P = P->Prox;
  }
  return prdR;
}

int validaProduto(void *elem1, void *elem2) {
  PRODUTO* produto1 = (PRODUTO *) elem1;
  PRODUTO* produto2 = (PRODUTO *) elem2;

  if (produto1->cod == produto2->cod) return 1; 
  
  return 0;
}

int GetQuantidadeProdutoCliente(ListaGenerica *lg, PRODUTO *Prod){
  PRODUTOCLIENTE *PC;
  int qtd = 0;
  NOG *P = lg->Inicio;
  while (P) {
    PC = P->Info;
    if (PC->produtoCL->cod == Prod->cod) {
      qtd = qtd + PC->quantidade;
    }
    P = P->Prox;
  }
  return qtd;
}

PRODUTOCLIENTE *GetProdutoCliente(ListaGenerica *lg, PRODUTO *Prod){
  PRODUTOCLIENTE *PC,*PCReturn;
  int qtd = 0;
  NOG *P = lg->Inicio;
  while (P) {
    PC = P->Info;
    if (PC->produtoCL->cod == Prod->cod){
      PCReturn = PC;
    }
    P = P->Prox;
  }
  return PCReturn;
}

void AdicionarProdutoAoCliente(SUPERMERCADO *S,CLIENTEASCOMPRAS *CC, RELOGIO* R){
  int icr = 1, altProd = aleatorio(1,1000);

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
  
  int qtd = GetQuantidadeProdutoCliente(CC->ProdutosClientes,Prod);
  if (qtd == 0){
    PRODUTOCLIENTE* PC = (PRODUTOCLIENTE *) malloc(sizeof(PRODUTOCLIENTE));
    PC->produtoCL = Prod;
    PC->quantidade = 1;
    AddBeginLG(CC->ProdutosClientes,PC);
    
    char *texto1 = (char *)malloc(500);
    sprintf(texto1, "O cliente %d colocou no ceste %d unidade(s) de %s.",CC->cliente->cod,PC->quantidade, Prod->designacao  );
    LOG  * logCriar = CriarLog(texto1, R);
    AddBeginLG(S->LogApp, logCriar);
    free(texto1);
  }else{
    PRODUTOCLIENTE* PC = GetProdutoCliente(CC->ProdutosClientes,Prod);
    if (!PC) return;
    PC->quantidade = qtd+1;
  }
}

void AdicionarTodosOsProdutosAosClientes(SUPERMERCADO *S,CLIENTEASCOMPRAS *CC,RELOGIO *R){
  int numProd = CC->nProdutos;

  for (int i = 1; i<=numProd; i++){
    AdicionarProdutoAoCliente(S,CC, R);
  }

  PRODUTOCLIENTE *PC;
  NOG *P = CC->ProdutosClientes->Inicio;
  time_t horaIrCaixa = VerTimeRelogio(R);
  struct tm *local = localtime(&horaIrCaixa);
  while (P) {
    PC = P->Info;
    local->tm_sec += PC->produtoCL->tempoCompra;
    P = P->Prox;
  }
  horaIrCaixa = mktime(local);
  CC->horaEntradaFila = horaIrCaixa;
}

void MostrarProdutoCliente(void* P){
  PRODUTOCLIENTE* objProdutoCliente = (PRODUTOCLIENTE *) P;
  PRODUTO* objProduto = objProdutoCliente->produtoCL;

  printf("\n Numero: %d", objProduto->cod);
  printf("\n Descricao: %s", objProduto->designacao);
  printf("\n Quantidade: %d", objProdutoCliente->quantidade);
  printf("\n Tempo Compra: %fs", objProduto->tempoCompra);
}

void DestruirProdutoCliente(void *x){
  PRODUTOCLIENTE *obj = (PRODUTOCLIENTE *) x;
  DestruirProduto(obj->produtoCL);
  free(obj);
}

// Funcao que determina se é necessario oferecer algum produto ao cliente 
int ofereceProduto(SUPERMERCADO * S, float tempoEsparaNaFila) {
  return tempoEsparaNaFila > S->tempoEsperaMax; 
}

// funcao que retorna o produto mais barado do cesto do cliente
PRODUTO* produtoMaisBarato(CLIENTEASCOMPRAS* CC) {
  float precoMaisBaixo = 9999999;
  ListaGenerica* lg = (ListaGenerica *) CC->ProdutosClientes;

  PRODUTO* prodAct;
  PRODUTO* prodRet;

  NOG *P = lg->Inicio;
  
  PRODUTOCLIENTE *PC;
  while (P)
  {
    PC = P->Info;
    prodAct = (PRODUTO *) PC->produtoCL;
    if (prodAct->preco < precoMaisBaixo) {
      prodRet = PC->produtoCL;
    }

    P = P->Prox;
  }
  
  return prodRet;
}

float tempoProcessarProdutosCaixa(CLIENTEASCOMPRAS* CC) {
  float tempo = 0;
  ListaGenerica* lg = (ListaGenerica *) CC->ProdutosClientes;

  PRODUTO* prodAct;

  NOG *P = lg->Inicio;
  
  PRODUTOCLIENTE *PC;
  while (P)
  {
    PC = P->Info;
    prodAct = (PRODUTO *) PC->produtoCL;
    tempo += (prodAct->tempoCaixa*PC->quantidade);

    P = P->Prox;
  }
  
  return tempo;
}

// calcula o total em valor de produtos oferecidos
float totalValorProdutosOferecidos(ListaGenerica* lg) {
  float valorTotal = 0;
  NOG *P = lg->Inicio;

  while(P) {
  PRODUTO* prodAct = (PRODUTO*) P->Info;
  valorTotal += prodAct->preco;
  P = P->Prox;
  }
  return valorTotal;
}

