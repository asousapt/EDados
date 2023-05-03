#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "ListaGenerica.h"
#include "Fila.h"

//cria fila generica
FILAGENERICA *CriarFila() {
    FILAGENERICA *fila = (FILAGENERICA *) malloc(sizeof(FILAGENERICA));
    fila->cabeca = fila->cauda = NULL;
    fila->tamanho = 0;
    return fila;
}

// Função para criar um novo nó para a fila passando apenas os dados
// NOFILA *CriarNoFila(void *dados) {
//     NOFILA *novoNo = (NOFILA *) malloc(sizeof(NOFILA));
//     novoNo->Dados = dados;
//     novoNo->Prox = NULL;
//     return novoNo;
// }

// // Função para verificar se a fila está vazia
// int FilaVazia(FILAGENERICA *fila) {
//     return fila->cabeca == NULL;
// }

// //adiciona na fila generica 
// void AdicionaAFila(FILAGENERICA *fila, void *dados) {
//     NOFILA *novoNo = CriarNoFila(dados);
//     if (isEmpty(fila)) {
//         fila->cabeca = fila->cauda = novoNo;
//         return;
//     }
//     fila->cauda->Prox = novoNo;
//     fila->cauda = novoNo;
// }

// //retira elemento da fila generica 
// void *RetirarDaFila(FILAGENERICA *fila) {
//     if (isEmpty(fila)) {
//         return NULL;
//     }
//     NOFILA *temp = fila->cabeca;
//     void *dados = temp->Dados;
//     fila->cabeca = fila->cabeca->Prox;
//     if (fila->cabeca == NULL) {
//         fila->cauda = NULL;
//     }
//     free(temp);
//     return dados;
// }