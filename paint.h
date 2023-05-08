#ifndef PAINT_H_INCLUDED
#define PAINT_H_INCLUDED

//Estrutura para definir pontos
typedef struct{
    float x;
    float y;
}Ponto;

void cliqueMouse(int botao, int estado, int x, int y);
void addPonto(float x, float y);
void addReta(Ponto p1, Ponto p2);
void addPoligono(Ponto p[], int tam);
void removePonto();
void removeReta();
void removePoligono();

void desenhaPontos();
void desenhaRetas();
void desenhaPoligono();

#endif // PAINT_H_INCLUDED
