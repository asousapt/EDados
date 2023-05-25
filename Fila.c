#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "Fila.h"
#include "Clientes.h"
#include "Produtos.h"

//cria fila generica
FILAGENERICA *CriarFila() {
    FILAGENERICA *fila = (FILAGENERICA *) malloc(sizeof(FILAGENERICA));
    fila->cabeca = fila->cauda = NULL;
    fila->tamanho = 0;
    return fila;
}

// Função para criar um novo nó para a fila passando apenas os dados
NOFILA *CriarNoFila(void *dados) {
    NOFILA *novoNo = (NOFILA *) malloc(sizeof(NOFILA));
    novoNo->Dados = dados;
    novoNo->Prox = NULL;

    return novoNo;
}

// Função para verificar se a fila está vazia
int FilaVazia(FILAGENERICA *fila) {
    return fila->cabeca == NULL;
}

//adiciona na fila generica 
void AdicionaAFila(FILAGENERICA *fila, void *dados) {
  
    NOFILA *novoNo = CriarNoFila(dados);
    if (FilaVazia(fila)) {
        fila->cabeca = fila->cauda = novoNo;
        fila->tamanho++;
        return;
    }
    fila->cauda->Prox = novoNo;
    fila->cauda = novoNo;
    fila->tamanho++;
}

//retira elemento da fila generica 
void *RetirarDaFilaInicio(FILAGENERICA *fila, void (*f)(void *)) {
    if (FilaVazia(fila)) {
        return NULL;
    }
    NOFILA *temp = fila->cabeca;
    void *dados = temp->Dados;
    fila->cabeca = fila->cabeca->Prox;
    if (fila->cabeca == NULL) {
        fila->cauda = NULL;
    }
    free(temp->Prox);
    free(temp);
    fila->tamanho--;
    return dados;
}

/*void *RetirarDaFila(FILAGENERICA *fila, int (comp)(void *, void *), NOFILA *noRemover) {
    if (FilaVazia(fila) || noRemover==NULL) {
        printf("Fila Vazia\n");
        return NULL;
    }
    void *dados;
    NOFILA *temp = fila->cabeca;
    NOFILA *seguinte = temp->Prox;

    // Procurar o nó a ser removido
    while (temp != NULL && comp(seguinte->Dados,noRemover->Dados) !=0) {
        if (comp(seguinte->Dados,noRemover)==0) {
            dados = seguinte->Dados;
            free(temp->Prox);
            free(temp);
            fila->tamanho--;
        }
       temp = seguinte;
    }
    if (fila->cabeca == NULL) {
        fila->cauda = NULL;
    }
    void *dados = temp->Dados;
    return dados;
}

void removerNoLG(ListaGenerica* lg, NOG* noRemover) {
    if (lg->Inicio == NULL || noRemover == NULL) {
        return; // Lista vazia ou nó inválido
    }

    // Caso especial: o nó a ser removido é o primeiro da lista
    if (lg->Inicio == noRemover) {
        lg->Inicio = noRemover->Prox;
        free(noRemover);
        lg->NEL--;
        return;
    }

    // Procurar o nó seguinte ao nó a ser removido
    NOG* seguinte = lg->Inicio;
    while (seguinte != NULL && seguinte->Prox != noRemover) {
        seguinte = seguinte->Prox;
    }

    // Se não encontrarmos o nó seguinte, o nó a ser removido não está presente na lista
    if (seguinte == NULL) {
        return;
    }

    // reconectar os nos
    seguinte->Prox = noRemover->Prox;
    free(noRemover);
    lg->NEL--;
    
}*/

void DestruirFila(FILAGENERICA *fila, void (*f)(void *)){
    if (FilaVazia(fila)) {
        return NULL;
    }
    NOFILA *temp = fila->cabeca;
    NOFILA *prox;
    while (temp) {
        prox = temp->Prox;
        fdest(temp->Dados);
        free(temp);
        temp = prox;
    }
}

void MostrarFila(FILAGENERICA *Fila, void (*f)(void *)){
    if(!Fila || !Fila->cabeca) return;
    NOFILA *p = (NOFILA *)Fila->cabeca;
    while(p){
        f(p->Dados);
        p=p->Prox;
    }
}

// Verifica qual o tempo que a compra do cliente vai demorar
float calcularTempoTotalCompra(FILAGENERICA* fila) {
    float tempoTotal = 0.0;
    NOFILA* atual = fila->cabeca;

    while (atual != NULL) {
        CLIENTEASCOMPRAS* clienteCompras = (CLIENTEASCOMPRAS*)atual->Dados;
        ListaGenerica* listaProdutos = clienteCompras->ProdutosClientes;

        NOG* atualLista = listaProdutos->Inicio;

        while (atualLista != NULL) {
            PRODUTOCLIENTE* produtoCliente = (PRODUTOCLIENTE*)atualLista->Info;

            PRODUTO* produto = produtoCliente->produtoCL;
            tempoTotal += produto->tempoCompra;

            atualLista = atualLista->Prox;
        }

        atual = atual->Prox;
    }
    
    return tempoTotal;
}

//Coloca os clientes compras na fila 
void adicionarClienteComprasFila(CAIXA* caixaAtual, CLIENTEASCOMPRAS* cesto) {
    FILAGENERICA* fila = (FILAGENERICA *) caixaAtual->filaCaixa;
    AdicionaAFila(fila, cesto);
    caixaAtual->tempoEsperaReal = calcularTempoTotalCompra(fila);
    printf("Adicionei cliente na fila\n");
}