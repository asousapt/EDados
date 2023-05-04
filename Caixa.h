#ifndef CAIXA_H_INCLUDED
#define CAIXA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaGenerica.h"
#include "Fila.h"
#include "Funcionarios.h"

typedef struct caixa {
    int numCaixa;
    char * NomeCaixa;
    int fechado; //1-fechado; 0-aberto
    float tempoEspera; //medio
    int contadorPessoas,contadorProdutos;
    FUNCIONARIO* func;
    FILAGENERICA* filaCaixa;
} CAIXA;

CAIXA* CriarCaixa(int numero );
void MostrarCaixa(void* F);
#endif // CAIXA_H_INCLUDED