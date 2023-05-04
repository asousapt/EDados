#ifndef SUPERMERCADO_H_INCLUDED
#define SUPERMERCADO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ListaGenerica.h"
#include "funcoes.h"
#include "Caixa.h"
#include "Funcionarios.h"

typedef struct supermercado{
    char *nome;
    time_t horaAbertura;
    time_t horaFecho;
    int numCaixas;
    int tempoEsperaMax; 
    int nmrMinCliFechaCaixa; 
    int nmrMaxClientesFila;
    ListaGenerica *Produtos;
    ListaGenerica *Clientes;
    ListaGenerica *Funcionarios;
    ListaGenerica *Caixas;
} SUPERMERCADO;

SUPERMERCADO * CriarSM();
<<<<<<< HEAD
void destruirSM(SUPERMERCADO super);
int carregaSupermercado(SUPERMERCADO* supermercadoActual);
=======
int carregaSupermercado(SUPERMERCADO* supermercadoActual);
void carregaCaixas(SUPERMERCADO* supermercadoActual);

#endif // SUPERMERCADO_H_INCLUDED
>>>>>>> ccaab5cb81d227b08d1254c9cc10845951113dbf
