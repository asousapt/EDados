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
void *RetirarDaFilaInicio(FILAGENERICA *fila) {
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

void *RetirarDaFila(FILAGENERICA *fila, int (comp)(void *, void *), void *dadosRemover) {
    void *dados;
    NOFILA *temp = fila->cabeca;
    if (FilaVazia(fila) || dadosRemover==NULL) {
        printf("Fila Vazia\n");
        return NULL;
    }
    
    NOFILA *seguinte = temp->Prox;

    // Caso especial: o nó a ser removido é o primeiro da lista
    if (comp(temp->Dados,dadosRemover)==0) {
        fila->cabeca = seguinte;
        dados = temp->Dados;
        free(temp);
        fila->tamanho--;
        return dados;
    }

    // Procurar o nó a ser removido
    while (!temp && comp(seguinte->Dados,dadosRemover) !=0) {
        temp = temp->Prox;
        seguinte = temp->Prox;
    }
    if (fila->cabeca == NULL) {
        fila->cauda = NULL;
    }
    dados = seguinte->Dados;
    temp->Prox = seguinte->Prox;
    free(seguinte);
    fila->tamanho--;
    return dados;
}

void DestruirFila(FILAGENERICA *fila, void (*f)(void *)){
    if (FilaVazia(fila)) {
        return NULL;
    }
    NOFILA *temp = fila->cabeca;
    NOFILA *prox;
    while (temp) {
        prox = temp->Prox;
        f(temp->Dados);
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
