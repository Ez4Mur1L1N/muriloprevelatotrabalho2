#ifndef LISTA_H
#define LISTA_H

/*
TAD de uma Lista Ligada.
Dentro do contexto do projeto, esse TAD será de suma importância pois auxiliará 
na manutenção das formas que estão definidas dentro do "chão". Isso possibilitará
um arranjo mais flexível e direto.
*/

typedef void* Lista;
typedef void* No; //Representa um nó da lista, a qual poderemos percorrer e manipular de acordo com o interrese.
typedef void* Conteudo; //a informação (conteúdo) de um nó.

/**
 * @brief Cria uma lista vazia.
 * 
 * @return Retorna um ponteiro para a lista criada.
 *
 * @warning Caso a alocacao de memoria dê errado, encerra o programa.
 */
Lista criarLista();

/**
 * @brief Libera a memória da lista.
 *
 * @param Lista Ponteiro da lista analisada.
 * @param destroiConteudo Ponteiro para uma função que esteja de acordo com o conteúdo
 * e é capaz de liberar a memoria dele também.
 * 
 * @warning Se for NULL, a informação não é liberada. Apenas os seus nós.
 */
void killLista(Lista l, void (*destroiConteudo)(Conteudo c));

/**
 * @brief Função que insere um elemento no final da lista.
 * 
 * @param Lista Ponteiro da lista analisada. 
 * @param Conteudo Ponteiro para o elemento(conteúdo) a ser inserido. 
 *
 * @return Retorna um ponteiro para o nó criado.
 */
No insereFinalLista(Lista l, Conteudo c);

/**
 * @brief Função que insere um novo elemento no início da lista.
 * 
 * @param lista Ponteiro da lista analisada.
 * @param Conteudo Ponteiro para o elemento(conteúdo) a ser inserido.
 * 
 * @return Retorna o ponteiro para o nó criado.
 */
No insereNoComecoLista(Lista lista, Conteudo c);

/**
 * @brief Função que remove um nó da lista.
 * 
 * @param Lista Ponteiro da lista analisada.
 * @param No Ponteiro para o nó que deseja ser removido.
 *
 * @return Ponteiro para o conteúdo do nó removido.
 */
Conteudo removeNoLista(Lista l, No n);

/**
 * @brief Função que retorna o primeiro nó da lista.
 * 
 * @param Lista Ponteiro da lista analisada.
 * 
 * @return Ponteiro para o primeiro nó.
 *
 * @warning Retorna NULL se estiver vazia. 
 */
No getPrimeiroNoLista(Lista l);

/**
 * @brief Função que obtém o número de elementos atualmente na lista.
 * 
 * @param lista Ponteiro da lista analisada.
 * 
 * @return O número de elementos (tamanho) da lista, ou -1 se a lista for inválida.
 */
int getTamanhoLista(Lista lista);

/**
 * @brief Função que retorna o último nó da lista.
 * 
 * @param Lista Ponteiro da lista analisada.
 * 
 * @return Ponteiro para o último nó.
 *
 * @warning Retorna NULL se estiver vazia. 
 */
No getUltimoNoLista(Lista l);

/**
 * @brief Função que retorna o próximo nó de uma lista em relação ao indicado.
 * 
 * @param No Ponteiro do nó analisada.
 * 
 * @return Ponteiro para o próximo nó em relação ao nó analisado.
 *
 * @warning Retorna NULL se estiver vazia. 
 */
No getProximoNoLista(No n);

/**
 * @brief Função que indica o conteúdo de um nó.
 * 
 * @param No Ponteiro do nó analisado.
 *
 * @return Ponteiro para o contéudo do nó analisado.
 */
Conteudo getConteudoNoLista(No n);

#endif