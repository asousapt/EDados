#ifndef TEXTO_H_INCLUDED
#define TEXTO_H_INCLUDED
#include <stdio.h>
#include "ListaGenerica.h"
#include "Clientes.h"
#include "funcoes.h"
#include "Produtos.h"
#include "Caixa.h"
#include "supermercado.h"

#define STRING char *

int LerficheiroProdutos(char *ficheiro, SUPERMERCADO * supermercadoActual);
int LerficheiroClientes(char *ficheiro , SUPERMERCADO * supermercadoActual);
int LerficheiroFuncionarios(char *file, SUPERMERCADO * supermercadoActual);
STRING *Read_Split_Line_File(FILE *f, int n_campos_max, int *n_campos_lidos, char *separadores);

#endif // TEXTO_H_INCLUDED

