#ifndef FORMAS_H
#define FORMAS_H

#include "tipos.h" 

/*
TAD que vai ajudar na representação das formas, permitindo um acesso mais claro.
*/

/**
 * @brief Função que obtém a coordenada X da âncora de uma forma genérica.
 * 
 * @param forma Ponteiro genérico para a forma.
 * @param tipo Etiqueta para o tipo da forma.
 * 
 * @return Double que representa a coordenada 'X' da forma.
 */
double getAncoraXForma(void* forma, TipoForma tipo);

/**
 * @brief Função que obtém a coordenada Y da âncora de uma forma genérica.
 * 
 * @param forma Ponteiro genérico para a forma.
 * @param tipo Etiqueta para o tipo da forma.
 * 
 * @return Double que representa a coordenada 'Y' da forma.
 */
double getAncoraYForma(void* forma, TipoForma tipo);

/**
 * @brief Função que define uma cor (de preenchimento) nova para uma forma.
 * 
 * @param forma Ponteiro genérico para a forma.
 * @param tipo Etiqueta para o tipo da forma.
 * @param cor String da cor.
 */
void setCorPreenchimentoGenerica(void* forma, TipoForma tipo, char* cor);

/**
 * @brief Função que define uma cor (de borda) nova para uma forma.
 * 
 * @param forma Ponteiro genérico para a forma.
 * @param tipo Etiqueta para o tipo da forma.
 * @param cor String da cor.
 */
void setCorBordaGenerica(void* forma, TipoForma tipo, char* cor);

/**
 * @brief Função que libera a memória alocada para uma forma genérica.
 * 
 * @param forma Ponteiro genérico para a forma.
 * @param tipo Etiqueta para o tipo da forma.
 */
void killFormaGenerica(void* forma, TipoForma tipo);

/**
 * @brief Função que clona uma forma e aplica um deslocamento (dx, dy).
 * 
 * @param forma Ponteiro genérico para a forma.
 * @param tipo Etiqueta para o tipo da forma.
 * @param dx Deslocamento no eixo x.
 * @param dy Deslocamento no eixo y.
 */
void* clonarFormaGenerica(void* forma, TipoForma tipo, double dx, double dy);

#endif