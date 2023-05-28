#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Caixa.h"
#include "Funcionarios.h"
#include "Fila.h"

// Criar objecto caixa
CAIXA* CriarCaixa(int numero){
  CAIXA* novaCaixa = (CAIXA *) malloc(sizeof(CAIXA));
  FILAGENERICA *filaCaixa = CriarFila();

  novaCaixa->numCaixa = numero; 
  novaCaixa->contadorPessoas = 0;
  novaCaixa->contadorProdutos = 0;
  novaCaixa->fechado = 1;
  novaCaixa->filaCaixa = filaCaixa;
  novaCaixa->func = NULL;
  novaCaixa->tempoEsperaReal = 0;
  novaCaixa->tempoEsperaMed = 0;
  novaCaixa->tempoTotal = 0;
  novaCaixa->pessoasAtendidas = CriarLG();

  return novaCaixa;
}


void listarCaixas(ListaGenerica* listaCaixas) {
  printf("*****Caixas ******\n"); 
  printf("No | Caixa  | Estado  | Operador   |  Tempo Espera Reak\n");
  ShowLG(listaCaixas, MostrarCaixa);
}

void MostrarCaixa(void* F){
  CAIXA* objCaixa = (CAIXA *) F;
  FUNCIONARIO* funcionario1 = objCaixa->func;
  char *nome = (char *)malloc(10);
  sprintf(nome,"%s %d", "Caixa ", objCaixa->numCaixa);
 if (objCaixa->func != NULL) {
  printf("%d - %s * %d * %s * %f \n", objCaixa->numCaixa, nome, !objCaixa->fechado, funcionario1->nome, objCaixa->tempoEsperaReal);
 } else {
  printf("%d - %s * %d  \n", objCaixa->numCaixa, nome, !objCaixa->fechado);
 }

  free(nome);
  }


// Faz print de uma caixa aberta
void MostrarCaixaAberta(void* F){
  CAIXA* objCaixa = (CAIXA *) F;
  char *nome = (char *)malloc(10);
  sprintf(nome,"%s %d", "Caixa ", objCaixa->numCaixa);
  if (objCaixa->fechado == 0) {
    printf("%d - %s\n", objCaixa->numCaixa, nome);
  }
}

void MostrarCaixaFechada(void* F){
  CAIXA* objCaixa = (CAIXA *) F;
  char *nome = (char *)malloc(10);
  sprintf(nome,"%s %d", "Caixa ", objCaixa->numCaixa);
  if (objCaixa->fechado == 1) {
    printf("%d - %s\n", objCaixa->numCaixa, nome);
  }
}


void DestruirCaixa(void* F){
  CAIXA* objCaixa = (CAIXA *) F;
  DestruirFuncionario(objCaixa->func);
  DestruirFila(objCaixa->filaCaixa, DestruirClientesAsCompras);
  free(objCaixa);
}

CAIXA* ProcurarCaixa(ListaGenerica *lg,int numero){
  CAIXA *cx,*cxR;
  NOG *P = lg->Inicio;
  while (P) {
    cx = P->Info;
    if (cx->numCaixa == numero) {
      cxR = cx;
    }
    P = P->Prox;
  }
  return cxR;
}

// Retorna o numero de uma caixa que esteja fechada
int buscaUmaCaixaParaAbrir(ListaGenerica *lg){
  CAIXA *cx;
  NOG *P = lg->Inicio;
  while (P) {
    cx = P->Info;
    if (cx->fechado == 1) {
     return cx->numCaixa;
    }
    P = P->Prox;
  }
  return 0;
}

CAIXA* ProcurarCaixaAberta(ListaGenerica *lg,int numero){
  CAIXA *cx,*cxR;
  NOG *P = lg->Inicio;
  while (P) {
    cx = P->Info;
    if (cx->numCaixa == numero && cx->fechado == 0) {
      cxR = cx;
    }
    P = P->Prox;
  }
  return cxR;
}

// Funcao que abre e fecha caixas.
// Param Numero :
//        0 - Operacao manual feita pelo utilizador
//        <> numero de caixa passado automaticamente 
// Param operacao : 
//        0 - Fechar caixa 
//        1 - abrir caixa
void AbreFechaCaixa(SUPERMERCADO *super, int numero, int operacao, RELOGIO* R){
  ListaGenerica * lg = (ListaGenerica *) super->Caixas;
  CAIXA* caixaEscolhida = (CAIXA *) malloc(sizeof(CAIXA));

  if (!lg) return;
  if (numero == 0  && operacao == 0) {
    printf("\n***** Caixas -> Fechar *****\n");
    ShowLG(super->Caixas, MostrarCaixaAberta);
    do
    {
      printf("Introduza o numero da caixa a fechar\n"); 
      scanf("%d", &numero); 
      
      caixaEscolhida = ProcurarCaixa(super->Caixas, numero); 

    } while (!caixaEscolhida || caixaEscolhida->fechado < 0 || caixaEscolhida->fechado >=1);
    
  }

  if (numero == 0 && operacao == 1) {
    printf("\n***** Caixas -> Abrir *****\n");
    ShowLG(super->Caixas, MostrarCaixaFechada);
    do
    {
      printf("Introduza o numero da caixa a abrir\n"); 
      scanf("%d", &numero); 
      caixaEscolhida = ProcurarCaixa(super->Caixas, numero); 
    } while (!caixaEscolhida || caixaEscolhida->fechado <= 0 || caixaEscolhida->fechado >1);
  }

  if (numero >0) {
    caixaEscolhida = ProcurarCaixa(super->Caixas, numero);
  } 

  if (operacao == 0) {
    caixaEscolhida->fechado = 1;
    caixaEscolhida->func = NULL;
    char *texto = (char *)malloc(50);
     sprintf(texto, "Caixa %d fechada!", caixaEscolhida->numCaixa);
    LOG  * logCriar = CriarLog(texto, R);
    AddBeginLG(super->LogApp, logCriar);
    free(texto);
  } 
  else {
    caixaEscolhida->fechado = 0; 
    char *texto = (char *)malloc(50);
    sprintf(texto, "Caixa %d aberta!", caixaEscolhida->numCaixa);
    LOG  * logCriar = CriarLog(texto, R);
    AddBeginLG(super->LogApp, logCriar);
    FUNCIONARIO* funcionarioAtribuir =  encontrarFuncionarioLivre(super->Funcionarios, super->Caixas);
    caixaEscolhida->func = funcionarioAtribuir;
    
    char *texto1 = (char *)malloc(300);
    sprintf(texto1, "Funcionario %s atribuido a caixa %d.",funcionarioAtribuir->nome,  caixaEscolhida->numCaixa);
    LOG  * logCriar2 = CriarLog(texto1, R);
    AddBeginLG(super->LogApp, logCriar2);
    free(texto);
    free(texto1);
  }
}

// Retorna o ponteiro com a caixa mais rapida ja contando com os clientes que estao na fila
CAIXA* caixaComMenorTempo(ListaGenerica* lista) {
  NOG* atual = lista->Inicio;
  CAIXA* caixaMenorTempoEsperaReal = NULL;
  float menorTempo = 999999; 

  while (atual != NULL) {
    CAIXA* caixaAtual = (CAIXA*)atual->Info;
    if (caixaAtual->fechado == 0) {
      if (caixaAtual->filaCaixa->tamanho > 0) { 
        if ((caixaAtual->tempoEsperaReal) < menorTempo) {
          menorTempo = caixaAtual->tempoEsperaReal;
          caixaMenorTempoEsperaReal = caixaAtual;
        }
      } else {
        return caixaAtual;   
      }     
  }
  atual = atual->Prox;
}
  return caixaMenorTempoEsperaReal;
}

int nmrCaixasAbertas(SUPERMERCADO* super) {
  int nmrCaixas = 0;
  ListaGenerica * lg = (ListaGenerica *) super->Caixas;
   if (!lg) return 0;

  NOG* atual = lg->Inicio;
   while (atual != NULL) {
    CAIXA* caixaAtual = (CAIXA*)atual->Info;
    if (caixaAtual->fechado == 0) {
      nmrCaixas++;
    }

     atual = atual->Prox;
   }
   return nmrCaixas;
}

int decideAbreCaixaNova(SUPERMERCADO* super) {
  int nmrCaixasAberta  = 0;
  nmrCaixasAberta = nmrCaixasAbertas(super);
  int nmrCaixasNoLimite = 0;
  int nmrMaxFila = super->nmrMaxClientesFila; 
  ListaGenerica * lg = (ListaGenerica *) super->Caixas;
  
  if (!lg) return 0;

  NOG* atual = lg->Inicio;
   while (atual != NULL) { 
    CAIXA* caixaAtual = (CAIXA*)atual->Info;
    if (caixaAtual->fechado == 0) {
      FILAGENERICA* filaActual = (FILAGENERICA*) caixaAtual->filaCaixa;
      if (filaActual->tamanho == nmrMaxFila ) nmrCaixasNoLimite++;
    }

    atual = atual->Prox;
   }
  return nmrCaixasAberta == nmrCaixasNoLimite;
}

//Devolve a diferenca entre o numero de pessoas atendidas numa caixa e outra
int CompararPessoas(void *obj1,void *obj2){
  CAIXA *caixa1 = (CAIXA *) obj1,*caixa2 = (CAIXA *) obj2;
  return caixa1->contadorPessoas - caixa2->contadorPessoas;
};

//Devolve a diferenca entre o numero de produtos vendidos numa caixa e outra
int CompararProdutos(void *obj1,void *obj2){
  CAIXA *caixa1 = (CAIXA *) obj1,*caixa2 = (CAIXA *) obj2;
  return caixa1->contadorProdutos - caixa2->contadorProdutos;
}

// // Verifica qual o tempo que a compra do cliente vai demorar
// float calcularTempoTotalCompra(FILAGENERICA* fila) {
//     float tempoTotal = 0.0;
//     NOFILA* atual = fila->cabeca;

 // Verifica qual o tempo que a compra do cliente vai demorar
  float calcularTempoTotalCompra(FILAGENERICA* fila) {
  float tempoTotal = 0.0;
  NOFILA* atual = fila->cabeca;

  while (atual != NULL) {
    CLIENTEASCOMPRAS* clienteCompras = (CLIENTEASCOMPRAS*)atual->Dados;
    ListaGenerica* listaProdutos = clienteCompras->ProdutosClientes;

    NOG* atualLista = listaProdutos->Inicio;

    while (atualLista != NULL) {
      PRODUTOCLIENTE* produtoCliente = (PRODUTOCLIENTE*)atualLista->Info;

      PRODUTO* produto = produtoCliente->produtoCL;

      int qtd = produtoCliente->quantidade;
      float tempoCompra = produto->tempoCompra * qtd;
      tempoTotal += tempoCompra;
      atualLista = atualLista->Prox;
      }

      atual = atual->Prox;
  }
    
  return tempoTotal;
}

void atendeClientesCaixas(ListaGenerica *lg,RELOGIO *R){
  NOG* P = lg->Inicio;
  while (P) {
    CAIXA *cx = P->Info;
    if (FilaVazia(cx->filaCaixa) == 0){
      atendeClientesPorCaixa(cx,R);
    }
  }
}

void atendeClientesPorCaixa(CAIXA *cx,RELOGIO *R){
  NOFILA *P = cx->filaCaixa->cabeca;
  time_t tempoAtual = VerTimeRelogio(R);
  struct tm *tmp = localtime(&tempoAtual);

  double tempo = 0;

  int remove = 0;

  while(P){
    CLIENTEASCOMPRAS *CC = P->Dados;
    time_t HoraSaida = CC->horaSaidaSupermercado;
    struct tm *strHoraSaida = localtime(&HoraSaida);

    if (strHoraSaida->tm_hour < tmp->tm_hour){
      AddBeginLG(cx->pessoasAtendidas,CC);
      remove = 1; 
    }else if (strHoraSaida->tm_hour == tmp->tm_hour && strHoraSaida->tm_min < tmp->tm_min){
      AddBeginLG(cx->pessoasAtendidas,CC);
      remove = 1;
    }else if (strHoraSaida->tm_hour == tmp->tm_hour && strHoraSaida->tm_min == tmp->tm_min && strHoraSaida->tm_sec <= tmp->tm_sec){
      AddBeginLG(cx->pessoasAtendidas,CC);
      remove = 1;
    }

    P = P->Prox;

    if (remove = 1) {
      cx->contadorPessoas = cx->contadorPessoas+1;
      cx->contadorPessoas = cx->contadorPessoas + CC->nProdutos;

      tempo += difftime(CC->horaEntradaFila,CC->horaSaidaSupermercado);
      //Produtos Oferecidos
      RetirarDaFilaInicio(cx->filaCaixa);
      remove = 0;
    }
  }

  float tempoTotal = (float) tempo;

  cx->tempoEsperaReal = calcularTempoTotalCompra(cx->filaCaixa);
  cx->tempoTotal = tempo;
  cx->tempoEsperaMed = calcularTempoEsperaMedio(cx);
}

float calcularTempoEsperaMedio(CAIXA *cx){
  if (cx->contadorPessoas < 1) return 0;

  float tempoMedio = cx->tempoTotal/cx->contadorPessoas;

  return tempoMedio;
}

//Caixa que mais atendeu pessoas
CAIXA *CaixaMaisAtendeu(ListaGenerica *lg){
	CAIXA *caixa = Maior(lg,CompararPessoas);
	return caixa;
}
