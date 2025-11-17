#ifndef LDEC_H
#define LDEC_H

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <windows.h>
    #define PAUSA(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define PAUSA(ms) usleep(ms * 1000)
#endif

typedef struct No{
    int id;              
    int tempo_restante;
    struct No *prox;
    struct No *ant;
} No;

extern No *head;

// PROTÓTIPOS: Note que só pedimos "int n"
No* criar_No(int id);
void inserir_final(int id);     
void deletar_Elemento_porTecla(int key); 
void mostrar();

#endif
