#include "ldec.h"

No* criar_No(int n) {
    No* novoNo = (No*) malloc(sizeof(No));
    if (novoNo == NULL){
        printf("'Alocacao de Memoria Falhou!/n");
    exit(1);
    }
    novoNo->n = n;
    novoNo->prox = NULL;
    novoNo ->ant = NULL;
    return novoNo;
}

int inserir_No_Inicio(int n){
    struct No* novoNo = criar_No(n);
    if (head == NULL) {
        head->prox = head;
        head->ant = head;
    } else {
        struct No* ultimo = head->ant;
        novoNo->prox =head;
        novoNo->ant=ultimo;
        head->ant = novoNo;
        ultimo->prox = novoNo;
        head = novoNo;
    }
    printf("%d inserir no inicio!", n);
}

int inserir_final(int n){
    struct No* novoNo = criar_No(n);
    if (head == NULL) {
        head = novoNo;
        head->prox = head;
        No* ultimo;
        ultimo->prox = novoNo;
        head->ant = novoNo; 
    }
    printf("inserir %d no final\n", n);
}

int deletar_Elemento_porTecla(int key) {
    if (head == NULL) {
        printf("A lista está vazia! Nada para deletar.\n");
        return;
    }

    No *curr = head;

    // Buscar o nó
    while (curr->n != key) {
        curr = curr->prox;
        if (curr == head) {
            printf("Nó com valor %d não encontrado.\n", key);
            return;
        }
    }

    // Caso: apenas um nó
    if (curr->prox == head && curr->ant == head) {
        head = NULL;
        free(curr);
        printf("Elemento %d deletado.\n", key);
        return;
    }

    // Caso: nó é o primeiro
    if (curr == head) {
        No *ultimo = head->ant;
        head = head->prox;
        head->ant = ultimo;
        ultimo->prox = head;
    } else {
        curr->ant->prox = curr->prox;
        curr->prox->ant = curr->ant;
    }

    free(curr);
    printf("Elemento %d deletado.\n", key);
}

void mostrar() {
    if(head == NULL) {
        printf("Lista esta vazia!\n");
    return;
    }

    struct No* current = head;
    printf("Lista Duplamente Encadeada Circular\n");
    printf("--- Simulacao de Nucleos de CPU ---\n");
    do {
        printf("%d <->\n", current->n);
        current = current->prox;
    }while(current != head);
    printf("(Head)\n");
}

