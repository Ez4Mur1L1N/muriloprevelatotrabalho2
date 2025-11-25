#ifndef LEITORGEO_H
#define LEITORGEO_H

/*
TAD que será utilizado para leitura e processamento do arquivo .geo.
Esse TAD, basicamente, será capaz de ler os comandos .geo e, dessa maneira,
inicializar as formas e seus respectivos atributos.
As formas serão guardadas numa lista genérica que será usada em outros momentos do projeto.
*/

typedef void* ListaFormas;

/**
 * @brief Função que lê um arquivo .geo e cria todas as formas que ele indica.
 * 
 * @param caminhoAqrGeo Nome do arquivo .geo a ser lido (diretório). 
 * 
 * @return Um ponteiro para a lista génerica com todas as formas criadas.
 *
 * @warning Caso o programa não consiga abrir o arquivo, encerra ele 'exit(1).
 */
ListaFormas lerArqGeo(char *caminhoAqrGeo);

/**
 * @brief Função que libera a memória dessa lista genérica, desassociando cada elemento.
 * 
 * @param lst Ponteiro para a lista genérica analisada.
 */
void killListaFormasGeo(ListaFormas lst);

#endif