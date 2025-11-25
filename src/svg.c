#include <stdio.h>
#include <stdlib.h>
#include "svg.h"
#include "lista.h"
#include "tipos.h"

#define OPACIDADE 0.7

typedef struct{
    int id;
    TipoForma tipo;
} FormaGenerica;


void abreSVG(FILE* arqSVG){
    if(arqSVG == NULL){
        return;
    }
    fprintf(arqSVG, "<svg width=\"1000\" height=\"1000\" xmlns=\"http://www.w3.org/2000/svg\">\n");
}

void fechaSVG(FILE* arqSVG){
    if(arqSVG == NULL){
        return; //Para caso esse arquivo não exista ou não foi aberto (fopen).
    }
    fprintf(arqSVG, "</svg>\n");
}

void processarListaSvg(FILE* arqSVG, Lista lst){
    if(arqSVG == NULL || lst == NULL){
        return;
    }
    
    No noAtual = getPrimeiroNoLista(lst);
    while(noAtual != NULL){
        void* forma = getConteudoNoLista(noAtual);
        FormaGenerica* generico = (FormaGenerica*) forma;

        switch(generico->tipo){
            case CIRCULO:
                desenhaCirculoSVG(arqSVG, forma);
                break;
            case RETANGULO:
                desenhaRetanguloSVG(arqSVG, forma);
                break;
            case LINHA:
                desenhaLinhaSVG(arqSVG, forma);
                break;
            case TEXTO:
                desenhaTextoSVG(arqSVG, forma);
                break;
            default:
                break;
        }
        noAtual = getProximoNoLista(noAtual);    
    }

}

void desenhaCirculoSVG(FILE* arqSVG, Circulo c){
    if(arqSVG == NULL || c == NULL){
        return;
    }
    fprintf(arqSVG, "\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"%.1f\" />\n",
            getXCirculo(c),
            getYCirculo(c),
            getRCirculo(c),
            getCorBCirculo(c),
            getCorPCirculo(c),
            OPACIDADE);
}

void desenhaRetanguloSVG(FILE* arqSVG, Retangulo r){
    if (arqSVG == NULL || r == NULL){
        return;
    }
    fprintf(arqSVG, "\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"%.1f\" />\n",
            getXRetangulo(r),
            getYRetangulo(r),
            getWRetangulo(r),
            getHRetangulo(r),
            getCorBRetangulo(r),
            getCorPRetangulo(r),
            OPACIDADE);
}

void desenhaLinhaSVG(FILE* arqSVG, Linha l){
    if(arqSVG == NULL || l == NULL){
        return;
    }
    fprintf(arqSVG, "\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\" />\n",
            getX1Linha(l),
            getY1Linha(l),
            getX2Linha(l),
            getY2Linha(l),
            getCorLinha(l));
}

void desenhaTextoSVG(FILE* arqSVG, Texto t){
    if(arqSVG == NULL || t == NULL){
        return;
    }
    // Transformar a ancora para o jeito que o SVG entende
    char *ancoraTXT;
    char* ancoraStr = getAncoraTexto(t); // Agora retorna "i", "m", ou "f"
    if (strcmp(ancoraStr, "i") == 0) {
        ancoraTXT = "start";
    } else if (strcmp(ancoraStr, "m") == 0) {
        ancoraTXT = "middle";
    } else {
        ancoraTXT = "end";
    }
    fprintf(arqSVG, "\t<text x=\"%f\" y=\"%f\" stroke=\"%s\" fill=\"%s\" text-anchor=\"%s\" font-family=\"%s\" font-weight=\"%s\" font-size=\"%s\" fill-opacity=\"%.1f\">%s</text>\n", // <-- ESPAÇO REMOVIDO AQUI
            getXTexto(t),
            getYTexto(t),
            getCorBTexto(t),
            getCorPTexto(t),
            ancoraTXT,
            getFontFamilyTexto(t),
            getFontWeightTexto(t),
            getFontSizeTexto(t),
            OPACIDADE,
            getTexto_Texto(t));
}
