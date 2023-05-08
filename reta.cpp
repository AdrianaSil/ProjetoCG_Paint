#include <stdlib.h>
#include <GL/glut.h>
#include "reta.h"

Lr* criarLr(){
    Lr *lr;
    lr = (Lr*)malloc(sizeof(Lr));
    if(lr != NULL){
        lr->qtd_retas = 0;
    }
    return lr;
}

int ListaVazia(Lr *lr){
    if(lr->qtd_retas == 0)
        return 1; //lista vazia
    else
        return 0;
}

int ListaCheia(Lr *lr){
    if(lr->qtd_retas == MAX_LINES)
        return 1;
    else
        return 0;
}

void addReta(Lr *lr, Ponto p1, Ponto p2){
    if(lr == NULL)
        printf("Erro na lista.\n");
    else if(ListaCheia(lr))
        printf("Atingiu qtd maxima de retas.\n");
    else{
        lr->retas[lr->qtd_retas].inicio = p1;
        lr->retas[lr->qtd_retas].fim = p2;
        lr->qtd_retas++;
    }
}

void removerReta(Lr *lr, int indice){
    if(lr == NULL || ListaVazia(lr) == 1)
        printf("Lista vazia ou ocorreu um erro inesperado.\n");
    else{
        for(int i = indice; i<(lr->qtd_retas-1); i++){
            lr->retas[i] = lr->retas[i+1];
        }
        lr->qtd_retas--;
    }
}

void desenhaRetas(Lr *lr){
    glLineWidth(2.0);
    glBegin(GL_LINES);
    for(int i = 0; i < lr->qtd_retas; i++){
        glColor3f(0, 1, 0);
        glVertex2f(lr->retas[i].inicio.x, altura - lr->retas[i].inicio.y);
        glVertex2f(lr->retas[i].fim.x, altura - lr->retas[i].fim.y);
    }
    glEnd();
}

int codificacao(Ponto p, float mx, float my){
    int code = 0;
    //E D AB AC
    if(p.x < mx - t)        //Verifica se está a esquerda
        code += 8;
    else if(p.x > my + t)   //Verifica se está a direita
        code += 4;
    if(p.y < my - t)        //Verifica se está abaixo
        code += 2;
    else if(p.y > my + t)  //Verifica se está acima
        code += 1;
    return code;
}

int cohenSutherlandLineClip(Ponto p1, Ponto p2, float mx, float my){
    int cod1 = codificacao(p1, mx, my);
    int cod2 = codificacao(p2, mx, my);
    boolean done = FALSE;
    int selecionado = 0;

    /*printf("Verificando seleção\n");
    printf("Mouse: %f %f \n", mx, my);
    printf("cod1 %d\n", cod1);
    printf("cod2 %d\n", cod2);
    printf("Estão fora: %d\n", (cod1 & cod2));*/

    do{ //interrompido quando estiver totalmente dentro ou totalmente fora do limite do mouse
        if((cod1 == 0) && (cod2 == 0)) { //ambos estão dentro
            selecionado = 1;
            done = TRUE;
        }
        else if((cod1 & cod2) != 0){ //ambos estão fora
            done = TRUE;
        }
        else{
            int cod_out; // vertice que esta fora do limite do mouse
            float x, y;

            if(cod1 != 0)  //se p1 for o ponto que está fora do limite
                cod_out = cod1;
            else
                cod_out = cod2; //se p2 for o ponto fora do limite

            //faz corte e determina ponto de intersecção
            if(cod_out & 8) { //Lado E foi cortado pela linha
                x = (mx - t);
                y = p1.y + (p2.y - p1.y) * ((mx - t) - p1.x) / (p2.x - p1.x);
            }
            else if(cod_out & 4) { //Lado D foi cortado pela linha
                x = (mx + t);
                y = p1.y + (p2.y - p1.y) * ((mx + t) - p1.x) / (p2.x - p1.x);
            }
            else if(cod_out & 2) { //Lado AB foi cortado pela linha
                x = p1.x + (p2.x - p1.x) * ((my - t) - p1.y) / (p2.y - p1.y);
                y = (my - t);
            }
            else if(cod_out & 1) { //Lado AC foi cortado pela linha
                x = p1.x + (p2.x - p1.x) * ((my + t) - p1.y) / (p2.y - p1.y);
                y = (my + t);
            }

            if(cod_out == cod1) { //se p1 estiver fora atualiza coordenadas e codificação
                p1.x = x;
                p1.y = y;
                cod1 = codificacao(p1, mx, my);
            }
            else{ //se p2 estiver fora atualiza coordenadas e codificação
                p2.x = x;
                p2.y = y;
                cod2 = codificacao(p2, mx, my);
            }
        }
    }while(!done);
    return selecionado;
}

int selecionarReta(Lr *lr, float mx, float my){ // determinar se uma linha, definida por seus pontos extremos, deve ser recortada em relação a uma região retangular definida por um ponto central (mx,my) e sua area de tolerancia t.
    if(lr == NULL || lr->qtd_retas == 0){
        printf("Lista vazia ou ocorreu um erro inesperado.\n");
        return -1;
    }
    else{
        Ponto p1;
        Ponto p2;
        for(int i = 0; i < lr->qtd_retas; i++){
            p1.x = lr->retas[i].inicio.x;
            p1.y = lr->retas[i].fim.x;

            p2.x = lr->retas[i].inicio.y;
            p2.y = lr->retas[i].fim.y;

            if(cohenSutherlandLineClip(p1, p2, mx, my) == 1){ //retorna indice da linha selecionada
                return i;
            }
        }
        return -1;
    }
}

void transladarReta(Lr *lr, int indice, float mx, float my){
    if(lr == NULL || lr->qtd_retas == 0)
        printf("Lista vazia ou ocorreu um erro inesperado.\n");
    else{
        mT = criarMatrizT(mx - lr->retas[indice].inicio.x, my - lr->retas[indice].inicio.y);
        mP = criarMatrizPonto(lr->retas[indice].inicio.x, lr->retas[indice].inicio.y);
        float **r1 = transladar(mP,mT);

        mP = criarMatrizPonto(lr->retas[indice].fim.x, lr->retas[indice].fim.y);
        float **r2 = transladar(mP,mT);

        lr->retas[indice].inicio.x = r1[0][0];
        lr->retas[indice].inicio.y = r1[1][0];

        lr->retas[indice].fim.x = r2[0][0];
        lr->retas[indice].fim.y = r2[1][0];

    }
}

void rotacionarReta(Lr *lr, int indice){
    if (lr == NULL || lr->qtd_retas == 0)
        printf("Lista vazia ou ocorreu um erro inesperado.\n");
    else{
        float meiox = (lr->retas[indice].inicio.x + lr->retas[indice].fim.x) / 2;
        float meioy = (lr->retas[indice].inicio.y + lr->retas[indice].fim.y) / 2;

        mR = criarMatrizR();
        mP = criarMatrizPonto(lr->retas[indice].inicio.x, lr->retas[indice].inicio.y);
        mT = criarMatrizT(meiox, meioy);
        mTi = criarMatrizTi(meiox, meioy);
        float **r1 = rotacionar(mP, mT, mR, mTi);

        mP = criarMatrizPonto(lr->retas[indice].fim.x, lr->retas[indice].fim.y);
        float **r2 = rotacionar(mP, mT, mR, mTi);

        lr->retas[indice].inicio.x = r1[0][0];
        lr->retas[indice].inicio.y = r1[1][0];

        lr->retas[indice].fim.x = r2[0][0];
        lr->retas[indice].fim.y = r2[1][0];
    }
}

void escalarReta(Lr *lr, int indice){
    if (lr == NULL || lr->qtd_retas == 0)
        printf("Lista vazia ou ocorreu um erro inesperado.\n");
    else{
        float meiox = (lr->retas[indice].inicio.x + lr->retas[indice].fim.y) / 2;
        float meioy = (lr->retas[indice].inicio.y + lr->retas[indice].fim.y) / 2;

        mE = criarMatrizE();
        mP = criarMatrizPonto(lr->retas[indice].inicio.x, lr->retas[indice].inicio.y);
        mT = criarMatrizT(meiox, meioy);
        mTi = criarMatrizTi(meiox, meioy);
        float **r1 = rotacionar(mP, mT, mE, mTi);

        mP = criarMatrizPonto(lr->retas[indice].fim.x, lr->retas[indice].fim.y);
        float **r2 = escalar(mP, mT, mE, mTi);

        lr->retas[indice].inicio.x = r1[0][0];
        lr->retas[indice].inicio.y = r1[1][0];

        lr->retas[indice].fim.x = r2[0][0];
        lr->retas[indice].fim.y = r2[1][0];
    }
}
