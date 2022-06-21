#ifndef _utils_h
#define _utils_h

#include "pilhas.h"

void imprimeCarta(Carta *c);
void shuffle(Carta *array[], int length);
void desempilhaNaPilha(Pilha *src, Pilha *dst);

#endif