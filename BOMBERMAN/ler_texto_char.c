#include <stdio.h>

#define MAX_LIN 60
#define MAX_COL 25

int main()
{
    FILE *arq;
    char matriz [MAX_LIN][MAX_COL];
    char matrizmapa [MAX_LIN][MAX_COL];
    int i,j;
    char c;
    arq = fopen("mapa", "r");
    if(arq == NULL)
    {
        printf("Erro");
    }
    else
    {

        while(!feof(arq))
        {
            fscanf(arq, "%c", matriz[i][j]);

            if(fscanf(arq, "%c", matriz) >=0)
            {
                for(i=0; i<MAX_LIN; i++)
                {
                    for(j=0; j<MAX_COL; i++)
                    {
                        c=fgetc(arq);
                        if(c==EOF){
                            matrizmapa[i][j]=c;
                        }
                        matrizmapa[i][j] = matriz[i][j];
                        printf("%c", matriz[i][j]);
                    }
                    printf("\n");
                }
            }
        }
        fclose(arq);

    }

    return 0;
}
