#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Log.h"

LOG* CriarLog(char * mensagem, time_t *dataAccao){
    LOG* novoLog = (LOG *) malloc(sizeof(LOG));

    strcpy(novoLog->mensagem, mensagem);
     time_t tempo_atual;
    time(&tempo_atual);
    novoLog->data_hora_atual = malloc(sizeof(time_t));
    *(novoLog->data_hora_atual) = tempo_atual;

    return novoLog;
}

void MostrarLog(void* C){
  LOG* objLog = (LOG *) C;
  printf("\n === Log ===");
  printf("\n Mensagem: %s", objLog->mensagem);
  printf("\n Data: %s",objLog->data_hora_atual);
}