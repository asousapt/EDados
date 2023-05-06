#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "supermercado.h"
#include "ListaGenerica.h"
#include "Clientes.h"
#include "Caixa.h"
#include "Funcionarios.h"
#include "texto.h"

// estes ficheiros estao incluidos aqui para compilar apenas com main.c 
#include "funcoes.c"
#include "supermercado.c"
#include "ListaGenerica.c"
#include "texto.c"
#include "Clientes.c"
#include "Produtos.c"
#include "Funcionarios.c"
#include "Caixa.c"

int main(void) {
  printf("*** Bem-vindo ***\n"); 

  // Vamos pedir ao utilizador para criar o supermercado
  SUPERMERCADO * supermercadoActual = CriarSM();

  //carrega dados do supermercado
  if(carregaSupermercado(supermercadoActual) == 0) {
    printf("%s", "Erro ao carregar os dados do supermercado! O programa vai ser encerrado!\n"); 
    return 0;
  }

  ShowLG(supermercadoActual->Caixas, MostrarCaixa);
  AbrirCaixa(supermercadoActual->Caixas);
  ShowLG(supermercadoActual->Caixas, MostrarCaixa);

  free(supermercadoActual);

  return 0;
}