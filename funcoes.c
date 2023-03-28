#include <stdio.h>
#include <unistd.h>
#include "structs.c"
#include "ListaGenerica.c"


void ConfigInicial(char* ficheiroConfig){
    if(!access(ficheiroConfig, F_OK )){
        printf("The File %s\t was Found\n",ficheiroConfig);
    }else{
        printf("The File %s\t not Found\n",ficheiroConfig);
    }

}


SUPERMERCADO CriarSM(SUPERMERCADO *SM, int nCaixas);
