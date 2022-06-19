#include <stdlib.h>
#include <stdio.h>
#include "pilhas.h"


void colocaDado(Carta *c, Pilha *p) {
    c->prox = p->topo;
    p->topo = c;
}

Carta *retiraDado(Pilha *p) {
    if (p != NULL || p->topo != NULL){
        Carta *saida = p->topo;
        p->topo = p->topo->prox;
        return saida;
    }
}

Pilha *inicializaPilha() {
    Pilha *p;
    p = (Pilha *)malloc(sizeof(Pilha));
    for(int v=Quatro;v<=Tres;v++){
        for(int n=Ouros;n<=Paus;n++){
            Carta *c = (Carta *)malloc(sizeof(Carta));
            c->c_Naipe=n;
            c->c_Valor=v;

            colocaDado(c,p);
        }
    }
    return p;
}

void embaralhaPilha(Pilha *p)
{
    int tamanho = tamanhoPilha(p);
    printf("%d\n", tamanho);
    Carta *baralho[tamanho];
    for (int i = 0; i < tamanho; i++)
    {
        baralho[i] = retiraDado(p);
    }
    shuffle(baralho,tamanho);

    for (int j = 0; j < tamanho; j++)
    {
        colocaDado(baralho[j],p);
    }
    
}


int tamanhoPilha (Pilha *p)
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

void imprimePilha(Pilha *p) {
    Carta *iterador;    
    iterador = p->topo;
    while (iterador != NULL) {
      imprimeCarta(iterador); 
      iterador = iterador->prox; 
    }
    printf("  ");
}