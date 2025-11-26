#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "leitorGeo.h"
//#include "leitorQry.h" ainda não existe!
#include "svg.h"
#include "lista.h"
#include "tipos.h"

int main(int argc, char *argv[]) {
    char* dirEntrada = NULL;
    char* arqGeoNome = NULL;
    char* dirSaida = NULL;
    char* arqQryNome = NULL;

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
    
    char caminhoSvg[512];
    sprintf(caminhoSvg, "%s/%s.svg", dirSaida, nomeBase);

char caminhoTxt[512];
    char nomeQrySemExt[256];
    nomeQrySemExt[0] = '\0'; 

    if (arqQryNome != NULL) {
        
        char* barraQry = strrchr(arqQryNome, '/');
        char* inicioNomeQry;

        if (barraQry != NULL) {
            inicioNomeQry = barraQry + 1;
        } else {
            inicioNomeQry = arqQryNome;
        }
        
        strcpy(nomeQrySemExt, inicioNomeQry); 

        char* pontoQry = strrchr(nomeQrySemExt, '.');
        if (pontoQry != NULL) {
            *pontoQry = '\0'; 
        }
        snprintf(caminhoTxt, sizeof(caminhoTxt), "%s/%s-%s.txt", dirSaida, nomeBase, nomeQrySemExt);
        
    } else {
        snprintf(caminhoTxt, sizeof(caminhoTxt), "%s/%s.txt", dirSaida, nomeBase); 
    }


    // Execução Principal
    printf("Lendo arquivo GEO: %s\n", caminhoGeo);
    ListaFormas formas = lerArqGeo(caminhoGeo);

    printf("Gerando SVG inicial: %s\n", caminhoSvg);
    FILE* arqSvg = fopen(caminhoSvg, "w");
    if(arqSvg != NULL){
        abreSVG(arqSvg);
        processarListaSvg(arqSvg, formas);
        fechaSVG(arqSvg);
        fclose(arqSvg);
    } else{
        printf("Erro ao abrir/criar arquivo SVG!\n");
    }

    // Processamento de Consultas 

    // Desenvolvimento do qry...

    // printf("\nProcesso concluido!\n");

    // Limpeza Final
    printf("Liberando memoria das formas...\n");
    killListaFormasGeo(formas);
    printf("Limpeza de memória concluída!\n");

    return 0;
}