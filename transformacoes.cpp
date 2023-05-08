#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

float sx = 5.0;
float sy = 5.0;

float **criarMatrizPonto(float x, float y){
    float **mP = (float **)malloc(3 * sizeof(float *));
    for(int i = 0; i < 3; i++){
        mP[i] = (float *)malloc(sizeof(float));
    }
    mP[0][0] = x;
    mP[1][0] = y;
    mP[2][0] = 1.0;
    return mP;
}

float **criarMatrizTi(float tx, float ty){
    float **mTi = (float **)malloc(3 * sizeof(float *));
    for(int i = 0; i < 3; i++){
        mTi[i] = (float *)malloc(3 * sizeof(float));
        for(int j = 0; j < 3; j++) {
            if(i == j)
                mTi[i][j] = 1.0;
            else
                mTi[i][j] = 0;
        }
    }

    mTi[0][2] = (-1) * tx;
    mTi[1][2] = (-1) * ty;
    return mTi;
}

float **criarMatrizT(float tx, float ty){
    float **mT = (float **)malloc(3 * sizeof(float *));
    for(int i = 0; i < 3; i++){
        mT[i] = (float *)malloc(3 * sizeof(float));
        for(int j = 0; j < 3; j++) {
            if(i == j)
                mT[i][j] = 1.0;
            else
                mT[i][j] = 0;
        }
    }

    mT[0][2] = tx;
    mT[1][2] = ty;
    return mT;
}

float **criarMatrizR(){
    float **mR = (float **)malloc(3 * sizeof(float *));
    for(int i = 0; i < 3; i++){
        mR[i] = (float *)malloc(3 * sizeof(float));
        for(int j = 0; j < 3; j++) {
            if(i == j)
                 mR[i][j] = 1.0;
            else
                mR[i][j] = 0;
        }
    }
    //rotaçao 30º
    mR[0][0] = 0.8660; //cos(30º)
    mR[0][1] = -0.5000; //-sen(30º)
    mR[1][0] = 0.5000; //sen(30º)
    mR[1][1] = 0.8660; //cos(30º)
    return mR;
}

float **criarMatrizE(){
    float **mE = (float **)malloc(3 * sizeof(float *));
    for(int i = 0; i < 3; i++){
        mE[i] = (float *)malloc(3 * sizeof(float));
        for(int j = 0; j < 3; j++) {
            if(i == j)
                mE[i][j] = 1.0;
            else
                mE[i][j] = 0;
        }
    }
    mE[0][0] = sx;
    mE[1][1] = sy;
    return mE;
}

float **mult_matrizes(float **m1, float **m2, int l, int c){
    float **r = (float **)malloc(l * sizeof(float *));
    for(int i = 0; i < l; i++) {
        r[i] = (float *)malloc(c * sizeof(float));
        for(int j = 0; j < c; j++) {
             r[i][j] = 0;
            for(int k = 0; k < l; k++) {
                r[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
    return r;
}

float **matrizComposta(float **m1, float **m2, float **m3){
    float **r = (float **)malloc(3 * sizeof(float *));
    for(int i = 0; i < 3; i++) {
        r[i] = (float *)malloc(3 * sizeof(float));
    }
    r = mult_matrizes(mult_matrizes(m1,m2, 3, 3), m3, 3, 3);
    return r;
}

float **transladar(float **mP, float **mT){
    float **r = (float **)malloc(3 * sizeof(float *));
    for(int i = 0; i < 3; i++) {
        r[i] = (float *)malloc(sizeof(float));
    }
    r = mult_matrizes(mT,mP, 3, 1);
    return r;
}


float **escalar(float **mP, float **mT, float **mE, float **mTi){
    float **r = (float **)malloc(3 * sizeof(float *));
    for(int i = 0; i < 3; i++) {
        r[i] = (float *)malloc(sizeof(float));
    }
    r = mult_matrizes(matrizComposta(mT,mE,mTi), mP, 3, 1);
    return r;
}

float **rotacionar(float **mP, float **mT, float **mR, float **mTi){
    float **r = (float **)malloc(3 * sizeof(float *));
    for(int i = 0; i < 3; i++) {
        r[i] = (float *)malloc(sizeof(float));
    }
    r = mult_matrizes(matrizComposta(mT,mR,mTi), mP, 3, 1);
    return r;
}
