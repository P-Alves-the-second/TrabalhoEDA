#include "header.h"
#include <stdio.h>

int main()
{
    int nm,op,max,min,x,y;
    Matriz* inicio = lerDados();
    LC formato = getLC(inicio);
    if(formato.colunas == -1)return 0;
    MatrizAlg* inicioAlg = copiarMatriz(inicio);
    do{
        if((formato.linhas == 0) || (formato.colunas == 0)){formato.linhas = 0; formato.colunas = 0;}
        op = menu();
        switch(op)
        {
            case 1:
                if (mostraMatriz(inicio,formato.colunas))
                printf("Linhas:%d\nColunas:%d\n",formato.linhas,formato.colunas);
            break;
            case 2:
                printf("Linha do valor a ser mudado :\n");
                scanf("%d",&x);
                printf("Coluna do valor a ser mudado :\n");
                scanf("%d",&y);
                printf("Valor desejado: ");
                scanf("%d",&nm);
                mudarValor(formato,inicio,x,y,nm);
            break;
            case 3:
                formato = novaLinha(inicio,formato);
            break;
            case 4:
                formato = novaColuna(inicio,formato);
            break;
            case 5:
                printf("Qual linha deseja remover : \n");
                scanf("%d",&x);
                inicio = removeLinha(inicio,formato,x);
                formato.linhas--;
            break;
            case 6:
                printf("Qual coluna deseja remover : \n");
                scanf("%d",&y);
                inicio = removeColuna(inicio,formato,y);
                formato.colunas--;
            break;
            case 11:
                max = acharMax(inicio);
                mostraMatrizAlg(inicioAlg,formato.colunas);
                printf("Max: %d\n",max);
                printf("InicioAlg: %d\n",inicioAlg->numero);
            break;
            case 12:
                max = acharMax(inicio);
                inicioAlg = subtrairMax(inicioAlg,max);
                inicioAlg = subtrairMinLinha(inicioAlg,formato);
                inicioAlg = subtrairMinColuna(inicioAlg,formato);
            break;
            case 13:
                
            break;
            case 14:
                //for(int conta = 1;conta<=formato.colunas;conta++)printf("%d\n",acharMinColuna(inicioAlg,conta,formato));
                printf("%d\n",checarZerosLinhas(inicioAlg,formato));
                printf("%d\n",checarZerosColunas(inicioAlg,formato));
            break;
        }
    }while(op != 0);
}

   