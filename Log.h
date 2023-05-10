#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Funcionarios.h"
#include "ListaGenerica.h"
#include "funcoes.h"


typedef struct log {
    struct tm *data_hora_atual;  
    char * mensagem; 
} LOG;

LOG* CriarLog(char * mensagem, time_t dataAccao);
void MostrarLog(void* C);
#endif // LOG_H_INCLUDED