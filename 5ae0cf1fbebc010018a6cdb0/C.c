#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char TipoItem;

typedef struct structNo {
    TipoItem item;
    struct structNo *proximo;
} TipoNo;

typedef TipoNo *TipoApontador;

typedef struct {
    TipoApontador topo;
    unsigned tamanho;
} TipoPilha;

void criaPilha(TipoPilha *P);
TipoItem topoPilha(TipoPilha *P);
TipoItem popPilha(TipoPilha *P);
void pushPilha(TipoPilha *P, TipoItem I);
void esvaziaPilha(TipoPilha *P);
void infixaPosfixa(char *infixa);

int main() {
    int N, i;
    char inf[310];

    scanf("%d", &N);

    for (i = 0; i < N; ++i) {
        scanf("%s", inf);

        infixaPosfixa(inf);
    }

    return 0;
}

void infixaPosfixa(char *infixa) {
    TipoPilha P;
    criaPilha(&P);

    pushPilha(&P, '(');
    strcat(infixa, ")");
    int len = strlen(infixa), i;

    for (i = 0; i < len; ++i) {
        if (infixa[i] == '(')
            pushPilha(&P, infixa[i]);
        else if (infixa[i] == ')') {
            while (topoPilha(&P) != '(')
                printf("%c", popPilha(&P));
            popPilha(&P);
        } else if (infixa[i] == '+' || infixa[i] == '-') {
            while (topoPilha(&P) != '(')
                printf("%c", popPilha(&P));
            pushPilha(&P, infixa[i]);
        } else if (infixa[i] == '*' || infixa[i] == '/') {
            TipoItem aux = topoPilha(&P);
            while (aux != '(' && aux != '+' && aux != '-') {
                printf("%c", popPilha(&P));
                aux = topoPilha(&P);
            }
            pushPilha(&P, infixa[i]);
        } else if (infixa[i] == '^') {
            TipoItem aux = topoPilha(&P);
            while (aux != '(' && aux != '+' && aux != '-' && aux != '*' && aux != '/') {
                printf("%c", popPilha(&P));
                aux = topoPilha(&P);
            }
            pushPilha(&P, infixa[i]);
        } else {
            printf("%c", infixa[i]);
        }
    }

    printf("\n");

    esvaziaPilha(&P);
}


void criaPilha(TipoPilha *P) {
    P->topo = NULL;
    P->tamanho = 0;
}

TipoItem topoPilha(TipoPilha *P) {
    return P->topo->item;
}

TipoItem popPilha(TipoPilha *P) {
    TipoApontador aux = P->topo;
    TipoItem I = P->topo->item;
    P->topo = P->topo->proximo;
    free(aux);
    --P->tamanho;
    return I;
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
