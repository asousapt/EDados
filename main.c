#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Relogio.h"
#include "ListaGenerica.h"
#include "Clientes.h"
#include "Produtos.h"
#include "Caixa.h"
#include "Funcionarios.h"
#include "texto.h"
#include "Log.h"
#include "supermercado.h"
#include "Fila.h"

// estes ficheiros estao incluidos aqui para compilar apenas com main.c 
#include "funcoes.c"
#include "Relogio.c"
#include "supermercado.c"
#include "ListaGenerica.c"
#include "Fila.c"
#include "texto.c"
#include "Clientes.c"
#include "Produtos.c"
#include "Funcionarios.c"
#include "Caixa.c"
#include "Log.c"


int main(void) {
  printf("*** Bem-vindo ***\n"); 

  // Vamos pedir ao utilizador para criar o supermercado
  SUPERMERCADO * supermercadoActual = CriarSM();
    //Iniciar Relogio
  RELOGIO* R = (RELOGIO *) malloc(sizeof(RELOGIO));
  StartRelogio(R, 100, supermercadoActual);
  LOG  * logCriar = CriarLog("Supermercado inicializado com sucesso!", R);
    AddBeginLG(supermercadoActual->LogApp, logCriar);

  //carrega dados do supermercado
  if(carregaSupermercado(supermercadoActual) == 0) {
    printf("%s", "Erro ao carregar os dados do supermercado! O programa vai ser encerrado!\n"); 
    return 0;
  } else {
    logCriar = CriarLog("Supermercado carregado com sucesso!", R);
    AddBeginLG(supermercadoActual->LogApp, logCriar);
  }
  
  // Abre uma caixa do supermercado 
  int primeiraCaixaAbrir =  buscaUmaCaixaParaAbrir(supermercadoActual->Caixas);
  AbreFechaCaixa(supermercadoActual, primeiraCaixaAbrir, 1, R);
  //listarCaixas(supermercadoActual->Caixas);

  
   //ShowLG(supermercadoActual->ClientesAsCompras, MostrarClientesAsCompras);
  // indica qual a caixa com menos pessoas
  AdicionarVariosClientesAsCompras(supermercadoActual,R);
sleep(10);
 VerificaTempoEntradaCaixa(supermercadoActual, R); 

  
 
  //ShowLG(supermercadoActual->Caixas, MostrarCaixa);
  
  //ShowLG(supermercadoActual->LogApp, MostrarLog);
  //ShowLG(supermercadoActual->Clientes, MostrarCliente);
  //AdicionarClienteAsCompras(supermercadoActual);
 

  //printf("Hora de abertura do supermercado: %s", asctime(localtime(&(supermercadoActual->horaAbertura))));

  exportaLogCsv(supermercadoActual->LogApp);

  // while(1){
  //   if(kbhit()){
  //     puts("Key was pressed");
  //   }
  // }

  free(supermercadoActual);

  return 0;
}