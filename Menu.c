#include "Menu.h"

void menuUtilizador(SUPERMERCADO *S,RELOGIO *R){
  int opcao = -1;

  printf("\n====================================\n");
  printf("========== Menu Utilizador =========\n");
  printf("====================================\n");
  printf("= 1 - Operacoes com Caixas         =\n");
  printf("= 2 - Operacoes com Clientes       =\n");
  printf("= 3 - Estatistica                  =\n");
  printf("= 0 - Continuar                    =\n");
  printf("====================================\n");
  opcao = validarInt("Escolha uma opcao", 0,3);

  while (opcao != 0) {
    switch(opcao){
      case 1:
        menuOperacoesCaixa(S,R);
        break;
        
      case 2:
        menuOperacoesClientes(S);
        break;
        
      case 3:
        mostraEstatisticasGerais(S);
        break;
      
      case 0:
        break;
      
      default:
        printf("Opção inválida\n");
        break;
    }
  }
}

/*void menuMostrarClientes(SUPERMERCADO *S){
  int opcao = -1;

  printf("\n============================================\n");
  printf("============ Mostrar Clientes ==============\n");
  printf("============================================\n");
  printf("= 1 - Mostrar Clientes atendidos numa caixa=\n");
  printf("= 2 - Pesquisar Cliente                    =\n");
  printf("= 0 - Sair                                 =\n");
  printf("============================================\n");
  scanf("%d",&opcao);

  while (opcao != 0) {
    switch(opcao){
      case 1:
        listarCaixas(S->Caixas);

        int maxCaixa = 9+S->Caixas->NEL;
        int codCaixa = validarInt("Caixa: ",10,maxCaixa);
        CAIXA *cx = ProcurarCaixa(S->Caixas,codCaixa);

        ShowLG(cx->pessoasAtendidas,MostrarClientesAsCompras);
        break;

      case 2:
        int codCliente = validarInt("Cliente: ",10,100000000000000);

        CLIENTEASCOMPRAS *CC = ProcurarClienteAsCompras(S->ClientesAsCompras,codCliente);

        if (CC){
          printf("O cliente encontra-se no supermercado!\n");
        } else {
          CAIXA *cx = procurarCaixaCliente(S->Caixas,codCliente);

          if (cx){
            printf("O cliente encontra-se na caixa Nº:%d!\n",cx->numCaixa);
          }else{
            printf("O cliente ainda não entrou no supermercado!\n");
          }
        }

        CLIENTE *CL = ProcurarCliente(S->Clientes,codCliente);
        MostrarCliente(CL);
        break;

      case 0:
        break;

      default:
        printf("Opção inválida\n");
        break;
    }
  }
}*/

void menuOperacoesClientes(SUPERMERCADO *S){
  int opcao = -1;

  printf("\n===========================================\n");
  printf("========== Operacoes com Clientes =========\n");
  printf("===========================================\n");
  printf("= 1 - Mostrar Clientes atendidos numa caixa=\n");
  printf("= 2 - Pesquisar Cliente                    =\n");
  printf("= 3 - Mudar Cliente de uma fila para outra =\n");
  printf("= 0 - Sair                                 =\n");
  printf("============================================\n");
  opcao = validarInt("Escolha uma opcao", 0,3);

  while (opcao != 0) {
    switch(opcao){
      case 1:
        listarCaixas(S->Caixas);

        int maxCaixa = 9+S->Caixas->NEL;
        int codCaixa = validarInt("Caixa: ",10,maxCaixa);
        CAIXA *cx = ProcurarCaixa(S->Caixas,codCaixa);

        ShowLG(cx->pessoasAtendidas,MostrarClientesAsCompras);
        break;

      case 2:
        int codCliente = validarInt("Cliente: ",10,100000000000000);
        CLIENTEASCOMPRAS *CC = ProcurarClienteAsCompras(S->ClientesAsCompras,codCliente);

        if (CC != NULL){
          printf("O cliente encontra-se no supermercado!\n");
        } else {
          CAIXA *cx = procurarCaixaCliente(S->Caixas,codCliente);

          if (cx != NULL){
            printf("O cliente encontra-se na caixa Nº:%d!\n",cx->numCaixa);
          }else{
            printf("O cliente ainda não entrou no supermercado!\n");
          }
        }

        CLIENTE *CL = ProcurarCliente(S->Clientes,codCliente);
        MostrarCliente(CL);
        break;

      case 3: 
        ShowLG(S->Caixas, MostrarCaixaAberta);

        int maxCaixa = 9+S->Caixas->NEL;

        CAIXA *cx = NULL;
        int codCaixa;
        while (cx == NULL){
          codCaixa = validarInt("Caixa Destino: ",10,maxCaixa);
          cx = ProcurarCaixaAberta(S->Caixas,codCaixa);
          if (cx == NULL) printf("Caixa selecionada não se encontra aberta!");
        }

        int codCliente = validarInt("Cliente para trocar: ",10,100000000000000);

        CLIENTEASCOMPRAS *CC = NULL;
        while (cx == NULL){
          CC = procurarClienteCaixa(S->Caixas,codCliente);
          if (CC == NULL) printf("Cliente selecionado não se encontra numa caixa!");
        }

        trocarClientedeFila(S,cx,CC);
        break;

      case 0:
        break;

      default:
        printf("Opção inválida\n");
        break;
    }
  }
}

void menuOperacoesCaixa(SUPERMERCADO *S,RELOGIO *R){
  int opcao = -1;

  printf("\n============================================\n");
  printf("========== Operacoes com Caixas ============\n");
  printf("============================================\n");
  printf("= 1 - Mostrar Todas as Caixas              =\n");
  printf("= 2 - Mostrar Caixas Abertas               =\n");
  printf("= 3 - Mostrar Caixas Fechadas              =\n");
  printf("= 4 - Mostrar Clientes atendidos numa caixa=\n");
  printf("= 5 - Abrir Caixa                          =\n");
  printf("= 6 - Fechar Caixa                         =\n");
  printf("= 0 - Sair                                 =\n");
  printf("============================================\n");
  opcao = validarInt("Escolha uma opcao", 0,6);

  while (opcao != 0) {
    switch(opcao){
      case 1:
        listarCaixas(S->Caixas);
        break;

      case 2:
        ShowLG(S->Caixas, MostrarCaixaAberta);
        break;

      case 3: 
        ShowLG(S->Caixas, MostrarCaixaFechada);
        break;

      case 4: 
        listarCaixas(S->Caixas);

        int maxCaixa = 9+S->Caixas->NEL;
        int codCaixa = validarInt("Caixa: ",10,maxCaixa);
        CAIXA *cx = ProcurarCaixa(S->Caixas,codCaixa);

        ShowLG(cx->pessoasAtendidas,MostrarClientesAsCompras);
        break;
        
      case 5: 
        AbreFechaCaixa(S,0,1,R);
        break;

      case 6: 
        AbreFechaCaixa(S,0,0,R);
        break;

      case 0:
        break;

      default:
        printf("Opção inválida\n");
        break;
    }
  }
}

/*void menuMostrarCaixa(SUPERMERCADO *S){
  
  printf("\n====================================\n");
  printf("========== Mostrar Caixas ==========\n");
  printf("====================================\n");
  printf("= 1 - Todas as Caixas              =\n");
  printf("= 2 - Caixas Abertas               =\n");
  printf("= 3 - Caixas Fechadas              =\n");
  printf("= 0 - Sair                         =\n");
  printf("====================================\n");
}*/


