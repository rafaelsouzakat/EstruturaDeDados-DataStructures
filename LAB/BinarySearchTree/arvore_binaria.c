#include <stdio.h>
#include <stdlib.h>
#define MAX 50

// Estrutura do nó da árvore
typedef struct No {
    int codigo_produto; // Não pode ser repetido (é único)
    char nome[MAX];
    int stock_amount;   // Deve ser positivo
    struct No* esq;
    struct No* dir;
} No;

// Estrutura da BST: guarda o ponteiro da raiz (e pode ter mais campos se desejar)
typedef struct BST {
    No* raiz;
    int tamanho;
    // Você pode incluir também campos como "int tamanho;" etc.
} BST;

// Cria um novo nó
No* criaNo(int codigo_produto, char nome[MAX], int stock_amount) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    novo->codigo_produto = codigo_produto;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

// Cria uma nova BST (inicialmente vazia)
BST* criaBST() {
    BST* bst = (BST*)malloc(sizeof(BST));
    if (bst == NULL) {
        printf("Erro ao alocar memória para a BST.\n");
        exit(1);
    }
    bst->raiz = NULL;
    return bst;
}

// Função auxiliar recursiva para inserir na BST
No* insereRec(No* raiz, int codigo_produto, char nome[MAX], int stock_amount) {
    if (raiz == NULL) {
        return criaNo(codigo_produto, nome, stock_amount);
    }
    if (codigo_produto < raiz->codigo_produto) {
        raiz->esq = insereRec(raiz->esq, codigo_produto, nome, stock_amount);
    } else {
        raiz->dir = insereRec(raiz->dir, codigo_produto, nome, stock_amount);
    }
    return raiz;
}

// Função pública de inserção
void insereBST(BST* bst, int codigo_produto, char nome[MAX], int stock_amount) {
    if (bst == NULL) return;
    
    // Verifica se a quantidade em estoque é negativa - OBS: passei essa verificação para o main, mas poderia ser aqui também
    //if(stock_amount < 0){
    //    printf("Quantidade em estoque deve ser positiva.\n");
    //    return;
    //}

    bst->raiz = insereRec(bst->raiz, codigo_produto, nome, stock_amount);
}

// Função auxiliar recursiva de busca
No* buscaRec(No* raiz, int codigo_produto) {
    if (raiz == NULL || raiz->codigo_produto == codigo_produto) {
        return raiz;
    }
    if (codigo_produto < raiz->codigo_produto) {
        return buscaRec(raiz->esq, codigo_produto);
    } else {
        return buscaRec(raiz->dir, codigo_produto);
    }
}

// Função pública de busca
No* buscaBST(BST* bst, int codigo_produto) {
    if (bst == NULL) return NULL;
    return buscaRec(bst->raiz, codigo_produto);
}

// Percurso em-ordem recursivo
void emOrdemRec(No* raiz) {
    if (raiz != NULL) {
        emOrdemRec(raiz->esq);
        printf("%d ", raiz->codigo_produto);
        emOrdemRec(raiz->dir);
    }
}

// Função pública de percurso em-ordem
void emOrdemBST(BST* bst) {
    if (bst == NULL) return;
    emOrdemRec(bst->raiz);
}

// Função auxiliar recursiva para liberar nós
void liberaArvoreRec(No* raiz) {
    if (raiz != NULL) {
        liberaArvoreRec(raiz->esq);
        liberaArvoreRec(raiz->dir);
        free(raiz);
    }
}

// Função pública para liberar a BST
void liberaBST(BST* bst) {
    if (bst == NULL) return;
    liberaArvoreRec(bst->raiz);
    free(bst);
}

int main() {
    // Cria uma BST
    BST* arv = criaBST();

    int opcao;

    do{

        printf("Menu:\n");
        printf("1 - Cadastrar produto\n");
        printf("2 - Buscar produto por código\n");
        printf("3 - Listar produtos em ordem\n");
        printf("4 - Mostrar menor código de produto\n");
        printf("5 - Mostrar maior código de produto\n");
        printf("6 - Sair\n");

        opcao = scanf("%d", &opcao);

        int codigo_produto;
        char nome[MAX];
        int stock_amount;

        switch(opcao){
            case 1:
                printf("Digite o código do produto: ");
                scanf("%d", &codigo_produto);

                printf("Digite o nome do produto: ");
                scanf("%s", nome);

                printf("Digite a quantidade em estoque: ");
                scanf("%d", &stock_amount);

                if(stock_amount < 0){
                    printf("Quantidade em estoque deve ser positiva.\n");
                    break;
                }
                if(buscaBST(arv, codigo_produto)){
                    printf("Esse código já foi cadastrado. Tente novamente.\n");
                    break;
                }

                insereBST(arv, codigo_produto, nome, stock_amount);
                printf("Produto cadastrado com sucesso!\n");
                break;
            
            case 2:
                printf("Digite o código do produto para buscar: ");
                scanf("%d", &codigo_produto);

                No* encontrado = buscaBST(arv, codigo_produto);
                if(encontrado){
                    printf("Produto encontrado: \nCódigo: %d\nNome: %s\nQuantidade em estoque: %d\n", encontrado->codigo_produto, encontrado->nome, encontrado->stock_amount);
                } else {
                    printf("Produto com código %d não encontrado.\n", codigo_produto);
                }
                break;

            case 3:
                printf("Produtos em ordem: ");
                emOrdemBST(arv);
                printf("\n");
                break;
            
            case 4:
                // Implementar função para mostrar menor código de produto
                break;

            case 5:
                // Implementar função para mostrar maior código de produto
                break;
        }

    } 
    while(opcao != 6);

    // Insere alguns valores
    // Cada produto tem um código único, um nome e uma quantidade em estoque (positiva)
    //insereBST(arv, 001, "Produto 1", 10);
    //insereBST(arv, 002, "Produto 2", 20);
    //insereBST(arv, 003, "Produto 3", 15);
    //insereBST(arv, 004, "Produto 4", 5);
    //insereBST(arv, 005, "Produto 5", 8);
    //insereBST(arv, 006, "Produto 6", 12);
    //insereBST(arv, 007, "Produto 7", 25);

    // Percorre em-ordem
    printf("Valores em-ordem: ");
    emOrdemBST(arv);
    printf("\n");

    // Faz uma busca
    //int codigoParaBuscar = 40;
    //No* encontrado = buscaBST(arv, codigoParaBuscar);
    //if (encontrado) {
    //    printf("Código %d encontrado na árvore.\n", codigoParaBuscar);
    //} else {
    //    printf("Código %d não encontrado.\n", codigoParaBuscar);
    //}

    // Libera toda a memória
    liberaBST(arv);
    return 0;
}