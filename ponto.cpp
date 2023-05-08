#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <GL/glut.h>
#include "ponto.h"
#include "transformacoes.cpp"

#define largura 500
#define altura 500
#define t 10

float **mTi, **mR, **mT, **mP, **mE;

Lp* criarLp(){
    Lp *lp;
    lp = (Lp*)malloc(sizeof(Lp));
    if(lp != NULL){
        lp->qtd_pontos = 0;
    }
    return lp;
}

int ListaVazia(Lp *lp){
    if(lp->qtd_pontos == 0)
        return 1; //vazia
    else
        return 0;
}

int ListaCheia(Lp *lp){
    if(lp->qtd_pontos == MAX_POINTS)
        return 1; //cheia
    else
        return 0;
}

void addPonto(Lp *lp, float x, float y){
    if(lp == NULL)
        printf("Erro na lista.\n");
    else if(ListaCheia(lp) == 1)
        printf("Atingiu qtd maxima de pontos.\n");
    else{
        lp->pontos[lp->qtd_pontos].x = x;
        lp->pontos[lp->qtd_pontos].y = y;
        lp->qtd_pontos++;
    }
}

void removerPonto(Lp *lp, int indice){
    if(lp == NULL || ListaVazia(lp) == 1)
        printf("Lista vazia ou ocorreu um erro inesperado.\n");
    else{
        for(int i = indice; i<(lp->qtd_pontos-1); i++){
            lp->pontos[i] = lp->pontos[i+1];
        }
        lp->qtd_pontos--;
    }
}

void desenhaPontos(Lp *lp){
    glPointSize(5.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < lp->qtd_pontos; i++){
        glColor3f(1, 0, 0);
        glVertex2f(lp->pontos[i].x, altura - lp->pontos[i].y);
    }
    glEnd();
}

int selecionarPonto(Lp *lp, float mx, float my){
    if(lp == NULL || lp->qtd_pontos == 0)
        return 0;
    else{
        for(int i = 0; i < lp->qtd_pontos; i++){
            if(mx <= lp->pontos[i].x + t && mx >= lp->pontos[i].x - t) {
                if(my <= lp->pontos[i].y + t && my >= lp->pontos[i].y - t) {
                        printf("%d\n", i);
                    return i;
                }
            }
        }
    }
}

void transladarPonto(Lp *lp, int indice, float mx, float my){
    if(lp == NULL || lp->qtd_pontos == 0)
        printf("Lista vazia ou ocorreu um erro inesperado.\n");
    else{
        mT = criarMatrizT(mx - lp->pontos[indice].x, my - lp->pontos[indice].y);
        mP = criarMatrizPonto(lp->pontos[indice].x, lp->pontos[indice].y);

        float **r = transladar(mP,mT);
        lp->pontos[indice].x = r[0][0];
        lp->pontos[indice].y = r[1][0];
    }
}

void rotacionarPonto(Lp *lp, int indice){
    if (lp == NULL || lp->qtd_pontos == 0)
        printf("Lista vazia ou ocorreu um erro inesperado.\n");
    else{
        mR = criarMatrizR();
        mP = criarMatrizPonto(lp->pontos[indice].x, lp->pontos[indice].y);

        float **r = mult_matrizes(mR,mP, 3,1);
        lp->pontos[indice].x = r[0][0];
        lp->pontos[indice].y = r[1][0];
    }
}
