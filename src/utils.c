#include "montador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int contarOcorrencias(char* entrada, unsigned tamanho, char caracter){
    int contador = 0;
    int i = 0;
    while(entrada[i] != '\0') {
        if(entrada[i] == caracter){
            contador++;
        }
        i++;
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
int includes(char* key, char** array, int tamanho) {
    int i = 0;
    
    while(i < tamanho){
        if (strcmp(key,array[i]) == 0) {
            return 1;
        }
        i++;
    }
    return 0;
}
void toLowerCase(char* source) {
    // char *new_word = malloc((sizeof source) * sizeof (char));
    int i=0;
    while(source[i] != '\0') {
        source[i] = tolower(source[i]);
        i++;
    }
}
int isHexadecimal(char* source) {
    int i = 0;
    if(source[0] != '0' || source[1] != 'x') return 0;

    while(source[i] != '\0') {
        if(!isxdigit(source[i]) && source[i] != 'x') {
            return 0;
        }    
        i++;
    }
    return 1;
}
int isDecimal(char* source) {
    int i = 0;
    // printf(" is decimal - %lu\n",strlen(source));
    while(source[i] != '\0') {
        if(!isdigit(source[i])) {
            return 0;
        }
        i++;    
    }
    return strlen(source) > 0;
}