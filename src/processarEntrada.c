#include "montador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

typedef enum Erros {Lexico, Gramatical, SemErros} Erros;

int verificarToken(char* palavra, TipoDoToken *token) {
    //identifica qual tipo do token foi passado
    return 1;
}
int getValorToken(TipoDoToken token, char* palavra) {
    switch (token) {
        case DefRotulo: return 1; break;
        case Instrucao: return 2; break;
        case Diretiva: return 2; break;
        default: return (palavra[0] == '#' ? 4 : 0); break;
    }
}
int verificarLinha(char* linha, int numero_linha){
    char **palavras = separarString(linha, sizeof linha, ' ');
    int i = 0;
    int ordem_tokens = 0;
    int resultado, valor_token;
    while (palavras[i] != NULL) {
       
        TipoDoToken *token = NULL;
        resultado = verificarToken(palavras[i], token);
        if (!resultado) {
            //Erro léxico
            return Lexico;
        }
        valor_token =  getValorToken(*token, palavras[i]);
        if (ordem_tokens > valor_token) {
            //Erro gramatical
            return Gramatical;
        }
        ordem_tokens = ordem_tokens + valor_token;
        i++;
    }
    return SemErros;
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
