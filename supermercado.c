#include "structs.c"
#include "supermercado.h"
#include "funcoes.h"

SUPERMERCADO CriarSM(){
    int nCaixas, nmrMinCliFechaCaixa, nmrMaxClientesFila;
    time_t horaAbertura, horaFecho;
    char *nome;

    SUPERMERCADO *SM = (SUPERMERCADO *)malloc(sizeof(SUPERMERCADO));

    nCaixas = validarInt("Número de caixas do supermercado:",1,10);
    nmrMaxClientesFila = validarInt("Máximo de clientes na fila:",1,20);
    nmrMinCliFechaCaixa = validarInt("Número de clientes para fechar a caixa:",1,5);


    SM->numCaixas = nCaixas;
    SM->nmrMaxClientesFila = nmrMaxClientesFila;
    SM->nmrMinCliFechaCaixa = nmrMinCliFechaCaixa;
}