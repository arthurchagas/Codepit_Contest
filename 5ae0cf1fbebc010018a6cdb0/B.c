#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned chegada;
    unsigned critico;
} TipoItem;

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
TipoItem frenteFila(TipoFila *F);
void popFila(TipoFila *F);
void pushFila(TipoFila *F, TipoItem I);
void esvaziaFila(TipoFila *F);

int main() {
    int N, i, k;
    unsigned H, M, C;
    TipoFila F;
    TipoItem aux;

    while (scanf("%d", &N) != EOF) {
        criaFila(&F);

        for (i = 0; i < N; ++i) {
            scanf("%d %d %d", &H, &M, &C);

            aux.chegada = H * 60 + M;
            aux.critico = aux.chegada + C;

            pushFila(&F, aux);
        }

        i = 420;
        k = 0;

        while (!filaVazia(&F)) {
            aux = frenteFila(&F);

            if (i >= aux.chegada) {
                if (i > aux.critico)
                    ++k;
                popFila(&F);
            }

            i += 30;
        }

        printf("%d\n", k);

        esvaziaFila(&F);
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

TipoItem frenteFila(TipoFila *F) {
    return F->fim->proximo->item;
}

void popFila(TipoFila *F) {
    TipoApontador aux = F->fim->proximo;
    F->fim->proximo = F->fim->proximo->proximo;
    --F->tamanho;
    free(aux);
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

void esvaziaFila(TipoFila *F) {
    while (F->tamanho)
        popFila(F);
}
