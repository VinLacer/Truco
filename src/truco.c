#include "truco.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void jogo()
{
    Pilha *baralho = criaBaralho();
    Jogador *player1 = criaJogador(1);
    Jogador *player2 = criaJogador(2);

    while (!jogoAcabou(player1, player2))
    {
        embaralhaPilha(baralho);
        rodada(player1, player2, baralho);
    }
    imprimeVencedor(player1, player2);

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
    printf("O JOGADOR %d VENCEU O JOGO!!!!\n\n\n", player1->pontos > player2->pontos ? 1 : 2);
}

int rodadaAcabou(Jogador *player1, Jogador *player2, int valCartada)
{
    return player1->cartadas >= valCartada || player2->cartadas >= valCartada;
}

void rodada(Jogador *player1, Jogador *player2, Pilha *baralho)
{
    int valendo = UmPonto;
    int valCartada = CARTADAS(TAM_MAO);

    entregaCartas(baralho, player1);
    entregaCartas(baralho, player2);

    Pilha *mesa = criaPilha();
    Carta *vira = retiraDado(baralho);

    player1->cartadas = 0;
    player2->cartadas = 0;

    while (!rodadaAcabou(player1, player2, valCartada))
    {
        mostraJogo(player1, player2, mesa, vira);

        valendo = truco(valendo, player1);
        system("clear");
        mostraJogo(player1, player2, mesa, vira);
        fazerJogada(player1, mesa);
        system("clear");

        valendo = truco(valendo, player2);
        system("clear");
        mostraJogo(player1, player2, mesa, vira);
        fazerJogada(player2, mesa);
        system("clear");

        valCartada = pontuaCartada(mesa, player1, player2, vira, valCartada);
        sleep(3);
    }
    pontuaRodada(player1, player2, valendo, valCartada);
    sleep(3);
    colocaDado(vira, baralho);
    desempilhaNaPilha(player1->mao, baralho);
    desempilhaNaPilha(player2->mao, baralho);
    desempilhaNaPilha(mesa, baralho);
}

Jogador *criaJogador(int nJogador)
{
    Jogador *j = (Jogador *)malloc(sizeof(Jogador));
    j->pontos = 0;
    j->mao = criaPilha();
    j->cartadas = 0;
    j->nJogador = nJogador;

    return j;
}

void mostraJogo(Jogador *player1, Jogador *player2, Pilha *mesa, Carta *vira)
{
    system("clear");
    printf("O VIRA É:   ");
    imprimeCarta(vira);
    printf("\nMÃO DO JOGADOR 1:    \n");
    imprimePilha(player1->mao);
    printf("\nMÃO DO JOGADOR 2:    \n");
    imprimePilha(player2->mao);
    printf("\nCARTAS DA MESA:     \n");
    imprimePilha(mesa);
}

int escolheCarta(Jogador *player)
{
    int escolha = 0;
    int nCartas = tamanhoPilha(player->mao);

    while (escolha <= 0 || escolha > nCartas)
    {
        printf("JOGADOR %d ESCOLHE CARTA: ", player->nJogador);
        scanf("%d", &escolha);
    }
    return escolha;
}

int jogoAcabou(Jogador *player1, Jogador *player2)
{
    return player1->pontos >= PONT_MAX || player2->pontos >= PONT_MAX;
}

void fazerJogada(Jogador *player, Pilha *mesa)
{
    int escolha = escolheCarta(player);
    int tamanho_pilha = tamanhoPilha(player->mao);
    Carta *mao[tamanho_pilha];
    for (int i = 0; i < tamanho_pilha; i++)
    {
        mao[i] = retiraDado(player->mao);
    }

    for (int i = tamanho_pilha - 1; i >= 0; i--)
    {
        colocaDado(mao[i], i == escolha - 1 ? mesa : player->mao);
    }
}

int pontuaCartada(Pilha *mesa, Jogador *player1, Jogador *player2, Carta *vira, int valCartada)
{
    system("clear");
    if (mesa->topo->c_Valor == vira->c_Valor + 1 && mesa->topo->prox->c_Valor == vira->c_Valor + 1)
    {
        if (mesa->topo->c_Naipe > mesa->topo->prox->c_Naipe)
        {
            printf("JOGADOR %d GANHOU A CARTADA POR MANILHA!!!!!\n\n", player2->nJogador);
            player2->cartadas += 1;
            return valCartada;
        }
        else
        {
            printf("JOGADOR %d GANHOU A CARTADA POR MANILHA!!!!!\n\n", player1->nJogador);
            player1->cartadas += 1;
            return valCartada;
        }
    }

    else if ((mesa->topo->c_Valor) == vira->c_Valor + 1 && (mesa->topo->prox->c_Valor) != vira->c_Valor + 1)
    {
        printf("JOGADOR %d GANHOU A CARTADA POR MANILHA!!!!!\n\n", player2->nJogador);
        player2->cartadas += 1;
        return valCartada;
    }

    else if ((mesa->topo->prox->c_Valor) == vira->c_Valor + 1 && mesa->topo->c_Valor != vira->c_Valor + 1)
    {
        printf("JOGADOR %d GANHOU A CARTADA POR MANILHA!!!!!\n\n", player1->nJogador);
        player1->cartadas += 1;
        return valCartada;
    }

    else if (mesa->topo->c_Valor > mesa->topo->prox->c_Valor)
    {
        printf("JOGADOR %d GANHOU A CARTADA!!!!!\n\n", player2->nJogador);
        player2->cartadas += 1;
        return valCartada;
    }
    else if (mesa->topo->c_Valor < mesa->topo->prox->c_Valor)
    {
        printf("JOGADOR %d GANHOU A CARTADA!!!!!\n\n", player1->nJogador);
        player1->cartadas += 1;
        return valCartada;
    }

    else
    {
        printf("CARTADA EMPATADA!!!!!\n\n");
        valCartada = CARTADAS(TAM_MAO) - 1;
        return valCartada;
    }
}

void pontuaRodada(Jogador *player1, Jogador *player2, int valendo, int valCartada)
{
    system("clear");
    if (player1->cartadas >= valCartada)
    {
        player1->pontos += valendo;
        printf("JOGADOR %d GANHOU A RODADA!!!!!\n\n", player1->nJogador);
    }

    else if (player2->cartadas >= valCartada)
    {
        player2->pontos += valendo;
        printf("JOGADOR %d GANHOU A RODADA!!!!!\n\n", player2->nJogador);
    }

    printf("PONTOS JOGADOR %d : %d  \n", player1->nJogador, player1->pontos);
    printf("PONTOS JOGADOR %d : %d  \n", player2->nJogador, player2->pontos);
}

int truco(int valendo, Jogador *player)
{
    int reposta = 0;
    printf("JOGADOR %d DESEJA TRUCAR OU AUMENTAR A APOSTA?\n\n", player->nJogador);
    printf("[1] SIM\n[2] NAO\n");
    scanf("%d", &reposta);

    if (reposta == 1)
    {
        if (valendo == UmPonto)
        {
            valendo = TresPontos;
            return valendo;
        }

        else
        {
            valendo += TresPontos;
            return valendo;
        }
    }
    else
        return valendo;
}
