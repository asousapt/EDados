#include <stdio.h>
#include "texto.h"
#include "funcoes.h"
#include "ListaGenerica.h"
#include "texto.h"
#include "Fila.h"

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
        printf("\n\n\tImpossivel abrir Ficheiro \n\n");
        return 0;
    }

     while(!feof(F1))
    {
        STRING *V = Read_Split_Line_File(F1, n_campos_max, &n_campos_lidos, "\t\r"); 
       
        PRODUTO * produtoInserir = CriarProduto(V[0], V[1], V[2], V[3], V[4]);
        
        AddBeginLG(LgProd,produtoInserir);

        free (V);
    }
   
    fclose(F1);
    return 1;
}

//funcao que coloca numa lista os funcionarios da empresa
int LerficheiroFuncionarios(char *ficheiro, ListaGenerica * LgFunc) {
    int n_campos_max = 20;
    int n_campos_lidos;
    int n_linhas_lidas = 0;
    
    FILE *F1 = fopen(ficheiro,"r"); 
    if (!F1) {
        printf("\n\n\tImpossivel abrir Ficheiro \n\n");
        return 0;
    }

        while(!feof(F1))
    {
        STRING *V = Read_Split_Line_File(F1, n_campos_max, &n_campos_lidos, "\t\r"); 
       
        FUNCIONARIO * funcionarioInserir = CriarFuncionario(V[0], V[1]);
        
        AddBeginLG(LgFunc,funcionarioInserir);

        free (V);
    }
   
    fclose(F1);
    return 1;
}


// funcao que le o ficheiro de clientes e coloca numa lista generica
int LerficheiroClientes(char *ficheiro , ListaGenerica * LgCl){
  
    int n_campos_max = 20;
    int n_campos_lidos;
    int n_linhas_lidas = 0;
    
    FILE *F1 = fopen(ficheiro,"r"); 
    if (!F1) {
        printf("\n\n\tImpossivel abrir Ficheiro \n\n");
        return 0;
    }
    
    int linhas = 0; 
    while(!feof(F1))
    {
        STRING *V = Read_Split_Line_File(F1, n_campos_max, &n_campos_lidos, "\t\r"); 
       
        CLIENTE *clienteInserir = CriarCliente(V[0], V[1]);
        
        AddBeginLG(LgCl,clienteInserir);

        free (V);
    }
   
    fclose(F1);
    return 1;
}

// Faz print de um cliente 
void MostrarCliente(void* C){
  CLIENTE* objCliente = (CLIENTE *) C;
  printf("\n === Cliente ===");
  printf("\n Numero: %d", objCliente->cod);
  printf("\n Nome: %s", objCliente->nome);

}

// Faz print de um cliente 
void MostrarFuncionario(void* F){
  FUNCIONARIO* objFuncionario = (FUNCIONARIO *) F;
  printf("\n === Funcionario ===");
  printf("\n Numero: %d", objFuncionario->cod);
  printf("\n Nome: %s", objFuncionario->nome);

}

// Faz print de um produto 
void MostrarProduto(void* P){
  PRODUTO* objProduto = (PRODUTO *) P;

  printf("\n === Produto ===");
  printf("\n Numero: %d", objProduto->cod);
  printf("\n Descricao: %s", objProduto->designacao);
  printf("\n Preco: %f", objProduto->preco);
  printf("\n Tempo Compra: %f", objProduto->tempoCompra);
  printf("\n Tempo Caixa: %f", objProduto->tempoCaixa);

}

//funcao que limpa da memoria o cliente 
void DestruirCliente(void* C){
  CLIENTE* objCliente = (CLIENTE *) C;
  free(objCliente);
}

void DestruirFuncionario(void* F){
  FUNCIONARIO* objFuncionario = (FUNCIONARIO *) F;
  free(objFuncionario);
}

void DestruirProduto(void* P){
  PRODUTO* objProduto = (PRODUTO *) P;
  free(objProduto);
}