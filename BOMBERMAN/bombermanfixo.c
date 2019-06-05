#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<conio.c>
#include<conio.h>
#include<stdlib.h>
#define COMP 61 // tamanho do jogo
#define LARG 25 //tamanho do jogo
//Beep(5580,500);
//cogigo no github
typedef struct coordenada // coordenada xy
{
    int x;
    int y;

} posi;
typedef struct jogador // jogador
{
    posi pos;
    int bomba;
    int vidas;
} player;
player atualiza(int x,int y, player atualiza)// atualizar a coordenada do jogador
{
    atualiza.pos.x=x;
    atualiza.pos.y=y;
    return atualiza;
}
player atualiza_bomba(player atualiza)//atualiza o estoque de bombas
{
    atualiza.bomba=atualiza.bomba-1;
    return atualiza;
}
void imprime_infos(player jog)// imprime embaixo da tela
{
    textcolor(GREEN);
    gotoxy(1,26);
    printf("::::::::Vidas((%d))::::::::Bombas((%d))::::::::Pontos((%d))",jog.vidas,jog.bomba,10);
    gotoxy(jog.pos.x,jog.pos.y);
}
void abre_mapa(char matriz[][COMP])
{
    FILE *arq;
    char nome_arquivo[50];
    char c;
    int x,y;
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

                matriz[i][j] = c;
                j++;
            }
        }
        fclose(arq);
    }

}
posi imprime_mapa(char matriz[][COMP])
{
    int i,j;
    posi pos;
    gotoxy(0,0);
    for(i=0; i<LARG; i++)
    {
        for(j=0; j<COMP; j++)
        {
            if(matriz[i][j]=='J')
            {
                pos.x=i;
                pos.y=j;
            }
            printf("%c",matriz[i][j]);
        }
    }
    return pos;
}

void novo_jogo(char matriz[][COMP])// começa um novo jogo
{
    posi pos;
    system("cls");
    textcolor(WHITE);
    pos=imprime_mapa(matriz);
    player p1= {pos.x+2,pos.y,3,5};
    imprime_infos(p1);
    gotoxy(pos.x+1,pos.y+1);

    movimentacao(p1,matriz);
}
void opcao_menu(char matriz[][COMP])// le a opção de inicio
{
    char c;
    do
    {
        c = getch();
    }
    while(c!='n'&&c!='c'&&c!='s'&&c!='q');
    switch(c)
    {
    case'n':
        novo_jogo(matriz);
        //case'c':carregar jogo
        //case's': salvar jogo
        //case'q': terminaar jogo
    }
}
char menu(char matriz[][COMP])//imprime o menu
{
    textcolor(RED);
    char c;
    printf("                    Bomberman\n\n");
    printf("                Selecione a opcao de jogo\n\n");
    printf("     N- NOVO JOGO\n\n     C- CARREGAR JOGO\n\n     S-SALVAR JOGO\n\n     Q-SAIR DO JOGO");
    opcao_menu(matriz);
}
player andar_cima(player jog) //andar para cima
{
    //printf("x=%d,y%d",jog.pos.x,jog.pos.y);
    if(jog.pos.y-1>0)
    {
        gotoxy(jog.pos.x,jog.pos.y);
        printf(" ");
        gotoxy(jog.pos.x,jog.pos.y-1);
        printf("J");
        jog=atualiza(jog.pos.x,jog.pos.y-1,jog);
    }
    else
    {
        gotoxy(jog.pos.x,jog.pos.y);
        printf("J");
    }
    return jog;
}
player andar_baixo(player jog)//andar para baixo
{

    if((jog.pos.y+1)<LARG)
    {
        gotoxy(jog.pos.x,jog.pos.y);
        printf(" ");
        gotoxy(jog.pos.x,jog.pos.y+1);
        printf("J");
        jog=atualiza(jog.pos.x,jog.pos.y+1,jog);
    }
    else if ((jog.pos.y+1)>LARG || (jog.pos.y+1)=='B' || (jog.pos.y+1)=='W'|| (jog.pos.y+1)>0=='D')
    {
        gotoxy(jog.pos.x,jog.pos.y);
        printf("J");
    }
    return jog;
}
player andar_esquerda(player jog)//andar para esquerda
{

    if((jog.pos.x-1)>0)
    {
        gotoxy(jog.pos.x,jog.pos.y);
        printf(" ");
        gotoxy(jog.pos.x-1,jog.pos.y);
        printf("J");
        jog=atualiza(jog.pos.x-1,jog.pos.y,jog);
    }
    else if ((jog.pos.x-1)<0 || (jog.pos.x-1)=='B' || (jog.pos.x-1)=='W'|| (jog.pos.x-1)>0=='D')
    {
        gotoxy(jog.pos.x,jog.pos.y);
        printf("J");
    }
    return jog;
}
player andar_direita(player jog)//andar para direita
{

    if((jog.pos.x+1)<COMP)
    {
        gotoxy(jog.pos.x,jog.pos.y);
        printf(" ");
        gotoxy(jog.pos.x+1,jog.pos.y);
        printf("J");
        jog = atualiza(jog.pos.x+1,jog.pos.y,jog);
    }
    else if ((jog.pos.x+1)<0 || (jog.pos.x+1)=='B' || (jog.pos.x+1)=='W'|| (jog.pos.x+1)>0=='D')
    {
        gotoxy(jog.pos.x,jog.pos.y);
        printf("J");
    }
    return jog;
}
player bomba(player jog,int x) //plantar bomba
{

    switch (x)
    {
    case 1:
        gotoxy(jog.pos.x,jog.pos.y-1);
        if(jog.pos.y-1>0)
        {
            textcolor(YELLOW);
            printf("#");
            jog=atualiza_bomba(jog);

        }
        return jog;
    case 2:
        gotoxy(jog.pos.x,jog.pos.y+1);
        if(jog.pos.y+1<LARG)
        {
            textcolor(YELLOW);
            printf("#");
            jog=atualiza_bomba(jog);
        }
        return jog;
    case 3:
        gotoxy(jog.pos.x-1,jog.pos.y);
        if(jog.pos.x-1>0)
        {
            textcolor(YELLOW);
            printf("#");
            jog=atualiza_bomba(jog);
        }
        return jog;
    case 4:
        gotoxy(jog.pos.x+1,jog.pos.y);
        if(jog.pos.x+1<COMP)
        {
            textcolor(YELLOW);
            printf("#");
            jog=atualiza_bomba(jog);
        }
        return jog;
    }
}
void movimentacao(player p1, char matriz[][COMP]) //movimentar
{
    int x=0;
    char c;
    do
    {
        textcolor(WHITE);
        c = getch( );

        switch (c)
        {
        case 'w':
            p1 = andar_cima(p1);
            x=1;
            break;
        case 's':
            p1 = andar_baixo(p1);
            x=2;
            break;
        case 'a':
            p1 = andar_esquerda(p1);
            x=3;
            break;
        case 'd':
            p1 = andar_direita(p1);
            x=4;
            break;
        case 'b':
            if(p1.bomba!=0)
            {
                p1=bomba(p1,x);
                gotoxy(1,26);
                imprime_infos(p1);
            }
            break;
        case 'x':
            system("cls");
            c = menu(matriz);
        }
    }
    while(c!='10');
}
int main()
{
    char matriz[LARG][COMP]= {'0'};
    _setcursortype(_NOCURSOR);
    abre_mapa(matriz);
    menu(matriz);

}
