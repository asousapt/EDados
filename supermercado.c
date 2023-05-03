#include <time.h>
#include <stdio.h>
#include <string.h>
#include "supermercado.h"
#include "funcoes.c"

SUPERMERCADO * CriarSM(){
    int nCaixas, nmrMinCliFechaCaixa, nmrMaxClientesFila;
    int horaAbertura, minutoAbertura, horaFecho, minutoFecho = 0;
    char *nome;

    SUPERMERCADO *SM = (SUPERMERCADO *)malloc(sizeof(SUPERMERCADO));

    nome = getString("Nome do Supermercado:");
    
    // pede ao utilizador a hora de abertura do supermercado
    do
    {
        printf("\nHora de abertura (HH:MM):");
        scanf("%d:%d", &horaAbertura, &minutoAbertura);
    } while (validaHoras(horaAbertura, minutoAbertura) == 0);
    

    //pede ao utilizador a hora de fecho do supermercado
    do
    {
        printf("\nHora de fecho (HH:MM):");
        scanf("%d:%d",&horaFecho, &minutoFecho);
    } while (validaHoras(horaAbertura, minutoAbertura) == 0);
    

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

void destruirSM(SUPERMERCADO super){
};

int carregaSupermercado(SUPERMERCADO* supermercadoActual){
    // Lê dos ficheiros e alimenta as listas com dados dos clientes, funcionarios e produtos 
    if (LerficheiroClientes("Clientes.txt",supermercadoActual->Clientes) == 0) return 0; 
    if (LerficheiroFuncionarios("Funcionarios.txt", supermercadoActual->Funcionarios) == 0) return 0;
    if (LerficheiroProdutos("Produtos.txt", supermercadoActual->Produtos) == 0) return 0;

    return 1;
}