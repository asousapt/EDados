#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING char *
#define MAX_LINHA_FICHEIRO 200

typedef char LinhaTexto[MAX_LINHA_FICHEIRO];

LinhaTexto LT;

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


int main()
{
    int n_campos_max = 20;
    int n_campos_lidos;
    int n_linhas_lidas = 0;
    
    //----------------------------------------------------------------------------
    FILE *F1 = fopen("Clientes.txt","r"); 
    if (!F1) {
        printf("\n\n\tImpossivel abrir Ficheiro \n\n");
        return -1;
    }
    while(!feof(F1))
    {
        STRING *V = Read_Split_Line_File(F1, n_campos_max, &n_campos_lidos, "\t\r\n"); 

       
        for (int i = 0; i < n_campos_lidos; i++)
            printf("%s\n", V[0]);
            printf("%s\n", V[1]);

        for (int i = 0; i < n_campos_lidos; i++)
            free (V[i]);
        free (V);
    }
    fclose(F1);

    return 0;
}