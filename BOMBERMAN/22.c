#include <stdio.h>

#define MAX_LIN 25
#define MAX_COL 61

int main()
{
    FILE *arq;
    char nome_arquivo[50];
    char c, matriz[MAX_LIN][MAX_COL];
    int i=0,j=0;
    arq = fopen("mapa", "r");
    if(arq == NULL)
    {
        printf("Erro ao abrir arquivo %s\n", nome_arquivo);
    }
    else
    {
        while(!feof(arq))
        {
            c = getc(arq);

            if(c != EOF)
            {
                printf("%c",c);
                matriz[i][j] = c;
                j++;
            }
        }
        fclose(arq);
    }
    for(i=0; i<MAX_LIN; i++)
    {
        for(j=0; j<MAX_COL; j++)
        {
            printf("%c",matriz[i][j]);
        }
    }
    return 0;
}
