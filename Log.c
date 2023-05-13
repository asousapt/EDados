#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Log.h"

LOG* CriarLog(char * mensagem, time_t *dataAccao){
    LOG* novoLog = (LOG *) malloc(sizeof(LOG));
    
    novoLog->data_hora_atual = (time_t*) malloc(sizeof(time_t));
    novoLog->mensagem = (char*) malloc(strlen(mensagem) + 1);
    novoLog->data_hora_atual = dataAccao;
    strcpy(novoLog->mensagem, mensagem);

    return novoLog;
}

void MostrarLog(void* C){
  LOG* objLog = (LOG *) C;
  printf("\n === Log ===");
  printf("\n Mensagem: %s", objLog->mensagem);
  printf("\n Data: %s", ctime(&objLog->data_hora_atual));
}