#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ListaGenerica.h"
#include "Caixa.h"

typedef struct cliente {
    int cod;
    char* nome;
} CLIENTE;

CLIENTE* CriarCliente(char* numeroCliente,char* NomeCliente);
void MostrarCliente(void* C);
void DestruirCliente(void* C); 
CLIENTE* ProcurarCliente (ListaGenerica *lg,int codigoCliente);
// void AdicionarClienteCaixa(ListaGenerica *lgCx,ListaGenerica *lgCl,int numeroCaixa,int codigoCliente);

#endif // CLIENTES_H_INCLUDED