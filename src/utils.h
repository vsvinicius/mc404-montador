#ifndef UTILS_H
#define UTILS_H

/**
    * Conta a quantidade de vezes que determinado caracter esta presente na string
    * entrada: string que deve ser analisada
    * tamanho: tamanho da string entrada
    * caracter: caracter utilizado para separar a entrada
*/
int contarOcorrencias(char* entrada, unsigned tamanho, char caracter);

/*
    * Separa uma string com base em uma caracter passado por parametro
    * entrada: string que deve ser analisada
    * tamanho: tamanho da string entrada
    * caracter: caracter utilizado para separar a entrada
*/
char** separarString(char* entrada, unsigned tamanho, char caracter);

#endif  /* UTILS_H */
