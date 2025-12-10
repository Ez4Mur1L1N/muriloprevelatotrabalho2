#ifndef VISIBILIDADE_H
#define VISIBILIDADE_H

#include "lista.h"
#include "segmento.h"

/*
TAD para representar a área visível de uma bomba, o qual
é determinado através de um algoritmo de varredura. 
*/

/**
 * @brief 
 * 
 * @param listaSegmentos Lista de todos os segmentos que bloqueiam a visão (anteparos).
 * @param listaFormas Lista das formas geométricas.
 * @param xBomba Coordenada 'X' do centro da bomba.
 * @param yBomba Coordenada 'Y' do centro da bomba.
 * @param metodoOrd String que define o algoritmo de ordenação.
 * @param limitInsertion Limite para o uso do Insertion Sort (caso o Merge seja escolhido).
 * @param tipoBomba String que define o tipo da bomba ('d', 'p', 'cln').
 * @param sfx Sufixo para desenhar a região de visibilidade em um novo arquivo.
 * @param dirSaidaO diretório para para a pasta onde os arquivos da saída serão designados.
 * @param nomeBase Ajuda na montagem do nome.
 * @param arqSvgPrincipal Caminho do Svg principal.
 * @param arqTxt Caminho completo para salvar o relatório .txt.
 * @param cor Cor para a bomba "p".
 * @param dx Deslocamento para a bomba de clonagem.
 * @param dy Deslocamento para a bomba de clonagem.
 */
void calcularVisibilidadeEProcessar(Lista listaSegmentos, Lista listaFormas, double xBomba, double yBomba, char *metodoOrd, int limitInsertion, char *tipoBomba, char *sfx, char *dirSaida, char*nomeBase, char *arqSvgPrincipal, FILE *arqTxt, char *cor, double dx, double dy);

#endif