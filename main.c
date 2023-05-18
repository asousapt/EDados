#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "supermercado.h"
#include "ListaGenerica.h"
#include "Clientes.h"
#include "Produtos.h"
#include "Caixa.h"
#include "Funcionarios.h"
#include "texto.h"
#include "Log.h"
#include "Fila.h"
#include "Relogio.h"

// estes ficheiros estao incluidos aqui para compilar apenas com main.c 
#include "funcoes.c"
#include "supermercado.c"
#include "ListaGenerica.c"
#include "Fila.c"
#include "texto.c"
#include "Clientes.c"
#include "Produtos.c"
#include "Funcionarios.c"
#include "Caixa.c"
#include "Log.c"
#include "Relogio.c"

int main(void) {
  printf("*** Bem-vindo ***\n"); 

  //Relogio* R = (Relogio *) malloc(sizeof(Relogio));

  // Vamos pedir ao utilizador para criar o supermercado
  SUPERMERCADO * supermercadoActual = CriarSM();
  
  //StartRelogio(R, 100, supermercadoActual);
  
  //carrega dados do supermercado
  if(carregaSupermercado(supermercadoActual) == 0) {
    printf("%s", "Erro ao carregar os dados do supermercado! O programa vai ser encerrado!\n"); 
    return 0;
  }
   //CAIXA* caixa1 = caixaComMenorTempo(supermercadoActual->Caixas);
   AbreFechaCaixa(supermercadoActual, 0, 1);
  listarCaixas(supermercadoActual->Caixas); 
  //ShowLG(supermercadoActual->Caixas, MostrarCaixa);
  
  //ShowLG(supermercadoActual->LogApp, MostrarLog);
  //ShowLG(supermercadoActual->Clientes, MostrarCliente);
  //AdicionarClienteAsCompras(supermercadoActual);
  //ShowLG(supermercadoActual->ClientesAsCompras, MostrarClientesAsCompras);

  printf("Hora de abertura do supermercado: %s", asctime(localtime(&(supermercadoActual->horaAbertura))));

  exportaLogCsv(supermercadoActual->LogApp);

  // while(1){
  //   if(kbhit()){
  //     puts("Key was pressed");
  //   }
  // }

  free(supermercadoActual);

  return 0;
}