#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "sort.h"
#include "segmento.h"

typedef struct{
    double x;
    double y;
    double angulo;
    int IdSegmento;
    int inicio; // 1-início, 0-fim.
} Vertice;

typedef struct{
    Vertice* array; 
    int qtd;
} vetorVERTICES;

// Funções auxiliares.

//INSERTION SORT
void insertionSort(Vertice* vet, int esquerda, int direita){
    for(int i = esquerda + 1; i <= direita; i++){
        Vertice chave = vet[i];
        int j = i - 1;
        //Comparando os ângulos.
        while(j >= esquerda && vet[j].angulo > chave.angulo){
            vet[j + 1] =  vet[j];
            j--;
        }
        vet[j + 1] = chave;
    }
}

void merge(Vertice* vet, int esquerda, int meio, int direita){
    int n1 = meio - esquerda + 1;
    int n2 = direita - meio;

    Vertice* E = (Vertice*) malloc(n1 * sizeof(Vertice));
    Vertice* D = (Vertice*) malloc(n2 * sizeof(Vertice));

    if(E == NULL || D == NULL){
        printf("Erro ao alocar memoria (funcao merge)!\n");
        free(E);
        free(D);
        exit(1);
    }

    for(int i = 0; i < n1; i++) E[i] = vet[esquerda + i];
    for(int j = 0; j < n2; j++) D[j] = vet[meio + 1 + j];

    int i = 0, j = 0, k = esquerda;
    while(i < n1 && j < n2){
        // Menor ângulo vem primeiro.
        if(E[i].angulo <= D[j].angulo){
            vet[k] = E[i];
            i++;
        } else{
            vet[k] = D[j];
            j++;
        }
        k++;
    }

    while(i < n1) { vet[k] = E[i]; i++; k++;}
    while(j < n2) { vet[k] = D[j]; j++; k++;}

    free(E);
    free(D);
}

// Recursivo.

void mergeSortRecursivo(Vertice *vet, int esquerda, int direita, int limitInsertion){
    if(esquerda < direita){
        //Se o tamanho do subvetor for menor que o limite, usa o Insertion Sort.
        if((direita - esquerda + 1) <= limitInsertion) {
            insertionSort(vet, esquerda, direita);
        } else{
            int meio = esquerda + (direita - esquerda) / 2;
            mergeSortRecursivo(vet, esquerda, meio, limitInsertion);
            mergeSortRecursivo(vet, meio+1, direita, limitInsertion);
            merge(vet, esquerda, meio , direita);
        }
    }
}

// Função de comparação do QuickSort

int compararQuickSort(const void *a, const void *b){
    Vertice* v1 = (Vertice*) a;
    Vertice* v2 = (Vertice*) b;

    if(v1->angulo < v2->angulo) return -1;
    if(v1->angulo > v2->angulo) return 1;
    return 0;
}

// Funções públicas.

VetorVertices criarVetorVertices(Lista listaSegmentos, double xBomba, double yBomba){
    vetorVERTICES* v = (vetorVERTICES*) malloc(sizeof(vetorVERTICES));
    if(v == NULL){
        printf("Erro ao alocar memoria! Programa encerrado.");
        exit(1);
    }

    int qtdSeg = getTamanhoLista(listaSegmentos);
    if(qtdSeg < 0) qtdSeg = 0; // Como mecanismo de segurança, meu .c de lista retorna -1 em alguns casos.
    // Esse if trata isso.

    v->qtd = qtdSeg*2; // 2 vértices por segmento.

    if(v->qtd > 0){
        v->array = (Vertice*) malloc(v->qtd * sizeof(Vertice));
    } else{
        v->array = NULL;
    }

    No no = getPrimeiroNoLista(listaSegmentos);
    int i = 0;
    while(no != NULL){
        Segmento s = (Segmento)getConteudoNoLista(no);

        double x1 = getX1Segmento(s);
        double y1 = getY1Segmento(s);
        double x2 = getX2Segmento(s);
        double y2 = getY2Segmento(s);
        int id = getIDSegmento(s);

        double ang1 = atan2(y1 - yBomba, x1 - xBomba); // atan2 função da biblioteca math.h que ajuda nesses cálculo de ângulos;
        double ang2 = atan2(y2 - yBomba, x2 - xBomba);

        v->array[i].x = x1;
        v->array[i].y = y1;
        v->array[i].IdSegmento = id;
        v->array[i].angulo = ang1;

        v->array[i+1].x = x2;
        v->array[i+1].y = y2;
        v->array[i+1].IdSegmento = id;
        v->array[i+1].angulo = ang2;

        if(ang1<ang2){
            v->array[i].inicio = 1;
            v->array[i+1].inicio = 0;
        } else{
            v->array[i].inicio = 0;
            v->array[i+1].inicio = 1;
        }

        i += 2;
        no = getProximoNoLista(no);
    }

    return (VetorVertices) v;
}

void ordenarVertices(VetorVertices vetor, char *metodo, int limitInsertion) {
    vetorVERTICES* v = (vetorVERTICES*) vetor;
    if (v == NULL || v->array == NULL || v->qtd <= 1){
        return;
    } 
    // Verifica se o método é "m" (Merge) ou "q" (Quick, padrão dentro da convenção do projeto).
    if(strcmp(metodo, "m") == 0){
        mergeSortRecursivo(v->array, 0, v->qtd - 1, limitInsertion);
    } else{
        qsort(v->array, v->qtd, sizeof(Vertice), compararQuickSort);
    }
}

void killVetorVertices(VetorVertices vetor){
    vetorVERTICES* v = (vetorVERTICES*) vetor;
    if(v != NULL){
        if(v->array != NULL) free(v->array);
        free(v);    
    }
}

int getTamanhoVetor(VetorVertices vetor){
    vetorVERTICES* v = (vetorVERTICES*) vetor;
    if(v == NULL){
        return -1;
    }
    return v->qtd;
}

double getXVertice(VetorVertices vetor, int indice){
    vetorVERTICES* v = (vetorVERTICES*) vetor;
    if(v == NULL){
        return 0.0;
    }
    return v->array[indice].x;
}

double getYVertice(VetorVertices vetor, int indice){
    vetorVERTICES* v = (vetorVERTICES*) vetor;
    if(v == NULL){
        return 0.0;
    }
    return v->array[indice].y;
}

double getAnguloVertice(VetorVertices vetor, int indice){
    vetorVERTICES* v = (vetorVERTICES*) vetor;
    if(v == NULL){
        return 0.0;
    }
    return v->array[indice].angulo;
}

int getIdSegVertice(VetorVertices vetor, int indice){
    vetorVERTICES* v = (vetorVERTICES*) vetor;
    if(v == NULL){
        return -1;
    }
    return v->array[indice].IdSegmento;
}

int getInicioVertice(VetorVertices vetor, int indice){
    vetorVERTICES* v = (vetorVERTICES*) vetor;
    if(v == NULL){
        return -1;
    }
    return v->array[indice].inicio;
}