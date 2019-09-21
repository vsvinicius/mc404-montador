#include "montador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

typedef enum Erros {Lexico, Gramatical, SemErros} Erros;
typedef enum Tokens {Instrucao, Diretiva, DefRotulo, Hexadecimal, Decimal, Nome, Comentario} Tokens;

Tokens verificarToken(char* palavra) {
    //identifica qual tipo do token foi passado
}
int somarTokens(Tokens token, char* palavra) {
    switch (token) {
        case DefRotulo: return 1; break;
        case Instrucao: return 2; break;
        case Diretiva: return 2; break;
        case Comentario: return 4; break;
        default: return 0; break;
    }
}

int verificarLinha(char* linha, int numero_linha){
    char **palavras = separarString(linha, sizeof linha, ' ');
    int i = 0;
    int ordem_tokens = 0;
    while (palavras[i] != NULL) {
       
        Tokens token = verificarToken(palavras[i]);
        if (token == NULL) {
            //Erro léxico
            return Lexico;
        }
        if (temErroGramatical(ordem_tokens, token)) {
            return Gramatical;
        }
        return SemErros;
    }
}

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
