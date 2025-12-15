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

#ifndef EPSILON 
#define EPSILON 0.00001
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
        int atravessaY = (pts[i].y > y) != (pts[j].y > y);
        if(atravessaY){
            double xIntersecta = (pts[j].x - pts[i].x) * (y - pts[i].y) / (pts[j].y - pts[i].y) + pts[i].x;
            if(x < xIntersecta + EPSILON){
                dentro = !dentro;
            }
        } 
    }

    free(pts);
    return dentro;
}

double distSqAux(double x1, double y1, double x2, double y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

int segmentoInterceptaCirculo(double x1, double y1, double x2, double y2, double cx, double cy, double r) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    double l2 = dx*dx + dy*dy; // Comprimento do segmento ao quadrado.

    double t;
    if (l2 == 0.0) {
        t = 0.0; // O segmento é apenas um ponto.
    } else {

        t = ((cx - x1) * dx + (cy - y1) * dy) / l2;
        
       
        if (t < 0.0) t = 0.0;
        else if (t > 1.0) t = 1.0;
    }

    double closestX = x1 + t * dx;
    double closestY = y1 + t * dy;

    return distSqAux(cx, cy, closestX, closestY) <= (r * r);
}

double produtoVetorialAux(Ponto a, Ponto b, Ponto c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int segmentosSeInterceptam(Ponto p1, Ponto p2, Ponto q1, Ponto q2) {
    double d1 = produtoVetorialAux(q1, q2, p1);
    double d2 = produtoVetorialAux(q1, q2, p2);
    double d3 = produtoVetorialAux(p1, p2, q1);
    double d4 = produtoVetorialAux(p1, p2, q2);

    if (((d1 > EPSILON && d2 < -EPSILON) || (d1 < -EPSILON && d2 > EPSILON)) &&
        ((d3 > EPSILON && d4 < -EPSILON) || (d3 < -EPSILON && d4 > EPSILON))) {
        return 1;
    }
    return 0;
}

int segmentoCruzaPoligono(Lista poligono, double x1, double y1, double x2, double y2) {
    Ponto t1 = {x1, y1};
    Ponto t2 = {x2, y2};
    
    No noAtual = getPrimeiroNoLista(poligono);

    while(noAtual != NULL && getProximoNoLista(noAtual) != NULL) {
        Ponto* pA = (Ponto*) getConteudoNoLista(noAtual);
        Ponto* pB = (Ponto*) getConteudoNoLista(getProximoNoLista(noAtual));
        
        if(segmentosSeInterceptam(t1, t2, *pA, *pB)) {
            return 1;
        }
        noAtual = getProximoNoLista(noAtual);
    }

    if(getTamanhoLista(poligono) > 2) {
        Ponto* pUltimo = (Ponto*) getConteudoNoLista(getUltimoNoLista(poligono));
        Ponto* pPrimeiro = (Ponto*) getConteudoNoLista(getPrimeiroNoLista(poligono));
        if(segmentosSeInterceptam(t1, t2, *pUltimo, *pPrimeiro)) {
            return 1;
        }
    }

    return 0;
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
    Segmento obstaculoInicialManual = NULL;
    double menorDistInicial = 1e30;

    No noSegCheck = getPrimeiroNoLista(listaSegmentos);
    while(noSegCheck != NULL){
        Segmento s = (Segmento) getConteudoNoLista(noSegCheck);
        double x1 = getX1Segmento(s);
        double y1 = getY1Segmento(s);
        double x2 = getX2Segmento(s);
        double y2 = getY2Segmento(s);

        // Verifica se o segmento cruza a linha horizontal da bomba (Y = yBomba)
        // Logica: um ponto está estritamente acima e outro abaixo (ou igual)
        double min_y = (y1 < y2) ? y1 : y2;
        double max_y = (y1 > y2) ? y1 : y2;

        if(min_y < yBomba && max_y >= yBomba){
            double xIntersecta = x1 + (yBomba - y1) * (x2 - x1) / (y2 -y1);
            if(xIntersecta > xBomba){
                inserirSegmentoArvore(ativos, s);
                double dist = xIntersecta - xBomba;
                if(dist < menorDistInicial){
                    menorDistInicial = dist;
                    obstaculoInicialManual = s;
                }
            }
        }
        noSegCheck = getProximoNoLista(noSegCheck);
    }

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

        Segmento obstaculoAtual;
        if(primeiraPassada && obstaculoInicialManual != NULL){
            obstaculoAtual = obstaculoInicialManual;
        } else{
            obstaculoAtual = getSegMaisProx(ativos);
        }

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

    No noForma = getPrimeiroNoLista(listaFormas);
    static int geradorIdClone = 200;

    while(noForma != NULL){
        No proximoNo = getProximoNoLista(noForma);
        void* forma = getConteudoNoLista(noForma);
        FormaGenericaHeader* header = (FormaGenericaHeader*) forma;

        int foiAtingido = 0;

        if(header->tipo == RETANGULO) {
            Retangulo r = (Retangulo) forma;
            double x = getXRetangulo(r);
            double y = getYRetangulo(r);
            double w = getWRetangulo(r);
            double h = getHRetangulo(r);

            if(pontoDentroDoPoligono(poligono, x, y) || 
               pontoDentroDoPoligono(poligono, x + w, y) || 
               pontoDentroDoPoligono(poligono, x + w, y + h) || 
               pontoDentroDoPoligono(poligono, x, y + h)) {
                foiAtingido = 1;
            } else if(xBomba >= x && xBomba <= x+w && yBomba >= y && yBomba <= y+h) {
                foiAtingido = 1;
            } else if(segmentoCruzaPoligono(poligono, x, y, x+w, y) ||      // Base
                    segmentoCruzaPoligono(poligono, x+w, y, x+w, y+h) ||  // Dir
                    segmentoCruzaPoligono(poligono, x+w, y+h, x, y+h) ||  // Topo
                    segmentoCruzaPoligono(poligono, x, y+h, x, y)) {      // Esq
                foiAtingido = 1;
            }
        } else if (header->tipo == CIRCULO) {
            Circulo c = (Circulo) forma;
            double cx = getXCirculo(c);
            double cy = getYCirculo(c);
            double r = getRCirculo(c);

            if (pontoDentroDoPoligono(poligono, cx, cy)) {
                foiAtingido = 1;
            } else if (distSqAux(xBomba, yBomba, cx, cy) <= r*r) {
                foiAtingido = 1;
            } else {
                No noAtual = getPrimeiroNoLista(poligono);
                
                while(noAtual != NULL && getProximoNoLista(noAtual) != NULL) {
                    Ponto* pA = (Ponto*) getConteudoNoLista(noAtual);
                    Ponto* pB = (Ponto*) getConteudoNoLista(getProximoNoLista(noAtual));
                    
                    if (segmentoInterceptaCirculo(pA->x, pA->y, pB->x, pB->y, cx, cy, r)) {
                        foiAtingido = 1;
                        break; 
                    }
                    noAtual = getProximoNoLista(noAtual);
                }

                
                if (!foiAtingido && getTamanhoLista(poligono) > 2) {
                    Ponto* pUltimo = (Ponto*) getConteudoNoLista(getUltimoNoLista(poligono));
                    Ponto* pPrimeiro = (Ponto*) getConteudoNoLista(getPrimeiroNoLista(poligono));
                    
                    if (segmentoInterceptaCirculo(pUltimo->x, pUltimo->y, pPrimeiro->x, pPrimeiro->y, cx, cy, r)) {
                        foiAtingido = 1;
                    }
                }
            }
        } else if (header->tipo == LINHA) {
            Linha l = (Linha) forma;
            double x1 = getX1Linha(l);
            double y1 = getY1Linha(l);
            double x2 = getX2Linha(l);
            double y2 = getY2Linha(l);

            // A) Pontos extremos dentro?
            if(pontoDentroDoPoligono(poligono, x1, y1) || 
               pontoDentroDoPoligono(poligono, x2, y2)){
                foiAtingido = 1;
            }
            
            else if(segmentoCruzaPoligono(poligono, x1, y1, x2, y2)) {
                foiAtingido = 1;
            }
        } else {
            Texto t = (Texto) forma;
            double xt = getXTexto(t);
            double yt = getYTexto(t);
            char* conteudo = getTexto_Texto(t); 
            char* anc = getAncoraTexto(t);
            double tamanhoSeg = 10.0 * strlen(conteudo);
            double x1, x2;
            
            if(strcmp(anc, "i") == 0) { x1 = xt; x2 = xt + tamanhoSeg; } 
            else if(strcmp(anc, "f") == 0) { x1 = xt - tamanhoSeg; x2 = xt; } 
            else { x1 = xt - (tamanhoSeg / 2.0); x2 = xt + (tamanhoSeg / 2.0); }

            if(pontoDentroDoPoligono(poligono, x1, yt) || 
               pontoDentroDoPoligono(poligono, x2, yt) ||
               pontoDentroDoPoligono(poligono, xt, yt)) {
                foiAtingido = 1;
            }
        }

        // Aplicação dos efeitos da bomba
        if(foiAtingido){
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