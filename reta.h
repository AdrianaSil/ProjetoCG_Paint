#ifndef RETA_H_INCLUDED
#define RETA_H_INCLUDED

#include "ponto.c"
#define MAX_LINES 10

//Estrutura para definir uma reta
typedef struct{
    Ponto inicio;
    Ponto fim;
}Reta;

//Estrutura para definir uma lista de retas
typedef struct{
    Reta retas[MAX_LINES];
    int qtd_retas;
}Lr;

Lr* criarLr();
int ListaVazia(Lr *lr);
int ListaCheia(Lr *lr);
void addReta(Lr *lr, Ponto p1, Ponto p2);
void removerReta(Lr *lr, int indice);
void desenhaRetas(Lr *lr);
int cohenSutherlandLineClip(Ponto p1, Ponto p2, float mx, float my);
int selecionarReta(Lr *lr, float mx, float my);
void transladarReta(Lr *lr, int indice, float mx, float my);
void rotacionarReta(Lr *lr, int indice);
void escalarReta(Lr *lr, int indice);

#endif // RETA_H_INCLUDED
