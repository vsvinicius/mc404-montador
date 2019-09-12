#include "montador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contarOcorrencias(char* entrada, unsigned tamanho, char caracter){
    int contador = 0;
    int i;
    for(i = 0; i < tamanho; i++){
        if(entrada[i] == caracter){
            contador++;
        }
    }
    return contador;
}
char** separarString(char* entrada, unsigned tamanho, char caracter){
    int ocorrencias_total= contarOcorrencias(entrada,tamanho,caracter);
    char *separador = &caracter;
    char **nova_string= malloc(ocorrencias_total * sizeof (char *));

    nova_string[0]= strtok(entrada,separador);
    int ocorrencias= 1;
    while (nova_string[ocorrencias-1] != NULL) {
       nova_string[ocorrencias] = strtok(NULL,separador);
       ocorrencias++;
    }
    return nova_string;
}