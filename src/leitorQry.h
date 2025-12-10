#ifndef LEITORQRY_H
#define LEITORQRY_H

#include "lista.h"

/*
TAD responsável pela leitura e processamento do arquivo de consultas (.qry).
Comandos suportados:
- a: Transforma formas em segmentos (anteparos).
- d: Bomba de Destruição (calcula visibilidade e remove).
- p: Bomba de Pintura (calcula visibilidade e altera cor das formas dentro da região).
- cln: Bomba de Clonagem (calcula visibilidade e clona/move).
*/

typedef void* ListaFormas; 

/**
 * @brief 
 * 
 * @param formas A lista original de formas (Círculos, Retângulos, etc).
 * @param caminhoQry Caminho completo do arquivo .qry.
 * @param caminhoTxt Caminho completo para salvar o relatório .txt.
 * @param dirSaidaO Diretório para para a pasta onde os arquivos da saída serão designados
 * @param nomeBaseGeo Ajuda na montagem dos caminhos para a saída.
 * @param arqSvgPrincipal caminho do svg principal.
 * @param metodoOrd String do algoritmo de ordenação que vai ser usado.
 * @param limitInsertion Limite para o uso do insertion sort.
 */
void lerArqQry(ListaFormas formas, char* caminhoQry, char* caminhoTxt, char* dirSaida, char* nomeBaseGeo, char* arqSvgPrincipal, char* metodoOrd, int limitInsertion);

#endif