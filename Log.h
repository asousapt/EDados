#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Relogio.h"
#include "Funcionarios.h"
#include "ListaGenerica.h"
#include "supermercado.h"

typedef struct log {
    time_t *data_hora_atual;  
    char * mensagem; 
} LOG;

LOG* CriarLog(char * mensagem, RELOGIO* R);
void MostrarLog(void* C);
void exportaLogCsv(ListaGenerica* ListaLog);
void EscreveLog(void *L, FILE *ficheiro);
void DestruirLog(void *L);
void exportaProdutosG(ListaGenerica* ListaProdGratis);
void mostraEstatisticasGerais(SUPERMERCADO* S);

#endif // LOG_H_INCLUDED