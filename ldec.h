#include <stdio.h>
#include <stdlib.h>

#ifdef  _WIN32
    #define LIMPAR_TELA "cls"
#else
    #define LIMPAR_TELA "clear"
#endif

typedef struct No{
    int n;
    struct No *prox;
    struct No *ant;
}No;

extern No *head = NULL;