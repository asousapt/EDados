#ifndef STRUCTS_C
#define STRUCTS_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct cliente {
    int cod;
    char *nome;
    time_t entrada;
    time_t saida;
    int tempoEspera;
} CLIENTE;

typedef struct funcionario {
    int cod;
    char *nome;
} FUNCIONARIO;

typedef struct produto{
    int cod;
    char *designacao;
    float preco;
    time_t tempoCompra;
    time_t tempoCaixa;
} PRODUTO;

typedef struct NOFila{
    CLIENTE   *Info;
    struct NO *Prox;
} NOFILE;

typedef struct {
    NOFILE *Inicio;
    NOFILE *Fim;
    int NEL;
} FILAESPERA;

typedef struct Caixa {
    int numCaixa;
    int fechado; //1-fechado; 0-aberto
    time_t tempoEspera; //medio
    int contadorPessoas,contadorProdutos;
    FUNCIONARIO func;
    FILAESPERA Fila;
} CAIXA;

typedef struct NOG{
    void *Info;
    struct NOG *Prox;
}NOG;

typedef struct{
    int NEL;
    NOG *Inicio;
}ListaGenerica;

typedef struct supermercado{
    char *nome;
    time_t horaAbertura;
    time_t horaFecho;
    int numCaixas;
    int tempoEsperaMax; 
    int nmrMinCliFechaCaixa; 
    int nmrMaxClientesFila;
    ListaGenerica *Produtos;
    ListaGenerica *Clientes;
    ListaGenerica *Funcionarios;
    ListaGenerica *Caixas;
} SUPERMERCADO;


#endif
