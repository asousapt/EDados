#ifndef TEXTO_H_INCLUDED
#define TEXTO_H_INCLUDED
#include <stdio.h>
#include "ListaGenerica.h"
#include "Clientes.h"
#include "funcoes.h"
#include "Produtos.h"
#include "Caixa.h"

#define STRING char *

// PRODUTO *LerFicheiroProdutos(char *file);
int LerficheiroProdutos(char *ficheiro, ListaGenerica * LgProd);
int LerficheiroClientes(char *ficheiro, ListaGenerica * LgCl);
int LerficheiroFuncionarios(char *file, ListaGenerica * LgFunc);
STRING *Read_Split_Line_File(FILE *f, int n_campos_max, int *n_campos_lidos, char *separadores);

#endif // TEXTO_H_INCLUDED

