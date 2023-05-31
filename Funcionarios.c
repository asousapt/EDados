#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Funcionarios.h"
#include "Caixa.h"

//Cria um novo objecto funcionario 
FUNCIONARIO* CriarFuncionario(char* numeroFuncionario,char* nomeFuncionario) {
  FUNCIONARIO* novoFuncionario = (FUNCIONARIO *) malloc(sizeof(FUNCIONARIO));

  novoFuncionario->cod = atoi(numeroFuncionario);
  novoFuncionario->nome = (char*) malloc(strlen(nomeFuncionario) + 1);
  novoFuncionario->nmrClientesAtendidos = 0; 


  strcpy(novoFuncionario->nome, nomeFuncionario);

  return novoFuncionario;
}

// Faz print de um Funcionario 
void MostrarFuncionario(void* F){
  FUNCIONARIO* objFuncionario = (FUNCIONARIO *) F;
  printf("\n === Funcionario ===");
  printf("\n Numero: %d", objFuncionario->cod);
  printf("\n Nome: %s", objFuncionario->nome);
}

void DestruirFuncionario(void* F){
  FUNCIONARIO* objFuncionario = (FUNCIONARIO *) F;
  free(objFuncionario->nome);
  free(objFuncionario);
}

FUNCIONARIO* ProcurarFuncionario(ListaGenerica *lg,int codFuncionario){
  FUNCIONARIO *f,*fR;
  NOG *P = lg->Inicio;
  while (P) {
    f = P->Info;
    if (f->cod == codFuncionario) {
      fR = f;
    }
    P = P->Prox;
  }
  return fR;
}

int validaFuncionario(void *elem1, void *elem2) {
  FUNCIONARIO* funcionario1 = (FUNCIONARIO *) elem1;
  FUNCIONARIO* funcionario2 = (FUNCIONARIO *) elem2;

  if (funcionario1->cod == funcionario2->cod) return 1; 
  
  return 0;
}

// Funcao que encontra um funcionario que esteja livre
FUNCIONARIO* encontrarFuncionarioLivre(ListaGenerica* listaFuncionarios, ListaGenerica* listaCaixas) {
    NOG* atualFunc = listaFuncionarios->Inicio;
    while (atualFunc != NULL) {
        FUNCIONARIO* func = (FUNCIONARIO*)atualFunc->Info;
        int atribuido = 0;
        NOG* caixaAtual = listaCaixas->Inicio;
        while (caixaAtual != NULL) {
            CAIXA* caixa = (CAIXA*) caixaAtual->Info ;
            if (caixa->func == func) {
                atribuido = 1;
                break;
            }
            caixaAtual = caixaAtual->Prox;
        }
        if (!atribuido) {
            return func;
        }
        atualFunc = atualFunc->Prox;
    }
    return NULL;
}

// Funcao que retorna o funcionario que atendeu mais e menos 
// 0 - menor 
// 1 - maior 
FUNCIONARIO* funcionarioAtendeuMaisMenos(ListaGenerica* listaFuncionarios,int operacao) {
    NOG* atualFunc = listaFuncionarios->Inicio;
    FUNCIONARIO* funcRetornar = NULL; 
    int numero = 0; 

    while (atualFunc != NULL) {
      FUNCIONARIO* func = (FUNCIONARIO*)atualFunc->Info;
      
      if (func->nmrClientesAtendidos > 0) {
        if (operacao == 1) {
          if (func->nmrClientesAtendidos > numero) {
            numero = func->nmrClientesAtendidos; 
            funcRetornar = func;
          }
        } else {
          if (numero == 0) { 
            numero = func->nmrClientesAtendidos; 
            funcRetornar = func;
          } else {
            if (func->nmrClientesAtendidos < numero) {
               numero = func->nmrClientesAtendidos; 
            funcRetornar = func;
            }
          }
        }
      }
      atualFunc = atualFunc->Prox;
    }
    return funcRetornar;
}

void EscreveFuncionario(void *L, FILE *ficheiro) {
  FUNCIONARIO* objFunc = (FUNCIONARIO *) L;
    fprintf(ficheiro, "%d;%s;%d\n", objFunc->cod, trim(objFunc->nome), objFunc->nmrClientesAtendidos);
}

// Exporta Lista de funcionarios 
void exportaFuncionarios(ListaGenerica* lg) {
  FILE *f = fopen("funcionarios-est.csv", "w");
  if (f == NULL){
		printf("Erro ao abrir o ficheiro funcionarios-est.csv");
		exit(1);
	}

  printf("A exportar Log de funcionarios...\n");

  EscreveLG(lg, f, EscreveFuncionario);
  
  FUNCIONARIO* funcMais =  funcionarioAtendeuMaisMenos(lg,1);
  FUNCIONARIO* funcMenos =  funcionarioAtendeuMaisMenos(lg,0);
  fprintf(f, "%s;%s;%d\n","Funcionario que atendeu mais clientes", funcMais->nome, funcMais->nmrClientesAtendidos);
  fprintf(f, "%s;%s;%d\n","Funcionario que atendeu menos clientes", funcMenos->nome, funcMenos->nmrClientesAtendidos);
  fclose(f);
  
  printf("Log de funcionarios Exportado com sucesso!\n");
}