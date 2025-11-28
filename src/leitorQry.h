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
 * @brief Processa o arquivo .qry, executando as simulações de bombas.
 * 
 * @param formas A lista original de formas (Círculos, Retângulos, etc).
 * @param caminhoQry Caminho completo do arquivo .qry.
 * @param caminhoTxt Caminho completo para salvar o relatório .txt.
 * @param dirSaida Diretório para salvar os SVGs de visibilidade (***obs: quando sfx != "-").
 */
void lerArqQry(ListaFormas formas, char* caminhoQry, char* caminhoTxt, char* dirSaida);

#endif