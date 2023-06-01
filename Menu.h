#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED

#include "supermercado.h"
#include "Fila.h"
#include "ListaGenerica.h"
#include "Clientes.h"
#include "Caixa.h"
#include "Produtos.h"
#include "Log.h"

void menuUtilizador(SUPERMERCADO *S,RELOGIO *R);
void menuOperacoesClientes(SUPERMERCADO *S,RELOGIO *R);
void menuOperacoesCaixa(SUPERMERCADO *S,RELOGIO *R);

#endif
