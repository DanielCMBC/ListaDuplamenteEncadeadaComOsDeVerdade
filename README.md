# Simulação de Processador com Lista Duplamente Encadeada Circular

**1. Introdução:**

O presente projeto implementa, em linguagem C, uma simulação de um processador que utiliza uma lista duplamente encadeada circular para representar núcleos de execução (threads).
Cada nó da lista representa um núcleo da CPU e o programa realiza o escalonamento cíclico até que um dos núcleos execute uma “tarefa especial”.

Este tipo de estrutura de dados é amplamente utilizado em sistemas reais, como escalonadores de processos e gerenciamento de recursos em sistemas operacionais, devido à sua natureza circular, que permite percorrer os elementos de forma contínua e eficiente.

**2. Estrutura do Projeto:**

O projeto é composto por três arquivos principais:

- main.c	Controla a simulação e o comportamento geral do processador.
- ldec.h	Declara a estrutura do nó e as funções da lista circular.
- ldec.c	Implementa as funções de criação, inserção, remoção e exibição dos nós.

**3. Estrutura de Dados: Lista Duplamente Encadeada Circular:**

A estrutura básica do nó está definida em ldec.h:

typedef struct No {
    int n;
    struct No *prox;
    struct No *ant;
} No;

extern No *head;

Descrição:

- n: identifica o número do núcleo (thread);

- prox: ponteiro para o próximo nó da lista;

- ant: ponteiro para o nó anterior;

- head: ponteiro global que aponta para o início da lista.

O fato de a lista ser circular significa que o último nó aponta de volta para o primeiro (head), e o primeiro aponta para o último — permitindo percorrer a lista indefinidamente sem chegar a NULL.

**4. Implementação das Funções:**

**4.1. Criação de um Nó:**

No* criar_No(int n) {
    No* novoNo = (No*) malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Alocação de memória falhou!\n");
        exit(1);
    }
    novoNo->n = n;
    novoNo->prox = NULL;
    novoNo->ant = NULL;
    return novoNo;
}


- Essa função aloca dinamicamente memória para um novo nó e inicializa seus ponteiros.
O controle de erro evita travamentos caso a alocação falhe.

**4.2: Inserção no Início da Lista:**

void inserir_No_Inicio(int n) {
    No* novoNo = criar_No(n);
    if (head == NULL) {
        head = novoNo;
        head->prox = head;
        head->ant = head;
    } else {
        No* ultimo = head->ant;
        novoNo->prox = head;
        novoNo->ant = ultimo;
        head->ant = novoNo;
        ultimo->prox = novoNo;
        head = novoNo;
    }
    printf("%d inserido no início!\n", n);
}


*Explicação:*

- Caso a lista esteja vazia, o nó é inicializado apontando para si mesmo.

- Caso contrário, o novo nó é conectado entre o último e o primeiro elementos.

**4.3. Inserção no Final da Lista:**

void inserir_final(int n) {
    No* novoNo = criar_No(n);
    if (head == NULL) {
        head = novoNo;
        head->prox = head;
        head->ant = head;
    } else {
        No* ultimo = head->ant;
        novoNo->prox = head;
        novoNo->ant = ultimo;
        ultimo->prox = novoNo;
        head->ant = novoNo;
    }
    printf("Inserido %d no final\n", n);
}


- Essa função é amplamente utilizada no main.c para criar os núcleos iniciais.

**4.4. Exclusão de um Nó Específico:**

void deletar_Elemento_porTecla(int key) {
    if (head == NULL) {
        printf("A lista está vazia! Nada para deletar.\n");
        return;
    }

    No* curr = head;
    while (curr->n != key) {
        curr = curr->prox;
        if (curr == head) {
            printf("Nó com valor %d não encontrado.\n", key);
            return;
        }
    }

    if (curr->prox == head && curr->ant == head) {
        head = NULL;
        free(curr);
        printf("Elemento %d deletado.\n", key);
        return;
    }

    if (curr == head) {
        No* ultimo = head->ant;
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


*Explicação:*

- A função percorre a lista até encontrar o nó com valor igual a key, ajusta os ponteiros vizinhos e libera a memória.
Se o nó for o único da lista, a cabeça é definida como NULL.

4.5. Exibição dos Nós:

void mostrar() {
    if (head == NULL) {
        printf("Lista está vazia!\n");
        return;
    }

    No* current = head;
    printf("\n--- Lista Duplamente Encadeada Circular ---\n");
    do {
        printf("%d <-> ", current->n);
        current = current->prox;
    } while (current != head);
    printf("(Volta ao HEAD %d)\n", head->n);
}


- Essa função percorre toda a lista e exibe os elementos de forma contínua, mostrando o retorno ao início.

**5. Simulação no main.c:**

**5.1. Criação e Exibição dos Núcleos:**

int num_nucleos = 4;
for (int i = 0; i < num_nucleos; i++){
    inserir_final(i);
}
mostrar();

O 'int num_nucleos' representa a quantidade de nucleos que estaram participando da simulação.

*Saída esperada:*

--- Lista Duplamente Encadeada Circular ---
0 <-> 1 <-> 2 <-> 3 <-> (Volta ao HEAD 0)

(Representação de uma Lista Duplamente Encadeada Circular)

5.2. Escalonamento de Threads:

O código sorteia um núcleo que deve executar uma tarefa especial e percorre a lista até encontrá-lo:

int nucleo_alvo = rand() % num_nucleos;
printf("\n*** Tarefa especial designada para a thread %d ***\n", nucleo_alvo);

No* thread_atual = head;
int executando = 1;

while (executando) {
    printf("Thread escalonada para tarefa\n");
    PAUSA(500);

    if (thread_atual->n == nucleo_alvo) {
        printf(">>> Núcleo %d encontrou e executou a operação! <<<\n", thread_atual->n);
        executando = 0;
    } else {
        printf(">>> Thread %d em espera <<<\n", thread_atual->n);
        thread_atual = thread_atual->prox;
    }
}

*Exemplo de saída simulada:*

Thread Escalonado para Tarefa 0
>>>Thread 0 em espera<<<
Thread Escalonado para Tarefa 1
>>>Thread 1 em espera<<<
Thread Escalonado para Tarefa 2
>>>Nucleo 2 encontrou e executou a operacao! <<<

A  Operação pecorreu os núcleos até chegar no núcleo que foi selecionado para executar a operação

**6. Conclusão:**

O código apresentado demonstra de forma eficiente o uso de listas duplamente encadeadas circulares para simular o comportamento de um escalonador de CPU.
A estrutura circular permite que o sistema percorra infinitamente os núcleos, simulando o comportamento de round-robin scheduling usado em sistemas operacionais reais.

Conceitos reforçados:

- Manipulação de ponteiros;

- Estruturas dinâmicas (malloc/free);

- Controle de fluxo e travessia circular;

- Simulação de escalonamento de tarefas.

**7. Resultados e Análise da Execução:**

Após a compilação e execução do programa, a seguinte saída foi obtida:

inserido 0 no final
inserido 1 no final
inserido 2 no final
inserido 3 no final
--- Simulado de CPU ---
--- Sistema inicializado com 4 nucleos ---

--- Lista Duplamente Encadeada Circular ---
0 <-> 1 <-> 2 <-> 3 <-> (Volta ao HEAD 0)

***Tarefa especial designada para a thread 2

Thread Escalonado para Tarefa 0
>>>Thread 0 em espera<<<
Thread Escalonado para Tarefa 1
>>>Thread 1 em espera<<<
Thread Escalonado para Tarefa 2
>>>Nucleo 2 encontrou e executou a operacao! <<<

--- Simulação Finalizada ---
Desalocando todos os núcleos...
Elemento 0 deletado.
Elemento 1 deletado.
Elemento 2 deletado.
Elemento 3 deletado.
Lista esta vazia!

*Análise detalhada:*

*Inicialização da lista:*

- Quatro nós (0, 1, 2 e 3) foram criados e conectados corretamente.

A exibição confirma que o último elemento aponta de volta para o HEAD 0, validando o comportamento circular.

*Designação da tarefa:*

- O núcleo sorteado foi o nº 2.

Isso demonstra o uso da função rand() para gerar tarefas dinâmicas, simulando a distribuição aleatória de processos pelo sistema.

*Escalonamento:*

- A simulação percorreu os nós na sequência circular: 0 → 1 → 2.

Ao alcançar o nó 2, o sistema interrompeu o ciclo, simbolizando que o núcleo 2 executou com sucesso sua operação.

*Finalização:*

- Todos os nós foram desalocados em sequência, garantindo que não há vazamento de memória.

A mensagem "Lista esta vazia!" confirma o sucesso da limpeza.

*8. Compilação e Execução do Código.*

Para compilar o projeto, é necessário ter um compilador C instalado (como GCC).
Os três arquivos — main.c, ldec.c e ldec.h — devem estar na mesma pasta.

- Passos para Compilação (no terminal):

No terminal do codespaces:

gcc main.c ldec.c -o simulador

E execute com:

./simulador
