#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "texto.h"
#include "tipos.h"

typedef struct estiloTexto{
    char *fFamily;
    char *fWeight;
    char *fSize;
} EstiloTexto;

typedef struct{
    int id;
    TipoForma tipo;
    double x;
    double y;
    char *corBo;
    char *corPr;
    char *an; //âncora
    char *texto;
    EstiloTexto estilo;
} TEXTOT;

Texto criarTexto(int id, double x, double y, char *corB, char *corP, char *a, char *texto, char *fFamily, char *fWeight, char *fSize){
    TEXTOT* te = (TEXTOT*) malloc(sizeof(TEXTOT));
    if(te == NULL){
        printf("Erro ao alocar memoria! Programa encerrado.");
        exit(1);
    }

    te->id = id;
    te->tipo = TEXTO;
    te->x = x;
    te->y = y;
    te->corBo = (char*) malloc(strlen(corB) + 1);
    te->corPr = (char*) malloc(strlen(corP)+1);
    te->an = (char*) malloc(strlen(a) + 1);
    te->texto = (char*) malloc(strlen(texto) + 1);
    te->estilo.fFamily = (char*) malloc(strlen(fFamily) + 1);
    te->estilo.fWeight = (char*) malloc(strlen(fWeight) + 1);
    te->estilo.fSize = (char*) malloc(strlen(fSize) + 1);

    if(te->corBo == NULL || te->corPr == NULL || te->an == NULL || te->texto == NULL || te->estilo.fFamily == NULL || te->estilo.fWeight == NULL || te->estilo.fSize == NULL){
        printf("Erro ao alocar memoria.");
        free(te->corBo);
        free(te->corPr);
        free(te->an);
        free(te->texto);
        free(te->estilo.fFamily);
        free(te->estilo.fWeight);
        free(te->estilo.fSize);
        free(te);
        exit(1);
    }

    strcpy(te->corBo, corB);
    strcpy(te->corPr, corP);
    strcpy(te->an, a);
    strcpy(te->texto, texto);
    strcpy(te->estilo.fFamily, fFamily);
    strcpy(te->estilo.fWeight, fWeight);
    strcpy(te->estilo.fSize, fSize);

    return te;
}

void killTexto(Texto t){
    TEXTOT* te = (TEXTOT*) t;
    if(te == NULL){
        return;
    }
    free(te->corBo);
    free(te->corPr);
    free(te->an);
    free(te->texto);
    free(te->estilo.fFamily);
    free(te->estilo.fWeight);
    free(te->estilo.fSize);
    free(te);
}

int getIDTexto(Texto t){
    TEXTOT* te = (TEXTOT*) t;
    if (te == NULL) {
        return -1;
    }
    return te->id;
}

TipoForma getTipoTexto(Texto t){
    TEXTOT* te = (TEXTOT*) t;
    if (te == NULL) {
        return -1;
    }
    return te->tipo;
}

double getXTexto(Texto t){
    TEXTOT* te = (TEXTOT*) t;
    if (te == NULL) {
        return 0.0;
    }
    return te->x;
}

double getYTexto(Texto t){
    TEXTOT* te = (TEXTOT*) t;
    if (te == NULL) {
        return 0.0;
    }
    return te->y;
}

char *getCorBTexto(Texto t){
    TEXTOT* te = (TEXTOT*) t;
    if (te == NULL) {
        return "";
    }
    return te->corBo;
}

char *getCorPTexto(Texto t){
    TEXTOT* te = (TEXTOT*) t;
    if (te == NULL) {
        return "";
    }
    return te->corPr;
}

char *getAncoraTexto(Texto t){
    TEXTOT* te = (TEXTOT*) t;
    if (te == NULL) {
        return "";
    }
    return te->an;
}

char *getTexto_Texto(Texto t){
    TEXTOT* te = (TEXTOT*) t;
    if (te == NULL) {
        return "";
    }
    return te->texto;
}

char *getFontFamilyTexto(Texto t){
    TEXTOT* te = (TEXTOT*) t;
    if (te == NULL) {
        return "";
    }
    return te->estilo.fFamily;
}

char *getFontWeightTexto(Texto t){
    TEXTOT* te = (TEXTOT*) t;
    if (te == NULL) {
        return "";
    }
    return te->estilo.fWeight;
}

char *getFontSizeTexto(Texto t){
    TEXTOT* te = (TEXTOT*) t;
    if (te == NULL) {
        return "";
    }
    return te->estilo.fSize;
}

void setXTexto(Texto t, double xNovo) {
    TEXTOT* te = (TEXTOT*) t;
    if (te == NULL) {
        return;
    }
    te->x = xNovo;
}

void setYTexto(Texto t, double yNovo) {
    TEXTOT* te = (TEXTOT*) t;
    if (te == NULL) {
        return;
    }
    te->y = yNovo;
}

void setCorBTexto(Texto t, char *corBNova) {
    TEXTOT* te = (TEXTOT*) t;
    if (te == NULL) {
        return;
    }
    free(te->corBo);
    te->corBo = (char*)malloc(strlen(corBNova) + 1);
    if (te->corBo == NULL) {
        printf("Erro ao alocar memoria para nova cor!");
        exit(1);
    }
    strcpy(te->corBo, corBNova);
}

void setCorPTexto(Texto t, char *corPNova) {
    TEXTOT* te = (TEXTOT*) t;
    if (te == NULL) {
        return;
    }
    free(te->corPr);
    te->corPr = (char*)malloc(strlen(corPNova) + 1);
    if (te->corPr == NULL) {
        printf("Erro ao alocar memoria para nova cor!");
        exit(1);
    }
    strcpy(te->corPr, corPNova);
}

Texto clonarTexto(Texto t, int IDnovo){
    TEXTOT* te = (TEXTOT*) t;
    if(te == NULL){
        return NULL;
    }

    TEXTOT* clone = (TEXTOT*) malloc(sizeof(TEXTOT));
    if(clone == NULL){
        printf("Erro ao alocar memoria! Programa encerrado.");
        exit(1);
    }

    clone->id = IDnovo;
    clone->tipo = te->tipo;
    clone->x = te->x;
    clone->y = te->y;

    clone->corBo = (char*) malloc(strlen(te->corBo) + 1);
    clone->corPr = (char*) malloc(strlen(te->corPr) + 1);
    clone->an = (char*) malloc(strlen(te->an) + 1);
    clone->texto = (char*) malloc(strlen(te->texto) + 1);
    clone->estilo.fFamily = (char*) malloc(strlen(te->estilo.fFamily) + 1);
    clone->estilo.fWeight = (char*) malloc(strlen(te->estilo.fWeight) + 1);    
    clone->estilo.fSize = (char*) malloc(strlen(te->estilo.fSize) + 1);


    if (clone->corBo == NULL || clone->corPr == NULL || clone->an == NULL || clone->texto == NULL || clone->estilo.fFamily == NULL || clone->estilo.fWeight == NULL || clone->estilo.fSize == NULL) {
        printf("Erro de memoria ao clonar cores da Texto!\n");
        free(clone->corBo);
        free(clone->corPr); 
        free(clone->an);
        free(clone->texto); 
        free(clone->estilo.fFamily);
        free(clone->estilo.fWeight); 
        free(clone->estilo.fSize); 
        free(clone);        
        return NULL; // Caso dê erro, libera as memórias.
    }
    strcpy(clone->corBo, te->corBo);
    strcpy(clone->corPr, te->corPr);
    strcpy(clone->an, te->an);
    strcpy(clone->texto, te->texto);
    strcpy(clone->estilo.fFamily, te->estilo.fFamily);
    strcpy(clone->estilo.fWeight, te->estilo.fWeight);
    strcpy(clone->estilo.fSize, te->estilo.fSize);

    return clone;
}