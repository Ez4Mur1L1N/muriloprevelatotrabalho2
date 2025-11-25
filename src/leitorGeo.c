#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leitorGeo.h"
#include "lista.h"

#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "tipos.h"

typedef struct{
    int id;
    TipoForma tipo;
} FormaGenerica;

// Função auxiliar para ajudar no killListaFormasGeo
void killForma(void *forma){
    if(forma == NULL){
        return;
    }

    FormaGenerica* generico = (FormaGenerica*) forma;
    switch(generico->tipo){
        case CIRCULO:
            killCirculo(forma);
            break;
        case RETANGULO:
            killRetangulo(forma);
            break;
        case LINHA:
            killLinha(forma);
            break;
        case TEXTO:
            killTexto(forma);
            break;
        default:
            break;
    }
}

void killListaFormasGeo(ListaFormas lst) {
    Lista lista = (Lista) lst;
    killLista(lista, killForma); 
}

ListaFormas lerArqGeo(char *caminhoAqrGeo) {
    FILE* arqGeo = fopen(caminhoAqrGeo, "r");
    if (arqGeo == NULL) {
        printf("Erro ao abrir o arquivo .geo em: %s  !! Programa encerrado.", caminhoAqrGeo);
        exit(1);
    }

    Lista formas = criarLista();

    char linha[512];
    int id;
    double x, y, r, w, h, x2, y2;
    char corB[32], corP[32], ancora[32], texto[256];
    
    // Padrões de segurança para o estilo (Sua ideia)
    char fFamily_atual[64], fWeight_atual[32], fSize_atual[16];
    strcpy(fFamily_atual, "Arial");
    strcpy(fWeight_atual, "normal");
    strcpy(fSize_atual, "12px");

    while (fgets(linha, sizeof(linha), arqGeo)) {
        linha[strcspn(linha, "\n")] = 0; // Remove o \n
        
        char comando[10];
        sscanf(linha, "%s", comando); 
        
        // Limpar buffers.
        corB[0] = '\0';
        corP[0] = '\0';
        texto[0] = '\0';
        ancora[0] = '\0'; 

        if (strcmp(comando, "c") == 0) {
            sscanf(linha, "c %d %lf %lf %lf %s %s", &id, &x, &y, &r, corB, corP);
            insereFinalLista(formas, criarCirculo(id, x, y, r, corB, corP));
        
        } else if (strcmp(comando, "r") == 0) {
            sscanf(linha, "r %d %lf %lf %lf %lf %s %s", &id, &x, &y, &w, &h, corB, corP);
            insereFinalLista(formas, criarRetangulo(id, x, y, w, h, corB, corP));
        
        } else if (strcmp(comando, "l") == 0) {
            sscanf(linha, "l %d %lf %lf %lf %lf %s", &id, &x, &y, &x2, &y2, corB);
            insereFinalLista(formas, criarLinha(id, x, y, x2, y2, corB));
        
        } else if (strcmp(comando, "ts") == 0) {
            // "Muda o estilo dos textos (comando t) subsequentes."
            sscanf(linha, "ts %s %s %s", fFamily_atual, fWeight_atual, fSize_atual);
        
        } else if (strcmp(comando, "t") == 0) {
            int camposLidos = sscanf(linha, "t %d %lf %lf %s %s %s %[^\n]", &id, &x, &y, corB, corP, ancora, texto);

            if(camposLidos < 6){
                continue;
            }

        if (texto[0] == '"') {
            // Remove a aspa inicial (movendo o conteúdo uma casa pra trás)
            memmove(texto, texto + 1, strlen(texto));
            // Remove a aspa final
            int len = strlen(texto);
            if (len > 0 && texto[len - 1] == '"') {
                texto[len - 1] = '\0';
            }
        }

            insereFinalLista(formas, criarTexto(id, x, y, corB, corP, ancora, texto, fFamily_atual, fWeight_atual, fSize_atual));
        }
    } // Fim do while

    fclose(arqGeo);
    return (ListaFormas) formas;
}