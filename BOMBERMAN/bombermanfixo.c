#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<conio.c>
#include<conio.h>
#include<stdlib.h>
#define COMP 61 // tamanho do jogo
#define LARG 25 //tamanho do jogo
//Beep(5580,500);

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
void novo_jogo()// começa um novo jogo
{
    system("cls");
    player p1= {4,3,3,5};
    textcolor(WHITE);
    mapa();
    imprime_infos(p1);
    gotoxy(4,3);
    textcolor(RED);
    printf("J");

    movimentacao(p1);
}
void opcao_menu()// le a opção de inicio
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
        novo_jogo();
        //case'c':carregar jogo
        //case's': salvar jogo
        //case'q': terminaar jogo
    }
}
char menu()//imprime o menu
{
    textcolor(RED);
    char c;
    printf("                    Bomberman\n\n");
    printf("                Selecione a opcao de jogo\n\n");
    printf("     N- NOVO JOGO\n\n     C- CARREGAR JOGO\n\n     S-SALVAR JOGO\n\n     Q-SAIR DO JOGO");
    opcao_menu();
}
player andar_cima(player jog) //andar para cima
{

    if((jog.pos.y-1)>0)
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
void movimentacao(player p1) //movimentar
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
            c = menu();
        }
    }
    while(c!='27');
}
int main()
{
    _setcursortype(_NOCURSOR);
    menu();

}
void mapa(){
    FILE *arq;
    char nome_arquivo[50];
    char c, matriz[LARG][COMP];
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
    gotoxy(0,0);
    for(i=0; i<LARG; i++)
    {
        for(j=0; j<COMP; j++)
        {
            printf("%c",matriz[i][j]);
        }
    }
  }

