#ifndef FUNCIONARIOS_H_INCLUDED
#define FUNCIONARIOS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ListaGenerica.h"

typedef struct funcionario {
    int cod;
    char *nome;
    int nmrClientesAtendidos;
} FUNCIONARIO;


FUNCIONARIO* CriarFuncionario(char* numeroFuncionario,char* nomeFuncionario);
void MostrarFuncionario(void* F);
void DestruirFuncionario(void* F);
FUNCIONARIO* ProcurarFuncionario(ListaGenerica *lg,int codFuncionario);
int validaFuncionario(void *elem1, void *elem2);
FUNCIONARIO* encontrarFuncionarioLivre(ListaGenerica* listaFuncionarios, ListaGenerica* listaCaixas);
FUNCIONARIO* funcionarioAtendeuMaisMenos(ListaGenerica* listaFuncionarios,int operacao);
void EscreveFuncionario(void *L, FILE *ficheiro);
void exportaFuncionarios(ListaGenerica* lg);

#endif // FUNCIONARIOS_H_INCLUDED
