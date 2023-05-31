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

  //Cria o supermecado com dados introduzidos pelo usuario ou autopreenchidos
  SUPERMERCADO * supermercadoActual = CriarSM();

  //Iniciar Relogio
  RELOGIO* R = (RELOGIO *) malloc(sizeof(RELOGIO));
  StartRelogio(R, 500, supermercadoActual);

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
  int primeiraCaixaAbrir = buscaUmaCaixaParaAbrir(supermercadoActual->Caixas);
  AbreFechaCaixa(supermercadoActual, primeiraCaixaAbrir, 1, R);

  //Adicionar primeiros clientes
  AdicionarVariosClientesAsCompras(supermercadoActual,R); 

  int PessoasSuper = supermercadoActual->ClientesAsCompras->NEL;
  int PessoasFila = 0;
  while (PessoasSuper > 0 || PessoasFila > 0 ) {
    
    VerificaTempoEntradaCaixa(supermercadoActual,R);
    PessoasFila = totalClientesFila(supermercadoActual->Caixas);
    if (PessoasSuper<=100 && PessoasFila<=100){
      AdicionarVariosClientesAsCompras(supermercadoActual,R);
      PessoasSuper = supermercadoActual->ClientesAsCompras->NEL;
    }
    

    time_t horaRelogio = VerTimeRelogio(R);
    struct tm *tmp = localtime(&horaRelogio);
    int nmrcaixas = nmrCaixasAbertas(supermercadoActual);
    printf("Pessoas no supermercado: %d\n",PessoasSuper);
    printf("Caixas Abertas:%d\n", nmrcaixas);
    printf("Pessoas nas filas: %d\n",PessoasFila);
    printf("Hora Relógio: %dh %dm %ds\n",tmp->tm_hour,tmp->tm_min,tmp->tm_sec);


    
    atendeClientesCaixas(supermercadoActual->Caixas,R,supermercadoActual);
    Wait(2);
  }


  //listarCaixas(supermercadoActual->Caixas);

  
   //ShowLG(supermercadoActual->ClientesAsCompras, MostrarClientesAsCompras);
  // indica qual a caixa com menos pessoas

 sleep(3);
 VerificaTempoEntradaCaixa(supermercadoActual, R); 

sleep(3);
int i = 1;
while (i < 100 ) {
  
  atendeClientesCaixas(supermercadoActual->Caixas,R, supermercadoActual); 
  i++;
}
 
  //ShowLG(supermercadoActual->Caixas, MostrarCaixa);
  
  //ShowLG(supermercadoActual->ProdutosOferecidos, MostrarProduto);
  //ShowLG(supermercadoActual->Clientes, MostrarCliente);
  //AdicionarClienteAsCompras(supermercadoActual);
 
  //mostraEstatisticasGerais(supermercadoActual);
  //printf("Hora de abertura do supermercado: %s", asctime(localtime(&(supermercadoActual->horaAbertura))));
  exportaCaixas(supermercadoActual->Caixas);
  exportaLogCsv(supermercadoActual->LogApp);
  exportaProdutosG(supermercadoActual->ProdutosOferecidos);
  exportaFuncionarios(supermercadoActual->Funcionarios);
  // while(1){
  //   if(kbhit()){
  //     puts("Key was pressed");
  //   }
  // }

  free(supermercadoActual);

  return 0;
}