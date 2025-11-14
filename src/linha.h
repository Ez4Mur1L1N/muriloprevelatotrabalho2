#ifndef LINHA_H
#define LINHA_H

#include "tipos.h"

/*
TAD que vai representar uma linha. Como proposto,
cada linha é definida por duas âncoras em suas extremidades.
Coordenadas para inicio (x1, y1) e final (x2, y2).
*/

typedef void* Linha;

/**
 * @brief Função que cria uma linha com os atributos indicados.
 * 
 * @param id Indica o ID da forma.
 * @param x1 Indica a coordenada "X" do início da linha.
 * @param y1 Indica a coordenada "Y" do início da linha.
 * @param x2 Indica a coordenada "X" do final da linha.
 * @param y2 Indica a coordenada "Y" do final da linha.
 * @param cor Indica a cor da linha.
 *
 * @return Retorna um ponteiro para a linha criada.
 *
 * @details Cria uma linha, inicializa seus atributos e retorna um ponteiro para ele.
 *
 * @warning Caso dê erro de alocação de memória, o programa encerra. 
 */
Linha criarLinha(int id, double x1, double y1, double x2, double y2, char *cor);

/**
 * @brief Função que libera toda memória alocada para a linha.
 * 
 * @param Linha Ponteiro da linha analisada.
 */
void killLinha(Linha l);

/**
 * @brief Função que 'pega' o ID da linha.
 * 
 * @param Linha Ponteiro da linha analisada.
 *
 * @return Um inteiro que representa o id da linha.
 */
int getIDLinha(Linha l);

/**
 * @brief Função que 'pega' o 'tipo' da linha.
 * 
 * @param Linha Ponteiro da linha analisada.
 *
 * @return Retorna a 'etiqueta' da forma.
 */
TipoForma getTipoLinha(Linha l); 

/**
 * @brief Função que 'pega' a coordenada 'X' (plano cartesiano) do início da linha.
 *
 * @param Linha Ponteiro da linha analisada.
 * 
 * @return Um double que representa a coordenada 'X' da forma na sua extremidade incial.
 */
double getX1Linha(Linha l);

/**
 * @brief Função que 'pega' a coordenada 'Y' (plano cartesiano) do início da linha.
 *
 * @param Linha Ponteiro da linha analisada.
 * 
 * @return Um double que representa a coordenada 'Y' da forma na sua extremidade incial.
 */
double getY1Linha(Linha l);

/**
 * @brief Função que 'pega' a coordenada 'X' (plano cartesiano) do final da linha.
 *
 * @param Linha Ponteiro da linha analisada.
 * 
 * @return Um double que representa a coordenada 'X' da forma na sua extremidade final.
 */
double getX2Linha(Linha l);

/**
 * @brief Função que 'pega' a coordenada 'Y' (plano cartesiano) do final da linha.
 *
 * @param Linha Ponteiro da linha analisada.
 * 
 * @return Um double que representa a coordenada 'Y' da forma na sua extremidade final.
 */
double getY2Linha(Linha l);

/**
 * @brief Função que 'pega' a cor da linha.
 * 
 * @param Linha Ponteiro da linha analisada.
 * 
 * @return Uma string com a cor da linha.  
 */
char *getCorLinha(Linha l);

/**
 * @brief Função que define uma nova coordenada para 'X1'.
 *
 * @param Linha Ponteiro da linha analisada.
 *
 * @param x1Novo Novo valor para a coordenada 'X1'.
 */
void setX1Linha(Linha l, double x1Novo);

/**
 * @brief Função que define uma nova coordenada para 'Y1'.
 *
 * @param Linha Ponteiro da linha analisada.
 *
 * @param y1Novo Novo valor para a coordenada 'Y1'.
 */
void setY1Linha(Linha l, double y1Novo);

/**
 * @brief Função que define uma nova coordenada para 'X2'.
 *
 * @param Linha Ponteiro da linha analisada.
 *
 * @param x2Novo Novo valor para a coordenada 'X2'.
 */
void setX2Linha(Linha l, double x2Novo);

/**
 * @brief Função que define uma nova coordenada para 'Y2'.
 *
 * @param Linha Ponteiro da linha analisada.
 *
 * @param y2Novo Novo valor para a coordenada 'Y2'.
 */
void setY2Linha(Linha l, double y2Novo);

/**
 * @brief Função que define uma nova cor para a linha.
 *
 * @param Linha Ponteiro da linha analisada.
 *
 * @param corNova Nova cor para a linha.
 */
void setCorLinha(Linha l, char *corNova);

/**
 * @brief Função que clona uma linha.
 * 
 * @param Linha Ponteiro da linha original analisada. 
 * @param IDnovo Novo ID (único) para o clone.
 *  
 * @return Ponteiro para a nova forma clonada. 
 */
Linha clonarLinha(Linha l, int IDnovo);

#endif