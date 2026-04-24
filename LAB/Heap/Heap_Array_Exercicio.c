#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HEAP_SIZE 20

typedef struct {
    int id;
    char descricao[100];
    int prioridade;
} Chamado;

typedef struct {
    Chamado data[MAX_HEAP_SIZE];
    int size;
} HeapMax;

// Índices
int parent(int i) { return (i - 1) / 2; }
int left_child(int i) { return (2 * i + 1); }
int right_child(int i) { return (2 * i + 2); }

// Troca
void swap(Chamado *a, Chamado *b) {
    Chamado temp = *a;
    *a = *b;
    *b = temp;
}

// Subir
void heapify_up(HeapMax *heap, int index) {
    while (index > 0 &&
           heap->data[index].prioridade > heap->data[parent(index)].prioridade) {

        swap(&heap->data[index], &heap->data[parent(index)]);
        index = parent(index);
    }
}

// Descer
void heapify_down(HeapMax *heap, int index) {
    int largest = index;
    int left = left_child(index);
    int right = right_child(index);

    if (left < heap->size &&
        heap->data[left].prioridade > heap->data[largest].prioridade) {
        largest = left;
    }

    if (right < heap->size &&
        heap->data[right].prioridade > heap->data[largest].prioridade) {
        largest = right;
    }

    if (largest != index) {
        swap(&heap->data[index], &heap->data[largest]);
        heapify_down(heap, largest);
    }
}

// Inicializar
void init_heap(HeapMax *heap) {
    heap->size = 0;
}

// Inserir chamado
void heap_insert(HeapMax *heap, Chamado c) {
    if (heap->size == MAX_HEAP_SIZE) {
        printf("Erro: Heap cheio!\n");
        return;
    }

    int index = heap->size;
    heap->data[index] = c;
    heap->size++;

    heapify_up(heap, index);

    printf("Chamado inserido com sucesso.\n");
}

// Remover maior prioridade
Chamado heap_extract_max(HeapMax *heap) {
    Chamado vazio = {-1, "", -1};

    if (heap->size == 0) {
        printf("Erro: Heap vazio!\n");
        return vazio;
    }

    Chamado max = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;

    heapify_down(heap, 0);

    return max;
}

// Ver topo
Chamado heap_peek(HeapMax *heap) {
    Chamado vazio = {-1, "", -1};

    if (heap->size == 0) {
        printf("Heap vazio!\n");
        return vazio;
    }

    return heap->data[0];
}

// Listar heap
void print_heap(HeapMax *heap) {
    if (heap->size == 0) {
        printf("Heap vazio!\n");
        return;
    }

    printf("\n--- Chamados ---\n");
    for (int i = 0; i < heap->size; i++) {
        printf("ID: %d | Prioridade: %d | Descricao: %s\n",
               heap->data[i].id,
               heap->data[i].prioridade,
               heap->data[i].descricao);
    }
}

// Menu principal
int main() {
    HeapMax heap;
    init_heap(&heap);

    int opcao;

    do {
        printf("\n1 - Inserir chamado\n");
        printf("2 - Atender chamado mais prioritario\n");
        printf("3 - Exibir proximo chamado\n");
        printf("4 - Listar heap\n");
        printf("5 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            Chamado c;

            printf("ID: ");
            scanf("%d", &c.id);
            getchar();

            printf("Descricao: ");
            fgets(c.descricao, sizeof(c.descricao), stdin);
            c.descricao[strcspn(c.descricao, "\n")] = '\0';

            printf("Prioridade: ");
            scanf("%d", &c.prioridade);

            if (c.prioridade <= 0) {
                printf("Prioridade deve ser positiva!\n");
            } else {
                heap_insert(&heap, c);
            }

        } else if (opcao == 2) {
            Chamado c = heap_extract_max(&heap);
            if (c.id != -1) {
                printf("Chamado atendido: ID %d | Prioridade %d | %s\n",
                       c.id, c.prioridade, c.descricao);
            }

        } else if (opcao == 3) {
            Chamado c = heap_peek(&heap);
            if (c.id != -1) {
                printf("Proximo chamado: ID %d | Prioridade %d | %s\n",
                       c.id, c.prioridade, c.descricao);
            }

        } else if (opcao == 4) {
            print_heap(&heap);
        }

    } while (opcao != 5);

    printf("Encerrando...\n");
    return 0;
}