#include "ldec.h"

No *head = NULL;

No* criar_No(int id) {
    No* novoNo = (No*) malloc(sizeof(No));
    if (novoNo == NULL){
        printf("Erro de memoria!\n");
        exit(1);
    }
    novoNo->id = id;
    
    // Intervalo de tempo dado para executar uma tarefa
    novoNo->tempo_restante = (rand() % 4000) + 2000; 
    
    novoNo->prox = NULL;
    novoNo->ant = NULL;
    return novoNo;
}

void inserir_No_Inicio(int id, int tempo){
    struct No* novoNo = criar_No(id);
    if (head == NULL) {
        head = novoNo;
        head->prox = head;
        head->ant = head;
    } else {
        struct No* ultimo = head->ant;
        novoNo->prox = head;
        novoNo->ant = ultimo;
        head->ant = novoNo;
        ultimo->prox = novoNo;
    head = novoNo;
    }
    printf("Processo [ID: %d] criado (Duracao: %dms)\n", id, tempo);
}

void inserir_final(int id, int tempo){
    struct No* novoNo = criar_No(id);
    if (head == NULL) {
        head = novoNo;
        head->prox = head;
        head->ant = head; 
    } else {
        struct No* ultimo = head->ant;
        novoNo->prox = head;
        novoNo->ant = ultimo;
        ultimo->prox = novoNo;
        head->ant = novoNo;
    }
    printf("Processo [ID: %d] criado (Duracao: %dms)\n", id, tempo);
}

void deletar_Elemento_porID(int key) {
    if (head == NULL) return;

    No *curr = head;

    do {
        if(curr->id==key) break;
        curr= curr -> prox;
    } while (curr != head);

    if(curr->id!=key) {
        printf("ID %d nao encontrado.\n", key);
    }

    // Se for o único elemento
    if (curr->prox == curr) {
        head = NULL;
        free(curr);
        return;
    }

    // Se for o head, move o head para frente antes de apagar
    if (curr == head) {
        head = head->prox;
    }

    // Ajusta os ponteiros
    curr->ant->prox = curr->prox;
    curr->prox->ant = curr->ant;

    free(curr);
}
void mostrar() {
    if(head == NULL) {
        printf("Todos os processos finalizados! Lista vazia.\n");
        return;
    }

    struct No* current = head;
    printf("\n--- Fila de Processos ---\n");
    do {
        printf("[P%d | %dms] <-> ", current->id, current->tempo_restante);
        current = current->prox;
    } while(current != head);
    printf("(Volta)\n");
}
