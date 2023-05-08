#ifndef POLIGONO_H_INCLUDED
#define POLIGONO_H_INCLUDED

#include "ponto.c"
#define MAX_POLYGON 10
#define MAX_P_POLYGON 10

typedef struct{
    Ponto pontos[MAX_P_POLYGON];
    int qtd_p_poligono;
}Poligono;

typedef struct{
    Poligono poligonos[MAX_POLYGON];
    int qtd_poligonos;
}Lpol;

Lpol* criarLpol();
int ListaVazia(Lpol *);
int ListaCheia(Lpol *);
void addPoligono(Lpol *lpol, Ponto p[], int tam);
void removerPoligono(Lpol *lpol, Poligono p);
void desenhaPoligono(Lpol *lpol);
int selecionarPoligono(Lpol *lpol, float mx, float my);
int selecionaArea(Poligono lpol, float mx, float my);
void transladarPoligono(Lpol *lpol, int indice, float mx, float my);
void rotacionarPoligono(Lpol *lpol, int indice);
void escalarPoligono(Lpol *lpol, int indice);

#endif // POLIGONO_H_INCLUDED
