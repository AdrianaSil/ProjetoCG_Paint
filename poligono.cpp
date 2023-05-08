#include <stdlib.h>
#include <windows.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include "poligono.h"

#define largura 500
#define altura 500

Lpol* criarLpol(){
    Lpol *lpol;
    lpol = (Lpol*)malloc(sizeof(Lpol));
    if(lpol != NULL){
        lpol->qtd_poligonos = 0;
    }
    return lpol;
}

int ListaVazia(Lpol *lpol){
    if(lpol->qtd_poligonos == 0)
        return 1; //vazia
    else
        return 0;
}

int ListaCheia(Lpol *lpol){
    if(lpol->qtd_poligonos == MAX_POLYGON)
        return 1; //cheia
    else
        return 0;
}

void addPoligono(Lpol *lpol, Ponto p[], int tam){
    if(lpol == NULL)
        printf("Erro na lista.\n");
    else if(ListaCheia(lpol))
        printf("Atingiu qtd maxima de poligonos.\n");
    else{
        for(int i=0; i<tam; i++){
            lpol->poligonos[lpol->qtd_poligonos].pontos[i] = p[i];
        }
        lpol->poligonos[lpol->qtd_poligonos].qtd_p_poligono = tam;
        lpol->qtd_poligonos ++;
    }
}

int comparar(Poligono p1, Poligono p2){
    int cont = 0;
    if(p1.qtd_p_poligono == p2.qtd_p_poligono){
        for(int i = 0; i< p1.qtd_p_poligono; i++){
            if(p1.pontos[i].x == p2.pontos[i].x && p1.pontos[i].y == p2.pontos[i].y)
                cont++;
        }
    }
    if(cont == p1.qtd_p_poligono)
        return 1;
    return 0;
}

void removerPoligono(Lpol *lpol, int indice){
    if(lpol == NULL || ListaVazia(lpol) == 1)
        printf("Lista vazia ou ocorreu um erro inesperado.\n");
    else{
        for(int i = indice; i<(lpol->qtd_poligonos - 1); i++){
            lpol->poligonos[i] = lpol->poligonos[i+1];
        }
        lpol->qtd_poligonos--;
    }
}

void desenhaPoligono(Lpol *lpol){
    glLineWidth(2.0);
    for(int i = 0; i < lpol->qtd_poligonos; i++){
        glBegin(GL_POLYGON);
        glColor3f(0, 0, 1);
        for(int j = 0; j < lpol->poligonos[i].qtd_p_poligono; j++){
            glVertex2f(lpol->poligonos[i].pontos[j].x, altura - lpol->poligonos[i].pontos[j].y);
        }
        glEnd();
    }
}

int selecionarPoligono(Lpol *lpol, float mx, float my){
    if (lpol == NULL || lpol->qtd_poligonos == 0)
        return -1;
    else{
        for(int i = 0; i < lpol->qtd_poligonos; i++){
            if(selecionaArea(lpol->poligonos[i], mx, my)){
                return i;
            }
        }
        return -1;
    }
}

int selecionaArea(Poligono lpol, float mx, float my){

}

void transladarPoligono(Lpol *lpol, int indice, float mx, float my){
    if(lpol == NULL || lpol->qtd_poligonos == 0)
        printf("Lista vazia ou ocorreu um erro inesperado.\n");
    else{
        float **r;
        float centroidex = 0, centroidey = 0;
        for(int i = 0; i<lpol->poligonos[indice].qtd_p_poligono; i++){
            centroidex += lpol->poligonos[indice].pontos[i].x;
            centroidey += lpol->poligonos[indice].pontos[i].y;
        }

        centroidex /= lpol->poligonos[indice].qtd_p_poligono;
        centroidey /= lpol->poligonos[indice].qtd_p_poligono;

        mT = criarMatrizT(mx - centroidex, my - centroidey);

        for(int i = 0; i<lpol->poligonos[indice].qtd_p_poligono; i++){
            mP = criarMatrizPonto(lpol->poligonos[indice].pontos[i].x, lpol->poligonos[indice].pontos[i].y);
            r = transladar(mP,mT);
            lpol->poligonos[indice].pontos[i].x = r[0][0];
            lpol->poligonos[indice].pontos[i].y = r[1][0];
        }
    }
}

void rotacionarPoligono(Lpol *lpol, int indice){
    if (lpol == NULL || lpol->qtd_poligonos == 0)
        printf("Lista vazia ou ocorreu um erro inesperado.\n");
    else{
        float **r;
        float centroidex = 0, centroidey = 0;
        for(int i = 0; i<lpol->poligonos[indice].qtd_p_poligono; i++){
            centroidex += lpol->poligonos[indice].pontos[i].x;
            centroidey += lpol->poligonos[indice].pontos[i].y;
        }

        centroidex /= lpol->poligonos[indice].qtd_p_poligono;
        centroidey /= lpol->poligonos[indice].qtd_p_poligono;

        mT = criarMatrizT(centroidex, centroidey);
        mTi = criarMatrizTi(centroidex, centroidey);
        mR = criarMatrizR();

        for(int i = 0; i<lpol->poligonos[indice].qtd_p_poligono; i++){
            mP = criarMatrizPonto(lpol->poligonos[indice].pontos[i].x, lpol->poligonos[indice].pontos[i].y);
            r = rotacionar(mP,mT,mR,mTi);
            lpol->poligonos[indice].pontos[i].x = r[0][0];
            lpol->poligonos[indice].pontos[i].y = r[1][0];
        }
    }
}

void escalarPoligono(Lpol *lpol, int indice){
    if (lpol == NULL || lpol->qtd_poligonos == 0)
        printf("Lista vazia ou ocorreu um erro inesperado.\n");
    else{
        float **r;
        float centroidex = 0, centroidey = 0;
        for(int i = 0; i<lpol->poligonos[indice].qtd_p_poligono; i++){
            centroidex += lpol->poligonos[indice].pontos[i].x;
            centroidey += lpol->poligonos[indice].pontos[i].y;
        }

        centroidex /= lpol->poligonos[indice].qtd_p_poligono;
        centroidey /= lpol->poligonos[indice].qtd_p_poligono;

        mT = criarMatrizT(centroidex, centroidey);
        mTi = criarMatrizTi(centroidex, centroidey);
        mE = criarMatrizR();

        for(int i = 0; i<lpol->poligonos[indice].qtd_p_poligono; i++){
            mP = criarMatrizPonto(lpol->poligonos[indice].pontos[i].x, lpol->poligonos[indice].pontos[i].y);
            r = escalar(mP,mT,mE,mTi);
            lpol->poligonos[indice].pontos[i].x = r[0][0];
            lpol->poligonos[indice].pontos[i].y = r[1][0];
        }
    }
}
