#include <stdlib.h>
#include <stdio.h>
#include "pilhas.h"
#include "utils.h"

void colocaDado(Carta *c, Pilha *p)
{
    c->prox = p->topo;
    p->topo = c;
}

Carta *retiraDado(Pilha *p)
{
    Carta *ptr;
    if (p != NULL || p->topo != NULL)
    {
        ptr = p->topo;
        p->topo = p->topo->prox;
    }
    return ptr;
}

Pilha *criaPilha()
{
    Pilha *p = (Pilha *)malloc(sizeof(Pilha));
    return p;
}

void embaralhaPilha(Pilha *p)
{
    int tamanho = tamanhoPilha(p);
    Carta *baralho[tamanho];
    for (int i = 0; i < tamanho; i++)
    {
        baralho[i] = retiraDado(p);
    }
    shuffle(baralho, tamanho);

    for (int j = 0; j < tamanho; j++)
    {
        colocaDado(baralho[j], p);
    }
}

int tamanhoPilha(Pilha *p)
{
    int tamanho = 0;
    Carta *iterador = p->topo;
    while (iterador != NULL)
    {
        tamanho++;
        iterador = iterador->prox;
    }
    return tamanho;
}

void imprimePilha(Pilha *p)
{
    int contador = 1;
    Carta *iterador;
    iterador = p->topo;

    while (iterador != NULL)
    {
        printf("[%d] ", contador++);
        imprimeCarta(iterador);
        iterador = iterador->prox;
        
    }
    // printf("  ");
}