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
    printf("1 - Gerar automaticamente N núcleos (1 até N)\n");
    printf("2 - Mostrar lista circular\n");
    printf("3 - Criar automaticamente conexões aleatórias\n");
    printf("4 - Mostrar grafo (matriz de adjacência)\n");
    printf("5 - BFS a partir de um núcleo\n");
    printf("6 - DFS a partir de um núcleo\n");
    printf("7 - Verificar se dois núcleos estão conectados\n");
    printf("8 - Executar simulador de CPU (original)\n");
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

    int nucleo_alvo = (rand() % num_nucleos) + 1;
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

    do {
        menu();
        scanf("%d", &opcao);

        switch(opcao) {

            case 1: { // Gerar automaticamente N núcleos
                printf("Digite quantos núcleos deseja criar: ");
                scanf("%d", &valor);

                if (valor <= 0) {
                    printf("Valor invalido!\n");
                    break;
                }

                // Limpa lista anterior
                while (head != NULL)
                    deletar_Elemento_porTecla(head->n);

                // Cria núcleos de 1 até N
                for (int i = 1; i <= valor; i++)
                    inserir_final(i);

                printf("Foram criados %d nucleos (1 ate %d)\n", valor, valor);
                break;
            }

            case 2:
                mostrar();
                break;


            case 3: {

                int totalConexoes;
                printf("Quantas conexões aleatórias deseja criar? ");
                scanf("%d", &totalConexoes);

                if (head == NULL) {
                printf("Nao ha nucleos cadastrados!\n");
                break;
            }

            int num_nucleos = 0;
              No* tmp = head;
              do {
              num_nucleos++;
              tmp = tmp->prox;
            } while (tmp != head);

            printf("Gerando %d conexoes aleatórias...\n", totalConexoes);

             for (int i = 0; i < totalConexoes; i++) {
             int a, b;

            do {
            a = (rand() % num_nucleos) + 1;
            b = (rand() % num_nucleos) + 1;
            } while (a == b);  // evitar conexao de um nodo com ele mesmo

            printf("Criando aresta aleatória: %d <-> %d\n", a, b);
            adicionarAresta(&grafo, a, b);
         }

          printf("Conexões aleatórias criadas com sucesso!\n");
          break;
        }
    
            case 4:
                mostrarGrafo(&grafo);
                break;

            case 5:
                printf("BFS a partir de qual núcleo? ");
                scanf("%d", &a);
                BFS(&grafo, a);
                break;

            case 6:
                printf("DFS a partir de qual núcleo? ");
                scanf("%d", &a);
                DFS(&grafo, a);
                break;

            case 7:
                printf("Verificar conexao entre:\nID 1: ");
                scanf("%d", &a);
                printf("ID 2: ");
                scanf("%d", &b);

                if (conectados(&grafo, a, b))
                    printf("Núcleos %d e %d ESTÃO conectados!\n", a, b);
                else
                    printf("Núcleos %d e %d NÃO estão conectados.\n", a, b);
                break;

            case 8:
                simuladorCPU();
                break;

            case 0:
                printf("Encerrando programa...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 0);

    printf("\nLimpando memória...\n");
    while (head != NULL)
        deletar_Elemento_porTecla(head->n);

    return 0;
}
