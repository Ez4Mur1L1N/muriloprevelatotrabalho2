#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "visibilidade.h"
#include "lista.h"
#include "segmento.h"
#include "sort.h"
#include "arvore.h"
#include "svg.h"
#include "tipos.h"

#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "formas.h"

#ifndef M_PI
#define M_PI 3.14159265359
#endif

// Estrutura auxiliar para guardar um ponto.
typedef struct{
    double x, y;
} Ponto;

// Estrutura auxiliar para ler o cabeçalho de qualquer forma (ID e Tipo)
typedef struct {
    int id;
    TipoForma tipo;
} FormaGenericaHeader;

// Funções auxiliares
// Essa função vai buscar um segmento pelo seu id e retornando seu ponteiro.
Segmento buscarSegmentoPorID(Lista lista, int idBusca){
    No no = getPrimeiroNoLista(lista);
    while(no != NULL){
        Segmento s = (Segmento) getConteudoNoLista(no);
        if(getIDSegmento(s) == idBusca){
            return s;
        }
        no = getProximoNoLista(no);
    }
    return NULL; // Não existe ou digitação errada.
}

// Calcula onde o raio que sai da bomba e passa pelo vértice 'V' bate no segmento 'S'.
Ponto calcularInterseccao(double xBomba, double yBomba, double xVert, double yVert, Segmento seg){
    Ponto pRetorno = {xVert, yVert}; // Padrão de retorno: o próprio vértice.

    if(seg == NULL) return pRetorno;

    double x1 = getX1Segmento(seg);
    double y1 = getY1Segmento(seg);
    double x2 = getX2Segmento(seg);
    double y2 = getY2Segmento(seg);

    // O raio é a reta definida por (xBomba, yBomba) -> (xVert, yVert)
    // O segmento é (x1, y1) -> (x2, y2)

    // Usando determinante para intersecção de duas retas:
    double det = (xBomba - xVert) * (y1 - y2) - (yBomba - yVert) * (x1 - x2);

    // Para o caso de retas paralelas (pouco provável, segurança).
    if(fabs(det) < 1e-9) return pRetorno;

    // parâmetro 'p' para o ponto na reta do segmento.
    double p = ((xBomba - x1) * (y1 - y2) - (yBomba - y1) * (x1 - x2)) / det;

    // Intersecção:
    pRetorno.x = xBomba + p * (xVert - xBomba);
    pRetorno.y = yBomba + p * (yVert - yBomba);
    
    return pRetorno;
}

int pontoDentroDoPoligono(Lista poligono, double x, double y){
    int dentro = 0;
    No noAtual = getPrimeiroNoLista(poligono);

    int n = getTamanhoLista(poligono);
    if (n < 3) return 0;

    Ponto* pts = malloc(n * sizeof(Ponto));
    int k = 0;
    while(noAtual != NULL) {
        Ponto* p = (Ponto*) getConteudoNoLista(noAtual);
        pts[k++] = *p;
        noAtual = getProximoNoLista(noAtual);
    }

    // Algoritmo Ray Casting
    int i, j;
    for (i = 0, j = n - 1; i < n; j = i++) {
        if (((pts[i].y > y) != (pts[j].y > y)) &&
            (x < (pts[j].x - pts[i].x) * (y - pts[i].y) / (pts[j].y - pts[i].y) + pts[i].x)) {
            dentro = !dentro;
        }
    }

    free(pts);
    return dentro;
}

void calcularVisibilidadeEProcessar(Lista listaSegmentos, Lista listaFormas, double xBomba, double yBomba, char *metodoOrd, int limitInsertion, char *tipoBomba, char *sfx, char *dirSaida, char*nomeBase, char *arqSvgPrincipal, FILE *arqTxt, char *cor, double dx, double dy){
    if(arqTxt){
        fprintf(arqTxt, "\n=> Processando bomba '%s' em (%.2f, %.2f)\n", tipoBomba, xBomba, yBomba);
        if(strcmp(tipoBomba, "p") == 0){
            fprintf(arqTxt, " Atributos: cor = %s\n", cor);
        } else if(strcmp(tipoBomba, "cln") == 0){
            fprintf(arqTxt, " Atributos: deslocamento dx=%.2f, dy=%.2f\n", dx, dy);
        }
        fprintf(arqTxt," Resultados:\n");
    }
    
    double minX = -500.0, minY = -500.0;
    double maxX = 2000.0, maxY = 2000.0;

    Segmento bbox[4];
    bbox[0] = criarSegmento(-1, minX, minY, maxX, minY); // baixo.
    bbox[1] = criarSegmento(-2, maxX, minY, maxX, maxY); // direita.
    bbox[2] = criarSegmento(-3, maxX, maxY, minX, maxY); // cima.
    bbox[3] = criarSegmento(-4, minX, maxY, minX, minY); // esquerda.

    for(int i = 0; i < 4; i++){
        insereFinalLista(listaSegmentos, bbox[i]);
    }


    VetorVertices eventos = criarVetorVertices(listaSegmentos, xBomba, yBomba);
    ordenarVertices(eventos, metodoOrd, limitInsertion);
    Arvore ativos = criarArvore(xBomba, yBomba);
    Lista poligono = criarLista();

    int qtdEventos = getTamanhoVetor(eventos);

    int i = 0;
    int primeiraPassada = 1; // Flag para controlar o início.
    Segmento ultimoObstaculo = NULL; 

    while(i < qtdEventos){
        double anguloAtual = getAnguloVertice(eventos, i);
        double xVertRef = getXVertice(eventos, i);
        double yVertRef = getYVertice(eventos, i);

        int j = i;
        while(j < qtdEventos){
            if(fabs(getAnguloVertice(eventos, j) - anguloAtual) > 1e-9) break;

            int idSeg = getIdSegVertice(eventos, j);
            int ehInicio = getInicioVertice(eventos, j);
            Segmento segEvento = buscarSegmentoPorID(listaSegmentos, idSeg);
            
            if(segEvento){
                if(ehInicio) inserirSegmentoArvore(ativos, segEvento);
                else removerSegmentoArvore(ativos, segEvento);
            }
            
            // Atualiza referência para o vértice mais recente do lote.
            xVertRef = getXVertice(eventos, j);
            yVertRef = getYVertice(eventos, j);
            j++;
        }

        Segmento obstaculoAtual = getSegMaisProx(ativos);

        if(primeiraPassada){
            // CASO ESPECIAL: Primeira iteração (ângulo 0)
            // Apenas registramos o ponto inicial do polígono no obstáculo atual.
            Ponto* p = malloc(sizeof(Ponto));
            if(obstaculoAtual != NULL){
                *p = calcularInterseccao(xBomba, yBomba, xVertRef, yVertRef, obstaculoAtual);
            } else {
                p->x = xVertRef; p->y = yVertRef;
            }
            insereFinalLista(poligono, p);
            
            primeiraPassada = 0; // Desliga a flag.
        } 
        else {
            // CASO NORMAL: Compara com o último obstáculo processado.
            if(ultimoObstaculo != obstaculoAtual){
                
                // Ponto 1: Onde o raio batia no obstáculo VELHO (usando ângulo NOVO).
                Ponto* p1 = malloc(sizeof(Ponto));
                if(ultimoObstaculo != NULL){
                    *p1 = calcularInterseccao(xBomba, yBomba, xVertRef, yVertRef, ultimoObstaculo);
                } else{
                    p1->x = xVertRef; p1->y = yVertRef;
                }
                insereFinalLista(poligono, p1);

                if(anguloAtual < 2 * M_PI - 1e-4){
                    // Ponto 2: Onde o raio bate no obstáculo NOVO (usando ângulo NOVO).
                    Ponto* p2 = malloc(sizeof(Ponto));
                    if(obstaculoAtual != NULL){
                        *p2 = calcularInterseccao(xBomba, yBomba, xVertRef, yVertRef, obstaculoAtual);
                    } else{
                        p2->x = xVertRef; p2->y = yVertRef;
                    }
                
                    // Evita duplicar pontos idênticos.
                    if(fabs(p1->x - p2->x) > 1e-5 || fabs(p1->y - p2->y) > 1e-5){
                        insereFinalLista(poligono, p2);
                    } else{     
                        free(p2);
                    }
                }
            }
        }

        ultimoObstaculo = obstaculoAtual;
        i = j;
    }

    char caminhoSvgFinal[512];
    int novoArquivo = 0;

    if(strcmp(sfx, "-") == 0){
        strcpy(caminhoSvgFinal, arqSvgPrincipal);
        novoArquivo = 0;
    } else{
        sprintf(caminhoSvgFinal, "%s/%s-%s.svg", dirSaida, nomeBase, sfx);
        novoArquivo = 1;
    }

    FILE* svg = fopen(caminhoSvgFinal, novoArquivo ? "w" : "a");
    if(svg){
        if(novoArquivo){
            abreSVG(svg);
            processarListaSvg(svg, listaFormas);
        }

        fprintf(svg, "\t<circle cx=\"%.2f\" cy=\"%.2f\" r=\"5\" fill=\"red\" stroke=\"black\" stroke-width=\"2\" />\n", xBomba, yBomba); 
        desenhaPoligonoSVG(svg, poligono, "yellow", "orange", 0.5);

        if(novoArquivo){
            fechaSVG(svg);
        }
        fclose(svg);
    } else{
        printf("Erro ao abir SVG para desenho: %s\n", caminhoSvgFinal);
    }
        

    No noForma = getPrimeiroNoLista(listaFormas);
    static int geradorIdClone = 200;

    while(noForma != NULL){
        No proximoNo =getProximoNoLista(noForma);
        void* forma = getConteudoNoLista(noForma);
        FormaGenericaHeader* header = (FormaGenericaHeader*) forma;

        double xAnc = getAncoraXForma(forma, header->tipo);
        double yAnc = getAncoraYForma(forma, header->tipo);

        if(pontoDentroDoPoligono(poligono, xAnc, yAnc)){
            // Caso "D": Destruir;
            if(strcmp(tipoBomba, "d") == 0){
                if(arqTxt) fprintf(arqTxt, "d: Removido ID %d (Tipo %d)\n", header->id, header->tipo);
                removeNoLista(listaFormas, noForma);
                killFormaGenerica(forma, header->tipo);
            } else if(strcmp(tipoBomba, "p") == 0){
                setCorPreenchimentoGenerica(forma, header->tipo, cor);
                setCorBordaGenerica(forma, header->tipo, cor);
                if(arqTxt) fprintf(arqTxt, "p: Pintado ID %d (Tipo %d) com cor %s\n", header->id, header->tipo, cor);
            } else if(strcmp(tipoBomba, "cln") == 0){
                void* clone = clonarFormaGenerica(forma, header->tipo, dx, dy);
                if(clone){
                    FormaGenericaHeader* headerClone = (FormaGenericaHeader*) clone;
                    headerClone->id = geradorIdClone++;
                    insereFinalLista(listaFormas, clone);
                    if(arqTxt) fprintf(arqTxt, "cln: Clonado forma ID %d (Tipo %d)\n", header->id, header->tipo);
                }
            }
        }
        noForma = proximoNo;
    }

    killVetorVertices(eventos);
    killArvore(ativos);

    No noRemover = getPrimeiroNoLista(listaSegmentos);
    while(noRemover != NULL){
        No proximo = getProximoNoLista(noRemover);
        Segmento sRemover = (Segmento) getConteudoNoLista(noRemover);
        int idR = getIDSegmento(sRemover);
        if(idR < 0){
            removeNoLista(listaSegmentos, noRemover);
            killSegmento(sRemover);
        }
        noRemover = proximo;
    }

    No noP = getPrimeiroNoLista(poligono);
    while(noP != NULL){
        Ponto* p = (Ponto*) getConteudoNoLista(noP);
        free(p);
        noP = getProximoNoLista(noP);
    }
    killLista(poligono, NULL);
}