#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ListaGenerica.h"
#include "Log.h"
#include "texto.h"

LOG* CriarLog(char * mensagem, RELOGIO* R){
   time_t horaAtual = VerTimeRelogio(R);
    struct tm *tmp = localtime(&horaAtual);
    LOG* novoLog = (LOG *) malloc(sizeof(LOG));
    
    novoLog->data_hora_atual = (time_t*) malloc(sizeof(time_t));
    novoLog->mensagem = (char*) malloc(strlen(mensagem) + 1);
    novoLog->data_hora_atual = horaAtual;
    strcpy(novoLog->mensagem, mensagem);

    return novoLog;
}

void MostrarLog(void* C){
  LOG* objLog = (LOG *) C;
  printf("\n === Log ===");
  printf("\n Mensagem: %s", objLog->mensagem);
  printf("\n Data: %s", ctime(&objLog->data_hora_atual));
}

// Funcao que passamos para dentro da funcao de escrita em ficheiro para escrever o objecto log
void EscreveLog(void *L, FILE *ficheiro) {
  LOG* objLog = (LOG *) L;
  char* data_hora = ctime(&objLog->data_hora_atual);
  data_hora[strlen(data_hora) - 1] = ' ';
    fprintf(ficheiro, "%s;%s;\n", trim(data_hora), trim(objLog->mensagem));
}

// Exporta p log para um ficheiro CSV
void exportaLogCsv(ListaGenerica* ListaLog) {
  FILE *f = fopen("log.csv", "w");
  if (f == NULL){
		printf("Erro ao abrir o ficheiro log.csv");
		exit(1);
	}
  printf("A exportar Log...\n");

  EscreveLG(ListaLog, f, EscreveLog);
  
  fclose(f);
  
  printf("Log Exportado com sucesso!\n");
}
