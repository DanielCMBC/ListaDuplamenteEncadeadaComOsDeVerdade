#include "ldec.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Para sortear o número aleatório

// Inclui bibliotecas para a pausa (sleep)
#ifdef _WIN32
include <windows.h>
#define PAUSA(ms) Sleep(ms)
#else
#include <unistd.h>
#define PAUSA(ms) usleep(ms * 1000) // usleep é em microssegundos
#endif
int main(){
    srand(time(NULL));

    int num_nucleos = 4;
    for (int i = 0; i < num_nucleos; i++){
        inserir_final(i);
    }
    printf("--- Simulado de CPU ---\n");
    printf("--- Sistema inicializado com %d nucleos ---\n",num_nucleos);
    mostrar();

    //Sortear um Nucleo para Executar uma tarefa
    int nucleo_alvo = rand() % num_nucleos;
    printf("\n***Tarefa especial designada para a thread %d\n\n", nucleo_alvo);
    PAUSA(2000);
    
    //escalonador de Threads (Loop)

    No* thread_atual = head;
    int executando = 1;

    while(executando) {
        if(thread_atual == NULL){
            printf("Erro! Nenhhuma Thread Disponivel.\n");
        break;
        }
        printf("Thread Escalonado para Tarefa %d\n", thread_atual->n);
        PAUSA(500);

        //Verifica se o nucleo esta realizando uma operacao
        if(thread_atual-> n == nucleo_alvo) {
            printf(">>>Nucleo %d encontrou e executou a operacao! <<<\n",thread_atual->n);
            executando = 0;
        } else {
            printf(">>>Thread %d em espera<<<\n",thread_atual->n);
            thread_atual = thread_atual->prox;
        }
    }
    //Limpeza
    printf("\n--- Simulação Finalizada ---\n");
    printf("Desalocando todos os núcleos...\n");

    //Deletar TODOS os Nos (Um por Um)

    while (head != NULL) {
        deletar_Elemento_porTecla(head->n);
    }
    mostrar();
    return 0;
}