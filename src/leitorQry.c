#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "leitorQry.h"
#include "lista.h"
#include "segmento.h"
#include "tipos.h"
#include "arvore.h"
#include "sort.h"
#include "svg.h"
#include "visibilidade.h"

#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "formas.h"

typedef struct{
    int id;
    TipoForma tipo;
} FormaGenericaQry;

// Função auxiliar para converter o enum em string do "tipo" (Relatório TXT).
const char* getNomeTipo(TipoForma t) {
    switch(t) {
        case CIRCULO: return "CIRCULO";
        case RETANGULO: return "RETANGULO";
        case LINHA: return "LINHA";
        case TEXTO: return "TEXTO";
        default: return "DESCONHECIDO";
    }
}

void lerArqQry(ListaFormas formas, char* caminhoQry, char* caminhoTxt, char* dirSaida, char* nomeBaseGeo, char* arqSvgPrincipal, char* metodoOrd, int limitInsertion){
    FILE* arqQry = fopen(caminhoQry, "r");
    if (arqQry == NULL) {
        printf("Nao foi possivel abrir o arquivo de consultas em %s!\n", caminhoQry);
        return;
    }
    FILE* arqTxt = fopen(caminhoTxt, "w");
    if (arqTxt == NULL) {
        printf("Nao foi possivel criar o arquivo de saida TXT em %s!\n", caminhoTxt);
        fclose(arqQry); 
        return;
    }

    Lista listaSegmento = criarLista();
    // Posteriormente essa lista será utilizada na árvore de visibilidade.
    int idSegmentos = 200; // começa no 200 pra não ter chance de alguma outra forma prévia ter.

    char linha[256];
    while(fgets(linha, sizeof(linha), arqQry)){
        char comando[10];
        sscanf(linha, "%s", comando);

        if(strcmp(comando, "a") == 0){
            int IdIni, IdFim; // Faixa de comparação de IDs.
            char orienSegCirculo[10]; // **Tratar caso círculo (v/h).
            strcpy(orienSegCirculo, "");

            sscanf(linha, "a %d %d %s", &IdIni, &IdFim, orienSegCirculo); 

            No noAtual = getPrimeiroNoLista(formas);
            while(noAtual != NULL){
                No proximoNo = getProximoNoLista(noAtual);
                void* forma = getConteudoNoLista(noAtual);
                FormaGenericaQry* generico = (FormaGenericaQry*) forma;
                int idOrig = generico->id;
                //Vamos verificar se esse id está dentro da faixa analisada.
                TipoForma tipoOrig = generico->tipo;

                if(idOrig >= IdIni && idOrig <= IdFim){
                    int deveRemoverOriginal = 1;

                    if(tipoOrig == LINHA){
                        Linha l = (Linha) forma;
                        int idSeg = idSegmentos++;
                        Segmento s = criarSegmento(idSeg, getX1Linha(l), getY1Linha(l), getX2Linha(l), getY2Linha(l));
                        insereFinalLista(listaSegmento, s);
                        fprintf(arqTxt, "a: ID Orig: %d (%s) -> ID Seg: %d [(%.2f, %.2f) - (%.2f, %.2f)]\n", idOrig, getNomeTipo(tipoOrig), idSeg, getX1Linha(l), getY1Linha(l), getX2Linha(l), getY2Linha(l));
                        
                        deveRemoverOriginal = 0;

                    } else if(tipoOrig == CIRCULO){
                        Circulo c = (Circulo) forma;
                        double x = getXCirculo(c);
                        double y = getYCirculo(c);
                        double r = getRCirculo(c);
                        Segmento s = NULL;

                        int idSeg = idSegmentos++;

                        if(strcmp(orienSegCirculo, "v") == 0){
                            s = criarSegmento(idSeg, x, y-r, x, y+r);

                        } else if(strcmp(orienSegCirculo, "h") == 0){
                            s = criarSegmento(idSeg, x-r, y, x+r, y);

                        } else{
                            printf("Orientacao para criacao do segmento atraves do circulo invalida! Programa encerrado.");
                            exit(1);
                        }
                        insereFinalLista(listaSegmento, s);
                        fprintf(arqTxt, "a: ID Orig: %d (%s) -> ID Seg: %d [(%.2f, %.2f) - (%.2f, %.2f)]\n", idOrig, getNomeTipo(tipoOrig), idSeg, getX1Segmento(s), getY1Segmento(s), getX2Segmento(s), getY2Segmento(s));
                    
                    } else if(tipoOrig == RETANGULO){
                        Retangulo r = (Retangulo) forma;
                        double x = getXRetangulo(r);
                        double y = getYRetangulo(r);
                        double w = getWRetangulo(r);
                        double h = getHRetangulo(r);

                        double coordenadas [4][4]={
                            {x, y, x+w, y}, //Base.
                            {x+w, y, x+w, y+h}, //Direita.
                            {x+w, y+h, x, y+h}, //Topo.
                            {x, y+h, x, y} //Esquerda.
                        };

                        for(int i = 0; i < 4;i++){
                            int idSeg = idSegmentos++;
                            Segmento s = criarSegmento(idSeg, coordenadas[i][0], coordenadas[i][1], coordenadas[i][2], coordenadas[i][3]);
                            insereFinalLista(listaSegmento, s);

                            fprintf(arqTxt, "a: ID Orig: %d (%s) -> ID Seg: %d [(%.2f, %.2f) - (%.2f, %.2f)]\n", idOrig, getNomeTipo(tipoOrig), idSeg, coordenadas[i][0], coordenadas[i][1], coordenadas[i][2], coordenadas[i][3]);
                        }

                    } else if(tipoOrig == TEXTO){
                        Texto t = (Texto) forma;
                        double xt = getXTexto(t);
                        double yt = getYTexto(t);
                        char* conteudo = getTexto_Texto(t);
                        char *anc = getAncoraTexto(t);

                        double tamanho = 10 * strlen(conteudo);
                        double x1, x2;

                        if(strcmp(anc, "i") == 0) { x1 = xt; x2 = xt + tamanho;}
                        else if(strcmp(anc, "m") == 0) { x1 = xt - (tamanho/2); x2 = xt + (tamanho/2);}
                        else { x1 = xt - tamanho; x2 = xt;}

                        int idSeg = idSegmentos ++;
                        Segmento s = criarSegmento(idSeg, x1, yt, x2, yt);
                        insereFinalLista(listaSegmento, s);

                        fprintf(arqTxt, "a: ID Orig: %d (%s) -> ID Seg: %d [(%.2f, %.2f) - (%.2f, %.2f)]\n", idOrig, getNomeTipo(tipoOrig), idSeg, x1, yt, x2, yt);
                    }

                    if(deveRemoverOriginal){
                        removeNoLista(formas, noAtual);
                        killFormaGenerica(forma, tipoOrig);
                    }
                }
                noAtual = proximoNo;
            }
        } else if(strcmp(comando, "d") == 0 || strcmp(comando, "p") == 0 || strcmp(comando, "cln") == 0){
            double x, y;
            char sfx[100];
            char cor[100];
            double dx = 0, dy = 0;

            if(strcmp(comando, "d") == 0){
                sscanf(linha, "d %lf %lf %s", &x, &y, sfx);
                calcularVisibilidadeEProcessar(listaSegmento, formas, x, y, metodoOrd, limitInsertion, "d", sfx, dirSaida, nomeBaseGeo, arqSvgPrincipal, arqTxt, NULL, 0, 0);
            } else if(strcmp(comando, "p") == 0){
                sscanf(linha, "p %lf %lf %s %s", &x, &y, cor, sfx);
                calcularVisibilidadeEProcessar(listaSegmento, formas, x, y, metodoOrd, limitInsertion, "p", sfx, dirSaida, nomeBaseGeo, arqSvgPrincipal, arqTxt, cor, 0, 0);
            } else if(strcmp(comando, "cln") == 0){
                sscanf(linha, "cln %lf %lf %lf %lf %s", &x, &y, &dx, &dy, sfx);
                calcularVisibilidadeEProcessar(listaSegmento, formas, x, y, metodoOrd, limitInsertion, "cln", sfx, dirSaida, nomeBaseGeo, arqSvgPrincipal, arqTxt, NULL, dx, dy);
            }
        }
    }

    killLista(listaSegmento, (void(*)(void*))killSegmento);
    fclose(arqQry);
    fclose(arqTxt);
}