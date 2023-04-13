#include <time.h>

#include "supermercado.h"
#include "funcoes.c"

SUPERMERCADO CriarSM(){
    int nCaixas, nmrMinCliFechaCaixa, nmrMaxClientesFila;
    time_t horaAbertura, horaFecho;
    char *nome;

    SUPERMERCADO *SM = (SUPERMERCADO *)malloc(sizeof(SUPERMERCADO));

    nome = getString("Nome do Supermercado:");
    
    //pedir horas (testar se funciona!)
    printf("\nHora de abertura (HH:MM):");
    scanf("%H:%M",&horaAbertura);

    printf("\nHora de fecho (HH:MM):");
    scanf("%H:%M",&horaFecho);

    nCaixas = validarInt("\nNúmero de caixas do supermercado:",1,10);
    nmrMaxClientesFila = validarInt("\nMáximo de clientes na fila:",1,20);
    nmrMinCliFechaCaixa = validarInt("\nNúmero de clientes para fechar a caixa:",1,5);
    
    //Ler Ficheiros
    ListaGenerica *ListaCaixas = CriarLG();
    ListaGenerica *ListaClientes = CriarLG();
    ListaGenerica *ListaFuncionarios = CriarLG();
    ListaGenerica *ListaProdutos = CriarLG();

    SM->nome = nome;
    
    SM->horaAbertura = horaAbertura;
    SM->horaFecho = horaFecho;

    SM->numCaixas = nCaixas;
    SM->nmrMaxClientesFila = nmrMaxClientesFila;
    SM->nmrMinCliFechaCaixa = nmrMinCliFechaCaixa;

    SM->Caixas = ListaCaixas;
    SM->Clientes = ListaClientes;
    SM->Funcionarios = ListaFuncionarios;
    SM->Produtos = ListaProdutos;

    return SM;
}