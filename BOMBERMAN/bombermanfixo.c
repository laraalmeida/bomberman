#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<conio.c>
#include<conio.h>
#include<stdlib.h>
#define COL 61 // tamanho do jogo
#define LIN 25 //tamanho do jogo
//Beep(5580,500);
//cogigo no github
typedef struct coordenada // struct com coordenada xy
{
    int x;
    int y;

} posi;
typedef struct jogador // struct jogador(posicao(xy),bombas e vidas
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
void imprime_infos(player jog)// imprime embaixo da tela as informações do jogador
{
    textcolor(GREEN);
    gotoxy(1,25);
    printf("\n::::::::Vidas((%d))::::::::Bombas((%d))::::::::Pontos((%d))",jog.vidas,jog.bomba,10);
    gotoxy(jog.pos.x,jog.pos.y); //volta para a posição do jogador
}
void abre_mapa(char matriz[LIN][COL]) // abre o arquivo do mapa
{
    FILE *arq;
    char c;
    int i,j;
    arq = fopen("mapa2", "r");

    if(arq == NULL) //testa se abriu o mapa
    {
        printf("Erro ao abrir arquivo %s\n");
    }
    else // se abriu faz a leitura do arquivo para dentro da matriz
    {
        for(i=0; i<LIN; i++)
        {
            for(j=0; j<COL; j++)
            {
                matriz[i][j] = getc(arq);
            }
        }
        fclose(arq);
    }
}
posi imprime_mapa(char matriz[LIN][COL]) // imprime o mapa
{
    int i,j;
    posi pos;
    gotoxy(0,0);//começa no pornto 0,0 da tela
    for(i=0; i<LIN; i++)
    {
        for(j=0; j<COL; j++)
        {
            if(matriz[i][j]=='J')
            {
                matriz[i][j]=' ';// altera a matriz onde o jogador estava para um espaço em branco
                pos.x=j;// armazena as coordenadas do jogador
                pos.y=i;
            }
            else if(matriz[i][j]=='W')//parede indestrutível
            {
                textcolor(LIGHTGRAY);
                printf("%c",219);

            }
            else if(matriz[i][j]=='D')//parede destritível
            {
                textcolor(DARKGRAY);
                printf("%c",219);
            }
            else if (matriz[i][j]=='E')//inimigo
            {
                textcolor(YELLOW);
                printf("&");
            }
            else if (matriz[i][j]=='B' || matriz[i][j]=='K')//caixas
            {
                textcolor(LIGHTCYAN);
                printf("#");
            }
            else if (matriz[i][j]==' ')// espaços em brancos
            {

                printf(" ",matriz[i][j]);
            }
            else if (matriz[i][j]=='\n')//pula linhas
            {

                printf("\n",matriz[i][j]);
            }

        }
    }
    return pos; //retorna a posição do jogador ****TEM QUE RETORNAR MAIS POSIÇÕES***
}
void novo_jogo(char matriz[LIN][COL])// começa um novo jogo
{
    posi pos;
    system("cls"); //apaga tudo que estava na tela
    pos=imprime_mapa(matriz); //imprime a matriz e encontra jogador
    player p1= {pos.x+1,pos.y+1,3,5}; //inicializa o jogador(usa+1 por causa da diferença matriz\tela);
    imprime_infos(p1);
    gotoxy(pos.x+1,pos.y+1);
    textcolor(LIGHTMAGENTA);
    printf("J");
    movimentacao(p1,matriz);
}
void opcao_menu(char matriz[LIN][COL])// le a opção de inicio
{
    char c;
    do
    {
        c = getch(); //espera uma tecla
    }
    while(c!='n'&&c!='c'&&c!='s'&&c!='q'); //enquanto n for válida
    switch(c)
    {
    case'n':
        novo_jogo(matriz);
    case'c':
        //carregar_jogo();
        case's':
    //salvar_jogo();
    case'q':
        system("cls");
        printf("\n\n\n=====FIM DE JOGO=====\n\n\n");
        return 0;//***ENCONTRAR SOLUÇÃO PARA FIM DE JOGO***
    }
}
char menu(char matriz[LIN][COL])//imprime o menu
{
    textcolor(LIGHTCYAN);
    char c;
    printf("                             Bomberman\n\n\n\n");
    printf("                Selecione a opcao de jogo\n\n\n\n");
    printf("     N- NOVO JOGO\n\n     C- CARREGAR JOGO\n\n     S-SALVAR JOGO\n\n     Q-SAIR DO JOGO");
    opcao_menu(matriz);
}
player andar_cima(player jog,char matriz[LIN][COL]) //andar para cima
{
    if(matriz[jog.pos.y-2][jog.pos.x-1]==' ')//verifica se pode ir pra cima
    {
        gotoxy(jog.pos.x,jog.pos.y);
        printf(" "); //apaga onde estava
        gotoxy(jog.pos.x,jog.pos.y-1);
        printf("J");//imprime no novo lugar
        jog=atualiza(jog.pos.x,jog.pos.y-1,jog); //atualiza a posição do jogador
    }
    else //se n puder, só printa no mesmo lugar
    {
        gotoxy(jog.pos.x,jog.pos.y);
        printf("J");
    }
    return jog; //retorna o jogador com a posição atualizada
}
player andar_baixo(player jog,char matriz[LIN][COL])//andar para baixo
{
    if(matriz[jog.pos.y][jog.pos.x-1]==' ')
    {
        gotoxy(jog.pos.x,jog.pos.y);
        printf(" ");
        gotoxy(jog.pos.x,jog.pos.y+1);
        printf("J");
        jog=atualiza(jog.pos.x,jog.pos.y+1,jog);
    }
    else
    {
        gotoxy(jog.pos.x,jog.pos.y);
        printf("J");
    }
    return jog;
}
player andar_esquerda(player jog, char matriz[LIN][COL])//andar para esquerda
{
    if(matriz[jog.pos.y-1][jog.pos.x-2]==' ')
    {
        gotoxy(jog.pos.x,jog.pos.y);
        printf(" ");
        gotoxy(jog.pos.x-1,jog.pos.y);
        printf("J");
        jog=atualiza(jog.pos.x-1,jog.pos.y,jog);
    }
    else
    {
        gotoxy(jog.pos.x,jog.pos.y);
        printf("J");
    }
    return jog;
}
player andar_direita(player jog, char matriz[LIN][COL])//andar para direita
{
    if(matriz[jog.pos.y-1][jog.pos.x]==' ')
    {
        gotoxy(jog.pos.x,jog.pos.y);
        printf(" ");
        gotoxy(jog.pos.x+1,jog.pos.y);
        printf("J");
        jog = atualiza(jog.pos.x+1,jog.pos.y,jog);
    }
    else
    {
        gotoxy(jog.pos.x,jog.pos.y);
        printf("J");
    }
    return jog;
}
player bomba(player jog,int x,char matriz[LIN][COL]) //plantar bomba
{
    switch (x) // seleciona a flag da bomba
    {
    case 1: //para cima
        if(matriz[jog.pos.y-2][jog.pos.x-1]==' ')//verifica se pode plantar
        {
            gotoxy(jog.pos.x,jog.pos.y-1);// se puder, vai para o lugar
            textcolor(LIGHTRED);
            printf("@");//planta a bomba
            jog=atualiza_bomba(jog);//atualiza o estoque de bombas
        }
        return jog; //retorna jogador atualizado
    case 2://para baixo
        if(matriz[jog.pos.y][jog.pos.x-1]==' ')
        {
            gotoxy(jog.pos.x,jog.pos.y+1);
            textcolor(LIGHTRED);
            printf("@");
            jog=atualiza_bomba(jog);
        }
        return jog;
    case 3://para esquerda
        if(matriz[jog.pos.y-1][jog.pos.x-2]==' ')
        {
            gotoxy(jog.pos.x-1,jog.pos.y);
            textcolor(LIGHTRED);
            printf("@");
            jog=atualiza_bomba(jog);
        }
        return jog;
    case 4://para direita
        if(matriz[jog.pos.y-1][jog.pos.x]==' ')
        {
            gotoxy(jog.pos.x+1,jog.pos.y);
            textcolor(LIGHTRED);
            printf("@");
            jog=atualiza_bomba(jog);
        }
        return jog;
    }
}
void movimentacao(player p1, char matriz[LIN][COL]) //movimentar
{
    int x=0;
    char c;
    do
    {
        textcolor(LIGHTMAGENTA);
        c = getch( );// aguarda comandos do teclado ***SETAS E ESC***

        switch (c)
        {
        case 'w':
            p1 = andar_cima(p1,matriz);
            x=1;
            break;
        case 's':
            p1 = andar_baixo(p1,matriz);
            x=2;
            break;
        case 'a':
            p1 = andar_esquerda(p1,matriz);
            x=3;
            break;
        case 'd':
            p1 = andar_direita(p1,matriz);
            x=4;
            break;
        case 'b':
            if(p1.bomba!=0)// verifica se o estoque é != 0
            {
                p1=bomba(p1,x,matriz);
                gotoxy(1,25);
                imprime_infos(p1);//atualiza o painel de controle
            }
            break;
        case 'x':
            system("cls");//limpa a tela e chama menu
            c = menu(matriz);
        }
    }
    while(c!='x');//loop infinito
}
int main()
{
    char matriz[LIN][COL]= {'0'};//inicializa uma matriz
    _setcursortype(_NOCURSOR);//retira o cursor da tela
    abre_mapa(matriz);
    menu(matriz);//chama menu de inicio
}

