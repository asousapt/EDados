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

//Procura um Cliente com o codigoCliente na lg e o devolve
CLIENTE* ProcurarCliente(ListaGenerica *lg,int codigoCliente){
  CLIENTE *cl = NULL; 
  CLIENTE *clR = NULL;

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

//Verifica se um Cliente ja esta as compras
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

//Procura e devolve um cliente as compras na lista lg
CLIENTEASCOMPRAS* ProcurarClienteAsCompras(ListaGenerica *lg,int codigoCliente){
  CLIENTEASCOMPRAS *cl = NULL;
  CLIENTEASCOMPRAS *clR = NULL;
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

//compara cliente pele codigo
int CompararCliente(void *c1, void *c2){
  CLIENTE *cl1 = c1,*cl2 = c2;
  return cl1->cod - cl2->cod;
}

//devolve a posicao de um cliente numa lista
int devolveClientePosicao(ListaGenerica* lg, int posicao){ 
  int nmrCl = 0;
  int i = 0;  
  NOG* p = lg->Inicio;

  while (p)
  {
    CLIENTE* cl = p->Info; 
    if (i == posicao) {
      return cl->cod;
    }
    i++;
    p = p->Prox;
  }
}

//retorna um cliente livre da lista 
CLIENTE* retornaClienteLivre(SUPERMERCADO* S) {
  CLIENTEASCOMPRAS* CC = NULL;
  CLIENTEASCOMPRAS* CCC = NULL;
  CLIENTE* ClLivre = NULL;
  int numeroClienteAleatorio = 0;
  int posicaoClienteAl = 0;
  int clienteFoiAtendido = 0;

  do
  {
    posicaoClienteAl = aleatorio(1, 10000); 
    numeroClienteAleatorio =  devolveClientePosicao(S->Clientes,posicaoClienteAl);

    CC = ProcurarClienteAsCompras(S->ClientesAsCompras, numeroClienteAleatorio); 
    CCC = procurarClienteCaixa(S->Caixas, numeroClienteAleatorio);
    clienteFoiAtendido = clienteJaFoiAtendido(S->Caixas, numeroClienteAleatorio);
    ClLivre = ProcurarCliente(S->Clientes, numeroClienteAleatorio);
   
  } while (CC != NULL || CCC != NULL || ClLivre == NULL || clienteFoiAtendido == 1 );
 
  return ClLivre;
}


void AdicionarClienteAsCompras(SUPERMERCADO *S,RELOGIO *R){
  int altCliente = 0,skip = 0,icr = 1;
  CLIENTE *cl = retornaClienteLivre(S);

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

  if (difftime(horaActual,S->horaFecho) > 0) {
    printf("Nº de clientes adicionados: 0\n");
    return;
  }

  int numClientesSM = S->ClientesAsCompras->NEL;
  int numVerificacao = (S->nmrClientesSupermercado) - numClientesSM;
  if (numVerificacao > 0) {
    int numClientes = aleatorio(1,numVerificacao);
    printf("Nº de clientes adicionados: %d\n",numClientes);
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
    if (difftime(horaAtual,HoraCaixa) > 0){
      //Verifica qual a caixa mais rapida 
      if (decideAbreCaixaNova(S) == 1) {
        int NumCaixaAbrir =  buscaUmaCaixaParaAbrir(S->Caixas);
        AbreFechaCaixa(S, NumCaixaAbrir, 1, R);
      }
      CAIXA* caixaAtual = caixaComMenorTempo(S->Caixas);
      //Adiciona o cesto do cliente na fila da caixa
      adicionarClienteComprasFila(caixaAtual, CC,R);
      
      noTratar = P;    
    }

    /*if (strHoraCaixa->tm_hour < tmp->tm_hour){
        //Verifica qual a caixa mais rapida 
      if (decideAbreCaixaNova(S) == 1) {
        int NumCaixaAbrir =  buscaUmaCaixaParaAbrir(S->Caixas);
        AbreFechaCaixa(S, NumCaixaAbrir, 1, R);
      }
      CAIXA* caixaAtual = caixaComMenorTempo(S->Caixas);
      //Adiciona o cesto do cliente na fila da caixa
      adicionarClienteComprasFila(caixaAtual, CC,R);
      
      noTratar = P; 
    }else if (strHoraCaixa->tm_hour == tmp->tm_hour && strHoraCaixa->tm_min < tmp->tm_min){
      if (decideAbreCaixaNova(S) == 1) {
        int NumCaixaAbrir =  buscaUmaCaixaParaAbrir(S->Caixas);
        AbreFechaCaixa(S, NumCaixaAbrir, 1, R);
      }
      CAIXA* caixaAtual = caixaComMenorTempo(S->Caixas);
      adicionarClienteComprasFila(caixaAtual, CC,R);
      noTratar = P;
    }else if (strHoraCaixa->tm_hour == tmp->tm_hour && strHoraCaixa->tm_min == tmp->tm_min && strHoraCaixa->tm_sec <= tmp->tm_sec){
      if (decideAbreCaixaNova(S) == 1) {
        int NumCaixaAbrir =  buscaUmaCaixaParaAbrir(S->Caixas);
        AbreFechaCaixa(S, NumCaixaAbrir, 1, R);
      }
      CAIXA* caixaAtual = caixaComMenorTempo(S->Caixas);
      adicionarClienteComprasFila(caixaAtual, CC,R);
      noTratar = P;
    }*/
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

  tempoEspera += tempoProcessarProdutosCaixa(cesto);

  time_t horaSaida = VerTimeRelogio(R);
  struct tm *tmp = localtime(&horaSaida);
  tmp->tm_sec += tempoEspera;
  horaSaida = mktime(tmp);
  cesto->horaSaidaSupermercado = horaSaida; 
}

void trocarClientedeFila(SUPERMERCADO *S,CAIXA *cxDestino,CLIENTEASCOMPRAS *CC,RELOGIO *R){
  CAIXA *cxOrigem = procurarCaixaCliente(S->Caixas,CC->cliente->cod);

  if (cxOrigem != NULL){
    AdicionaAFila(cxDestino->filaCaixa,CC);
    RetirarDaFila(cxOrigem->filaCaixa,CompararCliente,CC);

    float tempoEsperaOrigem = calculaTempoRealEspera(cxOrigem->filaCaixa);
    cxOrigem->tempoEsperaReal = tempoEsperaOrigem;
    
    float tempoEsperaDestino = calculaTempoRealEspera(cxDestino->filaCaixa);
    cxDestino->tempoEsperaReal = tempoEsperaOrigem;

    tempoEsperaDestino += tempoProcessarProdutosCaixa(CC);
    time_t horaSaida = VerTimeRelogio(R);
    struct tm *tmp = localtime(&horaSaida);
    tmp->tm_sec += tempoEsperaDestino;
    horaSaida = mktime(tmp);
    CC->horaSaidaSupermercado = horaSaida; 

    char *texto = (char *)malloc(300);
    sprintf(texto, "Cliente n %d saio da fila da caixa %d e entrou na fila da caixa %d", CC->cliente->cod, cxOrigem->numCaixa,cxDestino->numCaixa);
    LOG  * logCriar = CriarLog(texto, R);
    AddBeginLG(S->LogApp, logCriar);
    free(texto); 

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

