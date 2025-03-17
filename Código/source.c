#include "header.h"
#include <stdio.h>
#include <stdlib.h>

///
/**
 * @brief Cria uma variável do tipo Matriz utilizando a função malloc(), guarda o inteiro recebido por parâmetro na variável [Matriz::numero] e define a variável [Matriz* Matriz::prox] como nulo
 * 
 * @param num Valor a ser guardado no inteiro [Matriz::numero]
 * @return Retorna o endereço da variável criada
*/
Matriz* criarNum(int num)
{
    Matriz* aux = (Matriz*)malloc(sizeof(Matriz));
    if(aux == NULL) return NULL;
    aux->numero = num;
    aux->prox = NULL;
    return aux;
}

///escreve um menu no terminal que lista as operacoes possiveis
int menu()
{
    int x;

    printf("1 - Mostrar matriz\n");
    printf("2 - Alterar valor na matriz\n");
    printf("3 - Adicionar nova linha\n");
    printf("4 - Adicionar nova coluna\n");
    printf("5 - Remover Linha\n");
    printf("6 - Remover Coluna\n");
    printf("11 - MatrizAlg\n");
    printf("0 - Sair\n");

    printf("Opcao : ");
    scanf("%d",&x);
    return x;
}

///Escreve no terminal a váriavel [Matriz::numero]
bool mostraNum(Matriz* aux)
{
    if(aux == NULL)return false;
    printf("%-9d ",aux->numero);
    return true;
}


/**
 * @brief Percorre uma lista ligada e escreve os valores da variavel [Matriz::numero] em formato de uma matriz
 * 
 * @param inicio Apontador para o inicio da lista ligada
 * @param y Variável contendo número de colunas da matriz 
*/
bool mostraMatriz(Matriz* inicio,int y)
{
    int conta = 0;
    if(inicio == NULL)return false;
    Matriz* aux = inicio;
    while(aux != NULL)
    {
        if(conta == y)
        {
            printf("\n");
            conta = 0;
        }
        mostraNum(aux);
        aux = aux->prox;
        conta++;
    }
    printf("\n");
    return true;
}

/**
 * @brief insere uma variavel do tipo Matriz no final de uma lista ligada
 * 
 * @param inicio Apontador para o inicio da lista ligada
 * @param nova Apontador para a variável a ser adicionada na lista ligada
 * @return Retorna o apontador para o inicio da lista ligada
*/
Matriz* insereMatrizFim(Matriz* inicio,Matriz* nova)
{
    if(nova == NULL) return inicio;
    if(inicio == NULL)
    {
        inicio = nova;
    }
    else
    {
        Matriz* aux = inicio;
        while(aux->prox != NULL) aux = aux->prox;
        aux->prox = nova;
    }
    return inicio;
}

/**
 * @brief insere uma variavel do tipo Matriz em uma posicao específica de uma lista ligada
 * 
 * @param inicio Apontador para o inicio da lista ligada
 * @param nova Apontador para a variável a ser adicionada na lista ligada
 * @param pos Inteiro contendo a posição onde deseja-se adicionar a nova variável
 * @return Retorna o apontador para o inicio da lista ligada
*/
Matriz* insereMatrizMeio(Matriz* inicio,Matriz* nova,int pos)
{
    if(nova == NULL) return inicio;
    Matriz* aux = inicio;
    for(int conta=1;conta<pos;conta++)aux = aux->prox;
    nova->prox = aux->prox;
    aux->prox= nova;
    return inicio;
}

///Le os dados do ficheiro matriz.txt e cria uma lista ligada para os armazenar
Matriz* lerDados()
{
    FILE *fp;
    int num;
    Matriz* inicio = NULL;
    Matriz* aux;

    fp = fopen("matriz.txt","rt");
    if(fp != NULL)
    {
        do{
            fscanf(fp,"%d;",&num);
            aux = criarNum(num);
            inicio = insereMatrizFim(inicio,aux);
        }while(!feof(fp));
        fclose(fp);
        return inicio;
    }else
    (printf("matriz.txt não encontrado\n"));
}

/**
 * @brief Calcula o numero de linhas da matriz
 * 
 * Calcula o numero de linhas da matriz apartir da quantidade de mudanças de linhas presentes no ficheiro matriz.txt e divide este valor do tamanho da lista ligada para chegar ao numero de colunas da matriz e armazena os valores nas variáveis [LC::linhas] e [LC::colunas] respetivamente
 * 
 * @param inicio Apontador para o inicio da lista ligada
 * @return Retorna estrutura contendo o número de linhas e colunas da matriz 
*/
LC getLC(Matriz* inicio){

    FILE* fp;
    LC formato;
    formato.linhas = 1;
    int c;

    fp = fopen("matriz.txt","rt");
    while ((c = fgetc(fp)) != EOF)
    {
        if(c == '\n')
        {
            formato.linhas++;
        }
    }
    fclose(fp);

    Matriz* aux = inicio;
    formato.colunas = 0;

    while(aux != NULL)
    {
        aux = aux->prox;
        formato.colunas++;
    }

    if(formato.colunas % formato.linhas != 0)
        formato.colunas = -1;
    
    formato.colunas = formato.colunas/formato.linhas;

    return formato;
}

/**
 * @brief Muda o valor da variavel [Matriz::numero] em uma posicao especifica de uma lista ligada do tipo Matriz
 * 
 * @param formato Estrutura contendo o número de linhas e colunas da matriz
 * @param inicio Apontador para o inicio da lista ligada
*/
int mudarValor(LC formato,Matriz* inicio)
{
    int x,y,conta,num,posicao;
    Matriz* aux = inicio;
    printf("Linha do valor a ser mudado :\n");
    scanf("%d",&x);
    printf("Coluna do valor a ser mudado :\n");
    scanf("%d",&y);
    posicao = ((x-1)*formato.linhas + y);
    for(int conta = 1;conta < posicao;conta++)aux = aux->prox;
    if(aux == NULL)return 0;
    printf("Valor desejado: ");
    scanf("%d",&num);
    aux->numero = num;
    return 1;
}

/**
 * @brief Adiciona uma nova linha de valores a lista ligada
 * 
 * @param inicio Apontador para o inicio da lista ligada
 * @param formato Estrutura contendo o número de linhas e colunas da matriz
 * @return Retorna estrutura contendo o número de linhas e colunas da matriz 
*/
LC novaLinha(Matriz* inicio,LC formato)
{
    int num = 0;
    Matriz* aux = inicio;
    Matriz* nova;
    printf("insira os numeros da nova linha(um de cada vez)\n");
    for(int conta=1;conta<=formato.colunas;conta++){
        scanf("%d",&num);
        nova = criarNum(num);
        if(nova == NULL)return formato;
        inicio = insereMatrizFim(aux,nova);
    }
    formato.linhas++;
    return formato;
} 

/**
 * @brief Adiciona uma nova coluna de valores a lista ligada
 * 
 * @param inicio Apontador para o inicio da lista ligada
 * @param formato Estrutura contendo o número de linhas e colunas da matriz
 * @return Retorna estrutura contendo o número de linhas e colunas da matriz 
*/
LC novaColuna(Matriz* inicio,LC formato)
{
    int num = 0,pos = 0;
    Matriz* aux = inicio;
    Matriz* nova;
    printf("Insira os numeros da nova coluna(um de cada vez)\n");
    for(int conta=1;conta<=formato.linhas;conta++)
    {
        pos = pos + formato.colunas;
        scanf("%d",&num);
        nova = criarNum(num);
        if(nova == NULL)return formato;
        inicio = insereMatrizMeio(inicio,nova,pos+conta-1);
    }
    formato.colunas++;
    return formato;
}

/**
 * @brief Remove uma linha especifica da matriz
 * 
 * @param inicio Apontador para o inicio da lista ligada
 * @param formato Estrutura contendo o número de linhas e colunas da matriz
 * @return Retorna o apontador para o inicio da lista ligada
*/
Matriz* removeLinha(Matriz* inicio,LC formato)
{
    int y,linha;
    Matriz* apontaI = inicio;
    Matriz* apontaF = inicio;
    Matriz* remove;
    y = formato.colunas;

    printf("Qual linha deseja remover : \n");
    scanf("%d",&linha);
    if(linha != 1)for(int conta=1;conta<(linha-1)*y;conta++)apontaI = apontaI->prox;
    if(linha != formato.linhas)for(int conta=0;conta<linha*y;conta++)apontaF = apontaF->prox;

    remove = apontaI;

    if(linha == 1){
        Matriz* aux = criarNum(0);
        aux->prox = apontaI;
        remove = aux;
        for(int conta = 0;conta<y;conta++){
            for(int num = 0;num<y-conta;num++)remove = remove->prox;
            free(remove);
            remove = aux;
        }
        inicio = apontaF;
        free(aux);
    }
    else{
    for(int conta = 0;conta<y;conta++){
        for(int num = 0;num<y-conta;num++)remove = remove->prox;
        free(remove);
        remove = apontaI;
    }
    if(linha != formato.linhas)apontaI->prox = apontaF;
    else apontaI->prox = NULL;
    }

    if(formato.linhas == 1)inicio = NULL;
    
    return inicio;
}

/**
 * @brief Deleta uma quantidade de variáveis em uma lista ligada com o objetivo de remover uma coluna da matriz que a lista representa
 * 
 * @param inicio Apontador para o inicio da lista ligada
 * @param formato Estrutura contendo o número de linhas e colunas da matriz
 * @return Retorna o apontador para o inicio da lista ligada
*/
Matriz* removeColuna(Matriz* inicio,LC formato){
    int x,coluna;
    Matriz* apontaI;
    Matriz* apontaF = inicio;
    Matriz* remove;
    x = formato.linhas;

    printf("Qual coluna deseja remover : \n");
    scanf("%d",&coluna);

    if(coluna == 1){
        Matriz* aux = criarNum(0);
        aux->prox = inicio;
        apontaI = aux;
    }     
    else apontaI = inicio;
    for(int i = 0;i<x;i++){

    if(i == 0){
        if(coluna == 1)apontaF = apontaF->prox;
        else{
            for(int conta = 1;conta<coluna+1;conta++)apontaF = apontaF->prox;
            for(int conta = 1;conta<coluna-1;conta++)apontaI = apontaI->prox;
        }
    }
    else{
        for(int conta = 0;conta<formato.colunas-1;conta++)apontaI = apontaI->prox;
        if((i!=x-1) || (coluna!=formato.colunas))for(int conta = 0;conta<formato.colunas;conta++)apontaF = apontaF->prox;
    }
    remove = apontaI->prox;
    free(remove);
    if(i==0 && coluna == 1)inicio = apontaF;
    if((i!=x-1) || (coluna!=formato.colunas))apontaI->prox = apontaF;
    else apontaI->prox = NULL;
    }

    return inicio;

}

//algoritmo hungaro
