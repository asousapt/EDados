#ifndef TEXTO_H_INCLUDED
#define TEXTO_H_INCLUDED
#include <stdio.h>
#include "ListaGenerica.h"

#define STRING char *

// PRODUTO *LerFicheiroProdutos(char *file);
int LerficheiroClientes(char *ficheiro , ListaGenerica * LgCl);
FUNCIONARIO *ficheiroFuncionarios(char *file);
STRING *Read_Split_Line_File(FILE *f, int n_campos_max, int *n_campos_lidos, char *separadores);
void MostrarCliente(void* C);
void DestruirCliente(void* C);
int str_length(char str[]) ;

#endif // TEXTO_H_INCLUDED

