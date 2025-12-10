#ifndef RETANGULO_H
#define RETANGULO_H

#include "tipos.h"

/*
TAD que vai representar a forma geométrica do retângulo.
A coordenada âncora dessa forma é seu canto inferior esquerdo (x,y) e suas
dimensões são definidas pelo altura (h) e largura (w)

*/

typedef void* Retangulo;

/**
 * @brief Função que cria um retângulo com os atributos indicados.
 *
 * @param id Indica o "ID" da forma geométrica.
 * @param x Indica a coordenada X (plano cartesiano) do canto inferior esquerdo do retângulo. 
 * @param y Indica a coordenada Y (plano cartesiano) do canto inferior esquerdo do retângulo.
 * @param h Indica a altura do retângulo.
 * @param w Indica a largura do retângulo.
 * @param corB Indica a cor da borda do retângulo.
 * @param corP Indica a cor do preenchimento do retângulo.
 *
 * @return Retorna o ponteiro para o retângulo criado.
 *
 * @details Cria um retângulo, inicializa seus atributos e retorna um ponteiro para ele.
 *
 * @warning Caso dê erro de alocação de memória, o programa encerra.
 */
Retangulo criarRetangulo(int id, double x, double y, double h, double w, char *corB, char *corP);

/**
 * @brief Função que libera toda a memória alocada para o retângulo.
 *
 * @param Retangulo Ponteiro do retângulo a ser destruído.
 */
void killRetangulo(Retangulo r); 

/**
 * @brief Função que 'pega' o ID do retângulo.
 *
 * @param Retangulo Ponteiro do retângulo analisado.
 * 
 * @return Um inteiro que representa o id da forma.
 */
int getIDRetangulo(Retangulo r);

/**
 * @brief Função que 'pega' o 'tipo' do retângulo.
 * 
 * @param Retangulo Ponteiro do retângulo analisado.
 *
 * @return Retorna a 'etiqueta' da forma.
 */
TipoForma getTipoRetangulo(Retangulo r); 

/**
 * @brief Função que 'pega' a coordenada 'X' (plano cartesiano) do retângulo.
 *
 * @param Retangulo Ponteiro do retângulo analisado.
 * 
 * @return Um double que representa a coordenada 'X' da forma.
 */
double getXRetangulo(Retangulo r);

/**
 * @brief Função que 'pega' a coordenada 'Y' (plano cartesiano) do retângulo.
 *
 * @param Retangulo Ponteiro do retângulo analisado.
 * 
 * @return Um double que representa a coordenada 'Y' da forma.
 */
double getYRetangulo(Retangulo r);

/**
 * @brief Função que 'pega' a altura do retângulo.
 *
 * @param Retangulo Ponteiro do retângulo analisado.
 * 
 * @return Um double que representa o tamanho da altura da forma.
 */
double getHRetangulo(Retangulo r);

/**
 * @brief Função que 'pega' a largura do retângulo.
 *
 * @param Retangulo Ponteiro do retângulo analisado.
 * 
 * @return Um double que representa o comprimento da largura da forma.
 */
double getWRetangulo(Retangulo r);

/**
 * @brief Função que 'pega' a cor da borda do retângulo.
 * 
 * @param Retangulo Ponteiro do retângulo analisado.
 * 
 * @return Uma string com a cor da borda da forma.  
 */
char *getCorBRetangulo(Retangulo r);

/**
 * @brief Função quen'pega' a cor de preenchimento do retângulo.
 * 
 * @param Retangulo Ponteiro do retângulo analisado.
 * 
 * @return Uma string com a cor de preenchimento da forma.  
 */
char *getCorPRetangulo(Retangulo r);

/**
 * @brief Função que define uma nova coordenada para 'X'.
 *
 * @param Retangulo Ponteiro do retângulo analisado.
 *
 * @param xNovo Novo valor para a coordenada 'X'.
 */
void setXRetangulo(Retangulo r, double xNovo);

/**
 * @brief Função que define uma nova coordenada para 'Y'.
 *
 * @param Retangulo Ponteiro do retângulo analisado.
 *
 * @param yNovo Novo valor para a coordenada 'Y'.
 */
void setYRetangulo(Retangulo r, double yNovo);

/**
 * @brief Função que define uma nova cor para a borda do retângulo.
 *
 * @param Retangulo Ponteiro do retângulo analisado.
 *
 * @param corBNova Nova cor para a borda do retângulo.
 */
void setCorBRetangulo(Retangulo r, char *corBNova);

/**
 * @brief Função que define uma nova cor para o preenchimento do retângulo.
 *
 * @param Retangulo Ponteiro do retângulo analisado.
 *
 * @param corPNova Nova cor para o preenchimento do retângulo.
 */
void setCorPRetangulo(Retangulo r, char *corPNova);

/**
 * @brief Função que clona um retângulo.
 * 
 * @param Retangulo Ponteiro do retângulo original analisado. 
 * @param IDnovo Novo ID (único) para o clone.
 * @param dx Deslocamento no eixo x.
 * @param dy Deslocamento no eixo y.
 *  
 * @return Ponteiro para a nova forma clonada. 
 */
Retangulo clonarRetangulo(Retangulo r, int IDnovo, double dx, double dy);

#endif