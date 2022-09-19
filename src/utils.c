#include "utils.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void imprimeCarta(Carta *c)
{

  switch (c->c_Naipe)
  {
  case Copas:
    printf("♥");
    break;
  case Ouros:
    printf("♦");
    break;
  case Paus:
    printf("♣");
    break;
  case Espadas:
    printf("♠");
    break;
  }

  switch (c->c_Valor)
  {
  case Valete:
    printf("J");
    break;
  case Dama:
    printf("Q");
    break;
  case Rei:
    printf("K");
    break;
  case As:
    printf("A");
    break;

  default:
    printf("%i", c->c_Valor > As ? c->c_Valor - 6 : c->c_Valor + 4);
  }
  // printf("\n");
}

void shuffle(Carta *array[], int length)
{
  srand(time(NULL));

  for (int i = 0; i < length; i++)
  {

    int swap_index = rand() % length;

    Carta *temp = array[i];
    array[i] = array[swap_index];
    array[swap_index] = temp;
  }
}

void desempilhaNaPilha(Pilha *src, Pilha *dst)
{
    while (src->topo != NULL)
    {
        colocaDado(retiraDado(src), dst);
    }
}
