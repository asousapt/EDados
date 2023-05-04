#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Produtos.h"

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