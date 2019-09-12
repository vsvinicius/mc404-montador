#include "montador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
/*
Exemplo de erros:
const char* get_error_string (enum errors code) {
    switch (code) {
        case ERR_HEXADECIMAL_NAO_VALIDO:
            return "LEXICO: Numero Hexadecimal Inválido!";
        case ERRO_ROTULO_JA_DEFINIDO:
            return "GRAMATICAL: ROTULO JA FOI DEFINIDO!";
        case ERR_DIRETIVA_NAO_VALIDA:
            return "LEXICO: Diretiva não válida";
*/

/*
    ---- Você Deve implementar esta função para a parte 1.  ----
    Essa função é chamada pela main em main.c
    Entrada da função: arquivo de texto lido e seu tamanho
    Retorna:
        * 1 caso haja erro na montagem; (imprima o erro em stderr)
        * 0 caso não haja erro.         (Caso não haja erro, na parte 1, ao retornar desta função, a lista de Tokens (adicionados utilizando a função adicionarToken()) é impressa)
*/
int processarEntrada(char* entrada, unsigned tamanho)
{
    printf("\n\n");
    char **n = separarString(entrada, tamanho,'\n');
    int i = 0;
    while(n[i] != NULL){
        char **k = separarString(n[i],sizeof n[i],' ');
        int j= 0;
        while(k[j] != NULL) printf("%s",k[j++]);
        printf("\n");
        i++;
        free(k);
    }
    /* printf("Você deve implementar esta função para a Parte 1.\n"); */
    return 0;
}
