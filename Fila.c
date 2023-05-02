#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "ListaGenerica.h"
#include "Fila.h"

// //cria fila generica
// FILAGENERICA *CriarFila() {
//     FILAGENERICA *q = (FILAGENERICA *) malloc(sizeof(FILAGENERICA));
//     q->cabeca = q->cauda = NULL;
//     return q;
// }

// // Função para criar um novo nó para a fila passando apenas os dados
// NOFILA *CriarNoFila(void *dados) {
//     NOFILA *novoNo = (NOFILA *) malloc(sizeof(NOFILA));
//     novoNo->Dados = dados;
//     novoNo->Prox = NULL;
//     return novoNo;
// }

// // Função para verificar se a fila está vazia
// int FilaVazia(FILAGENERICA *q) {
//     return q->cabeca == NULL;
// }

// //adiciona na fila generica 
// void AdicionaAFila(FILAGENERICA *q, void *dados) {
//     NOFILA *novoNo = CriarNoFila(dados);
//     if (isEmpty(q)) {
//         q->cabeca = q->cauda = novoNo;
//         return;
//     }
//     q->cauda->Prox = novoNo;
//     q->cauda = novoNo;
// }

// //retira elemento da fila generica 
// void *RetirarDaFila(FILAGENERICA *q) {
//     if (isEmpty(q)) {
//         return NULL;
//     }
//     NOFILA *temp = q->cabeca;
//     void *dados = temp->Dados;
//     q->cabeca = q->cabeca->Prox;
//     if (q->cabeca == NULL) {
//         q->cauda = NULL;
//     }
//     free(temp);
//     return dados;
// }