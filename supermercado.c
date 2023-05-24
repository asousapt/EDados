#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcoes.h"
#include "supermercado.h"
#include "ListaGenerica.h"
#include "Caixa.h"
#include "Funcionarios.h"
#include "Log.h"
#include "Produtos.h"

SUPERMERCADO * CriarSM(){
    time_t dataAtual;
    int emDesenvolvimento = 0; 
    int nCaixas, nmrMinCliFechaCaixa, nmrMaxClientesFila;
    int horaAbertura, minutoAbertura, horaFecho, minutoFecho,nmrClientesSupermercado, tempoMaxEspera = 0;
    char *nome;

    SUPERMERCADO *SM = (SUPERMERCADO *)malloc(sizeof(SUPERMERCADO));
    printf("\nAmbiente de desenvolvimento? (0-1)\n");
    scanf("%d", &emDesenvolvimento);
    
    if (emDesenvolvimento == 0) {
        nome = getString("Nome do Supermercado:");
    
        // pede ao utilizador a hora de abertura do supermercado
        do
        {
            printf("\nHora de abertura (HH:MM):");
            scanf("%d:%d", &horaAbertura, &minutoAbertura);
        } while (validaHoras(horaAbertura, minutoAbertura) == 0);
        
        SM->horaAbertura = convertToTime(horaAbertura, minutoAbertura);

        //pede ao utilizador a hora de fecho do supermercado
        do
        {
            printf("\nHora de fecho (HH:MM):");
            scanf("%d:%d",&horaFecho, &minutoFecho);
        } while (validaHorasFecho(horaAbertura, minutoAbertura,SM->horaAbertura) == 0);
        
        SM->horaFecho = convertToTime(horaFecho, minutoFecho);

        nCaixas = validarInt("\nNúmero de caixas do supermercado:",1,10);
        nmrMaxClientesFila = validarInt("\nNumero maximo de clientes na fila:",1,20);
        nmrMinCliFechaCaixa = validarInt("\nNúmero minimo de clientes para fechar a caixa:",1,5);
        tempoMaxEspera = validarInt("\nTempo maximo de espera de clientes na fila em minutos",1,60);
        nmrClientesSupermercado = validarInt("\nNúmero maximo de clientes em simultaneo no supermercado",1,100);
        
    } else  {
        nome ="LIDL";
        SM->horaAbertura = convertToTime(8, 0);
        SM->horaFecho = convertToTime(20, 0);
        nCaixas = 10; 
        nmrMaxClientesFila = 10; 
        nmrMinCliFechaCaixa = 3; 
        tempoMaxEspera = 5; 
        nmrClientesSupermercado = 100;
    }
    
    int i; 
    
    ListaGenerica *ListaCaixas = CriarLG();
    ListaGenerica *ListaClientes = CriarLG();
    ListaGenerica *ListaFuncionarios = CriarLG();
    ListaGenerica *ListaProdutos = CriarLG();
    ListaGenerica *ListaProdutosGratis = CriarLG();
    ListaGenerica *ListaLogApp = CriarLG(); 
    ListaGenerica *ListaClientesAsCompras = CriarLG(); 

    SM->nome = nome;

    SM->numCaixas = nCaixas;
    SM->nmrMaxClientesFila = nmrMaxClientesFila;
    SM->nmrMinCliFechaCaixa = nmrMinCliFechaCaixa;
    SM->tempoEsperaMax = tempoMaxEspera;
    SM->nmrClientesSupermercado = nmrClientesSupermercado;
    
    SM->Caixas = ListaCaixas;
    SM->Clientes = ListaClientes;
    SM->Funcionarios = ListaFuncionarios;
    SM->Produtos = ListaProdutos;
    SM->LogApp = ListaLogApp;
    SM->ProdutosOferecidos = ListaProdutosGratis;
    SM->ClientesAsCompras = ListaClientesAsCompras;

    time(&dataAtual);
    LOG  * logCriar = CriarLog("Supermercado inicializado com sucesso!", dataAtual);
    AddBeginLG(ListaLogApp, logCriar);

    return SM;
}

void carregaCaixas(SUPERMERCADO* supermercadoActual){
    time_t dataAtual;
    time(&dataAtual);
    LOG  * logCriar1 = CriarLog("Inicio de criacao de caixas do supermercado!", dataAtual);
    AddBeginLG(supermercadoActual->LogApp, logCriar1);

    int numeroCaixas = supermercadoActual->numCaixas+10;
    int i = 10;

    for ( i = 10; i < numeroCaixas; i++)
    {
        CAIXA* caixaInserir = CriarCaixa(i);
                
        AddBeginLG(supermercadoActual->Caixas,caixaInserir);
        
        time(&dataAtual);
        char caixastr[30];
        sprintf(caixastr, "Caixa %d criada com sucesso", i);

        LOG  * logCriar2 = CriarLog(caixastr, dataAtual);
        AddBeginLG(supermercadoActual->LogApp, logCriar2);
    }
    
    time(&dataAtual);
    LOG  * logCriar3 = CriarLog("Caixas criadas com sucesso!", dataAtual);
    AddBeginLG(supermercadoActual->LogApp, logCriar3);
}

int carregaSupermercado(SUPERMERCADO* supermercadoActual){
    time_t dataAtual;
    time(&dataAtual);
    
    LOG  * logCriar1 = CriarLog("Inicio do carregamento do supermercado.", dataAtual);
    AddBeginLG(supermercadoActual->LogApp, logCriar1);

    // Lê dos ficheiros e alimenta as listas com dados dos clientes, funcionarios e produtos 
    if (LerficheiroClientes("Clientes.txt",supermercadoActual) == 0) return 0; 
    if (LerficheiroFuncionarios("Funcionarios.txt", supermercadoActual) == 0) return 0;
    if (LerficheiroProdutos("Produtos.txt", supermercadoActual) == 0) return 0;
    carregaCaixas(supermercadoActual);
    
    time(&dataAtual);
    LOG  * logCriar2 = CriarLog("Supermercado carregado cum sucesso!.", dataAtual);
    AddBeginLG(supermercadoActual->LogApp, logCriar2);
    return 1;
}

void DestruirSupermercado(SUPERMERCADO *mercado){
    free(mercado->nome);
    DestruirLG(mercado->Caixas, DestruirCaixa);
    DestruirLG(mercado->Clientes,DestruirCliente);
    DestruirLG(mercado->ClientesAsCompras,DestruirClientesAsCompras);
    DestruirLG(mercado->Funcionarios, DestruirFuncionario);
    DestruirLG(mercado->LogApp,DestruirLog);
    DestruirLG(mercado->Produtos,DestruirProduto);
    DestruirLG(mercado->ProdutosOferecidos,DestruirProduto);
    free(mercado);
}