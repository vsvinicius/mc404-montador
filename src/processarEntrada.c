#include "montador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

typedef enum Erros {Lexico=10, Gramatical, SemErros} Erros;
char* DIRETIVAS [] = {".word",".wfill",".align",".org",".set"};
char* INSTRUCOES [] = {"ld","ldinv","ldabs","ldmq","ldmqmx","store","jge","add","addabs","sub","subabs","mult","div","lsh","rsh","storend","jump"};

int verificarToken(char* palavra, int linha, int ordem) {
    //identifica qual tipo do token foi passado
    char* result = "";
    int i = 0;
    char *p = malloc(strlen(palavra)*sizeof(char));
    strcpy(p,palavra);
    char *lower_case = malloc(strlen(palavra) * sizeof(char));
    strcpy(lower_case,palavra);
    toLowerCase(lower_case);

    //Comentario ou linha em branco
    if (palavra[0] == '#' || palavra[0] == '\n' || strlen(p) == 0) return -1;
    //Diretiva
     if(palavra[0] == '.') {

        if(includes(lower_case,DIRETIVAS,5)){
            adicionarToken(Diretiva,p,linha);
            return SemErros;
        }
        return Lexico;       
    }
    //Rotulo
    if((result = strchr(palavra,':')) != NULL) {
        if(isdigit(palavra[0])) return 0;
        i = 0;
         while(palavra[i] != '\0' && palavra[i] != ' ' && palavra[i] != '\t' && palavra[i] != '\n' && palavra[i] != ':') {
            if(!isalnum(palavra[i]) && palavra[i] != '_') {
                return Lexico;
            }
            i++;
        }
        if(result[1] == '\0' || result[1] == ' ' || result[i] == '\t' || result[i] == '\n'){
            adicionarToken(DefRotulo,p,linha);
            return SemErros;
        }
        return Lexico;
    }
    //Instrucoes
   if(includes(lower_case,INSTRUCOES,17)) {
       adicionarToken(Instrucao,p,linha);
       return SemErros;
   }
    //Hexadecimal
    if(isHexadecimal(lower_case)) {
        adicionarToken(Hexadecimal,p,linha);
        return SemErros;
    }
    free(lower_case);
    //Decimal
    if(isDecimal(palavra)) {
        adicionarToken(Decimal,p,linha);
        return SemErros;
    }
    //Nomes
    if(!isdigit(palavra[0])) {
        i = 0;
        while(palavra[i] != '\0' && palavra[i] != ' ' && palavra[i] != '\t' && palavra[i] != '\n') {
            if(!isalnum(palavra[i]) && palavra[i] != '_') {
                return Lexico;
            }
            i++;
        }
        adicionarToken(Nome,p,linha);
        return SemErros;
    }
    return Lexico;
}
int verificarLinha(int linha){
    int qtd = getNumberOfTokens();
    int i=0;
    while(qtd > i) {
        Token *token = recuperaToken(i);
        if((*token).linha > linha) break;
        if(i == linha && (*token).linha == linha){
            if((*token).tipo == Diretiva){
                Token *arg_1 = recuperaToken(i+1);
                Token *arg_2 = recuperaToken(i+2);
                if((*arg_1).tipo == DefRotulo || (*arg_1).tipo == Instrucao) return Gramatical;
                char *diretiva = malloc(10*sizeof(char));
                 strcpy(diretiva,".set");
                if(strcmp((*token).palavra,diretiva) == 0){
                    if((*arg_1).tipo != Nome) return Gramatical;
                    if((*arg_2).tipo != Hexadecimal && (*arg_2).tipo != Decimal) return Gramatical;
                }
                strcpy(diretiva,".org");
                if(strcmp((*token).palavra,diretiva) == 0){
                    if((*arg_1).tipo != Hexadecimal && (*arg_1).tipo != Decimal) return Gramatical;
                    if((*arg_1).tipo == Decimal){
                        int decimal = (int) (*arg_1).palavra;
                        if(decimal > 1023 || decimal < 0) return Gramatical;
                    }
                }
                strcpy(diretiva,".align");
                if(strcmp((*token).palavra,diretiva) == 0){
                    if((*arg_1).tipo != Decimal) return Gramatical;
                    int decimal = (int) (*arg_1).palavra;
                    // printf("%d",decimal);
                    if(decimal > 1023 || decimal < 0) return Gramatical;
                }
                strcpy(diretiva,".wfill");
                if(strcmp((*token).palavra,diretiva) == 0){
                    if((*arg_1).tipo != Decimal) return Gramatical;
                    int decimal = (int) (*arg_1).palavra;
                    if(decimal > 1023 || decimal < 0) return Gramatical;
                    if((*arg_2).tipo != Hexadecimal && (*arg_2).tipo != Decimal && (*arg_2).tipo != Nome ) return Gramatical;
                }
                strcpy(diretiva,".word");
                if(strcmp((*token).palavra,diretiva) == 0){
                    if((*arg_1).tipo != Hexadecimal && (*arg_1).tipo != Decimal && (*arg_1).tipo != Nome ) return Gramatical;
                }
            }
            if((*token).tipo == Instrucao){
                Token *arg_1 = recuperaToken(i+1);
                if((*arg_1).tipo == Diretiva && (*arg_1).linha == linha) return Gramatical;
                if((*arg_1).tipo != Hexadecimal && (*arg_1).tipo != Decimal && (*arg_1).tipo != Nome && ((*arg_1).linha == linha)) return Gramatical;
                if((*arg_1).tipo == Decimal && ((*arg_1).linha == linha)) {
                    int decimal = (int) (*arg_1).palavra;
                    if(decimal > 1023 || decimal < 0) return Gramatical;
                }
            }
            if((*token).tipo == Decimal){
                Token *arg_1 = recuperaToken(i+1);
                if((*arg_1).tipo == Diretiva && (*arg_1).linha == linha) return Gramatical;
                if((*arg_1).tipo != Hexadecimal && (*arg_1).tipo != Decimal && (*arg_1).tipo != Nome && ((*arg_1).linha == linha)) return Gramatical;
                if((*arg_1).tipo == Decimal && ((*arg_1).linha == linha)) {
                    int decimal = (int) (*arg_1).palavra;
                    if(decimal > 1023 || decimal < 0) return Gramatical;
                }
            }
            
        }
        i++;
    }
    return 1;
}

int processarEntrada(char* entrada, unsigned tamanho) 
{

    int inicio = 0;
    int linha = 1;
    int resultado=1;
    char *token = malloc(tamanho * sizeof(char));
    int skip=0;
    int ordem=0;
    for(int i=0; i < tamanho; i++){

        if((entrada[i] == ' ' || entrada[i] == '\t' || entrada[i] == '\n' || entrada[i] == '\0') && !skip){
            strncpy(token,&entrada[inicio],(i - inicio + 1));

            int k=0;
            while(k < strlen(token)) { 
                if(token[k] == ' ' || token[k] == '\t' || token[k] == '\n' || token[k] == '\0'){
                    token[k] = '\0';
                    break;
                }
                k++;
            }
            inicio = i+1;

            // printf("token:%s- linha %d\n",token,linha);
            resultado = verificarToken(token,linha,ordem);
            if(resultado == Lexico){ 
                fprintf(stderr, "ERRO LEXICO: palavra inválida na linha %d!\n",linha);
                break;
            }
            if(token[0] == '#') {
                // printf("ENTROU");
                skip = 1;
            }
        }
        if(entrada[i] == '\n' && skip && resultado != Lexico) {
            // printf("ENTROU AA");
            resultado = verificarLinha(linha);
            skip = 0;
            linha++;
            inicio = i+1;
        } else if(entrada[i] == '\n' && resultado != Lexico){ 
            resultado = verificarLinha(linha);
            linha++;
        }
        if(resultado == Gramatical){ 
                fprintf(stderr, "ERRO Gramatical: palavra na linha %d!\n",linha-1);
                break;
            }
    }
    // imprimeListaTokens();
    free(token);
    return !(resultado != Gramatical && resultado != Lexico );
}