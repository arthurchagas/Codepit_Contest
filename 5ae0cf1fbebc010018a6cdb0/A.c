#include <stdio.h>
#include <stdlib.h>

typedef int TipoItem;

typedef struct structNo {
    TipoItem item;
    struct structNo *proximo;
} TipoNo;

typedef TipoNo *TipoApontador;

typedef struct {
    TipoApontador topo;
    unsigned tamanho;
} TipoPilha;

typedef struct {
    TipoApontador fim;
    unsigned tamanho;
} TipoFila;

void criaPilha(TipoPilha *P);
char pilhaVazia(TipoPilha *P);
TipoItem topoPilha(TipoPilha *P);
void popPilha(TipoPilha *P);
void pushPilha(TipoPilha *P, TipoItem I);
void esvaziaPilha(TipoPilha *P);

void criaFila(TipoFila *F);
char filaVazia(TipoFila *F);
TipoItem frenteFila(TipoFila *F);
void popFila(TipoFila *F);
void pushFila(TipoFila *F, TipoItem I);
void esvaziaFila(TipoFila *F);

int main() {
    int N, i, j, auxEntrada;
    TipoPilha P;
    TipoFila F, E;

    scanf("%d", &N);

    while (N != 0) {
        criaPilha(&P);
        criaFila(&F);
        criaFila(&E);

        scanf("%d", &auxEntrada);

        if (auxEntrada != 0) {
            pushFila(&E, auxEntrada);
            pushFila(&F, 1);

            for (i = 1; i < N; ++i) {
                scanf("%d", &auxEntrada);
                pushFila(&E, auxEntrada);
                pushFila(&F, i + 1);
            }

            while (!filaVazia(&F)) {
                if (frenteFila(&F) == frenteFila(&E)) {
                    popFila(&F);
                    popFila(&E);
                } else if (!pilhaVazia(&P) && frenteFila(&E) == topoPilha(&P)) {
                    popPilha(&P);
                    popFila(&E);
                } else {
                    pushPilha(&P, frenteFila(&F));
                    popFila(&F);
                }
            }

            for (j = P.tamanho; j > 0; --j) {
                if (topoPilha(&P) == frenteFila(&E)) {
                    popPilha(&P);
                    popFila(&E);
                } else
                    break;
            }

            if (filaVazia(&E))
                printf("Yes\n");
            else
                printf("No\n");

            esvaziaPilha(&P);
            esvaziaFila(&F);
            esvaziaFila(&E);
        } else {
            scanf("%d", &N);
            printf("\n");
        }
    }

    return 0;
}

void criaPilha(TipoPilha *P) {
    P->topo = NULL;
    P->tamanho = 0;
}

char pilhaVazia(TipoPilha *P) {
    return P->tamanho == 0;
}

TipoItem topoPilha(TipoPilha *P) {
    return P->topo->item;
}

void popPilha(TipoPilha *P) {
    TipoApontador aux = P->topo;
    P->topo = P->topo->proximo;
    free(aux);
    --P->tamanho;
}

void pushPilha(TipoPilha *P, TipoItem I) {
    TipoApontador aux = (TipoApontador) malloc(sizeof(TipoNo));
    aux->item = I;
    aux->proximo = P->topo;
    P->topo = aux;
    ++P->tamanho;
}

void esvaziaPilha(TipoPilha *P) {
    while (P->tamanho)
        popPilha(P);
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
