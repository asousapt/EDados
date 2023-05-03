#ifndef TEXTO_H_INCLUDED
#define TEXTO_H_INCLUDED
#include <stdio.h>
#include "ListaGenerica.h"
#include "Clientes.h"

#define STRING char *

// PRODUTO *LerFicheiroProdutos(char *file);
int LerficheiroProdutos(char *ficheiro, ListaGenerica * LgProd);
int LerficheiroClientes(char *ficheiro, ListaGenerica * LgCl);
int LerficheiroFuncionarios(char *file, ListaGenerica * LgFunc);
STRING *Read_Split_Line_File(FILE *f, int n_campos_max, int *n_campos_lidos, char *separadores);
void MostrarFuncionario(void* F);
void MostrarProduto(void* P);
void DestruirFuncionario(void* F);
void MostrarCaixa(void* F);
void DestruirProduto(void* P);



#endif // TEXTO_H_INCLUDED

