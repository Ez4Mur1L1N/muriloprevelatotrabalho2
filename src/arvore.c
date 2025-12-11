#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "arvore.h"

typedef struct noArvore{
    Segmento seg;
    struct noArvore *esquerda;
    struct noArvore *direita;
} NoSegmento;

typedef struct{
    NoSegmento *raiz;
    double xBomba; //Pontos de referência para o cálculo da distância.
    double yBomba;
    int qtd;
} ARVOREA;

// Funções auxiliares que vão amparar o cálculo da distância da bomba até o ponto onde corta o segmento.

double distSq(double x1, double y1, double x2, double y2){
    return (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
}

double obterDistancia(double xBomba, double yBomba, Segmento seg){
    double x1 = getX1Segmento(seg);
    double y1 = getY1Segmento(seg);
    double x2 = getX2Segmento(seg);
    double y2 = getY2Segmento(seg);

    double l2 = distSq(x1, y1, x2, y2);

    // Se o segmento é apenas um ponto
    if(l2 == 0.0) return sqrt(distSq(xBomba, yBomba, x1, y1));

    double t = ((xBomba - x1) * (x2 - x1) + (yBomba - y1) * (y2 - y1)) / l2;
    if(t < 0.0) t = 0.0;
    else if(t > 1.0) t = 1.0;

    double xProj = x1 + t *(x2 - x1);
    double yProj = y1 + t *(y2 - y1);

    return sqrt(distSq(xBomba, yBomba, xProj, yProj));
}

int compararSegmentos(Segmento segA, Segmento segB, double xBomba, double yBomba){
    double distA = obterDistancia(xBomba, yBomba, segA);
    double distB = obterDistancia(xBomba, yBomba, segB);

    // --- DEBUG TEMPORÁRIO (Remova depois) ---
    // Vamos printar apenas se a distância for pequena, para não poluir demais
    if (distA < 100 && distB < 100) {
        printf("COMP: SegID %d (Dist %.2f) vs SegID %d (Dist %.2f)\n", getIDSegmento(segA), distA, getIDSegmento(segB), distB);
    }

    // Para tratar distâncias muito pequenas(ou seja, iguais).
    if(fabs(distA - distB)< 1e-9){
        //Se as distâncias são iguais o desempate é pelo ID
        int idA = getIDSegmento(segA);
        int idB = getIDSegmento(segB);
        if(idA < idB) return -1;
        if(idA > idB) return 1;
        return 0; // Segurança;
    }

    if(distA<distB) return -1; // A menor(mais próxima).
    return 1; // B menor.
}

Arvore criarArvore(double xBomba, double yBomba){
    ARVOREA* arv = (ARVOREA*) malloc(sizeof(ARVOREA));
    if(arv == NULL){
        printf("Erro ao alocar memoria! Programa encerrado.");
        exit(1);
    }
    arv->raiz = NULL;
    arv->xBomba = xBomba;
    arv->yBomba = yBomba;
    arv->qtd = 0;
    return arv;
}    

void percorreEkill(NoSegmento *no){
    if(no != NULL){
        percorreEkill(no->esquerda);
        percorreEkill(no->direita);
        free(no);
    }
}

void killArvore(Arvore arvore){
    ARVOREA* arv = (ARVOREA*) arvore;
    if(arv == NULL){
        return;
    } else{
        percorreEkill(arv->raiz);
        free(arv);
    }
}

int arvoreVazia(Arvore arvore){
    ARVOREA* arv = (ARVOREA*) arvore;
    if(arv == NULL){
        return -1;
    }    
    return (arv == NULL || arv->raiz == NULL);
}

// função auxiliar para inserção.

NoSegmento* inserirRecursivo(NoSegmento *noAtual, Segmento seg, double xBomba, double yBomba){
    if(noAtual == NULL){
        NoSegmento *novo = (NoSegmento*) malloc(sizeof(NoSegmento));
        if(novo == NULL){
            printf("Erro ao alocar memoria! Programa encerrado.");
            exit(1);
        }
        novo->seg = seg;
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }
    int comp = compararSegmentos(seg, noAtual->seg, xBomba, yBomba);
    if(comp<0) noAtual->esquerda = inserirRecursivo(noAtual->esquerda, seg, xBomba, yBomba);
    else if(comp>0) noAtual->direita = inserirRecursivo(noAtual->direita, seg, xBomba, yBomba);
    return noAtual;
}

void inserirSegmentoArvore(Arvore arvore, Segmento seg){
    ARVOREA* arv = (ARVOREA*) arvore;
    if(arv == NULL){
        return;
    }    
    if(arv) arv->raiz = inserirRecursivo(arv->raiz, seg, arv->xBomba, arv->yBomba);
}

// funções auxiliares para remoção.

NoSegmento* noMinimo(NoSegmento* no){
    NoSegmento* atual = no;
    while(atual && atual->esquerda != NULL) atual = atual->esquerda;
    return atual;
}

NoSegmento* removerRecursivo(NoSegmento *noAtual, Segmento seg, double xBomba, double yBomba){
    if(noAtual == NULL){
        return noAtual;
    }

    int comp = compararSegmentos(seg, noAtual->seg, xBomba, yBomba);
    if(comp<0) noAtual->esquerda = removerRecursivo(noAtual->esquerda, seg, xBomba, yBomba);
    else if(comp>0) noAtual->direita = removerRecursivo(noAtual->direita, seg, xBomba, yBomba);
    else{
        if(noAtual->esquerda == NULL){
            NoSegmento *temp = noAtual->direita;
            free(noAtual);
            return temp;
        } else if(noAtual->direita == NULL){
            NoSegmento *temp = noAtual->esquerda;
            free(noAtual);
            return temp;
        }
        NoSegmento* temp = noMinimo(noAtual->direita);
        noAtual->seg = temp->seg;
        noAtual->direita = removerRecursivo(noAtual->direita, temp->seg, xBomba, yBomba);
    }
    return noAtual;
}

void removerSegmentoArvore(Arvore arvore, Segmento seg){
    ARVOREA* arv = (ARVOREA*) arvore;
    if(arv == NULL){
        return;
    }  
    if(arv) arv->raiz = removerRecursivo(arv->raiz, seg, arv->xBomba, arv->yBomba);
}

Segmento getSegMaisProx(Arvore arvore){
    ARVOREA* arv = (ARVOREA*) arvore;
    if(arv == NULL || arv->raiz == NULL){
        return NULL;
    }
    NoSegmento *atual = arv->raiz;
    while(atual->esquerda != NULL) atual = atual->esquerda;
    return atual->seg;
}