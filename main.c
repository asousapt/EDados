#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <conio.h>

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
#include "Menu.h"
#include "funcoes.h"

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
  inicializarAleatorio();
  printf("*** Bem-vindo ***\n"); 

  //Cria o supermecado com dados introduzidos pelo usuario ou autopreenchidos
  SUPERMERCADO * supermercadoActual = CriarSM();

  //Iniciar Relogio
  RELOGIO* R = (RELOGIO *) malloc(sizeof(RELOGIO));
  StartRelogio(R, 1000, supermercadoActual);

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

  time_t horaRelogio = VerTimeRelogio(R);
  int PessoasSuper = supermercadoActual->ClientesAsCompras->NEL;
  int PessoasFila = 0;
  while (PessoasSuper > 0 || PessoasFila > 0 || difftime(horaRelogio,supermercadoActual->horaFecho) < 0) {
    system("clear");
    VerificaTempoEntradaCaixa(supermercadoActual,R);
    PessoasFila = totalClientesFila(supermercadoActual->Caixas);
    if (PessoasSuper<=100 && PessoasFila<=100){
      AdicionarVariosClientesAsCompras(supermercadoActual,R);
      PessoasSuper = supermercadoActual->ClientesAsCompras->NEL;
    }

    horaRelogio = VerTimeRelogio(R);
    struct tm *tmp = localtime(&horaRelogio);
    int nmrcaixas = nmrCaixasAbertas(supermercadoActual);
    printf("===================================\n");
    printf("=Pessoas no supermercado:%d     =\n",PessoasSuper);
    printf("=Caixas Abertas:%d              =\n", nmrcaixas);
    printf("=Pessoas nas filas: %d          =\n",PessoasFila);
    printf("=Hora Relógio: %dh %dm %ds      =\n",tmp->tm_hour,tmp->tm_min,tmp->tm_sec);
    estatisticaHoraria(supermercadoActual->Caixas, tmp->tm_hour); 
    printf("===================================\n");

    if(kbhit()){
        char ch = getch();
        if ((int)ch == 13) {
            menuUtilizador(supermercadoActual,R);
        }
    }
    
    atendeClientesCaixas(supermercadoActual->Caixas,R,supermercadoActual);
    Wait(2);
  }
 
  mostraEstatisticasGerais(supermercadoActual);
  exportaCaixas(supermercadoActual->Caixas);
  exportaLogCsv(supermercadoActual->LogApp);
  exportaProdutosG(supermercadoActual->ProdutosOferecidos);
  exportaFuncionarios(supermercadoActual->Funcionarios);

  DestruirSupermercado(supermercadoActual);
  free(R);

  return 0;
}