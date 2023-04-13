#include <stdio.h>
#include <string.h>
#include "ListaGenerica.h"
#include "ListaGenerica.c"
#include "Fila.h"
#include "texto.h"
#include "texto.c"
#include "funcoes.h"

int main(void) {
    printf("*** Bem-vindo ***\n"); 
    char * ficheiroClientes = "Clientes.txt"; 

   ListaGenerica *LgCl = CriarLG();
  LerficheiroClientes(ficheiroClientes,LgCl);
  void *raw_result;
    ShowLG(LgCl, raw_result);

  return 0;
}