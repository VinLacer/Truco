#include "truco.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void jogo()
{
    Pilha *baralho = criaBaralho();
    Jogador *player1 = criaJogador();
    Jogador *player2 = criaJogador();

    while (!jogoAcabou(player1, player2))
    {   
        rodada(player1,player2,baralho);
    }
    imprimeVencedor(player1,player2);

    free(player1->mao);
    free(player1);
    free(player2->mao);
    free(player2);
    free(baralho);
}

Pilha *criaBaralho()
{
    Pilha *p = criaPilha();
    for (int v = Quatro; v <= Tres; v++)
    {
        for (int n = Ouros; n <= Paus; n++)
        {
            Carta *c = (Carta *)malloc(sizeof(Carta));
            c->c_Naipe = n;
            c->c_Valor = v;

            colocaDado(c, p);
        }
    }
    embaralhaPilha(p);
    return p;
}

void entregaCartas(Pilha *p, Jogador *j)
{   
    j->cartadas = 0;
    for (int i = 0; i < TAM_MAO; i++)
    {
        colocaDado(retiraDado(p), j->mao);
    }
}

void imprimeVencedor(Jogador *player1, Jogador *player2)
{
    printf("O JOGADOR %d VENCEU O JOGO!!!!", player1->pontos > player2->pontos ? 1 : 2);
}

int rodadaAcabou (Jogador *player1, Jogador *player2)
{
    return player1->cartadas >= CARTADAS || player2->cartadas >= CARTADAS;
}

void rodada(Jogador *player1, Jogador *player2, Pilha *baralho)
{
    //int valendo = UmPonto;
    entregaCartas(baralho, player1);
    entregaCartas(baralho, player2);
    
    int tamanho_pilha1 = tamanhoPilha(player1->mao);
    //int tamanho_pilha2 = tamanhoPilha(player2->mao);
    
    Carta *m1[tamanho_pilha1];
    //Carta *m2[tamanho_pilha2];
    Pilha *mesa = criaPilha();
    Carta *vira = retiraDado(baralho);


    while (!rodadaAcabou(player1,player2))
    {
        mostraJogo(player1,player2,mesa,vira);
        int escolha1 = escolheCarta(player1,1);
        escolheCarta(player2,2);
        transformaPilha(player1->mao);
        for (int i = 0; i < tamanho_pilha1; i++)
        {
            colocaDado(m1[i],i== escolha1 - 1 ? mesa : player1->mao);
            free(player1->mao);
        }
        
        //desempilha a mao coloca a carta selecionada na mesa
        //reempilha o resto da mao
        //quem ganhou essa cartada
        //da cartada pra qm ganhou
    }
    //da ponto pro vencedor
    free(mesa);
    free(vira);
}

Jogador *criaJogador(){   
    Jogador *j = (Jogador *)malloc(sizeof(Jogador));
    j->pontos = 0;
    j->mao = criaPilha();
    j->cartadas = 0;
}

void mostraJogo (Jogador *player1, Jogador *player2, Pilha *mesa, Carta *vira)
{
    printf("O VIRA É:   ");
    imprimeCarta(vira);
    printf("\nMÃO DO JOGADOR 1:    \n");
    imprimePilha(player1->mao);
    printf("\nMÃO DO JOGADOR 2:    \n");
    imprimePilha(player2->mao);
    printf("\nCARTAS DA MESA:     \n");
    imprimePilha(mesa);
}

int escolheCarta(Jogador *player, int nJogador)
{   
    int escolha = 0;
    int nCartas = tamanhoPilha(player->mao);

    while (escolha <= 0 || escolha > nCartas)
    {
        printf("JOGADOR %d ESCOLHE CARTA: ",nJogador);
        scanf("%d",&escolha);
    }
    return escolha;
}

int jogoAcabou(Jogador *player1, Jogador *player2)
{
    return player1->pontos >= PONT_MAX || player2->pontos >= PONT_MAX;
}

void transformaPilha(Pilha *p)
{
    Carta *c[tamanhoPilha(p)];
    int i;

    for ( i = 0; i < tamanhoPilha(p); i++)
    {
        c[i] = retiraDado(p);
    }  
}