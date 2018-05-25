#include <stdio.h>
#include <stdlib.h>

typedef unsigned TipoItem;

typedef struct structNo {
    TipoItem item;
    struct structNo *proximo;
    struct structNo *anterior;
} TipoNo;

typedef TipoNo *TipoApontador;

typedef struct {
    TipoApontador primeiro;
    TipoApontador ultimo;
    unsigned tamanho;
} TipoDeque;

void criaDeque(TipoDeque *D);
char dequeVazio(TipoDeque *D);
void insereFim(TipoDeque *D, TipoItem I);
void insereComeco(TipoDeque *D, TipoItem I);
TipoItem popFim(TipoDeque *D);
TipoItem popFrente(TipoDeque *D);
void limpaDeque(TipoDeque *D);

int main() {
    int H, P, F;
    unsigned auxU;
    int i, j;

    scanf("%d %d %d", &H, &P, &F);

    while (H != 0 || P != 0 || F != 0) {
        TipoDeque Dq[P], Fq;

        for (i = 0; i < P; ++i)
            criaDeque(&Dq[i]);

        for (j = 0; j < H; ++j) {
            for (i = 0; i < P; ++i) {
                scanf("%d", &auxU);

                if (auxU != 0)
                    insereComeco(&Dq[i], auxU);
            }
        }

        criaDeque(&Fq);

        for (i = 0; i < F; ++i) {
            scanf("%d", &auxU);

            insereFim(&Fq, auxU);
        }

        for (j = P - 1; !dequeVazio(&Fq) && j >= 0; --j)
            while (Dq[j].tamanho < H && !dequeVazio(&Fq))
                insereFim(&Dq[j], popFrente(&Fq));

        for (j = 0; j < H; ++j) {
            for (i = 0; i < P; ++i) {
                if (j + Dq[i].tamanho < H)
                    printf("0");
                else
                    printf("%d", popFim(&Dq[i]));

                if (i + 1 < P)
                    printf(" ");
            }
            printf("\n");
        }

        limpaDeque(&Fq);

        scanf("%d %d %d", &H, &P, &F);
    }

    return 0;
}

void criaDeque(TipoDeque *D) {
    D->tamanho = 0;
    D->primeiro = NULL;
    D->ultimo = NULL;
}

char dequeVazio(TipoDeque *D) {
    return D->tamanho == 0;
}

void insereFim(TipoDeque *D, TipoItem I) {
    TipoApontador aux = (TipoApontador) malloc(sizeof(TipoNo));
    aux->item = I;

    if (dequeVazio(D)) {
        D->primeiro = aux;
        D->primeiro->anterior = NULL;
        D->ultimo = aux;
        D->ultimo->proximo = NULL;
        ++D->tamanho;
        return;
    }

    aux->proximo = NULL;
    aux->anterior = D->ultimo;
    D->ultimo->proximo = aux;
    D->ultimo = aux;
    ++D->tamanho;
}

void insereComeco(TipoDeque *D, TipoItem I) {
    TipoApontador aux = (TipoApontador) malloc(sizeof(TipoNo));
    aux->item = I;

    if (dequeVazio(D)) {
        D->primeiro = aux;
        D->primeiro->anterior = NULL;
        D->ultimo = aux;
        D->ultimo->proximo = NULL;
        ++D->tamanho;
        return;
    }

    aux->anterior = NULL;
    aux->proximo = D->primeiro;
    D->primeiro->anterior = aux;
    D->primeiro = aux;
    ++D->tamanho;
}

TipoItem popFim(TipoDeque *D) {
    TipoItem aux = D->ultimo->item;
    TipoApontador aux2 = D->ultimo;

    D->ultimo = D->ultimo->anterior;
    if (D->tamanho > 1) {
        D->ultimo->proximo = NULL;
    } else {
        D->primeiro = NULL;
    }

    free(aux2);

    --D->tamanho;

    return aux;
}

TipoItem popFrente(TipoDeque *D) {
    TipoItem aux = D->primeiro->item;
    TipoApontador aux2 = D->primeiro;

    D->primeiro = D->primeiro->proximo;
    if (D->tamanho > 1) {
        D->primeiro->anterior = NULL;
    } else {
        D->ultimo = NULL;
    }

    free(aux2);

    --D->tamanho;

    return aux;
}

void limpaDeque(TipoDeque *D) {
    while (D->tamanho)
        popFrente(D);
}
