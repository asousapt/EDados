#include <stdio.h>
#include <string.h>
#include "ListaGenerica.h"
#include "supermercado.h"


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
  
free(supermercadoActual);


  return 0;
}