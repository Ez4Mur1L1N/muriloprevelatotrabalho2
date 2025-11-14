#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linha.h"
#include "tipos.h"

typedef struct{
    int id;
    TipoForma tipo;
    double x1;
    double y1;
    double x2;
    double y2;
    char *cor;
} LINHAL;

Linha criarLinha(int id, double x1, double y1, double x2, double y2, char *cor){
    LINHAL* li = (LINHAL*) malloc(sizeof(LINHAL));
    if(li == NULL){
        printf("Erro ao alocar memoria! Programa encerrado.");
        exit(1);
    }

    li->id = id;
    li->tipo = LINHA;
    li->x1 = x1;
    li->y1 = y1;
    li->x2 = x2;
    li->y2 = y2;
    li->cor = (char*) malloc(strlen(cor) + 1);
    if(li->cor == NULL){
        printf("Erro ao alocar memoria");
        free(li);
        exit(1);
    }
    strcpy(li->cor, cor);

    return li;
}

void killLinha(Linha l){
    LINHAL* li = (LINHAL*) l;
    if(li == NULL){
        return;
    }
    free(li->cor);
    free(li);
}

int getIDLinha(Linha l){
    LINHAL* li = (LINHAL*) l;
    if (li == NULL) {
        return -1;
    }
    return li->id;
}

TipoForma getTipoLinha(Linha l){
    LINHAL* li = (LINHAL*) l;
    if (li == NULL) {
        return -1;
    }
    return li->tipo;
}

double getX1Linha(Linha l){
    LINHAL* li = (LINHAL*) l;
    if (li == NULL) {
        return 0.0;
    }
    return li->x1;
}

double getY1Linha(Linha l){
    LINHAL* li = (LINHAL*) l;
    if (li == NULL) {
        return 0.0;
    }
    return li->y1;
}

double getX2Linha(Linha l){
    LINHAL* li = (LINHAL*) l;
    if (li == NULL) {
        return 0.0;
    }
    return li->x2;
}

double getY2Linha(Linha l){
    LINHAL* li = (LINHAL*) l;
    if (li == NULL) {
        return 0.0;
    }
    return li->y2;
}

char *getCorLinha(Linha l){
    LINHAL* li = (LINHAL*) l;
    if (li == NULL) {
        return "";
    }
    return li->cor;
}

void setX1Linha(Linha l, double x1Novo){
    LINHAL* li = (LINHAL*) l;
    if (li == NULL) {
        return;
    }
    li->x1 = x1Novo;
}

void setY1Linha(Linha l, double y1Novo){
    LINHAL* li = (LINHAL*) l;
    if (li == NULL) {
        return;
    }
    li->y1 = y1Novo;
}

void setX2Linha(Linha l, double x2Novo){
    LINHAL* li = (LINHAL*) l;
    if (li == NULL) {
        return;
    }
    li->x2 = x2Novo;
}

void setY2Linha(Linha l, double y2Novo){
    LINHAL* li = (LINHAL*) l;
    if (li == NULL) {
        return;
    }
    li->y2 = y2Novo;
}

void setCorLinha(Linha l, char *corNova){
    LINHAL* li = (LINHAL*) l;
    if (li == NULL) {
        return;
    }
    free(li->cor);
    li->cor = (char*)malloc(strlen(corNova) + 1);
    if (li->cor == NULL) {
        printf("Erro ao alocar memoria para nova cor!");
        exit(1);
    }
    strcpy(li->cor, corNova);
}

Linha clonarLinha(Linha l, int IDnovo){
    LINHAL* li = (LINHAL*) l;
    if(li == NULL){
        return NULL;
    }

    LINHAL* clone = (LINHAL*) malloc(sizeof(LINHAL));
    if(clone == NULL){
        printf("Erro ao alocar memoria! Programa encerrado.");
        exit(1);
    }

    clone->id = IDnovo;
    clone->tipo = li->tipo;
    clone->x1 = li->x1;
    clone->y1 = li->y1;
    clone->x2 = li->x2;
    clone->y2 = li->y2;
    clone->cor = (char*) malloc(strlen(li->cor) + 1);

    if (clone->cor == NULL) {
        printf("Erro de memoria ao clonar cores da linha!\n");
        free(clone->cor); 
        free(clone);        
        return NULL; // Caso dê erro, libera as memórias.
    }
    strcpy(clone->cor, li->cor);

    return clone;
}