#ifndef UTILS_H
#define UTILS_H

/**
    * Conta a quantidade de vezes que determinado caracter esta presente na string
    * entrada: string que deve ser analisada
    * tamanho: tamanho da string entrada
    * caracter: caracter utilizado para separar a entrada
*/
int contarOcorrencias(char*, unsigned, char);

/*
    * Separa uma string com base em uma caracter passado por parametro
    * entrada: 
    *   -> string que deve ser analisada
    *   -> tamanho da string entrada
    *   -> caracter utilizado para separar a entrada
*/
char** separarString(char*, unsigned, char);

/*
    *procura uma determinada palavra em um array de palavras
    *entradas: 
        -> palavra a ser procurada
        -> array que vai ser iterado
    *saida: 1 caso exista, 0 caso não exista
*/
int includes(char*, char**);

/*
    *retorna uma string com letras minusculas
    *entrada:
        -> string que deve ser modificada
    *saida:
        -> nova string com letras minusculas
*/
char* toLowerCase(char*);
/*
    *verifica se todos os digitos da string sao hexadecimais, retorna 1 caso todos forem e 0 caso nao algum nao for
    *entrada:
        -> string a ser analisada
*/
int isHexadecimal(char* source);
/*
    *verifica se todos os digitos da string sao decimais, retorna 1 caso todos forem e 0 caso nao algum nao for
    *entrada:
        -> string a ser analisada
*/
int isDecimal(char* source);
#endif  /* UTILS_H */
