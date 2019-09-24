#include "montador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

typedef enum Erros {Lexico, Gramatical, SemErros} Erros;
char* DIRETIVAS [] = {".word",".wfill",".align",".org",".set"};
char* INSTRUCOES [] = {"ld","ldinv","ldabs","ldmq","ldmqmx","store","jge","add","addabs","sub","subabs","mult","div","lsh","rsh","storend"};

int verificarToken(char* palavra, int linha) {
    //identifica qual tipo do token foi passado
    char* result = "";
    int i = 0;
    //Comentario
    if (palavra[0] == '#') return -1;
    //Diretiva
     if(palavra[0] == '.') {
        if(includes(palavra,DIRETIVAS)){
            adicionarToken(Diretiva,palavra,linha);
            return 1;
        }
        return 0;       
    }
    //Rotulo
    if((result = strchr(palavra,':')) != NULL) {
        if(isdigit(palavra[0])) return 0;       

        if(result[1] == '\0'){
            adicionarToken(DefRotulo,palavra,linha);
            return 1;
        }
        return 0;
    }
    //Instrucoes
   if(includes(toLowerCase(palavra), INSTRUCOES)) {
       adicionarToken(Instrucao,palavra,linha);
       return 1;
   }
    //Hexadecimal
    if(isHexadecimal(palavra)) {
        adicionarToken(Hexadecimal,palavra,linha);
        return 1;
    }
    //Decimal
    if(isDecimal(palavra)) {
        adicionarToken(Decimal,palavra,linha);
        return 1;
    }
    //Nomes
    if(!isdigit(palavra[0])) {
        i = 0;
        while(palavra[i] != '\0') {
            if(!isalnum(palavra[i]) && palavra[i] != '_') {
                return 0;
            }
        }
        adicionarToken(Nome,palavra,linha);
        return 1;
    }
    return 0;
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
    return 1;
}

int processarEntrada(char* entrada, unsigned tamanho) 
{
    //printf("\n\n");
    char **n = separarString(entrada, tamanho,'\n');
    int i = 0;
    int resultado;
    //int resultado;
  while(n[i] != NULL){
      char **k = separarString(n[i],sizeof n[i],' ');
      int j= 0;
      while(k[j] != NULL){
          printf("palavra: %s\n",k[j]);
          resultado = verificarToken(k[j],i);
          //printf("%d\n",resultado);
          if(resultado < 0) break;
          if(resultado == 0) break;
          j++;
      }
      if(resultado == 0){ 
          fprintf(stderr, "ERRO LEXICO: palavra inválida na linha %d!",i);
          break;
      }
      printf("\n");
      i++;
      free(k);
  }
  free(n);
    /* printf("Você deve implementar esta função para a Parte 1.\n"); */

    return (resultado == 0);
}
