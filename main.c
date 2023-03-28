#include <stdio.h>
#include <string.h>
#include "ListaGenerica.c"
#include "texto.c"
#include "funcoes.c"

int main(void) {
    printf("*** Bem-vindo ***\n"); 
    char * ficheiroConfig = "config.ini"; 

    ConfigInicial(ficheiroConfig);
    

    ListaGenerica * ListaCaixas = CriarLG();

  return 0;
}