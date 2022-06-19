#include "utils.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void imprimeCarta(Carta *iterador)
{
    switch(iterador->c_Naipe) {
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
        if(iterador->c_Valor<Dama){
            printf("%i",iterador->c_Valor+4);
        }
        else if (iterador->c_Valor>As)
        {
            printf("%i",iterador->c_Valor-6);
        }
        
        else{
            switch(iterador->c_Valor) {
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
            }
        }
        printf("\n");
        
}

void shuffle(Carta *array[], int length)
{
  srand( time(NULL) );
  
  for (int i = 0; i < length; i++)
  {
    
    int swap_index = rand() % length;
    
    
    Carta *temp = array[i];
    array[i] = array[swap_index];
    array[swap_index] = temp;
  }
}

