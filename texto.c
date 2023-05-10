#include <stdio.h>
#include "texto.h"
#include "funcoes.h"
#include "ListaGenerica.h"
#include "texto.h"
#include "Fila.h"
#include "Clientes.h"
#include "Produtos.h"
#include "Log.h"

#define STRING char *
#define MAX_LINHA_FICHEIRO 200


typedef char LinhaTexto[MAX_LINHA_FICHEIRO];
LinhaTexto LT;


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

int LerficheiroProdutos(char *ficheiro, ListaGenerica * LgProd) { 
    int n_campos_max = 20;
    int n_campos_lidos;
    int n_linhas_lidas = 0;
    
    FILE *F1 = fopen(ficheiro,"r"); 
    if (!F1) {
        printf("\n\n\tImpossivel abrir Ficheiro de produtos!\n\n");
        return 0;
    }
    printf("A importar produtos...\n");
    
     while(!feof(F1))
    {
        STRING *V = Read_Split_Line_File(F1, n_campos_max, &n_campos_lidos, "\t\r"); 
       
        PRODUTO * produtoInserir = CriarProduto(V[0], V[1], V[2], V[3], V[4]);
        
        if (PertenceLG(LgProd, produtoInserir, validaProduto) == 0) {
            AddBeginLG(LgProd,produtoInserir);
        }
        
        free (V);
    }
   
    fclose(F1);
    printf("Produtos importados com sucesso!\n");
    return 1;
}

//funcao que coloca numa lista os funcionarios da empresa
int LerficheiroFuncionarios(char *ficheiro, ListaGenerica * LgFunc) {
    int n_campos_max = 20;
    int n_campos_lidos;
    int n_linhas_lidas = 0;
    
    FILE *F1 = fopen(ficheiro,"r"); 
    if (!F1) {
        printf("\n\n\tImpossivel abrir Ficheiro de funcionarios \n\n");
        return 0;
    }

        while(!feof(F1))
    {
        STRING *V = Read_Split_Line_File(F1, n_campos_max, &n_campos_lidos, "\t\r"); 
       
        FUNCIONARIO * funcionarioInserir = CriarFuncionario(V[0], V[1]);
        if (PertenceLG(LgFunc, funcionarioInserir,validaFuncionario) == 0) {
            AddBeginLG(LgFunc,funcionarioInserir);
        }
        
        free (V);
    }
   
    fclose(F1);
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
    //struct tm *data_hora_atual; 
    //LOG  * logCriar = CriarLog("Clientes importados", data_hora_atual);
    //AddBeginLG()
    printf("Clientes importados com sucesso!\n");
    return 1;
}