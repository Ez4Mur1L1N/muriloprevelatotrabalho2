#include <stdio.h>
#include <stdlib.h>
#include "segmento.h"

typedef struct{
    int id;
    double x1;
    double y1;
    double x2;
    double y2;
} SEGMENTO_S;

Segmento criarSegmento(int id, double x1, double y1, double x2, double y2){
    SEGMENTO_S* seg = (SEGMENTO_S*) malloc(sizeof(SEGMENTO_S));
    if(seg == NULL){
        printf("Erro ao alocar memoria! Programa encerrado");
        exit(1);
    }

    seg->id = id;
    seg->x1 = x1;
    seg->y1 = y1;
    seg->x2 = x2;
    seg->y2 = y2;

    return seg;
}

void killSegmento(Segmento s){
    SEGMENTO_S* seg = (SEGMENTO_S*) s;
    if (seg == NULL){
        return;
    }
    free(seg);
}

int getIDSegmento(Segmento s){
    SEGMENTO_S* seg = (SEGMENTO_S*) s;
    if(seg == NULL){
        return -1;
    }
    return seg->id;
}

double getX1Segmento(Segmento s){
    SEGMENTO_S* seg = (SEGMENTO_S*) s;
    if(seg == NULL){
        return 0.0;
    }
    return seg->x1;
}

double getY1Segmento(Segmento s){
    SEGMENTO_S* seg = (SEGMENTO_S*) s;
    if(seg == NULL){
        return 0.0;
    }
    return seg->y1;
}

double getX2Segmento(Segmento s){
    SEGMENTO_S* seg = (SEGMENTO_S*) s;
    if(seg == NULL){
        return 0.0;
    }
    return seg->x2;
}

double getY2Segmento(Segmento s){
    SEGMENTO_S* seg = (SEGMENTO_S*) s;
    if(seg == NULL){
        return 0.0;
    }
    return seg->y2;
}