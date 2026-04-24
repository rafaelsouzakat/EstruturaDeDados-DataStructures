#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

typedef struct {
    int id;
    char descricao[100];
    int prioridade;
} Chamado;

typedef struct {
    Chamado itens[MAX];
    int tamanho;
} Heap;

// Função para trocar dois elementos
void trocar(Chamado *a, Chamado *b) {
    Chamado temp = *a;
    *a = *b;
    *b = temp;
}

// Subir elemento (heapify up)
void subir(Heap *h, int i) {
    int pai = (i - 1) / 2;

    if (i > 0 && h->itens[i].prioridade > h->itens[pai].prioridade) {
        trocar(&h->itens[i], &h->itens[pai]);
        subir(h, pai);
    }
}

// Descer elemento (heapify down)
void descer(Heap *h, int i) {
    int maior = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    if (esq < h->tamanho && h->itens[esq].prioridade > h->itens[maior].prioridade)
        maior = esq;

    if (dir < h->tamanho && h->itens[dir].prioridade > h->itens[maior].prioridade)
        maior = dir;

    if (maior != i) {
        trocar(&h->itens[i], &h->itens[maior]);
        descer(h, maior);
    }
}

// Inserir no heap
void inserir(Heap *h, Chamado c) {
    if (h->tamanho == MAX) {
        printf("Heap cheio!\n");
        return;
    }

    h->itens[h->tamanho] = c;
    subir(h, h->tamanho);
    h->tamanho++;

    printf("Chamado inserido com sucesso.\n");
}

// Remover maior prioridade
Chamado remover(Heap *h) {
    Chamado vazio = {-1, "", -1};

    if (h->tamanho == 0) {
        printf("Heap vazio!\n");
        return vazio;
    }

    Chamado raiz = h->itens[0];
    h->itens[0] = h->itens[h->tamanho - 1];
    h->tamanho--;

    descer(h, 0);

    return raiz;
}

// Ver topo
Chamado topo(Heap *h) {
    Chamado vazio = {-1, "", -1};

    if (h->tamanho == 0) {
        printf("Heap vazio!\n");
        return vazio;
    }

    return h->itens[0];
}

// Listar heap
void listar(Heap *h) {
    if (h->tamanho == 0) {
        printf("Heap vazio!\n");
        return;
    }

    printf("\n--- Chamados no Heap ---\n");
    for (int i = 0; i < h->tamanho; i++) {
        printf("ID: %d | Prioridade: %d | Descricao: %s\n",
               h->itens[i].id,
               h->itens[i].prioridade,
               h->itens[i].descricao);
    }
}

// Menu
int main() {
    Heap h;
    h.tamanho = 0;

    int opcao;

    do {
        printf("\n1 - Inserir chamado\n");
        printf("2 - Atender chamado mais prioritario\n");
        printf("3 - Exibir proximo chamado\n");
        printf("4 - Listar heap\n");
        printf("5 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer

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
                inserir(&h, c);
            }

        } else if (opcao == 2) {
            Chamado c = remover(&h);
            if (c.id != -1) {
                printf("Chamado atendido: ID %d | Prioridade %d | %s\n",
                       c.id, c.prioridade, c.descricao);
            }

        } else if (opcao == 3) {
            Chamado c = topo(&h);
            if (c.id != -1) {
                printf("Proximo chamado: ID %d | Prioridade %d | %s\n",
                       c.id, c.prioridade, c.descricao);
            }

        } else if (opcao == 4) {
            listar(&h);
        }

    } while (opcao != 5);

    printf("Encerrando...\n");
    return 0;
}