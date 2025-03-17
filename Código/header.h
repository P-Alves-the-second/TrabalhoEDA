#pragma once

#include <stdbool.h>

typedef struct Matriz{
    /// @brief Váriavel do tipo inteiro que guarda um número pertencente a matriz
    int numero;
    /// @brief Apontador do tipo Matriz que guarda o endereço do próximo valor da lista ligada
    struct Matriz* prox;
}Matriz;

typedef struct MatrizAlg{
    /// @brief Váriavel do tipo inteiro que guarda um número pertencente a matriz
    int numero;
    /// @brief Apontador do tipo MatrizAlg que guarda o endereço do próximo valor da lista ligada
    struct MatrizAlg* prox;
}MatrizAlg;

typedef struct LC{
    /// @brief Variável do tipo inteiro que guarda o número de linhas da matriz
    int linhas;
    /// @brief Variável do tipo inteiro que guarda o número de colunas da matriz
    int colunas;
}LC;

Matriz* lerDados();
Matriz* criarNum(int num);
Matriz* insereMatrizFim(Matriz* inicio,Matriz* nova);
LC getLC(Matriz* inicio);
LC novaLinha(Matriz* inicio,LC formato);
LC novaColuna(Matriz* inicio,LC formato);
Matriz* removeLinha(Matriz* inicio,LC formato);
Matriz* removeColuna(Matriz* inicio,LC formato);
MatrizAlg* copiarMatriz(Matriz* inicio);
MatrizAlg* criarNumAlg(int num);
MatrizAlg* insereMatrizFimAlg(MatrizAlg* inicioAlg,MatrizAlg* nova);
MatrizAlg* subtrairMax(MatrizAlg* inicioAlg,int max);
MatrizAlg* subtrairMinLinha(MatrizAlg* inicioAlg,LC formato);
MatrizAlg* subtrairMinColuna(MatrizAlg* inicioAlg,LC formato);
int acharMinLinha(MatrizAlg* aux,int y);
int acharMax(Matriz* inicio);
int acharMinColuna(MatrizAlg* inicioAlg,int y,LC formato);
int checarZerosLinhas(MatrizAlg* inicioAlg,LC formato);
int checarZerosColunas(MatrizAlg* inicioAlg,LC formato);
bool mostraMatriz(Matriz* inicio,int y);
bool mostraMatrizAlg(MatrizAlg* inicio,int y);
bool mostraNum(Matriz* num);
int menu();
int mudarValor(LC formato,Matriz* inicio);
