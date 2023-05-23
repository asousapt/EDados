#ifndef RELOGIO_H_INCLUDED
#define RELOGIO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "supermercado.h"


typedef struct relogio{
    time_t START;
    int VELOCIDADE;
    time_t Hora_Inicio;
}RELOGIO;

void StartRelogio(RELOGIO *R, int Vel, SUPERMERCADO *S);
time_t VerTimeRelogio(RELOGIO *R);
void WaitSegundos(int s);
void Wait(int s);

#endif // RELOGIO_H_INCLUDED