#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "sort.h"
#include "segmento.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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
        while(j >= esquerda && (vet[j].angulo > chave.angulo || (fabs(vet[j].angulo - chave.angulo) < 1e-9 && vet[j].inicio < chave.inicio))){
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
        int escolheE = 0;
        if(E[i].angulo < D[j].angulo) escolheE = 1;
        else if (E[i].angulo > D[j].angulo) escolheE = 0;
        else {
            if(E[i].inicio >= D[j].inicio) escolheE = 1;
            else escolheE = 0;
        }

        if(escolheE){
            vet[k] = E[i]; i++;
        } else{
            vet[k] = D[j]; j++;
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

    // 1. Compara Ângulos
    if(v1->angulo < v2->angulo) return -1;
    if(v1->angulo > v2->angulo) return 1;

    // Isso garante que a nova parede entra antes da velha sair, evitando buracos.
    if (v1->inicio > v2->inicio) return -1; 
    if (v1->inicio < v2->inicio) return 1;
    
    return 0;
}

// Funções públicas.

VetorVertices criarVetorVertices(Lista listaSegmentos, double xBomba, double yBomba) {
    vetorVERTICES* vetor = (vetorVERTICES*) malloc(sizeof(vetorVERTICES));
    if(vetor == NULL){
        printf("Erro ao alocar memoria! Programa encerrado.");
        exit(1);
    }

    int qtdSegmentos = getTamanhoLista(listaSegmentos);
    vetor->qtd = qtdSegmentos * 4; 
    vetor->array = (Vertice*) malloc(vetor->qtd * sizeof(Vertice));

    No no = getPrimeiroNoLista(listaSegmentos);
    int i = 0;

    while (no != NULL) {
        Segmento s = (Segmento) getConteudoNoLista(no);
        
        double x1 = getX1Segmento(s);
        double y1 = getY1Segmento(s);
        double x2 = getX2Segmento(s);
        double y2 = getY2Segmento(s);
        int id = getIDSegmento(s);

        double ang1 = atan2(y1 - yBomba, x1 - xBomba);
        double ang2 = atan2(y2 - yBomba, x2 - xBomba);

        if (ang1 < 0) ang1 += 2 * M_PI;
        if (ang2 < 0) ang2 += 2 * M_PI;
        
        double diferenca = ang2 - ang1;
        
        if (diferenca > M_PI) diferenca -= 2 * M_PI;
        else if (diferenca < -M_PI) diferenca += 2 * M_PI;
        
        double angStart, angEnd;
        double xStart, yStart, xEnd, yEnd;

        if (diferenca > 0) {
            angStart = ang1; xStart = x1; yStart = y1;
            angEnd = ang2;   xEnd = x2;   yEnd = y2;
        } else {
            angStart = ang2; xStart = x2; yStart = y2;
            angEnd = ang1;   xEnd = x1;   yEnd = y1;
        }

        // Caso ESPECIAL: Segmento cruza o zero
        if (angStart > angEnd) {
            
            // Calcula o ponto exato onde o segmento corta o eixo X da bomba (y = yBomba)
            double xCorte;
            if (fabs(yStart - yEnd) > 1e-9) {
                 xCorte = xStart + (yBomba - yStart) * ((xEnd - xStart) / (yEnd - yStart));
            } else {
                 xCorte = xStart; 
            }

            // --- Parte 1: Do Start até 2PI ---
            vetor->array[i].x = xStart; 
            vetor->array[i].y = yStart;
            vetor->array[i].angulo = angStart; 
            vetor->array[i].IdSegmento = id; 
            vetor->array[i].inicio = 1; 
            i++;
    
            // FIM virtual em 2PI (usando xCorte)
            vetor->array[i].x = xCorte; 
            vetor->array[i].y = yBomba;       
            vetor->array[i].angulo = 2 * M_PI; 
            vetor->array[i].IdSegmento = id; 
            vetor->array[i].inicio = 0; 
            i++;

            // --- Parte 2: De 0 até End ---
            // INÍCIO virtual em 0 (usando xCorte)
            vetor->array[i].x = xCorte; 
            vetor->array[i].y = yBomba;          
            vetor->array[i].angulo = 0.0; 
            vetor->array[i].IdSegmento = id; 
            vetor->array[i].inicio = 1; 
            i++;
                
            vetor->array[i].x = xEnd; 
            vetor->array[i].y = yEnd;
            vetor->array[i].angulo = angEnd; 
            vetor->array[i].IdSegmento = id; 
            vetor->array[i].inicio = 0; 
            i++;

        } else {
            // Caso NORMAL
            vetor->array[i].x = xStart; vetor->array[i].y = yStart;
            vetor->array[i].angulo = angStart; vetor->array[i].IdSegmento = id; vetor->array[i].inicio = 1; 
            i++;

            vetor->array[i].x = xEnd; vetor->array[i].y = yEnd;
            vetor->array[i].angulo = angEnd; vetor->array[i].IdSegmento = id; vetor->array[i].inicio = 0; 
            i++;
        }

        no = getProximoNoLista(no);
    }
    
    vetor->qtd = i; 
    return (VetorVertices) vetor;
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