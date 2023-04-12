#include <stdio.h>
#include "ListaGenerica.h"

#define STRING char *

// PRODUTO *LerFicheiroProdutos(char *file);
ListaGenerica *LerficheiroClientes(char *file , ListaGenerica * LgCl);
FUNCIONARIO *ficheiroFuncionarios(char *file);
STRING *Read_Split_Line_File(FILE *f, int n_campos_max, int *n_campos_lidos, char *separadores);

