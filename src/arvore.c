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

double produtoVetorial(double x1, double y1, double x2, double y2, double x3, double y3){
    return (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
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

    // Correção: critério - virada à direita ou à esquerda!!!
    if(fabs(distA - distB) < 1e-9){
        double ax1 = getX1Segmento(segA), ay1 = getY1Segmento(segA);
        double ax2 = getX2Segmento(segA), ay2 = getY2Segmento(segA);
        double bx1 = getX1Segmento(segB), by1 = getY1Segmento(segB);
        double bx2 = getX2Segmento(segB), by2 = getY2Segmento(segB);

        double cx, cy; // Ponto Comum.
        double oxA, oyA; // Outro ponto de A.
        double oxB, oyB; // Outro ponto de B.
        int temComum = 0;

        // Verifica todas as 4 combinações possíveis de conexão
        if (fabs(ax1 - bx1) < 1e-9 && fabs(ay1 - by1) < 1e-9) { 
            cx=ax1; cy=ay1; oxA=ax2; oyA=ay2; oxB=bx2; oyB=by2; temComum=1;
        }
        else if (fabs(ax1 - bx2) < 1e-9 && fabs(ay1 - by2) < 1e-9) { 
            cx=ax1; cy=ay1; oxA=ax2; oyA=ay2; oxB=bx1; oyB=by1; temComum=1;
        }
        else if (fabs(ax2 - bx1) < 1e-9 && fabs(ay2 - by1) < 1e-9) { 
            cx=ax2; cy=ay2; oxA=ax1; oyA=ay1; oxB=bx2; oyB=by2; temComum=1;
        }
        else if (fabs(ax2 - bx2) < 1e-9 && fabs(ay2 - by2) < 1e-9) { 
            cx=ax2; cy=ay2; oxA=ax1; oyA=ay1; oxB=bx1; oyB=by1; temComum=1;
        }

        if (temComum) {
            // Produto Vetorial usando o vértice comum como pivô.
            // (V -> OutroB) em relação a (V -> OutroA),
            double valor = produtoVetorial(cx, cy, oxA, oyA, oxB, oyB);
            
            // Se valor > 0, B está à "esquerda" (sentido anti-horário) de A.
            if (valor > 0) return -1; // A é menor
            if (valor < 0) return 1;  // A é maior (B está à direita de A)
            return 0; // Colineares
        }
        
        // Aí sim, para distâncias iguais vou usar ID como último recurso de comparação.
        if(getIDSegmento(segA) < getIDSegmento(segB)) return -1;
        return 1;
    }

    if(distA < distB) return -1; // A mais próximo.
    return 1; // B mais próximo.
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