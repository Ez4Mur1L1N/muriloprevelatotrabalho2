#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "leitorGeo.h"
#include "leitorQry.h" 
#include "svg.h"
#include "lista.h"
#include "tipos.h"

int main(int argc, char *argv[]) {
    char* dirEntrada = NULL;
    char* arqGeoNome = NULL;
    char* dirSaida = NULL;
    char* arqQryNome = NULL;
    char* metodoOrd = "q";
    int limitInsertion = 10;//valor padrão definido.

    // Processamento dos Argumentos da Linha de Comando 
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-e") == 0 && i + 1 < argc) {
            dirEntrada = argv[++i];
        } else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            arqGeoNome = argv[++i];
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            dirSaida = argv[++i];
        } else if (strcmp(argv[i], "-q") == 0 && i + 1 < argc) {
            arqQryNome = argv[++i];
        } else if (strcmp(argv[i], "-to") == 0 && i + 1 < argc){
            metodoOrd = argv[++i];
        } else if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
            limitInsertion = atoi(argv[++i]);
        }
    }

    if (arqGeoNome == NULL || dirSaida == NULL) {
        printf("Argumentos obrigatorios -f e -o nao foram fornecidos.\n");
        printf("Uso: ./programa -f <arq.geo> -o <dir_saida> [-e <dir_entrada> -q <arq.qry>]\n");
        return 1;
    }

    // Montagem dos Caminhos dos Arquivos
    char caminhoGeo[512];
    if (dirEntrada != NULL) {
        sprintf(caminhoGeo, "%s/%s", dirEntrada, arqGeoNome);
    } else {
        strcpy(caminhoGeo, arqGeoNome);
    }

    char nomeBase[256];
    
    char* barra = strrchr(arqGeoNome, '/'); 
    char* inicioNome;

    if (barra != NULL) {
        inicioNome = barra + 1;
    } else {
        inicioNome = arqGeoNome;
    }
    strcpy(nomeBase, inicioNome); 
    char* ponto = strrchr(nomeBase, '.');
    if (ponto != NULL) {
        *ponto = '\0';
    }
    
    char caminhoSvgInicial[512];
    sprintf(caminhoSvgInicial, "%s/%s.svg", dirSaida, nomeBase);

    // Execução Principal
    printf("Lendo arquivo GEO: %s\n", caminhoGeo);
    ListaFormas formas = lerArqGeo(caminhoGeo);

    printf("Gerando SVG inicial: %s\n", caminhoSvgInicial);
    FILE* arqSvg = fopen(caminhoSvgInicial, "w");
    if(arqSvg != NULL){
        abreSVG(arqSvg);
        processarListaSvg(arqSvg, formas);
        fechaSVG(arqSvg);
        fclose(arqSvg);
    } else{
        printf("Erro ao abrir/criar arquivo SVG inicial!\n");
    }

    if (arqQryNome != NULL) {
        char caminhoQry[512];
        if (dirEntrada != NULL) {
            sprintf(caminhoQry, "%s/%s", dirEntrada, arqQryNome);
        } else {
            strcpy(caminhoQry, arqQryNome);
        }

        char nomeQryBase[256];
        char* barra = strrchr(arqQryNome, '/');
        char* inicio = (barra != NULL) ? barra + 1 : arqQryNome;
        strcpy(nomeQryBase, inicio);
        char* ponto = strrchr(nomeQryBase, '.');
        if (ponto != NULL) *ponto = '\0';

        char caminhoTxt[512];
        sprintf(caminhoTxt, "%s/%s-%s.txt", dirSaida, nomeBase, nomeQryBase);

        char caminhoSvgFinal[512];
        sprintf(caminhoSvgFinal, "%s/%s-%s.svg", dirSaida, nomeBase, nomeQryBase);

        printf("Processando consultas: %s\n", caminhoQry);
        printf("Gerando relatorio: %s\n", caminhoTxt);
        printf("Preparando SVG Final: %s\n", caminhoSvgFinal);

        FILE* svgFinalBase = fopen(caminhoSvgFinal, "w");
        if(svgFinalBase){
            abreSVG(svgFinalBase);
            fclose(svgFinalBase);
        }

        lerArqQry(formas, caminhoQry, caminhoTxt, dirSaida, nomeBase, caminhoSvgFinal, metodoOrd, limitInsertion);
        
        FILE* svgFinalFim = fopen(caminhoSvgFinal, "a");
        if(svgFinalFim){
            processarListaSvg(svgFinalFim, formas);
            fechaSVG(svgFinalFim);
            fclose(svgFinalFim);
        }
    }



    printf("\nProcesso concluido!\n");

    // Limpeza Final
    printf("Liberando memoria das formas...\n");
    killListaFormasGeo(formas);
    printf("Limpeza de memória concluída!\n");

    return 0;
}