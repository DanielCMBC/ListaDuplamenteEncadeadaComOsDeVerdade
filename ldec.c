#include "ldec.h"

No *head = NULL;
Grafo grafo;


/* verifica se já existe um nó com o mesmo ID */
static int existeNo(int id) {
    if (head == NULL) return 0;
    No *cur = head;
    do {
        if (cur->n == id) return 1;
        cur = cur->prox;
    } while (cur != head);
    return 0;
}

No* criar_No(int n) {
    No* novoNo = (No*) malloc(sizeof(No));
    if (novoNo == NULL){
        printf("Alocacao de Memoria Falhou!\n");
        exit(1);
    }
    novoNo->n = n;
    novoNo->prox = NULL;
    novoNo->ant = NULL;
    return novoNo;
}


/* garante que grafo.numVertices >= id+1; limpa linhas/colunas novas */
void registrarNovoVerticeNoGrafo(int id) {
    if (id < 0 || id >= MAX_NUCLEOS) {
        printf("ID %d fora do intervalo suportado (0..%d)\n", id, MAX_NUCLEOS-1);
        return;
    }
    if (grafo.numVertices <= id) {
        /* inicializa as novas linhas/colunas */
        for (int i = grafo.numVertices; i <= id; i++) {
            for (int j = 0; j < MAX_NUCLEOS; j++) {
                grafo.adj[i][j] = 0;
                grafo.adj[j][i] = 0;
            }
        }
        grafo.numVertices = id + 1;
    }
}

/* remove todas as arestas associadas ao vértice id (mantém numVertices como está) */
void removerVerticeNoGrafo(int id) {
    if (id < 0 || id >= MAX_NUCLEOS) return;
    for (int i = 0; i < MAX_NUCLEOS; i++) {
        grafo.adj[id][i] = 0;
        grafo.adj[i][id] = 0;
    }
    /* não reduzimos grafo.numVertices para evitar reindexação complexa */
}


void inserir_No_Inicio(int n){
    if (existeNo(n)) {
        printf("ID %d já existe — insercao ignorada.\n", n);
        return;
    }

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

    registrarNovoVerticeNoGrafo(n);
    printf("%d inserido no inicio!\n", n);
}

void inserir_final(int n){
    if (existeNo(n)) {
        printf("ID %d já existe — insercao ignorada.\n", n);
        return;
    }

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

    registrarNovoVerticeNoGrafo(n);
    printf("inserido %d no final\n", n);
}

void deletar_Elemento_porTecla(int key) {
    if (head == NULL) {
        printf("A lista está vazia! Nada para deletar.\n");
        return;
    }

    No *curr = head;
    int encontrado = 0;

    do {
        if (curr->n == key) { encontrado = 1; break; }
        curr = curr->prox;
    } while (curr != head);

    if (!encontrado) {
        printf("Nó com valor %d não encontrado.\n", key);
        return;
    }

    /* se for único elemento */
    if (curr->prox == curr && curr->ant == curr) {
        head = NULL;
        free(curr);
        removerVerticeNoGrafo(key);
        printf("Elemento %d deletado.\n", key);
        return;
    }

    /* se for head */
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
    removerVerticeNoGrafo(key);
    printf("Elemento %d deletado.\n", key);
}

void mostrar() {
    if(head == NULL) {
        printf("Lista esta vazia!\n");
        return;
    }

    No* current = head;
    printf("\n--- Lista Duplamente Encadeada Circular ---\n");
    do {
        printf("%d <-> ", current->n);
        current = current->prox;
    } while(current != head);
    printf("(Volta ao HEAD %d)\n", head->n);
}


void inicializarGrafo(Grafo *g) {
    g->numVertices = 0;
    for (int i = 0; i < MAX_NUCLEOS; i++)
        for (int j = 0; j < MAX_NUCLEOS; j++)
            g->adj[i][j] = 0;
}

void adicionarAresta(Grafo *g, int a, int b) {
    if (a < 0 || a >= MAX_NUCLEOS || b < 0 || b >= MAX_NUCLEOS) {
        printf("IDs fora do intervalo permitido (0..%d)\n", MAX_NUCLEOS-1);
        return;
    }

    /* Verifica se os nós realmente existem na lista circular */
    if (!existeNo(a) || !existeNo(b)) {
        printf("IDs invalidos: %d, %d — o nó deve existir na lista.\n", a, b);
        return;
    }

    /* garante que grafo tem capacidade para esses ids */
    registrarNovoVerticeNoGrafo(a);
    registrarNovoVerticeNoGrafo(b);

    g->adj[a][b] = 1;
    g->adj[b][a] = 1;
    printf("Conexao criada entre %d e %d\n", a, b);
}

void BFS(Grafo *g, int start) {
    if (start < 0 || start >= MAX_NUCLEOS) {
        printf("Núcleo invalido!\n");
        return;
    }
    if (!existeNo(start)) {
        printf("Núcleo %d não existe na lista de núcleos.\n", start);
        return;
    }

    int visited[MAX_NUCLEOS] = {0};
    int dist[MAX_NUCLEOS];
    int fila[MAX_NUCLEOS];
    int ini = 0, fim = 0;

    for (int i = 0; i < MAX_NUCLEOS; i++) dist[i] = -1;

    fila[fim++] = start;
    visited[start] = 1;
    dist[start] = 0;

    printf("\nBFS a partir do núcleo %d:\n", start);

    while (ini < fim) {
        int v = fila[ini++];
        if (existeNo(v))  /* só imprime vértices que existem na lista */
            printf("Núcleo %d (distância %d)\n", v, dist[v]);

        for (int i = 0; i < MAX_NUCLEOS; i++) {
            if (g->adj[v][i] && !visited[i]) {
                if (!existeNo(i)) continue; /* pular vértices que não existem fisicamente */
                visited[i] = 1;
                dist[i] = dist[v] + 1;
                fila[fim++] = i;
            }
        }
    }
}

void DFS_visit(Grafo *g, int v, int *visited) {
    visited[v] = 1;
    if (existeNo(v)) printf(" %d", v);

    for (int i = 0; i < MAX_NUCLEOS; i++) {
        if (g->adj[v][i] && !visited[i]) {
            if (!existeNo(i)) continue;
            DFS_visit(g, i, visited);
        }
    }
}

void DFS(Grafo *g, int start) {
    if (start < 0 || start >= MAX_NUCLEOS) {
        printf("Núcleo invalido!\n");
        return;
    }
    if (!existeNo(start)) {
        printf("Núcleo %d não existe na lista de núcleos.\n", start);
        return;
    }

    int visited[MAX_NUCLEOS] = {0};
    printf("\nDFS a partir do núcleo %d:\n", start);
    DFS_visit(g, start, visited);
    printf("\n");
}

int conectados(Grafo *g, int a, int b) {
    if (a < 0 || b < 0 || a >= MAX_NUCLEOS || b >= MAX_NUCLEOS)
        return 0;
    if (!existeNo(a) || !existeNo(b)) return 0;

    int visited[MAX_NUCLEOS] = {0};
    int fila[MAX_NUCLEOS], ini = 0, fim = 0;

    fila[fim++] = a;
    visited[a] = 1;

    while (ini < fim) {
        int v = fila[ini++];

        if (v == b) return 1;

        for (int i = 0; i < MAX_NUCLEOS; i++) {
            if (g->adj[v][i] && !visited[i]) {
                if (!existeNo(i)) continue;
                visited[i] = 1;
                fila[fim++] = i;
            }
        }
    }
    return 0;
}

void mostrarGrafo(Grafo *g) {
    printf("\n--- Matriz de adjacência (somente IDs existentes) ---\n");
    /* determinar max id para imprimir (opcional: imprimir até MAX_NUCLEOS-1) */
    int maxPrint = grafo.numVertices;
    if (maxPrint < 1) maxPrint = 1;
    if (maxPrint > MAX_NUCLEOS) maxPrint = MAX_NUCLEOS;

    for (int i = 0; i < maxPrint; i++) {
        if (!existeNo(i)) continue;
        for (int j = 0; j < maxPrint; j++) {
            if (!existeNo(j)) continue;
            printf("%d ", g->adj[i][j]);
        }
        printf("\n");
    }
}
