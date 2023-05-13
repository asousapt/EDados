#include <stdio.h>
#include "texto.h"
#include "funcoes.h"
#include "ListaGenerica.h"
#include "texto.h"
#include "Fila.h"
#include "Clientes.h"
#include "Produtos.h"
#include "Log.h"
#include "supermercado.h"

#define STRING char *
#define MAX_LINHA_FICHEIRO 200


typedef char LinhaTexto[MAX_LINHA_FICHEIRO];
LinhaTexto LT;

char *trim(char *str)
{
    char *end;

    while(isspace((unsigned char)*str)) str++;

    if(*str == 0)
        return str;

    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    end[1] = '\0';

    return str;
}


// funcao que faz separacao das strings da linha 
STRING *Read_Split_Line_File(FILE *f, int n_campos_max, int *n_campos_lidos, char *separadores)
{
    *n_campos_lidos = 0;
    if (!f) return NULL;
    if (fgets(LT , MAX_LINHA_FICHEIRO , f) != NULL)    
    {
        
        STRING *Res = (STRING *)malloc(n_campos_max*sizeof(STRING));  
        char *pch = strtok (LT, separadores);
        int cont = 0;
        while (pch != NULL)
        {
            Res[cont] = (char *)malloc((strlen(pch)+1)*sizeof(char));
            strcpy(Res[cont++], pch);
            pch = strtok (NULL, separadores);
        }
        *n_campos_lidos = cont;
        return Res;
    }
    return NULL;
};

int LerficheiroProdutos(char *ficheiro, SUPERMERCADO * supermercadoActual) { 
    int n_campos_max = 20;
    int n_campos_lidos;
    int n_linhas_lidas = 0;
    
    FILE *F1 = fopen(ficheiro,"r"); 
    if (!F1) {
        printf("\n\n\tImpossivel abrir Ficheiro de produtos!\n\n");
        return 0;
    }
    printf("A importar produtos...\n");
    
    time_t dataAtual;
    time(&dataAtual);
    LOG  * logCriar1 = CriarLog("Inicio de importação de produtos.", dataAtual);
    AddBeginLG(supermercadoActual->LogApp, logCriar1);
    
     while(!feof(F1))
    {
        STRING *V = Read_Split_Line_File(F1, n_campos_max, &n_campos_lidos, "\t\r"); 
       
        PRODUTO * produtoInserir = CriarProduto(V[0], V[1], V[2], V[3], V[4]);
        
        if (PertenceLG(supermercadoActual->Produtos, produtoInserir, validaProduto) == 0) {
            AddBeginLG(supermercadoActual->Produtos,produtoInserir);
        }
        
        free (V);
    }
   
    fclose(F1);

    time(&dataAtual);
    LOG  * logCriar2 = CriarLog("Produtos importados com sucesso!", dataAtual);
    AddBeginLG(supermercadoActual->LogApp, logCriar2);

    printf("Produtos importados com sucesso!\n");
    return 1;
}

//funcao que coloca numa lista os funcionarios da empresa
int LerficheiroFuncionarios(char *ficheiro, SUPERMERCADO * supermercadoActual) {
    int n_campos_max = 20;
    int n_campos_lidos;
    int n_linhas_lidas = 0;
    
    FILE *F1 = fopen(ficheiro,"r"); 
    if (!F1) {
        printf("\n\n\tImpossivel abrir Ficheiro de funcionarios \n\n");
        return 0;
    }
    
    time_t dataAtual;
    time(&dataAtual);
    LOG  * logCriar1 = CriarLog("Inicio de importação de funcionarios.", dataAtual);
    AddBeginLG(supermercadoActual->LogApp, logCriar1);

    while(!feof(F1)) {
        STRING *V = Read_Split_Line_File(F1, n_campos_max, &n_campos_lidos, "\t\r"); 
        
        FUNCIONARIO * funcionarioInserir = CriarFuncionario(V[0], V[1]);
        if (PertenceLG(supermercadoActual->Funcionarios, funcionarioInserir,validaFuncionario) == 0) {
            AddBeginLG(supermercadoActual->Funcionarios,funcionarioInserir);
        }
        
        free (V);
    }
   
    fclose(F1);
    
    time(&dataAtual);
    LOG  * logCriar2 = CriarLog("Funcionários importados com sucesso!", dataAtual);
    AddBeginLG(supermercadoActual->LogApp, logCriar2);
    printf("Funcionários importados com sucesso!\n");

    return 1;
}

// funcao que le o ficheiro de clientes e coloca numa lista generica
int LerficheiroClientes(char *ficheiro , SUPERMERCADO * supermercadoActual){
  
    int n_campos_max = 20;
    int n_campos_lidos;
    int n_linhas_lidas = 0;
    
    FILE *F1 = fopen(ficheiro,"r"); 
    if (!F1) {
        printf("\n\n\tImpossivel abrir Ficheiro de Clientes!\n\n");
        return 0;
    }
    time_t dataAtual;
    time(&dataAtual);
    LOG  * logCriar1 = CriarLog("Inicio de importação de clientes.", dataAtual);
    AddBeginLG(supermercadoActual->LogApp, logCriar1);

    int linhas = 0; 
    while(!feof(F1))
    {
        STRING *V = Read_Split_Line_File(F1, n_campos_max, &n_campos_lidos, "\t\r"); 
       
        CLIENTE *clienteInserir = CriarCliente(V[0], V[1]);
        
       if (PertenceLG(supermercadoActual->Clientes, clienteInserir, validaCliente) == 0 ) {
            AddBeginLG(supermercadoActual->Clientes,clienteInserir);
        }
        

        free (V);
    }
   
    fclose(F1);
    
    time(&dataAtual);
    LOG  * logCriar2 = CriarLog("Clientes importados com sucesso!", dataAtual);
    AddBeginLG(supermercadoActual->LogApp, logCriar2);
    printf("Clientes importados com sucesso!\n");
    return 1;
}