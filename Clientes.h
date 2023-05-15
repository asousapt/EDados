#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ListaGenerica.h"
#include "supermercado.h"
#include "Produtos.h"
#include "Caixa.h"

typedef struct cliente {
    int cod;
    char* nome;
} CLIENTE;

typedef struct ClientesAsCompras {
    CLIENTE *cliente;
    ListaGenerica *Produtos;
    int nProdutos;
} CLIENTEASCOMPRAS;

typedef struct ClienteCaixa {
    CLIENTE *cliente;
    ListaGenerica *Produtos;
    CAIXA *cx;
} CLIENTECAIXA;

//Funcoes: Cliente
CLIENTE* CriarCliente(char* numeroCliente,char* NomeCliente);
void MostrarCliente(void* C);
void DestruirCliente(void* C); 
CLIENTE* ProcurarCliente (ListaGenerica *lg,int codigoCliente);
int validaCliente(void *elem1, void *elem2);

//Funcoes: Cliente - Supermercado
int VerificaClienteAsCompras (SUPERMERCADO *S,int codigoCliente);
CLIENTEASCOMPRAS* ProcurarClienteAsCompras (ListaGenerica *lg,int codigoCliente);
void AdicionarClienteAsCompras(SUPERMERCADO *S);
void AdicionarProdutoAoCliente(SUPERMERCADO *S,int codigo);
void MostrarClientesAsCompras(void* C);

// void AdicionarClienteCaixa(ListaGenerica *lgCx,ListaGenerica *lgCl,int numeroCaixa,int codigoCliente);

#endif // CLIENTES_H_INCLUDED