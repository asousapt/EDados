#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Log.h"

LOG* CriarLog(char * mensagem, time_t dataAccao){
    LOG* novoLog = (LOG *) malloc(sizeof(LOG));

    strcpy(novoLog->mensagem, mensagem);
    novoLog->data_hora_atual = dataAccao;

    return novoLog;
}

void MostrarLog(void* C){
  LOG* objLog = (LOG *) C;
  printf("\n === Log ===");
  printf("\n Mensagem: %d", objLog->mensagem);
  printf("\n Data: %d/%d/%d", objLog->data_hora_atual->tm_mday,objLog->data_hora_atual->tm_mon,objLog->data_hora_atual->tm_year);
}