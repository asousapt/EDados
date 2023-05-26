#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


int validarInt(char *pergunta, int menor,int maior);
char *getString(char *pergunta);
int aleatorio(int min, int max);
int validaHoras(int hora, int minutos);
int validaHorasFecho(int hora, int minutos,time_t abertura);
time_t convertToTime(int hora, int minutos);
CAIXA *CaixaMaisAtendeu(ListaGenerica *lg);
#endif // FUNCOES_H_INCLUDED
