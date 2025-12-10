#include <stdio.h>
#include <stdlib.h>
#include "formas.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

// Estrutura auxiliar para obter o ID e o Tipo (deve ser compatível com o primeiro campo das suas formas).
typedef struct{
    int id;
    TipoForma tipo;
} FormaGenericaBase;

double getAncoraXForma(void* forma, TipoForma tipo) {
    if (!forma) return 0.0;
    
    switch(tipo) {
        case CIRCULO: return getXCirculo(forma);
        case RETANGULO: return getXRetangulo(forma);
        case TEXTO: return getXTexto(forma);
        case LINHA: return getX1Linha(forma);
        default: return 0.0;
    }
}

double getAncoraYForma(void* forma, TipoForma tipo) {
    if (!forma) return 0.0;
    
    switch(tipo) {
        case CIRCULO: return getYCirculo(forma);
        case RETANGULO: return getYRetangulo(forma);
        case TEXTO: return getYTexto(forma);
        case LINHA: return getY1Linha(forma);
        default: return 0.0;
    }
}

void setCorPreenchimentoGenerica(void* forma, TipoForma tipo, char* cor) {
    if (!forma) return;
    switch(tipo) {
        case CIRCULO: setCorPCirculo(forma, cor); break; 
        case RETANGULO: setCorPRetangulo(forma, cor); break;
        case TEXTO: setCorPTexto(forma, cor); break;
        // Linha só tem cor de borda
        case LINHA: setCorLinha(forma, cor); break;
        default: break;
    }
}

void setCorBordaGenerica(void* forma, TipoForma tipo, char* cor) {
    if (!forma) return;
    switch(tipo) {
        case CIRCULO: setCorBCirculo(forma, cor); break;
        case RETANGULO: setCorBRetangulo(forma, cor); break;
        case TEXTO: setCorBTexto(forma, cor); break;
        default: break;
    }
}

void killFormaGenerica(void* forma, TipoForma tipo) {
    if (!forma) return;
    
    switch(tipo) {
        case CIRCULO: killCirculo(forma); break;
        case RETANGULO: killRetangulo(forma); break;
        case TEXTO: killTexto(forma); break;
        case LINHA: killLinha(forma); break;
        default: break;
    }
}

void* clonarFormaGenerica(void* forma, TipoForma tipo, double dx, double dy) {
    if (!forma){
        return NULL;
    } 

    void* clone = NULL;

    FormaGenericaBase* base = (FormaGenericaBase*) forma;
    int idTemporario = base->id;
    
    switch(tipo) {
        case CIRCULO: clone = clonarCirculo(forma, idTemporario, dx, dy); break; 
        case RETANGULO: clone = clonarRetangulo(forma, idTemporario, dx, dy); break;
        case TEXTO: clone = clonarTexto(forma, idTemporario, dx, dy); break;
        case LINHA: clone = clonarLinha(forma, idTemporario, dx, dy); break;
        default: break;
    }
    return clone;
}