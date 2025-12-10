#ifndef CIRCULO_H
#define CIRCULO_H

#include "tipos.h"

/*
TAD que vai representar a forma geométrica do círculo.
A coordenada âncora dessa forma é seu centro (x,y) e sua
dimensão é definida pelo raio

*/

typedef void* Circulo;

/**
 * @brief Função que cria um círculo com os atributos indicados.
 *
 * @param id Indica o "ID" da forma geométrica.
 * @param x Indica a coordenada X (plano cartesiano) do centro do círculo. 
 * @param y Indica a coordenada Y (plano cartesiano) do centro do círculo.
 * @param r Indica o raio do círculo.
 * @param corB Indica a cor da borda do círculo.
 * @param corP Indica a cor do preenchimento do círculo.
 *
 * @return Retorna o ponteiro para o círculo criado.
 *
 * @details Cria um círculo, inicializa seus atributos e retorna um ponteiro para ele.
 * 
 * @warning Caso dê erro de alocação de memória, o programa encerra.
 */
Circulo criarCirculo(int id, double x, double y, double r, char *corB, char *corP);

/**
 * @brief Função que libera toda a memória alocada para o círculo.
 *
 * @param c Ponteiro do círculo a ser destruído.
 */
void killCirculo(Circulo c); 

/**
 * @brief Função que 'pega' o ID do círculo.
 *
 * @param Circulo Ponteiro do círculo analisado.
 *
 * @return Um inteiro que representa o id da forma.
 */
int getIDCirculo(Circulo c);

/**
 * @brief Função que 'pega' o 'tipo' do círculo.
 * 
 * @param Circulo Ponteiro do círculo analisado. 
 *
 * @return Retorna a 'etiqueta' da forma.
 */
TipoForma getTipoCirculo(Circulo c); 

/**
 * @brief Função que 'pega' a coordenada 'X' (plano cartesiano) do círculo.
 *
 * @param Circulo Ponteiro do círculo analisado.
 *
 * @return Um double que representa a coordenada 'X' da forma.
 */
double getXCirculo(Circulo c);

/**
 * @brief Função que 'pega' a coordenada 'Y' (plano cartesiano) do círculo.
 *
 * @param Circulo Ponteiro do círculo analisado.
 *  
 * @return Um double que representa a coordenada 'Y' da forma.
 */
double getYCirculo(Circulo c);

/**
 * @brief Função que 'pega' o raio do círculo.
 *
 * @param Circulo Ponteiro do círculo analisado.
 *  
 * @return Um double que representa a dimensão do raio da forma.
 */
double getRCirculo(Circulo c);

/**
 * @brief Função que 'pega' a cor da borda do círculo.
 *  
 * @param Circulo Ponteiro do círculo analisado.
 *  
 * @return Uma string com a cor da borda da forma.  
 */
char *getCorBCirculo(Circulo c);

/**
 * @brief Função quen'pega' a cor de preenchimento do círculo.
 *  
 * @param Circulo Ponteiro do círculo analisado.
 *  
 * @return Uma string com a cor de preenchimento da forma.  
 */
char *getCorPCirculo(Circulo c);

/**
 * @brief Função que define uma nova coordenada para 'X'.
 *
 * @param Circulo Ponteiro do círculo analisado.
 *
 * @param xNovo Novo valor para a coordenada 'X'.
 */
void setXCirculo(Circulo c, double xNovo);

/**
 * @brief Função que define uma nova coordenada para 'Y'.
 *
 * @param Circulo Ponteiro do círculo analisado.
 *
 * @param yNovo Novo valor para a coordenada 'Y'.
 */
void setYCirculo(Circulo c, double yNovo);

/**
 * @brief Função que define uma nova cor para a borda do círculo.
 *
 * @param Circulo Ponteiro do círculo analisado.
 *
 * @param corBNova Nova cor para a borda do círculo.
 */
void setCorBCirculo(Circulo c, char *corBNova);

/**
 * @brief Função que define uma nova cor para o preenchimento do círculo.
 *
 * @param Circulo Ponteiro do círculo analisado.
 *
 * @param corPNova Nova cor para o preenchimento do círculo.
 */
void setCorPCirculo(Circulo c, char *corPNova);

/**
 * @brief Função que clona um círculo
 * 
 * @param Circulo Ponteiro do círculo original analisado. 
 * @param IDnovo Novo ID (único) para o clone.
 * @param dx Deslocamento no eixo x.
 * @param dy Deslocamento no eixo y.
 *  
 * @return Ponteiro para a nova forma clonada. 
 */
Circulo clonarCirculo(Circulo c, int IDnovo, double dx, double dy);

#endif