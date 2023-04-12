#include <stdio.h>
#include <string.h>
#include "ListaGenerica.h"
#include "texto.h"
#include "funcoes.h"

int main(void) {
    printf("*** Bem-vindo ***\n"); 
    char * ficheiroClientes = "Clientes.txt"; 

    ListaGenerica * LgCl = CriarLG();
    LgCl = LerficheiroClientes(ficheiroClientes,LgCl);
   

  return 0;
}