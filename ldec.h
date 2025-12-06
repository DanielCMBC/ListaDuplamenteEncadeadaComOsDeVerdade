#ifndef LDEC_H
#define LDEC_H

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #define LIMPAR_TELA "cls"
#else
    #define LIMPAR_TELA "clear"
#endif

typedef struct No{
    int n;
    struct No *prox;
    struct No *ant;
}No;

extern No *head;

No* criar_No(int n);
void inserir_No_Inicio(int n); 
void inserir_final(int n);     
void deletar_Elemento_porTecla(int key); 
void mostrar();

//Função do grafo:

#define MAX_NUCLEOS 100

typedef struct Grafo {
    int numVertices;
    int adj[MAX_NUCLEOS][MAX_NUCLEOS];  // 0 ou 1
} Grafo;

extern Grafo grafo;

void inicializarGrafo(Grafo *g);
void adicionarAresta(Grafo *g, int a, int b);
void BFS(Grafo *g, int start);
void DFS(Grafo *g, int start);
int conectados(Grafo *g, int a, int b);
void mostrarGrafo(Grafo *g);

#endif