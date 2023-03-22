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
    int qtd;
    char *unidade;
    float preco;
    //falta campos pq o txt é muito explicito
}produto;

typedef struct NO{
    cliente   *Info;
    struct NO *Prox;
}NO;

typedef struct{
    NO *Inicio;
    NO *Fim;
    int fechado; //1-fechado; 0-aberto
    int numCaixa;
    int NEL;
}caixa;
