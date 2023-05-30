#include "Menu.h"

int menuUtilizador(){
  int opcao = 0;

  printf("====================================");
  printf("========== Menu Utilizador =========");
  printf("====================================");
  printf("= 1 - Abrir Caixa                  =");
  printf("= 2 - Fechar Caixa                 =");
  printf("= 3 - Mostrar Caixas               =");
  printf("= 4 - Mostrar Clientes da Caixa    =");
  printf("= 5 - Pesquisar Cliente            =");
  printf("=              =");
  printf("= 6 - Continuar                    =");
  printf("= 0 - Terminar o programa          =");
  printf("====================================");
  scanf("%d",&opcao);

  return opcao;
}

int menuMostrarCaixa(){
  int opcao = 0;
  printf("====================================");
  printf("========== Mostrar Caixas ==========");
  printf("====================================");
  printf("= 1 - Todas as Caixas              =");
  printf("= 2 - Caixas Abertas               =");
  printf("= 3 - Caixas Fechadas              =");
  printf("= 0 - Sair                         =");
  printf("====================================");
  scanf("%d",&opcao);

  return opcao;
}
