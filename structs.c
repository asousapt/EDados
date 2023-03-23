#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct cliente{
    int cod;
    char *nome;
    time_t entrada;
    time_t saida;
    int tempoEspera;
}cliente;

typedef struct funcionario{
    int cod;
    char *nome;
}funcionario;

typedef struct produto{
    int cod;
    char *designacao;
    float preco;
    time_t tempoCompra;
    time_t tempoCaixa;
}produto;

typedef struct NOFila{
    cliente   *Info;
    struct NO *Prox;
}NOFila;

typedef struct{
    NOFila *Inicio;
    NOFila *Fim;
    int NEL;
}FilaEspera;

typedef struct Caixa{
    int numCaixa;
    int fechado; //1-fechado; 0-aberto
    time_t tempoEspera; //medio
    int contadorPessoas,contadorProdutos;
    funcionario f;
    FilaEspera Fila;
}Caixa;

// typedef struct NOG
// {
//     void *Info;
//     struct NOG *Prox;
// }NOG;


// typedef struct
// {
//     int NEL;
//     NOG *Inicio;
// }ListaGenerica;
