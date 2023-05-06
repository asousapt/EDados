#ifndef FUNCIONARIOS_H_INCLUDED
#define FUNCIONARIOS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ListaGenerica.h"

typedef struct funcionario {
    int cod;
    char *nome;
} FUNCIONARIO;

FUNCIONARIO* CriarFuncionario(char* numeroFuncionario,char* nomeFuncionario);
void MostrarFuncionario(void* F);
void DestruirFuncionario(void* F);
FUNCIONARIO* ProcurarFuncionario(ListaGenerica *lg,int codFuncionario);

#endif // FUNCIONARIOS_H_INCLUDED
