#include "Menu.h"
#include "funcoes.h"

void menuUtilizador(){
  printf("====================================");
  printf("========== Menu Utilizador =========");
  printf("====================================");
  printf("= 1 - Operacoes com Caixas         =");
  printf("= 2 - Operacoes com Clientes       =");
  printf("= 3 - Operacoes com Clientes       =");
  printf("= 5 - Continuar                    =");
  printf("= 0 - Terminar o programa          =");
  printf("====================================");
}

void menuMostrarClientes(){
  printf("============================================");
  printf("============ Mostrar Clientes ==============");
  printf("============================================");
  printf("= 1 - Mostrar Clientes atendidos numa caixa=");
  printf("= 2 - Pesquisar Cliente                    =");
  printf("= 0 - Sair                                 =");
  printf("============================================");
}

void menuOperacoesClientes(){
  printf("===========================================");
  printf("========== Operacoes com Clientes =========");
  printf("===========================================");
  printf("= 1 - Mostrar Clientes atendidos numa caixa=");
  printf("= 2 - Pesquisar Cliente                    =");
  printf("= 3 - Mudar Cliente de uma fila para outra =");
  printf("= 0 - Sair                                 =");
  printf("============================================");
}

void menuOperacoesCaixa(){
  printf("============================================");
  printf("========== Operacoes com Caixas ============");
  printf("============================================");
  printf("= 1 - Mostrar Clientes atendidos numa caixa=");
  printf("= 3 - Mostrar Caixas                       =");
  printf("= 0 - Sair                                 =");
  printf("============================================");
}

void menuMostrarClientes(){
  int opcao = validarInt("Escolha uma das opcoes: ", 0,3);
}

void menuMostrarCaixa(){
  
  printf("====================================");
  printf("========== Mostrar Caixas ==========");
  printf("====================================");
  printf("= 1 - Todas as Caixas              =");
  printf("= 2 - Caixas Abertas               =");
  printf("= 3 - Caixas Fechadas              =");
  printf("= 0 - Sair                         =");
  printf("====================================");
}


