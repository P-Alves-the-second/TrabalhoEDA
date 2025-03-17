#include "header.h"
#include <stdio.h>
#include <stdlib.h>


///Escreve a variável [MatrizAlg::numero]
bool mostraNumAlg(MatrizAlg* aux)
{
    if(aux == NULL)return false;
    printf("%-9d ",aux->numero);
    return true;
}

/**
 * @brief Percorre uma lista ligada e escreve os valores da variavel [MatrizAlg::numero] em formato de uma matriz
 * 
 * @param inicio Apontador para o inicio da lista ligada
 * @param y Variável contendo número de colunas da matriz 
*/
bool mostraMatrizAlg(MatrizAlg* inicio,int y)
{
    int conta = 0;
    if(inicio == NULL)return false;
    MatrizAlg* aux = inicio;
    while(aux != NULL)
    {
        if(conta == y)
        {
            printf("\n");
            conta = 0;
        }
        mostraNumAlg(aux);
        aux = aux->prox;
        conta++;
    }
    printf("\n");
    return true;
}

/**
 * @brief insere uma variavel do tipo MatrizAlg no final de uma lista ligada
 * 
 * @param inicio Apontador para o inicio da lista ligada
 * @param nova Apontador para a variável a ser adicionada na lista ligada
 * @return Retorna o apontador para o inicio da lista ligada
*/
MatrizAlg* insereMatrizFimAlg(MatrizAlg* inicioAlg,MatrizAlg* nova)
{
    if(nova == NULL) return inicioAlg;
    if(inicioAlg == NULL)
    {
        inicioAlg = nova;
    }
    else
    {
        MatrizAlg* aux = inicioAlg;
        while(aux->prox != NULL) aux = aux->prox;
        aux->prox = nova;
    }
    return inicioAlg;
}

///Cria uma variável do tipo MatrizAlg utilizando a funcao malloc
MatrizAlg* criarNumAlg(int num)
{
    MatrizAlg* aux = (MatrizAlg*)malloc(sizeof(MatrizAlg));
    if(aux == NULL) return NULL;
    aux->numero = num;
    aux->prox = NULL;
    return aux;
}

/**
 * @brief Copia os dados de uma lista ligada do tipo Matriz para uma nova lista ligada do tipo MatrizAlg
 * 
 * @param inicio Apontador para o inicio de uma lista ligada do tipo Matriz 
 * @return Retorna um apontador para o inicio de uma lista ligada do tipo MatrizAlg
*/
MatrizAlg* copiarMatriz(Matriz* inicio){
    Matriz* aux = inicio;
    MatrizAlg* auxAlg;
    MatrizAlg* inicioAlg = NULL;
    while(aux->prox != NULL){
        auxAlg = criarNumAlg(aux->numero);
        inicioAlg = insereMatrizFimAlg(inicioAlg,auxAlg);
        aux = aux->prox;
    }
    auxAlg = criarNumAlg(aux->numero);
    inicioAlg = insereMatrizFimAlg(inicioAlg,auxAlg);
    return inicioAlg;
}


/**
 * @brief Acha o maior inteiro pertencente a uma lista ligada
 * 
 * @param inicio Apontador para o inicio de uma lista ligada do tipo Matriz 
 * @return Retorna inteiro contendo o valor máximo
*/
int acharMax(Matriz* inicio)
{
    int max = inicio->numero;
    Matriz* aux = inicio;
    while(aux->prox != NULL){ 
        aux = aux->prox;
        if(aux->numero>max) max = aux->numero;
    }
    return max;
}

/**
 * @brief Subtrai do valor maximo os numeros da lista ligada
 * 
 * @param inicioAlg Apontador para o inicio de uma lista ligada do tipo MatrizAlg
 * @param max Inteiro contendo valor máximo da matriz original
 * @return Retorna um apontador para o inicio de uma lista ligada do tipo MatrizAlg
*/
MatrizAlg* subtrairMax(MatrizAlg* inicioAlg,int max)
{
    MatrizAlg* aux = inicioAlg;
    while(aux->prox != NULL){
        aux->numero = max - aux->numero;
        aux = aux->prox;
    }
    return inicioAlg;
}

/**
 * @brief Acha o valor minimo de uma linha da matriz armazenada em uma lista ligada
 * 
 * @param aux Apontador para o inicio da linha 
 * @param y Numero de colunas da matriz
 * @return Retorna o valor minimo da linha escaneada
*/
int acharMinLinha(MatrizAlg* aux,int y)
{
    int min = aux->numero;
    for(int conta=1;conta<y;conta++)
    {
        aux = aux->prox;
        if(aux->numero<min) min = aux->numero;
    }
    return min;
}

/**
 * @brief Subtrai dos numeros da matriz o valor minimo de sua respectiva linha
 * 
 * @param inicioAlg Apontador para o inicio de uma lista ligada do tipo MatrizAlg
 * @param formato Estrutura contendo o numero de linhas e colunas da matriz
 * @return Retorna um apontador para o inicio de uma lista ligada do tipo MatrizAlg
*/
MatrizAlg* subtrairMinLinha(MatrizAlg* inicioAlg,LC formato)
{
    int min;
    MatrizAlg* aux = inicioAlg;
    for(int i=0;i<formato.linhas;i++)
    {
        min = acharMinLinha(aux,formato.colunas);
        for(int conta=0;conta<formato.colunas;conta++){
            aux->numero -= min;
            aux = aux->prox;
        }
    }
    return inicioAlg;

}

/**
 * @brief Acha o valor minimo de uma coluna da matriz armazenada em uma lista ligada
 * 
 * @param inicioAlg Apontador para o inicio de uma lista ligada do tipo MatrizAlg
 * @param y Posição do inicio da coluna 
 * @param formato Estrutura contendo o numero de linhas e colunas da matriz
 * @return Retorna valor minimo da coluna
*/
int acharMinColuna(MatrizAlg* inicioAlg,int y,LC formato)
{
    int min;
    MatrizAlg* aux = inicioAlg;
    if(y!=1)for(int conta = 1;conta<y;conta++)aux = aux->prox;
    min = aux->numero; 

    for(int i = 1;i<formato.linhas;i++){
        for(int conta = 0;conta<formato.colunas;conta++)aux = aux->prox; 
        if(aux->numero<min)min = aux->numero;
    }

    return min;
}

/**
 * @brief Subtrai dos numeros da matriz o valor minimo de sua respectiva coluna
 * @param inicioAlg Apontador para o inicio de uma lista ligada do tipo MatrizAlg
 * @param formato Estrutura contendo o numero de linhas e colunas da matriz
 * @return Retorna um apontador para o inicio de uma lista ligada do tipo MatrizAlg
*/
MatrizAlg* subtrairMinColuna(MatrizAlg* inicioAlg,LC formato)
{
    int min;
    MatrizAlg* aux = inicioAlg;
    for(int i = 1;i<=formato.colunas;i++)
    {
        aux = inicioAlg;
        for(int j = 0;j<formato.linhas;j++){
            if(j==0){
                if(i!=1)for(int conta = 1;conta<i;conta++)aux =aux->prox;
                min = acharMinColuna(inicioAlg,i,formato);
            }
            else for(int conta = 0;conta<formato.colunas;conta++)aux =aux->prox;
            if(aux->numero!=0)aux->numero = aux->numero - min;
        }
    }
    return inicioAlg;
}

///Conta a quantidade de linhas da matriz que tem mais de um valor igual a zero
int checarZerosLinhas(MatrizAlg* inicioAlg,LC formato)
{
    int zeros,total = 0;
    MatrizAlg* aux = inicioAlg;
    for(int i = 1;i<=formato.linhas;i++){
        zeros = 0;
        for(int conta = 0;conta<formato.colunas;conta++){
            if(aux->numero == 0)zeros++;
            aux = aux->prox;
        }
        if(zeros>1)total++;
    }
    return total;
}

///Conta a quantidade de colunas da matriz que tem mais de um valor igual a zero
int checarZerosColunas(MatrizAlg* inicioAlg,LC formato)
{
    MatrizAlg* aux = inicioAlg;
    int zeros,total = 0;
    for(int i = 1;i<=formato.colunas;i++){
        aux = inicioAlg;
        zeros = 0;
        for(int j = 0;j<formato.linhas;j++){
            if(j==0){
                if(i!=1)for(int conta = 1;conta<i;conta++)aux =aux->prox;
            }else for(int conta = 0;conta<formato.colunas;conta++)aux =aux->prox;
            if(aux->numero==0)zeros++;
        }
        if(zeros>1)total++;
    }
    return total;
}
