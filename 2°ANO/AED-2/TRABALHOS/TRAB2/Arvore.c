#include <stdio.h>
#include <stdlib.h>

struct s_no {
    int chave;
    struct s_no *esq;
    struct s_no *dir;
};

// Inserção Recursiva (Mais segura e limpa)
struct s_no* insert(struct s_no *raiz, int x) {
    if (raiz == NULL) {
        struct s_no *novo = (struct s_no*) malloc(sizeof(struct s_no));
        novo->chave = x;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }
    if (x < raiz->chave) {
        raiz->esq = insert(raiz->esq, x);
    } else if (x > raiz->chave) {
        raiz->dir = insert(raiz->dir, x);
    }
    return raiz;
}

// Busca o nó com o menor valor (útil para remoção e busca)
struct s_no* menor_no(struct s_no *raiz) {
    struct s_no *atual = raiz;
    while (atual && atual->esq != NULL) {
        atual = atual->esq;
    }
    return atual;
}

void Busca_Maior(struct s_no *raiz) {
    if (raiz == NULL) {
        printf("ARVORE VAZIA\n");
        return;
    }
    struct s_no *atual = raiz;
    while (atual->dir != NULL) {
        atual = atual->dir;
    }
    printf("\nMAIOR ELEMENTO: %d\n", atual->chave);
}

void Busca_Menor(struct s_no *raiz) {
    struct s_no *min = menor_no(raiz);
    if (min != NULL) {
        printf("\nMENOR ELEMENTO: %d\n", min->chave);
    } else {
        printf("ARVORE VAZIA\n");
    }
}

void Ord_Simetrica(struct s_no *raiz) {
    if (raiz != NULL) {
        Ord_Simetrica(raiz->esq);
        printf("%d ", raiz->chave);
        Ord_Simetrica(raiz->dir);
    }
}

void Pre_Ordem(struct s_no *raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->chave);
        Pre_Ordem(raiz->esq);
        Pre_Ordem(raiz->dir);
    }
}

void Pos_Ordem(struct s_no *raiz) {
    if (raiz != NULL) {
        Pos_Ordem(raiz->esq);
        Pos_Ordem(raiz->dir);
        printf("%d ", raiz->chave);
    }
}

// Remoção Padrão de BST
struct s_no* REMOCAO(struct s_no *raiz, int x) {
    if (raiz == NULL) return raiz;

    if (x < raiz->chave) {
        raiz->esq = REMOCAO(raiz->esq, x);
    } else if (x > raiz->chave) {
        raiz->dir = REMOCAO(raiz->dir, x);
    } else {
        // Caso 1: Nó folha ou com 1 filho
        if (raiz->esq == NULL) {
            struct s_no *temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            struct s_no *temp = raiz->esq;
            free(raiz);
            return temp;
        }

        // Caso 2: Nó com 2 filhos (Substitui pelo menor da subárvore direita)
        struct s_no *temp = menor_no(raiz->dir);
        raiz->chave = temp->chave;
        raiz->dir = REMOCAO(raiz->dir, temp->chave);
    }
    return raiz;
}

int main() {
    struct s_no *raiz = NULL;

    raiz = insert(raiz, 5);
    raiz = insert(raiz, 3);
    raiz = insert(raiz, 2);
    raiz = insert(raiz, 1);
    raiz = insert(raiz, 9);
    raiz = insert(raiz, 6);
    raiz = insert(raiz, 7);
    raiz = insert(raiz, 4);
    raiz = insert(raiz, 8);

    printf("Ordem Simetrica: ");
    Ord_Simetrica(raiz);
    printf("\n");

    Busca_Maior(raiz);
    Busca_Menor(raiz);

    printf("\nRemovendo 8...\n");
    raiz = REMOCAO(raiz, 8);
    Ord_Simetrica(raiz);
    printf("\n");

    printf("\nRemovendo 4...\n");
    raiz = REMOCAO(raiz, 4);
    Ord_Simetrica(raiz);
    printf("\n");

    printf("\nRemovendo 3...\n");
    raiz = REMOCAO(raiz, 3);
    Ord_Simetrica(raiz);
    printf("\n");

    printf("\nRemovendo 9...\n");
    raiz = REMOCAO(raiz, 9);
    Ord_Simetrica(raiz);
    printf("\n");

    return 0;
}