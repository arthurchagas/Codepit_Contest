#include <stdio.h>
#include <stdlib.h>

typedef unsigned TipoItem;

typedef struct structNo {
    TipoItem item;
    struct structNo *proximo;
} TipoNo;

typedef TipoNo *TipoApontador;

typedef struct {
    TipoApontador fim;
    unsigned tamanho;
} TipoFila;

void criaFila(TipoFila *F);

char filaVazia(TipoFila *F);

TipoItem popFila(TipoFila *F);

void pushFila(TipoFila *F, TipoItem I);

int main() {
    int N, i;
    TipoFila F, Descartadas;

    scanf("%d", &N);

    while (N != 0) {
        criaFila(&F);
        criaFila(&Descartadas);

        for (i = 1; i <= N; ++i)
            pushFila(&F, i);

        while (F.tamanho > 1) {
            pushFila(&Descartadas, popFila(&F));
            pushFila(&F, popFila(&F));
        }

        printf("Discarded cards:");

        if (!filaVazia(&Descartadas))
            printf(" %d", popFila(&Descartadas));

        while (!filaVazia(&Descartadas))
            printf(", %d", popFila(&Descartadas));

        printf("\nRemaining card: %d\n", popFila(&F));

        scanf("%d", &N);
    }
    return 0;
}


void criaFila(TipoFila *F) {
    F->fim = NULL;
    F->tamanho = 0;
}

char filaVazia(TipoFila *F) {
    return F->tamanho == 0;
}

TipoItem popFila(TipoFila *F) {
    TipoApontador aux = F->fim->proximo;
    F->fim->proximo = F->fim->proximo->proximo;
    --F->tamanho;
    TipoItem I = aux->item;
    free(aux);
    return I;
}

void pushFila(TipoFila *F, TipoItem I) {
    TipoApontador aux = (TipoApontador) malloc(sizeof(TipoNo));
    aux->item = I;

    if (filaVazia(F)) {
        F->fim = aux;
        F->fim->proximo = F->fim;
        ++F->tamanho;
        return;
    }

    aux->proximo = F->fim->proximo;
    F->fim->proximo = aux;
    F->fim = aux;
    ++F->tamanho;
}

