#include <stdio.h>
#include <string.h>
#include "ListaGenerica.h"
#include "ListaGenerica.c"
#include "Fila.h"
#include "texto.h"
#include "texto.c"
#include "funcoes.h"
#include "supermercado.c"


int main(void) {
  printf("*** Bem-vindo ***\n"); 
  
 SUPERMERCADO * supermercadoActual = CriarSM();

  // cria as listas 
  ListaGenerica * listaCliente = CriarLG();
  ListaGenerica * listaFuncionarios = CriarLG();
  ListaGenerica * listaProdutos = CriarLG();

  // Lê dos ficheiros e alimenta as listas com dados dos clientes, funcionarios e produtos 
  LerficheiroClientes("Clientes.txt",listaCliente); 
  LerficheiroFuncionarios("Funcionarios.txt", listaFuncionarios); 
  LerficheiroProdutos("Produtos.txt", listaProdutos);
  
  //ShowLG(listaProdutos, MostrarProduto);
  
  //limpa da memoria todas as listas 
  DestruirLG(listaCliente, DestruirCliente);
  DestruirLG(listaFuncionarios, DestruirFuncionario);
  DestruirLG(listaProdutos, DestruirProduto);

  return 0;
}