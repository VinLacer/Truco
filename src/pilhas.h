#ifndef _pilhas_h
#define _pilhas_h


typedef enum naipe{
    Ouros,Espadas,Copas,Paus
} Naipe;

typedef enum valor{
    Quatro, Cinco, Seis, Sete, Dama, Valete, Rei, As, Dois, Tres 
} Valor ;

typedef struct carta{
    struct carta *prox;
    Naipe c_Naipe;
    Valor c_Valor;
} Carta;

typedef struct pilha {
    Carta *topo;
} Pilha;


void embaralhaPilha(Pilha *p);
int tamanhoPilha (Pilha *p);

void imprimePilha(Pilha *p);

void colocaDado(Carta *c, Pilha *p);
Carta *retiraDado(Pilha *p);
Pilha *criaPilha();

#endif
