
#include "structs.c"

ListaGenerica * CriarLG();
void DestruirLG(ListaGenerica *lg, void (*fdest)(void *));
void ShowLG(ListaGenerica *lg, void (*f)(void *));
void AddBeginLG(ListaGenerica *lg, void *X);
int PertenceLG(ListaGenerica *lg, void *X, int (*fcomp)(void *, void *));