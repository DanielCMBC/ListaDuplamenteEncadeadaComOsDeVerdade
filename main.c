#include "ldec.h"
#include <time.h>

#define QUANTUM 1500 // Tempo máximo por vez de nucleos da CPU

int main(){
    srand(time(NULL)); //Geracao de tempos diferentes para cada tarefa

    int num_nucleos = 4;
    
    printf("--- Criando Processos ---\n");
    for (int i = 1; i <= num_nucleos; i++){
        inserir_final(i);
    }

    printf("\n--- INICIANDO ROUND ROBIN (Quantum: %dms) ---\n", QUANTUM);
    PAUSA(2000);

    No* atual = head;
    
    while(head != NULL) {
        //Processamento
        printf("\nProcessando [P%d] (Resta: %dms)\n", atual->id, atual->tempo_restante);
        
        int tempo_gasto;
        
        if (atual->tempo_restante > QUANTUM) {
            tempo_gasto = QUANTUM;
            atual->tempo_restante -= QUANTUM;
            PAUSA(tempo_gasto); // Simulacao da execução da tarefa
            
            printf("   -> Interrompido! Falta %dms\n", atual->tempo_restante);
            atual = atual->prox;
        } else {
            tempo_gasto = atual->tempo_restante;
            atual->tempo_restante = 0;
            PAUSA(tempo_gasto);
            
            printf("   -> FINALIZADO!\n");
            No* prox_temp = atual->prox;
            deletar_Elemento_porID(atual->id);
            atual = prox_temp;
        }
     
        PAUSA(500); 
    }

    printf("\nTodos os processos finalizados.\n");
    return 0;
}
