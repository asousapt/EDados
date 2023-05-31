#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED

#include "supermercado.h"
#include "Fila.h"
#include "ListaGenerica.h"
#include "Clientes.h"
#include "Caixa.h"
#include "Produtos.h"

void menuUtilizador(SUPERMERCADO *S);
void menuMostrarClientes(SUPERMERCADO *S);
void menuOperacoesClientes(SUPERMERCADO *S);
void menuMostrarCaixa(SUPERMERCADO *S);
void menuOperacoesCaixa(SUPERMERCADO *S);

#endif
