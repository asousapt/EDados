#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ListaGenerica.h"


typedef struct {
    void *Dados;
    struct NOFILA *Prox;
} NOFILA;

typedef struct Filagenerica {
    NOFILA *cabeca;
    NOFILA *cauda;
} FILAGENERICA;

typedef struct compras {
    CLIENTE* ClienteActual
    ListaGenerica * ListaCompras; 
} FILACOMPRAS;

// FILAESPERA *CriarFila(){
//   FILAESPERA *NovaFila = (FILAESPERA *) malloc(sizeof(struct FILAESPERA));
//   if (!NovaFila) return NULL;
//   NovaFila->Cabeca = NovaFila->Cauda = NULL;
//   NovaFila->NElementos = 0;
//   return NovaFila;
// }

// //5. Escreva uma função que liste todas as viaturas em espera, mostrando os seus dados.
// void ListarViaturas(FILA *Fila){
//   printf("\n %s", __FUNCTION__);
//   if(!Fila || !Fila->Cabeca) return;
//   ELEMENTO *p = Fila->Cabeca;
//   while(p){
//     MostrarViatura(p->Dados);
//     p=p->Seg;
//   }
// }

// //6. Escreva uma função que calcule o tempo de lavagem da viatura em segundos.
// int TempoLavagem (time_t Inicio, time_t Fim){
//   return (int)difftime(Fim, Inicio);
// }
// //7. Escreva uma função que permita saber quantas viaturas estão ainda à espera da lavagem.
// int TotalViaturas(FILA *Fila){
//   if(!Fila || !Fila->Cabeca) return 0;
//   ELEMENTO *p = Fila->Cabeca;
//   int contador = 0;
//   while(p){
//     contador++;
//     p=p->Seg;
//   }
//   return contador;
// }

// //8. Escreva uma função que permita inserir uma viatura na fila de espera.
// void InserirViatura(FILA *Fila, VIATURA *Viatura){
//   if(!Fila || !Viatura) return;
// // criação do elemento para guardar a nova viatura
// ELEMENTO *NovoE = (ELEMENTO*)malloc(sizeof(ELEMENTO));
// NovoE->Dados=Viatura;
// NovoE->Seg=NULL;
  
//   if(!Fila->Cabeca){    // caso especifico Fila vazia
//    Fila->Cabeca = NovoE;
//    Fila->Cauda = NovoE;
//   }
//   else{                 // tem pelo menos um elemento
//     (Fila->Cauda)->Seg = NovoE;
//     Fila->Cauda = NovoE;    // atualizar a cauda para o "novo" ultimo elemento
//   }
//   Fila->NElementos++;
// }

// // 9. Escreva uma função que permita retirar uma viatura da fila de espera, mas que antes preencha o tempo de saída e calcule o tempo de lavagem para mostrar ao utilizador.

// ELEMENTO* RemoverViatura(FILA *Fila){
//   if(!Fila || !Fila->Cabeca) return NULL;
//   ELEMENTO *Ret;
//   Ret=Fila->Cabeca;
//   if(Fila->Cabeca==Fila->Cauda){//Só tem 1 Elemento
//     Fila->Cabeca = Fila->Cauda = NULL;
//   }
//   else{
//     Fila->Cabeca=(Fila->Cabeca)->Seg; // A cabeça passa a ser o segundo elemento
//   }
//   Fila->NElementos--;

//   // especifica ao problema
//   Ret->Dados->TempoSaida = time(NULL);
//   Ret->Dados->TempoLavagem = TempoLavagem (Ret->Dados->TempoEntrada, Ret->Dados->TempoSaida);
//   return Ret;
// }

#endif // FILA_H_INCLUDED
