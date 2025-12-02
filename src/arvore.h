#ifndef ARVORE_H
#define ARVORE_H

#include "segmento.h"

/*
TAD da estrutura da Árvore que vai armazenar os segmentos ativos.
Segue-se uma regra básica: os menores valores ficam à esquerda e os
maiores a direita.
Dentro do contexto do projeto, um menor valor representa um obstáculo
mais próximo de uma bomba.
*/

typedef void* Arvore;
typedef void* NoArvore;

/**
 * @brief Função que cria uma árvore vazia.
 * 
 * @param xBomba Coordenada 'X' do centro da bomba.
 * @param yBomba Coordenada 'Y' do centro da bomba.
 * 
 * @return Ponteiro para a estrutura da árvore.
 * 
 * @warning Caso dê erro de alocação de memória, o programa encerra.
 */
Arvore criarArvore(double xBomba, double yBomba);

/**
 * @brief Função que libera toda memória alocada para a árvore.
 * 
 * @param Arvore Ponteiro da árvore a ser destruída.
 * 
 * @details Desaloca os nós, não os segmentos.
 */ 
void killArvore(Arvore arvore);

/**
 * @brief Função que insere um segmento na árvore.
 * **A posição é determinada pela distância do segmento ao centro.
 * 
 * @param Arvore Ponteiro para a árvore.
 * @param Segmento Ponteiro para o segmento a ser inserido.
 */
void inserirSegmentoArvore(Arvore arvore, Segmento seg);

/**
 * @brief Função que remove um segmento da árvore.
 * 
 * @param Arvore Ponteiro para a árvore.
 * @param Segmento Ponteiro para o segmento a ser removido.
 */
void removerSegmentoArvore(Arvore arvore, Segmento seg);

/**
 * @brief Função que pega o segmento que possui a menor distância em relação à bomba.
 * 
 * @param Arvore Ponteiro para a árvore.
 * 
 * @return Ponteiro para o segmento mais próximo.
 */
Segmento getSegMaisProx(Arvore arvore);

/**
 * @brief Função que verifica se a árvore está vazia (ou não).
 * 
 * @param Arvore Ponteiro para a árvore.
 * 
 * @return Inteiro: 1-Vazia/0-Possui algum elemento.
 */
int arvoreVazia(Arvore arvore);

#endif