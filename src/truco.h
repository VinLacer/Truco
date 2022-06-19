#ifndef _truco_h
#define _truco_h

#include <math.h>
#include "pilhas.h"

#define PONT_MAX        12
#define TAM_MAO         3
#define CARTADAS        ceil(TAM_MAO/2)

typedef enum pontos{
    UmPonto = 1, TresPontos = 3, SeisPontos = 6, NovePontos = 9, DozePontos = 12
}Pontos;

typedef struct jogador
{
    int pontos;
    int cartadas;
    Pilha *mao;
}Jogador;


void jogo();
Pilha *criaBaralho();
Jogador *criaJogador();

void entregaCartas(Pilha *p, Jogador *j);
void rodada (Jogador *player1, Jogador *player2, Pilha *baralho);

int jogoAcabou(Jogador *player1, Jogador *player2);
int rodadaAcabou (Jogador *player1, Jogador *player2);
void imprimeVencedor(Jogador *player1, Jogador *player2);
void mostraJogo (Jogador *player1, Jogador *player2, Pilha *mesa, Carta *vira);
int escolheCarta(Jogador *player, int nJogador);
#endif