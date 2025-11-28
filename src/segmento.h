#ifndef SEGMENTO_H
#define SEGMENTO_H

typedef void* Segmento;

/*
TAD para a criação/inicialização de um segmento.
Objeto essencial para a lógica de transformação em anteparos:
linhas retas que bloqueiam a visão (região de visibilidade).
*/

/**
 * @brief Função que cria um segmento com os atributos indicados.
 * 
 * @param id Indica o ID da forma.
 * @param x1 Indica a coordenada "X" do início do segmento.
 * @param y1 Indica a coordenada "Y" do início do segmento.
 * @param x2 Indica a coordenada "X" do final do segmento.
 * @param y2 Indica a coordenada "Y" do final do segmento.
 *
 * @return Retorna um ponteiro para o segmento criada.
 *
 * @details Cria um segmento, inicializa seus atributos e retorna um ponteiro para ele.
 *
 * @warning Caso dê erro de alocação de memória, o programa encerra. 
 */
Segmento criarSegmento(int id, double x1, double y1, double x2, double y2);

/**
 * @brief Função que libera a memória alocada ao segmento.
 * 
 * @param Segmento Ponteiro para o segmento que deseja removido.
 */
void killSegmento(Segmento s);

/**
 * @brief Função que 'pega' o identificador do segmento.
 * 
 * @param Segmento Ponteiro para o segmento analisado. 
 * 
 * @return ID do segmento
 */
int getIDSegmento(Segmento s);

/**
 * @brief Função que 'pega' a coordenada 'X' (plano cartesiano) do início do segmento.
 *
 * @param Linha Ponteiro do segmento analisado.
 * 
 * @return Um double que representa a coordenada 'X' da forma na sua extremidade incial.
 */
double getX1Segmento(Segmento s);

/**
 * @brief Função que 'pega' a coordenada 'Y' (plano cartesiano) do início do segmento.
 *
 * @param Segmento Ponteiro da segmento analisado.
 * 
 * @return Um double que representa a coordenada 'Y' da forma na sua extremidade incial.
 */
double getY1Segmento(Segmento s);

/**
 * @brief Função que 'pega' a coordenada 'X' (plano cartesiano) do final do segmento.
 *
 * @param Segmento Ponteiro da segmento analisado.
 * 
 * @return Um double que representa a coordenada 'X' da forma na sua extremidade final.
 */
double getX2Segmento(Segmento s);

/**
 * @brief Função que 'pega' a coordenada 'Y' (plano cartesiano) do final do segmento.
 *
 * @param Segmento Ponteiro da segmento analisado.
 * 
 * @return Um double que representa a coordenada 'Y' da forma na sua extremidade final.
 */
double getY2Segmento(Segmento s);


#endif