#ifndef TEXTO_H
#define TEXTO_H

#include "tipos.h"

/*
TAD que vai representar um texto. Deve-se ressaltar que a representação desse texto
se dará dentro de um plano bidimensional.
Além disso, reitera-se que o texto pode ter sua coordenada âncora 
tanto no início, como no meio ou no final.
Esse TAD também guardará algumas informações estilísticas.
*/

typedef void* Texto;

/**
 * @brief 
 * 
 * @param id Indica o ID da forma.
 * @param x Indica a coordenada 'X' da âncora do texto.
 * @param y Indica a coordenada 'Y' da âncora do texto.
 * @param corB Indica a cor da borda do texto.
 * @param corP Indica a cor de preenchimento do texto.
 * @param a Indica a posição da coordenada âncora (inicio/meio/final).
 * @param texto Indica a mensagem em si.
 * @param fFamily Indica a família da fonte do texto;
 * @param fWeight Indica o 'peso' da fonte do texto.
 * @param fSize Indica o tamanho da fonte do texto.
 *
 * @return Retorna um ponteiro para o texto criado.
 *
 * @warning Caso dê erro de alocação de memória, o programa encerra.
 */
Texto criarTexto(int id, double x, double y, char *corB, char *corP, char* a, char *texto, char *fFamily, char *fWeight, char *fSize);

/**
 * @brief Função que libera toda memória alocada para o texto.
 * 
 * @param Texto Ponteiro do texto analisado.
 */
void killTexto(Texto t);

/**
 * @brief Função que 'pega' o ID do texto.
 * 
 * @param Texto Ponteiro do texto analisado.
 *
 * @return Um inteiro que representa o id do texto.
 */
int getIDTexto(Texto t);

/**
 * @brief Função que 'pega' o 'tipo' do texto.
 * 
 * @param Texto Ponteiro do texto analisado.
 *
 * @return Retorna a 'etiqueta' da forma.
 */
TipoForma getTipoTexto(Texto t); 

/**
 * @brief Função que 'pega' a coordenada âncora 'X' do texto.
 * 
 * @param Texto Ponteiro do texto analisado.
 *
 * @return Um double que representa a coordenada 'X' da âncora do texto.
 */
double getXTexto(Texto t);

/**
 * @brief Função que 'pega' a coordenada âncora 'Y' do texto.
 * 
 * @param Texto Ponteiro do texto analisado.
 *
 * @return Um double que representa a coordenada 'Y' da âncora do texto.
 */
double getYTexto(Texto t);

/**
 * @brief Função que 'pega' a cor de borda do texto.
 * 
 * @param Texto Ponteiro do texto analisado.
 *
 * @return Uma string que representa a cor de borda do texto.
 */
char *getCorBTexto(Texto t);

/**
 * @brief Função que 'pega' a cor de preenchimento do texto.
 * 
 * @param Texto Ponteiro do texto analisado.
 *
 * @return Uma string que representa a cor de preenchimento do texto.
 */
char *getCorPTexto(Texto t);

/**
 * @brief Função que 'pega' a âncora do texto.
 * 
 * @param Texto Ponteiro do texto analisado.
 *
 * @return Um char que representa a posição da coordenada âncora.
 */
char *getAncoraTexto(Texto t);

/**
 * @brief Função que 'pega' o texto em si (mensagem).
 * 
 * @param Texto Ponteiro do texto analisado.
 *
 * @return Uma string que representa o texto em si (mensagem).
 */
char *getTexto_Texto(Texto t);

/**
 * @brief Função que 'pega' a família da fonte do texto.
 * 
 * @param Texto Ponteiro do texto analisado.
 *
 * @return Uma string que representa a família da fonte do texto.
 */
char *getFontFamilyTexto(Texto t);

/**
 * @brief Função que 'pega' o 'peso' da fonte do texto.
 * 
 * @param Texto Ponteiro do texto analisado.
 *
 * @return Uma string que representa o 'peso' da fonte do texto.
 */
char *getFontWeightTexto(Texto t);

/**
 * @brief Função que 'pega' o tamanho da fonte do texto.
 * 
 * @param Texto Ponteiro do texto analisado.
 *
 * @return Uma string que representa o tamanho da fonte do texto.
 */
char *getFontSizeTexto(Texto t);

/**
 * @brief Função que define uma nova coordenada âncora 'X' do texto.
 *  * @param t Ponteiro do texto analisado.
 *
 * @param xNovo Novo valor para a coordenada âncora 'X' do texto.
 */
void setXTexto(Texto t, double xNovo);

/**
 * @brief Função que define uma nova coordenada âncora 'Y' do texto.
 *  * @param t Ponteiro do texto analisado.
 *
 * @param yNovo Novo valor para a coordenada âncora 'Y' do texto.
 */
void setYTexto(Texto t, double yNovo);

/**
 * @brief Função que define uma nova cor de borda do texto.
 * @param t Ponteiro do texto analisado.
 * @param corBNova Nova cor de borda do texto.
 */
void setCorBTexto(Texto t, char *corBNova);

/**
 * @brief Função que define uma nova cor de preenchimento do texto.
 * @param t Ponteiro do texto analisado.
 * @param corPNova Nova cor de preenchimento do texto.
 */
void setCorPTexto(Texto t, char *corPNova);

/**
 * @brief Função que clona um texto.
 * 
 * @param Linha Ponteiro do texto original analisado. 
 * @param IDnovo Novo ID (único) para o clone.
 *  
 * @return Ponteiro para a nova forma clonada. 
 */
Texto clonarTexto(Texto t, int IDnovo);

#endif