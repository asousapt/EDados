#include <stdlib.h>
#include <time.h>
#include "ListaGenerica.h"

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

SUPERMERCADO CriarSM();
