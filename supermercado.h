#ifndef SUPERMERCADO_H_INCLUDED
#define SUPERMERCADO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Relogio.h"
#include "funcoes.h"
#include "Funcionarios.h"

typedef struct supermercado{
    char *nome;
    time_t horaAbertura;
    time_t horaFecho;
    int nmrClientesSupermercado;
    int numCaixas;
    int tempoEsperaMax; 
    int nmrMinCliFechaCaixa; 
    int nmrMaxClientesFila;
    ListaGenerica *Produtos;
    ListaGenerica *Clientes;
    ListaGenerica *Funcionarios;
    ListaGenerica *Caixas;
    ListaGenerica *LogApp;
    ListaGenerica *ClientesAsCompras; 
    ListaGenerica *ProdutosOferecidos;
} SUPERMERCADO;

SUPERMERCADO * CriarSM();
int carregaSupermercado(SUPERMERCADO* supermercadoActual, RELOGIO* R);
void carregaCaixas(SUPERMERCADO* supermercadoActual);
void DestruirSupermercado(SUPERMERCADO *mercado);

#endif // SUPERMERCADO_H_INCLUDED
