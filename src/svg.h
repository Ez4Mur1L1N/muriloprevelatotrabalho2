#ifndef SVG_H
#define SVG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circulo.h"
#include "linha.h"
#include "retangulo.h"
#include "texto.h"
#include "lista.h"

/*
TAD que será utilizado para descrever as funcionalidades para a criação de um arquivo SVG.
Elucidando as formas expostas na descrição do projeto através de uma representação gráfica.
*/

/**
 * @brief Função que estabelece a tag SVG e determina o tamanho.
 * 
 * @param arqSVG Ponteiro para o arquivo SVG aberto.
 */
void abreSVG(FILE* arqSVG);

/**
 * @brief Função que estabelece a tag SVG de fechamento.
 * 
 * @param arqSVG Ponteiro para o arquivo SVG aberto.
 */
void fechaSVG(FILE* arqSVG);

/**
 * @brief Função que vai percorrer a lista de formas e chamará a função de desenho correta para cada item
 * 
 * @param arqSVG Ponteiro para o arquivo SVG aberto.
 * @param lst Ponteiro para a lista de formas.
 */
void processarListaSvg(FILE* arqSVG, Lista lst);

/**
 * @brief Função que desenha um círculo no arquivo SVG.
 * 
 * @param arqSVG Ponteiro para o arquivo SVG aberto.
 * @param Circulo O círculo que, factualmente, será desenhado.
 *
 * @details Usará as funções GETs do círculo para pegar as informações.
 */
void desenhaCirculoSVG(FILE* arqSVG, Circulo c);

/**
 * @brief Função que desenha uma linha no arquivo SVG.
 * 
 * @param arqSVG Ponteiro para o arquivo SVG aberto.
 * @param Linha A linha que, factualmente, será desenhada.
 *
 * @details Usará as funções GETs da linha para pegar as informações.
 */
void desenhaLinhaSVG(FILE* arqSVG, Linha l);

/**
 * @brief Função que desenha um retângulo no arquivo SVG.
 * 
 * @param arqSVG Ponteiro para o arquivo SVG aberto.
 * @param Retangulo O retângulo que, factualmente, será desenhado.
 *
 * @details Usará as funções GETs do retângulo para pegar as informações.
 */
void desenhaRetanguloSVG(FILE* arqSVG, Retangulo r);

/**
 * @brief Função que desenha um texto no arquivo SVG.
 * 
 * @param arqSVG Ponteiro para o arquivo SVG aberto.
 * @param Texto O texto que, factualmente, será desenhado.
 *
 * @details Usará as funções GETs do texto para pegar as informações.
 */
void desenhaTextoSVG(FILE* arqSVG, Texto t);

/**
 * @brief Função que desenha um polígono genérico no arquivo SVG a partir de uma lista de Pontos.
 * 
 * @param arqSVG Ponteiro para o arquivo SVG aberto.
 * @param listaPontos Lista que contém os pontos do polígono.
 * @param corPreenchimento Cor de preenchimento.
 * @param corContorno Cor de contorno.
 * @param opacidade Opacidade.
 */
void desenhaPoligonoSVG(FILE* arqSVG, Lista listaPontos, const char* corPreenchimento, const char* corContorno, double opacidade);


#endif