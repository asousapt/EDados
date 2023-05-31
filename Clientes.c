#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Relogio.h"
#include "Clientes.h"
#include "supermercado.h"
#include "Produtos.h"
#include "Log.h"


CLIENTE* CriarCliente(char* numeroCliente,char* nomeCliente){
  CLIENTE* NovoCliente = (CLIENTE *) malloc(sizeof(CLIENTE));
 
  NovoCliente->cod = atoi(numeroCliente);
   NovoCliente->nome = (char*) malloc(strlen(nomeCliente) + 1);
    strcpy(NovoCliente->nome, nomeCliente);

  return NovoCliente;
}

// Funcao que faz a validacao se o cliente ja existe na lista 
int validaCliente(void *elem1, void *elem2) {
  CLIENTE* cliente1 = (CLIENTE *) elem1;
  CLIENTE* cliente2 = (CLIENTE *) elem2;

  if (cliente1->cod == cliente2->cod) return 1; 
  
  return 0;
}

// Faz print de um cliente 
void MostrarCliente(void* C){
  CLIENTE* objCliente = (CLIENTE *) C;
  printf("\n === Cliente ===");
  printf("\n Numero: %d", objCliente->cod);
  printf("\n Nome: %s", objCliente->nome);
}

//funcao que limpa da memoria o cliente 
void DestruirCliente(void* C){
  CLIENTE* objCliente = (CLIENTE *) C;
  free(objCliente->nome);
  free(objCliente);
}

CLIENTE* ProcurarCliente(ListaGenerica *lg,int codigoCliente){
  CLIENTE *cl,*clR;
  NOG *P = lg->Inicio;
  while (P) {
    cl = P->Info;
    if (cl->cod == codigoCliente) {
      clR = cl;
    }
    P = P->Prox;
  }
  return clR;
}

int VerificaClienteAsCompras(SUPERMERCADO *S,int codigoCliente){
  CLIENTE *cl;
  NOG *P = S->ClientesAsCompras->Inicio;
  int retorna = 0;
  while (P) {
    cl = P->Info;
    if (cl->cod == codigoCliente) {
      retorna = 1;//encontrou
    }
    P = P->Prox;
  }

  //1->Encontrou cliente as compras
  //0->Não encontrou cliente as compras
  return retorna;
}

CLIENTEASCOMPRAS* ProcurarClienteAsCompras(ListaGenerica *lg,int codigoCliente){
  CLIENTEASCOMPRAS *cl,*clR;
  NOG *P = lg->Inicio;
  while (P) {
    cl = P->Info;
    if (cl->cliente->cod == codigoCliente) {
      clR = cl;
    }
    P = P->Prox;
  }
  return clR;
}

int CompararCliente(void *c1, void *c2){
  CLIENTE *cl1 = c1,*cl2 = c2;
  return cl1->cod - cl2->cod;
}

void AdicionarClienteAsCompras(SUPERMERCADO *S,RELOGIO *R){
  int altCliente = 0,skip = 0,icr = 1;
  CLIENTE *cl;

  while (skip == 0){
    altCliente = aleatorio(1,1000);
    
    NOG *P = S->Clientes->Inicio;
    while (P) {
      if (icr == altCliente) {
        CLIENTE *temp = P->Info;
        int codigo = temp->cod;
        CLIENTEASCOMPRAS* CC = procurarClienteCaixa(S->Caixas,codigo);
        if (VerificaClienteAsCompras(S,codigo) == 0 && CC == NULL){
          skip = 1;
          cl = P->Info;
           char *texto = (char *)malloc(300);
          sprintf(texto, "Cliente n %d entrou no supermercado", cl->cod);
          LOG  * logCriar2 = CriarLog(texto, R);
          AddBeginLG(S->LogApp, logCriar2);
          free(texto);
        }
        break;
      }
      P = P->Prox;
      icr++;
    }
  }

  int nProd = aleatorio(1,5); 
  CLIENTEASCOMPRAS* NovoCliente = (CLIENTEASCOMPRAS *) malloc(sizeof(CLIENTEASCOMPRAS));
  NovoCliente->cliente = cl;
  NovoCliente->nProdutos = nProd;
  NovoCliente->ProdutosClientes = CriarLG();
  NovoCliente->horaEntradaSuper = VerTimeRelogio(R);
  AddBeginLG(S->ClientesAsCompras,NovoCliente);

  AdicionarTodosOsProdutosAosClientes(S,NovoCliente,R);
} 

void MostrarClientesAsCompras(void* C){
  CLIENTEASCOMPRAS* objClienteCompras = (CLIENTEASCOMPRAS *) C;
  CLIENTE* objCliente = objClienteCompras->cliente;
  printf("\n === Cliente No Supermercado ===");
  printf("\n Numero: %d", objCliente->cod);
  printf("\n Nome: %s", objCliente->nome);
  printf(" Nº de Produtos: %d", objClienteCompras->nProdutos);
  
  struct tm *tmp = localtime(&objClienteCompras->horaEntradaSuper);
  printf("\n Entrada Supermercado: %dh%dm", tmp->tm_hour,tmp->tm_min);

  tmp = localtime(&objClienteCompras->horaEntradaFila);
  printf("\n Entrada Caixa: %dh%dm%ds", tmp->tm_hour,tmp->tm_min,tmp->tm_sec);
  printf("\n\n === Produtos do Cliente ===");

  ShowLG(objClienteCompras->ProdutosClientes,MostrarProdutoCliente);
}

void AdicionarVariosClientesAsCompras(SUPERMERCADO *S,RELOGIO *R){
  time_t horaActual = VerTimeRelogio(R);
  struct tm *strHoraActual = localtime(&horaActual);
  struct tm *strHoraFecho = localtime(&S->horaFecho);

  if (strHoraActual->tm_hour <= strHoraFecho->tm_hour && strHoraActual->tm_min <= strHoraFecho->tm_min && strHoraActual->tm_sec <= strHoraFecho->tm_sec ) {
    int numClientesSM = S->ClientesAsCompras->NEL;
    int numVerificacao = (S->nmrClientesSupermercado) - numClientesSM;
    int numClientes = aleatorio(1,numVerificacao);

    for (int i = 1; i<=numClientes; i++){
      AdicionarClienteAsCompras(S,R);
    }
  }
 
}

void VerificaTempoEntradaCaixa(SUPERMERCADO *S,RELOGIO * R){
  time_t horaAtual = VerTimeRelogio(R);
  struct tm *tmp = localtime(&horaAtual);
  CLIENTEASCOMPRAS * CC;
  NOG * noTratar = NULL;

  NOG *P = S->ClientesAsCompras->Inicio;
  int retorna = 0;
  while (P) {
    noTratar = NULL;
    CC = P->Info;

    time_t HoraCaixa = CC->horaEntradaFila;
    struct tm *strHoraCaixa = localtime(&HoraCaixa);
    if (strHoraCaixa->tm_hour < tmp->tm_hour){
      //Verifica qual a caixa mais rapida 
      if (decideAbreCaixaNova(S) == 1) {
        int NumCaixaAbrir =  buscaUmaCaixaParaAbrir(S->Caixas);
        AbreFechaCaixa(S, NumCaixaAbrir, 1, R);
      }
      CAIXA* caixaAtual = caixaComMenorTempo(S->Caixas);
      //Adiciona o cesto do cliente na fila da caixa
      adicionarClienteComprasFila(caixaAtual, CC);
      
      noTratar = P;      
    }else if (strHoraCaixa->tm_hour == tmp->tm_hour && strHoraCaixa->tm_min < tmp->tm_min){
      if (decideAbreCaixaNova(S) == 1) {
        int NumCaixaAbrir =  buscaUmaCaixaParaAbrir(S->Caixas);
        AbreFechaCaixa(S, NumCaixaAbrir, 1, R);
      }
      CAIXA* caixaAtual = caixaComMenorTempo(S->Caixas);
      adicionarClienteComprasFila(caixaAtual, CC);
      noTratar = P;
    }else if (strHoraCaixa->tm_hour == tmp->tm_hour && strHoraCaixa->tm_min == tmp->tm_min && strHoraCaixa->tm_sec <= tmp->tm_sec){
      if (decideAbreCaixaNova(S) == 1) {
        int NumCaixaAbrir =  buscaUmaCaixaParaAbrir(S->Caixas);
        AbreFechaCaixa(S, NumCaixaAbrir, 1, R);
      }
      CAIXA* caixaAtual = caixaComMenorTempo(S->Caixas);
      adicionarClienteComprasFila(caixaAtual, CC);
      noTratar = P;
    }
    P = P->Prox;
    if (noTratar != NULL) {
      
      removerNoLG(S->ClientesAsCompras,noTratar);
    }
  }
}

void DestruirClientesAsCompras(void *obj){
  CLIENTEASCOMPRAS *x = obj;
  DestruirCliente(x->cliente);
  DestruirLG(x->ProdutosClientes,DestruirProdutoCliente);
  free(x);
}

//Coloca os clientes compras na fila 
void adicionarClienteComprasFila(CAIXA* caixaAtual, CLIENTEASCOMPRAS* cesto,RELOGIO *R) {
  FILAGENERICA* fila = (FILAGENERICA *) caixaAtual->filaCaixa;
  AdicionaAFila(fila, cesto);
        
  float tempoEspera = calculaTempoRealEspera(fila);
  caixaAtual->tempoEsperaReal = tempoEspera;

  time_t horaSaida = VerTimeRelogio(R);
  struct tm *tmp = localtime(&horaSaida);
  tmp->tm_sec += tempoEspera;
  horaSaida = mktime(tmp);
  cesto->horaSaidaSupermercado = horaSaida; 
}

void trocarClientedeFila(SUPERMERCADO *S,CAIXA *cxDestino,CLIENTEASCOMPRAS *CC){
  CAIXA *cxOrigem = procurarCaixaCliente(S->Caixas,CC->cliente->cod);

  if (cxOrigem != NULL){
    AdicionaAFila(cxDestino->filaCaixa,CC);
    RetirarDaFila(cxOrigem->filaCaixa,CompararCliente,CC);
  }
}

CLIENTEASCOMPRAS* procurarClienteCaixa(ListaGenerica *lg,int codigoCliente){
  CAIXA *cx;
  NOG *P = lg->Inicio;
 
  while (P) {
    cx = P->Info;
    NOFILA* PF = cx->filaCaixa->cabeca;
    while (PF){
      CLIENTEASCOMPRAS *CC = PF->Dados;
      if (CC->cliente->cod == codigoCliente){
        return CC;
      }
      PF = PF->Prox;
    }
    P = P->Prox;
  }
  return NULL;
}

