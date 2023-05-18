#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Produtos.h"
#include "ListaGenerica.h"

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
    PC = P;
    if (PC->produtoCL->cod == Prod->cod) {
      qtd = qtd + PC->quantidade;
    }
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

void AdicionarProdutoAoCliente(SUPERMERCADO *S,CLIENTEASCOMPRAS *CC){
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
  }else{
    PRODUTOCLIENTE* PC = GetProdutoCliente(CC->ProdutosClientes,Prod);
    if (!PC) return;
    PC->quantidade = qtd+1;
  }
}

void AdicionarTodosOsProdutosAosClientes(SUPERMERCADO *S,CLIENTEASCOMPRAS *CC,Relogio *R){
  int numProd = CC->nProdutos;

  for (int i = 1; i>numProd; i++){
    AdicionarProdutoAoCliente(S,CC);
  }

  struct tm *tmp;

  PRODUTOCLIENTE *PC;
  NOG *P = CC->ProdutosClientes->Inicio;
  while (P) {
    PC = P->Info;
    tmp->tm_sec = tmp->tm_sec + PC->produtoCL->tempoCompra;
    P = P->Prox;
  }

  time_t horaIrCaixa = VerTimeRelogio(R);
  horaIrCaixa = mktime(tmp);

  CC->horaEntradaFila = horaIrCaixa;
}
