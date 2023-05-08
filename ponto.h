#ifndef PONTO_H_INCLUDED
#define PONTO_H_INCLUDED

#define MAX_POINTS 10

//Estrutura para definir pontos
typedef struct{
    float x;
    float y;
}Ponto;

//Estrutura para definir lista de pontos
typedef struct{
    Ponto pontos[MAX_POINTS];
    int qtd_pontos;
}Lp;

Lp* criarLp();
int ListaCheia(Lp *lp);
void addPonto(Lp *lp, float x, float y);
void removerPonto(Lp *lp, int indice);
void desenhaPontos(Lp *lp);
int selecionarPonto(Lp *lp, float mx, float my);
int transladarPonto(Lp *lp, int indice);
void rotacionarPonto(Lp *lp, int indice);

#endif // PONTO_H_INCLUDED
