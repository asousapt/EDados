#include "Switch.h"

/*void menuUtilizador(){
  printf("====================================");
  printf("========== Menu Utilizador =========");
  printf("====================================");
  printf("= 1 - Operacoes com Caixas         =");
  printf("= 2 - Operacoes com Clientes       =");
  printf("= 3 - Estatistica                  =");
  printf("= 4 - Continuar                    =");
  printf("= 0 - Terminar o programa          =");
  printf("====================================");
}*/


void switchPrincipal(){
    int op;
    do
    {
        menuUtilizador();
        op = validarInt("Escolha uma opcao", 0,4);
        switch (op)
        {
            case 1:
                switchOperacoesCaixa();
                break;

            case 2:
                switchOperacoesCliente();
                break;

            case 3:
                break;
            case 0:
                exit(0);
                break;
        }
    } while (op != 4);
}

void switchOperacoesCaixa(){

}

void switchOperacoesCliente(){

}