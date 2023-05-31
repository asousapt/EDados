#include "Menu.h"

void menuUtilizador(SUPERMERCADO *S){
  int opcao = -1;

  printf("\n====================================\n");
  printf("========== Menu Utilizador =========\n");
  printf("====================================\n");
  printf("= 1 - Operacoes com Caixas         =\n");
  printf("= 2 - Operacoes com Clientes       =\n");
  printf("= 3 - Operacoes com Clientes       =\n");
  printf("= 0 - Continuar                    =\n");
  printf("====================================\n");

  while (opcao != 0) {
    switch(opcao){
      case 1:
        menuOperacoesCaixa(S);
        break;
        
      case 2:
        menuOperacoesClientes(S);
        break;
        
      case 3:
        menuOperacoesClientes(S);
        break;
      
      case 0:
        break;
      
      default:
        printf("Opção inválida\n");
        break;
    }
  }

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


