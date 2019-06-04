#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<conio.c>
#include<conio.h>
#include<stdlib.h>
#define COMP 60 // tamanho do jogo
#define LARG 25 //tamanho do jogo

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
    gotoxy(1,25);
    printf("::::::::Vidas((%d))::::::::Bombas((%d))::::::::Pontos((%d))",jog.vidas,jog.bomba,10);
}
void novo_jogo()// começa um novo jogo
{
    system("cls");
    player p1= {10,10,3,5};
    imprime_infos(p1);
    gotoxy(p1.pos.x,p1.pos.y);
    textcolor(WHITE);
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
    else if ((jog.pos.y-1)<0 || (jog.pos.y-1)=='B' || (jog.pos.y-1)=='W'|| (jog.pos.y-1)>0=='D')
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

            Beep(5580,500);
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
