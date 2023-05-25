#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Relogio.h"
#include "supermercado.h"



void StartRelogio(RELOGIO *R, int Vel, SUPERMERCADO *S){
    R->START = time(0);
    R->VELOCIDADE = Vel;

    struct tm *tmp = localtime(&S->horaAbertura);
    //sscanf(S->horaAbertura, "%d:%d", &tmp->tm_hour, &tmp->tm_min);
    R->Hora_Inicio = mktime(tmp);
    //printf("Hora de Arranque = [%s]\n", asctime(localtime(&(R->Hora_Inicio))));
}

time_t VerTimeRelogio(RELOGIO *R){
    time_t Dif = difftime(time(0), R->START);
    time_t Simulada = R->Hora_Inicio + Dif * R->VELOCIDADE;
    return Simulada;
}

void WaitSegundos(int s){
    clock_t T0 = clock();
    clock_t T1 = T0 + s;
    while (clock() < T1);
}

void Wait(int s){
    WaitSegundos(s*CLOCKS_PER_SEC);
}

//Verificar tecla pressionada
// if (kbhit){
//     ch = getch();
//     //verificar se e o enter
// }

//Funcao Loop
// int Run(Supermercado *S)
// {
//     while(1)
//     {
//         printf("Estou a trabalhar... entre as [%d] e as [%d]\n", S->HORA_INICIO, S->HORA_FIM);
//         size_t MEMORIA = MemoriaOcupadaSupermercado(S);
//         printf("MEMORIA do [%s]= %lu Bytes\n", S->NOME, MEMORIA);
//         // ShowProdutos(LIDL);
//         // ShowClientes(LIDL);
//         // ShowFuncionarios(S);
//         ShowEstado(S);

//         ProcessarCaixas(S);

//         EntrarMaisCliente(S);

//         IrCaixaPagar(S);

//         wait(2000);
//     }
// }