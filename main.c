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
    
  ListaGenerica * listaCliente = CriarLG();
  LerficheiroClientes("Clientes.txt",listaCliente); 

  ShowLG(listaCliente, MostrarCliente);
  DestruirLG(listaCliente, DestruirCliente);

  return 0;
}