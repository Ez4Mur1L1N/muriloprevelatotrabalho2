#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

typedef struct nos{
    Conteudo conteudo;
    struct nos *prox;
    struct nos *ant; 
} NOS;
//Lista ligada, por isso aponta para o próximo e o anterior!!

typedef NOS *NO;

typedef struct{
    NO inicio;
    NO fim;
    int tamanho;
} LISTAL;

Lista criarLista(){
    LISTAL* li = (LISTAL*) malloc(sizeof(LISTAL));
    if(li == NULL){
        printf("Erro ao alocar memoria! Programa encerrado.");
        exit(1);
    }

    li->inicio = NULL;
    li->fim = NULL;
    li->tamanho = 0;
    return li;
}

void killLista(Lista l, void (*destroiConteudo)(Conteudo c)){
    LISTAL* li = (LISTAL*) l;
    if(li == NULL){
        return;
    }

    NO atual = li->inicio;
    while(atual != NULL){ // Vai percorrer essa lista enquanto tiver algum conteudo.
        NO proximo = atual->prox;
        if(destroiConteudo != NULL){
            destroiConteudo(atual->conteudo);
        }
        free(atual);
        atual = proximo;
    }

    free(li);
}

No insereFinalLista(Lista l, Conteudo c){
    LISTAL* li = (LISTAL*) l;
    if(li == NULL){
        return NULL;
    }

    NO novo = (NO) malloc(sizeof(NOS));
    if(novo == NULL){
        printf("Erro ao alocar memoria! Programa encerrado.");
        exit(1);
    }

    novo->conteudo = c;
    novo->prox = NULL;
    novo->ant = li->fim;

    // Vamos trabalhar dois casos agora:
    // Lista não estava vazia:
    if(li->fim != NULL){
        li->fim->prox = novo;
    }
    li->fim = novo;
    // Lista vazia:
    if(li->inicio == NULL){
        li->inicio = novo;
    }

    li->tamanho++;
    return novo;
}

No insereNoComecoLista(Lista l, Conteudo c){
    LISTAL* li = (LISTAL*) l;
    if(li == NULL){
        return NULL; 
    }

    NO novo = (NO) malloc(sizeof(NOS));
    if(novo == NULL){
        printf("Erro ao alocar memoria para novo no! Programa encerrado.");
        exit(1);
    }

    novo->conteudo = c;
    novo->prox = li->inicio;
    novo->ant = NULL;      

    // Vamos trabalhar dois casos agora:
    // Lista não estava vazia:
    if(li->inicio != NULL){
        li->inicio->ant = novo; 
    }
    li->inicio = novo; 

    // Lista estava vazia:
    if(li->fim == NULL){
        li->fim = novo; 
    }

    li->tamanho++;
    return novo;
}

Conteudo removeNoLista(Lista l, No n){
    LISTAL* li = (LISTAL*) l;
    NO noLista = (NO) n;
    if(li == NULL || noLista == NULL){
        return NULL;
    }

        // Conecta o nó anterior com o próximo, "pulando" o nó a ser removido.
    if (noLista->ant != NULL) {
        noLista->ant->prox = noLista->prox;
    } else {
        // Se o anterior é nulo, então estamos removendo o primeiro elemento, desse modo só redefinimos o primeiro elemento para o próximo do nó.
        li->inicio = noLista->prox;
    }

    if (noLista->prox != NULL) {
        noLista->prox->ant = noLista->ant;
    } else {
        // Se o próximo é nulo, estamos removendo o último elemento.
        li->fim = noLista->ant;
    }

    Conteudo conteudoRemovido = noLista->conteudo;
    free(noLista);
    li->tamanho--;

    return conteudoRemovido;
}

No getPrimeiroNoLista(Lista l){
    LISTAL* li = (LISTAL*) l;
    if(li == NULL){
        return NULL;
    }
    return li->inicio;
}

int getTamanhoLista(Lista lista){
    LISTAL* li = (LISTAL*) lista;
    if(li == NULL){
        return -1;
    }
    return li->tamanho;
}

No getUltimoNoLista(Lista l){
    LISTAL* li = (LISTAL*) l;
    if(li == NULL){
        return NULL;
    }
    return li->fim;
}

No getProximoNoLista(No n){
    NO noLista = (NO) n;
    if(noLista == NULL){
        return NULL;
    }
    return noLista->prox;
}

Conteudo getConteudoNoLista(No n){
    NO noLista = (NO) n;
    if(noLista == NULL){
        return NULL;
    }
    return noLista->conteudo;
}