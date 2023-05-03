#ifndef SUPERMERCADO_H_INCLUDED
#define SUPERMERCADO_H_INCLUDED
#include <stdlib.h>
#include <time.h>
#include "ListaGenerica.h"
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
int carregaSupermercado(SUPERMERCADO* supermercadoActual);
void carregaCaixas(SUPERMERCADO* supermercadoActual);

#endif // SUPERMERCADO_H_INCLUDED