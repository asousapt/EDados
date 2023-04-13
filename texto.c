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

// PRODUTO *LerFicheiroProdutos(char *file){
    
// }

// funcao que le o ficheiro de clientes e coloca numa lista generica
void LerficheiroClientes(char *file , ListaGenerica * LgCl){
    // faz a criacao da lista generica
    
    int n_campos_max = 20;
    int n_campos_lidos;
    int n_linhas_lidas = 0;
    
    FILE *F1 = fopen(file,"r"); 
    if (!F1) {
        printf("\n\n\tImpossivel abrir Ficheiro \n\n");
        //return NULL;
    }
    int linhas = 0; 
    while(!feof(F1))
    {
        STRING *V = Read_Split_Line_File(F1, n_campos_max, &n_campos_lidos, "\t\r"); 
        
        CLIENTE *clienteInserir = (CLIENTE *)malloc(sizeof(CLIENTE)); 
        clienteInserir->cod = atoi(V[0]);
        strcpy(clienteInserir->nome, V[1]);

        AddBeginLG(LgCl,clienteInserir);

        free (V);
    }
   
    fclose(F1);

    

}