#include <stdio.h>
#include <string.h>

#include "ListaGenerica.h"
#include "texto.h"
#include "funcoes.h"

int main(void) {
    printf("*** Bem-vindo ***\n"); 
    char * ficheiroConfig = "config.ini"; 

    ConfigInicial(ficheiroConfig);
    

    ListaGenerica * ListaCaixas = CriarLG();

  return 0;
}