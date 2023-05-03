#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cliente {
    int cod;
    char* nome;
} CLIENTE;

CLIENTE* CriarCliente(char* numeroCliente,char* NomeCliente);
void MostrarCliente(void* C);
void DestruirCliente(void* C); 

#endif // CLIENTES_H_INCLUDED