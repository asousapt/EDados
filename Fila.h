

typedef struct NOFila{
    CLIENTE   *Info;
    struct NO *Prox;
} NOFILA;

typedef struct FilaEspera {
    NOFILA *Inicio;
    NOFILA *Fim;
    int NEL;
} FILAESPERA;

