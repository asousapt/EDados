#ifndef RELOGIO_H_INCLUDED
#define RELOGIO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "supermercado.h"

typedef struct{
    time_t START;
    int VELOCIDADE;
    time_t Hora_Inicio;
}Relogio;

void StartRelogio(Relogio *R, int Vel, SUPERMERCADO *S);
time_t VerTimeRelogio(Relogio *R);
void WaitSegundos(int s);
void Wait(int s);

#endif // RELOGIO_H_INCLUDED