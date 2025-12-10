#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "retangulo.h"
#include "tipos.h"

typedef struct{
    int id;
    TipoForma tipo;
    double x;
    double y;
    double w;
    double h;
    char *corBo;
    char *corPr;
} RETANGULOR;

Retangulo criarRetangulo(int id, double x, double y, double w, double h, char *corB, char *corP){
    RETANGULOR* re = (RETANGULOR*) malloc(sizeof(RETANGULOR));
    if(re == NULL){
        printf("Erro ao alocar memoria! Programa encerrado.");
        exit(1);
    }

    re->id = id;
    re->tipo = RETANGULO;
    re->x = x;
    re->y = y;
    re->w = w;
    re->h = h;
    re->corBo = (char*) malloc(strlen(corB)+ 1);
    re->corPr = (char*) malloc(strlen(corP) + 1);

    if(re->corBo == NULL || re->corPr == NULL){
        printf("Erro ao alocar memoria!");
        free(re->corBo);
        free(re->corPr);
        free(re);
        exit(1);
    }

    strcpy(re->corBo, corB);
    strcpy(re->corPr, corP);

    return re;
}

void killRetangulo(Retangulo r){
    RETANGULOR* re = (RETANGULOR*) r;
    if (re == NULL) {
        return;
    }
    free(re->corBo);
    free(re->corPr);
    free(re);
}

int getIDRetangulo(Retangulo r){
    RETANGULOR* re = (RETANGULOR*) r;
    if (re == NULL) {
        return -1;
    }
    return re->id;
}

TipoForma getTipoRetangulo(Retangulo r){
    RETANGULOR* re = (RETANGULOR*) r;
    if (re == NULL) {
        return -1;
    }
    return re->tipo;
}

double getXRetangulo(Retangulo r){
    RETANGULOR* re = (RETANGULOR*) r;
    if (re == NULL) {
        return 0.0;
    }
    return re->x;
}

double getYRetangulo(Retangulo r){
    RETANGULOR* re = (RETANGULOR*) r;
    if (re == NULL) {
        return 0.0;
    }
    return re->y;
}

double getWRetangulo(Retangulo r){
    RETANGULOR* re = (RETANGULOR*) r;
    if (re == NULL) {
        return 0.0;
    }
    return re->w;
}

double getHRetangulo(Retangulo r){
    RETANGULOR* re = (RETANGULOR*) r;
    if (re == NULL) {
        return 0.0;
    }
    return re->h;
}

char *getCorBRetangulo(Retangulo r){
    RETANGULOR* re = (RETANGULOR*) r;
    if (re == NULL) {
        return "";
    }
    return re->corBo;
}

char *getCorPRetangulo(Retangulo r){
    RETANGULOR* re = (RETANGULOR*) r;
    if (re == NULL) {
        return "";
    }
    return re->corPr;
}

void setXRetangulo(Retangulo r, double xNovo){
    RETANGULOR* re = (RETANGULOR*) r;
    if (re == NULL) {
        return;
    }
    re->x = xNovo;
}

void setYRetangulo(Retangulo r, double yNovo){
    RETANGULOR* re = (RETANGULOR*) r;
    if (re == NULL) {
        return;
    }
    re->y = yNovo;
}

void setCorBRetangulo(Retangulo r, char *corBNova){
    RETANGULOR* re = (RETANGULOR*) r;
    if (re == NULL) {
        return;
    }
    free(re->corBo);
    re->corBo = (char*)malloc(strlen(corBNova) + 1);
    if (re->corBo == NULL) {
        printf("Erro ao alocar memoria para nova cor!");
        exit(1);
    }
    strcpy(re->corBo, corBNova);
}

void setCorPRetangulo(Retangulo r, char *corPNova){
    RETANGULOR* re = (RETANGULOR*) r;
    if (re == NULL) {
        return;
    }
    free(re->corPr);
    re->corPr = (char*)malloc(strlen(corPNova) + 1);
    if (re->corPr == NULL) {
        printf("Erro ao alocar memoria para nova cor!");
        exit(1);
    }
    strcpy(re->corPr, corPNova);
}

Retangulo clonarRetangulo(Retangulo r, int IDnovo, double dx, double dy){
    RETANGULOR* re = (RETANGULOR*) r;
    if(re == NULL){
        return NULL;
    }

    RETANGULOR* clone = (RETANGULOR*) malloc(sizeof(RETANGULOR));
    if(clone == NULL){
        printf("Erro ao alocar memoria! Programa encerrado.");
        exit(1);
    }

    clone->id = IDnovo;
    clone->tipo = re->tipo;
    clone->x = re->x + dx;
    clone->y = re->y + dy;
    clone->h = re->h;
    clone->w = re->w;
    clone->corBo = (char*) malloc(strlen(re->corBo) + 1);
    clone->corPr = (char*) malloc(strlen(re->corPr) + 1);

    if (clone->corBo == NULL || clone->corPr == NULL) {
        printf("Erro de memoria ao clonar cores do retangulo!\n");
        free(clone->corBo); 
        free(clone->corPr);
        free(clone);        
        return NULL; // Caso dê erro, libera as memórias.
    }
    strcpy(clone->corBo, re->corBo);
    strcpy(clone->corPr, re->corPr);

    return clone;
}