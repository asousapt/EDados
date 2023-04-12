#include "structs.c"
#include "supermercado.h"
#include "funcoes.h"

SUPERMERCADO CriarSM(){
    int nCaixas, nmrMinCliFechaCaixa, nmrMaxClientesFila;
    time_t horaAbertura, horaFecho;
    char *nome;

    SUPERMERCADO *SM = (SUPERMERCADO *)malloc(sizeof(SUPERMERCADO));

    //nome = getString("Nome do Supermercado:");

    horaAbertura; 
    horaFecho;

    nCaixas = validarInt("\nNúmero de caixas do supermercado:",1,10);
    nmrMaxClientesFila = validarInt("\nMáximo de clientes na fila:",1,20);
    nmrMinCliFechaCaixa = validarInt("\nNúmero de clientes para fechar a caixa:",1,5);

    
    ListaGenerica * ListaCaixas = CriarLG();

    SM->nome = nome;
    SM->numCaixas = nCaixas;
    SM->nmrMaxClientesFila = nmrMaxClientesFila;
    SM->nmrMinCliFechaCaixa = nmrMinCliFechaCaixa;
}