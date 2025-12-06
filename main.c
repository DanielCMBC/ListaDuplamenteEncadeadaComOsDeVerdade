#include "ldec.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#define PAUSA(ms) Sleep(ms)
#else
#include <unistd.h>
#define PAUSA(ms) usleep(ms * 1000)
#endif

void menu() {
    printf("\n========= MENU =========\n");
    printf("1 - Inserir núcleo no início\n");
    printf("2 - Inserir núcleo no final\n");
    printf("3 - Mostrar lista circular\n");
    printf("4 - Criar conexão entre dois núcleos\n");
    printf("5 - Mostrar grafo (matriz de adjacência)\n");
    printf("6 - BFS a partir de um núcleo\n");
    printf("7 - DFS a partir de um núcleo\n");
    printf("8 - Verificar se dois núcleos estão conectados\n");
    printf("9 - Executar simulador de CPU (original)\n");
    printf("0 - Sair\n");
    printf("========================\n");
    printf("Escolha: ");
}

void simuladorCPU() {
    if (head == NULL) {
        printf("Nao ha nucleos para simular.\n");
        return;
    }

    int num_nucleos = 0;
    No* temp = head;
    do {
        num_nucleos++;
        temp = temp->prox;
    } while (temp != head);

    srand(time(NULL));

    printf("\n--- Simulador de CPU ---\n");
    printf("--- Sistema inicializado com %d nucleos ---\n", num_nucleos);
    mostrar();

    int nucleo_alvo = rand() % num_nucleos;
    printf("\n*** Tarefa especial designada para a thread %d\n\n", nucleo_alvo);
    PAUSA(2000);

    No* thread_atual = head;
    int executando = 1;

    while(executando) {
        printf("\nThread escalonada para tarefa: %d\n", thread_atual->n);

        int tempo_tarefa = rand() % 3000 + 1000;
        printf(">>> Tarefa por %d ms...\n", tempo_tarefa);
        PAUSA(tempo_tarefa);

        if (thread_atual->n == nucleo_alvo) {
            printf(">>> Núcleo %d executou a operação especial! <<<\n", thread_atual->n);
            executando = 0;
        } else {
            printf(">>> Thread %d em espera...\n", thread_atual->n);
            thread_atual = thread_atual->prox;
        }
    }

    printf("\n--- Simulação Finalizada ---\n");
}

int main() {
    inicializarGrafo(&grafo);

    int opcao;
    int a, b, valor;

    // Inicializar com 4 núcleos como antes
    for (int i = 0; i < 4; i++)
        inserir_final(i);

    do {
        menu();
        scanf("%d", &opcao);

        switch(opcao) {

            case 1:
                printf("Digite o ID do núcleo: ");
                scanf("%d", &valor);
                inserir_No_Inicio(valor);
                break;

            case 2:
                printf("Digite o ID do núcleo: ");
                scanf("%d", &valor);
                inserir_final(valor);
                break;

            case 3:
                mostrar();
                break;

            case 4:
                printf("Criar conexao (aresta)\nID 1: ");
                scanf("%d", &a);
                printf("ID 2: ");
                scanf("%d", &b);
                adicionarAresta(&grafo, a, b);
                break;

            case 5:
                mostrarGrafo(&grafo);
                break;

            case 6:
                printf("BFS a partir de qual núcleo? ");
                scanf("%d", &a);
                BFS(&grafo, a);
                break;

            case 7:
                printf("DFS a partir de qual núcleo? ");
                scanf("%d", &a);
                DFS(&grafo, a);
                break;

            case 8:
                printf("Verificar conexao entre:\nID 1: ");
                scanf("%d", &a);
                printf("ID 2: ");
                scanf("%d", &b);

                if (conectados(&grafo, a, b))
                    printf("Núcleos %d e %d ESTÃO conectados!\n", a, b);
                else
                    printf("Núcleos %d e %d NÃO estão conectados.\n", a, b);
                break;

            case 9:
                simuladorCPU();
                break;

            case 0:
                printf("Encerrando programa...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 0);

    // Limpeza da lista circular
    printf("\nLimpando memória...\n");
    while (head != NULL) {
        deletar_Elemento_porTecla(head->n);
    }

    return 0;
}
