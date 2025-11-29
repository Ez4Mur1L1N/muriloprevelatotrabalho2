#ifndef SORT_H
#define SORT_H

#include "lista.h"

/*
TAD responsável por armazenar e ordenar(!) os vértices dos segmentos.
*/

typedef void* VetorVertices;

/**
 * @brief Função que cria um vetor de vértices a partir da lista de segmentos.
 * Calcula, automaticamente, o ângulo de cada vértice em relação à bomba.
 * 
 * @param listaSegmentos Ponteiro para a lista de segmentos.
 * @param xBomba Coordenada 'X' do centro de ordenação (bomba).
 * @param yBomba Coordenada 'Y' do centro de ordenação (bomba).
 * @return Ponteiro para o vetor criado.
 * 
 * @warning Caso dê erro de alocação de memória, o programa encerra.
 */
VetorVertices criarVetorVertices(Lista listaSegmentos, double xBomba, double yBomba);

/**
 * @brief Função que vai ordenar o vetor de vértices utilizando o algoritmo merge (com a otimização do insertion).
 * 
 * @param vetor Ponteiro para o vetor.
 * @param limitInsertion valor para se usar o Insertion sort (parâmetro -i)
 */
void mergeSortVertices(VetorVertices vetor, int limitInsertion);

/**
 * @brief Função que libera toda a memória alocada para o vetor.
 *
 * @param vetor Ponteiro do vetor a ser destruído.
 */
void killVetorVertices(VetorVertices vetor); 

// Funções GETs para o vetor.

/**
 * @brief Função que 'pega' o tamanho do nosso vetor de vértices
 * 
 * @param vetor Ponteiro do vetor analisado.
 * 
 * @return Inteiro que representa o tamanho do vetor. 
 */
int getTamanhoVetor(VetorVertices vetor);

/**
 * @brief Função que 'pega' a coordenada 'X' de um vértice específico do vetor.
 * 
 * @param vetor Ponteiro do vetor analisado.
 * @param indice indíce do elemento desejado do vetor.
 * 
 * @return Double que representa a coordenada 'X'.
 */
double getXVertice(VetorVertices vetor, int indice);

/**
 * @brief Função que 'pega' a coordenada 'Y' de um vértice específico do vetor.
 * 
 * @param vetor Ponteiro do vetor analisado.
 * @param indice indíce do elemento desejado do vetor.
 * 
 * @return Double que representa a coordenada 'Y'.
 */
double getYVertice(VetorVertices vetor, int indice);

/**
 * @brief Função que 'pega' o ângulo de um vértice específico do vetor.
 * 
 * @param vetor Ponteiro do vetor analisado.
 * @param indice indíce do elemento desejado do vetor.
 * 
 * @return Double que representa o ângulo'.
 */
double getAnguloVertice(VetorVertices vetor, int indice);

/**
 * @brief Função que 'pega' o ID do segmento que originou o vértice.
 * 
 * @param vetor Ponteiro do vetor analisado.
 * @param indice indíce do elemento desejado do vetor.
 * 
 * @return Inteiro que representa o ID.
 */
int getIdSegVertice(VetorVertices vetor, int indice);

/**
 * @brief Função que identifica se é o início ou não do segmento.
 * 
 * @param vetor Ponteiro do vetor analisado.
 * @param indice indíce do elemento desejado do vetor.
 * 
 * @return 1-Inicio//0-Fim.
 */
int getInicioVertice(VetorVertices vetor, int indice);

#endif