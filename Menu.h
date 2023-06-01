#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED

#include "supermercado.h"
#include "Fila.h"
#include "ListaGenerica.h"
#include "Clientes.h"
#include "Caixa.h"
#include "Produtos.h"

void menuUtilizador(SUPERMERCADO *S,RELOGIO *R);
//void menuMostrarClientes(SUPERMERCADO *S);
void menuOperacoesClientes(SUPERMERCADO *S,RELOGIO *R);
//void menuMostrarCaixa(SUPERMERCADO *S);
void menuOperacoesCaixa(SUPERMERCADO *S,RELOGIO *R);

#endif
