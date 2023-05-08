#include <stdlib.h>
#include <cstdio>
#include <windows.h>
#include <GL/glut.h>
#include "paint.h"
#include <GLFW/glfw3.h>

#define largura 500
#define altura 500

#define MAX_POINTS 10
#define MAX_LINES 10
#define MAX_POLYGON 10
#define MAX_P_POLYGON 10


//variaveis globais
GLfloat mx, my; //armazenar valor em float da posição do mouse
GLint op; //armazenar opção escolhida do menu
Ponto aux[MAX_P_POLYGON]; //vetor para auxiliar a criação de retas e poligonos
int qtd_p = 0; //controla e guarda a qtd de pontos (auxilia no controle da qtd de pontos na criação dos objetos)

/*
//Estrutura para definir uma reta
typedef struct{
    Ponto inicio;
    Ponto fim;
}Reta;

//Estrutura para definir um poligono
typedef struct{
    Ponto pontos[MAX_P_POLYGON];
    int tam;
}Poligono;

//define vetor para armazenar pontos no programa
int qtd_pontos = 0;
Ponto pontos[MAX_POINTS];

//define vetor para armazenar retas no programa
int qtd_retas = 0;
Reta retas[MAX_LINES];

//define vetor para armazenar poligonos no programa
int qtd_poligonos = 0;
Poligono poligonos[MAX_POLYGON];

*/

//Menu
void criarMenu() {
    int menu_id = glutCreateMenu(menu);

    glutAddMenuEntry("Ponto", 1);
    glutAddMenuEntry("Reta", 2);
    glutAddMenuEntry("Poligono", 3);
    glutAddMenuEntry("Transladar objeto", 4);
    glutAddMenuEntry("Rotacionar objeto", 5);
    glutAddMenuEntry("Escala de objeto", 6);
    glutAddMenuEntry("Deletar objeto", 7);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/*
//Ponto
void addPonto(float x, float y){
    if(qtd_pontos == MAX_POINTS){
        printf("Atingiu qtd maxima de pontos.\n");
    }
    else{
        pontos[qtd_pontos].x = x;
        pontos[qtd_pontos].y = y;
        qtd_pontos++;
    }
}
void removePonto(float x, float y){
    if(qtd_pontos == 0){
        //invalida
    }
    else{
        //remove
        qtd_pontos -= 1;
    }
}
*/

/*

//Reta
void addReta(Ponto p1, Ponto p2){
    if(qtd_retas == MAX_LINES){
        printf("Atingiu qtd maxima de pontos.\n");
    }
    else{
        retas[qtd_retas].inicio = p1;
        retas[qtd_retas].fim = p2;
        qtd_retas++;
    }
}
void removeReta(){
    if(qtd_retas == 0){
        //invalida
    }
    else{
        //remove
        qtd_retas -= 1;
    }
}
*/

/*
//Poligono
void addPoligono(Ponto p[], int tam){
    if(qtd_poligonos == MAX_POLYGON){
        printf("Atingiu qtd maxima de poligonos.\n");
    }
    else{
        for(int i=0; i<tam; i++){
            poligonos[qtd_poligonos].pontos[i] = p[i];
        }
        poligonos[qtd_poligonos].tam = tam;
        qtd_poligonos ++;
    }
}
void removePoligono(){
    if(qtd_poligonos == 0){
        //invalida
    }
    else{
        //remove
        qtd_poligonos -= 1;
    }
}
*/

/*
//Desenhar formas
void desenhaPontos(){
    glPointSize(5.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < qtd_pontos; i++){
        glColor3f(1, 0, 0); //define a cor vermelho
        glVertex2f(pontos[i].x, altura - pontos[i].y); //define localização do vértice
    }
    glEnd();
}
*/

/*
void desenhaRetas(){
    glLineWidth(2.0);
    glBegin(GL_LINES);
    for (int i = 0; i < qtd_pontos; i++){
        glColor3f(0, 0, 1); //define a cor azul
        glVertex2f(retas[i].inicio.x, altura - retas[i].inicio.y); //define localização do vértice A
        glVertex2f(retas[i].fim.x, altura - retas[i].fim.y); //define localização do vértice B
    }
    glEnd();
}
*/

/*
void desenhaPoligono(){
    glLineWidth(2.0);
    for(int i = 0; i < qtd_poligonos; i++){
        glBegin(GL_POLYGON);
        glColor3f(0, 1, 1);
        for(int j = 0; j < poligonos[i].tam; j++){
            glVertex2f(poligonos[i].pontos[j].x, altura - poligonos[i].pontos[j].y);
        }
        glEnd();
    }
}

*/

void menu(int opcao){
     op = opcao;
}

//Eventos do mouse
void cliqueMouse(int botao, int estado, int x, int y) {
    mx = x;
    my = y;

    switch(op) {
        case 1:
            if(botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN){
                addPonto(mx, my);
            }
            break;
        case 2: //criar reta
            if(botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN){
                aux[qtd_p].x = mx;
                aux[qtd_p].y = my;
                qtd_p++;
                if(qtd_p == 2){
                    addReta(aux[0], aux[1]);
                    qtd_p = 0;
                }
            }
            break;
        case 3: //criar poligono
            if(botao ==  GLUT_LEFT_BUTTON && estado == GLUT_DOWN){
                if(qtd_p <= MAX_P_POLYGON){
                    aux[qtd_p].x = mx;
                    aux[qtd_p].y = my;
                    qtd_p++;
                }
            }
            else if(botao == GLUT_MIDDLE_BUTTON && estado == GLUT_DOWN && qtd_p > 2){ //só se pode fazer um poligono com pelo menos 3 pontos
                addPoligono(aux, qtd_p);
                qtd_p = 0;
            }
            break;
    glutPostRedisplay();
    }
}


/*
void transPonto() {

    for (int i = 0; i < qtd_pontos; i++){
        if ((pontos[i].x == selecX) && (pontos[i].y == selecY)){
            float offX = transX - pontos[i].x;
            float offY = transY - pontos[i].y;

           float MatrizT[3][3] = {
           {1,0,offX},
           {0,1,offY},
           {0,0,   1}
           };

           float MatrizP[3][1] = {
           {pontos[i].x},
           {pontos[i].y},
           {     1    }
           };

           float MatrizR[3][1];

           for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 1; j++) {
                    MatrizR[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizR[i][j] += MatrizT[i][k] * MatrizP[k][j];
                    }
                }
            }

            pontos[i].x = MatrizR[0][0];
            pontos[i].y = MatrizR[1][0];
            glutPostRedisplay();
        }
    }
}

//FUNCAO DE TRANSLACAO DA RETA
void transReta() {
    float centroideX = 0;
    float centroideY = 0;

    centroideX = centroideX + retas[selecReta].inicio.x + retas[selecReta].fim.x;
    centroideY = centroideY + retas[selecReta].inicio.y + retas[selecReta].fim.y;

    centroideX = (centroideX/2);
    centroideY = (centroideY/2);

    int window_width = glutGet(GLUT_WINDOW_WIDTH);
    int window_height = glutGet(GLUT_WINDOW_HEIGHT);

    for (int i = 0; i < qtd_retas; i++){

        if (i == selecReta){
            float offX = transX - centroideX;
            float offY = transY - centroideY;

           float MatrizT[3][3] = {
           {1,0,offX},
           {0,1,offY},
           {0,0,   1}
           };

           float MatrizP[3][1] = {
           {retas[selecReta].inicio.x},
           {retas[selecReta].inicio.y},
           {     1    }
           };
           float MatrizP2[3][1] = {
           {retas[selecReta].fim.x},
           {retas[selecReta].fim.y},
           {     1    }
           };

           float MatrizR[3][1];
           float MatrizR2[3][1];
           for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 1; j++) {
                    MatrizR[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizR[i][j] += MatrizT[i][k] * MatrizP[k][j];
                    }
                }
            }
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 1; j++) {
                    MatrizR2[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizR2[i][j] += MatrizT[i][k] * MatrizP2[k][j];
                    }
                }
            }

            retas[selecReta].inicio.x = MatrizR[0][0];
            retas[selecReta].inicio.y = MatrizR[1][0];

            retas[selecReta].fim.x = MatrizR2[0][0];
            retas[selecReta].fim.y = MatrizR2[1][0];
            glutPostRedisplay();
        }
    }

}

// FUNCAO DE TRANSLAÇAO DO POLIGONO
void TransPoli(){

    float centroideX = 0;
    float centroideY = 0;
    for(int i =0; i < qtd_pontos_poligonos[selectPoligon]; i++){

        centroideX = centroideX + poligonos[selectPoligon][i].x;
        centroideY = centroideY + poligonos[selectPoligon][i].y;
    }

    centroideX = centroideX/(float)qtd_pontos_poligonos[selectPoligon];
    centroideY = centroideY/(float)qtd_pontos_poligonos[selectPoligon];
    //printf("Centroide x: %.2f", centroideX);


    int window_width = glutGet(GLUT_WINDOW_WIDTH);
    int window_height = glutGet(GLUT_WINDOW_HEIGHT);
    /*
    //centroideX = ((float)centroideX / (float)window_width - 0.5) * 2.0;
    //centroideY = ((float)(window_height - centroideY) / (float)window_height - 0.5) * 2.0;
    //*


    for(int n =0; n < qtd_pontos_poligonos[selectPoligon]; n++){

        float offX = mousex - centroideX;
        float offY = mousey - centroideY;

        printf("Ponto selecionado: %.2f, %.2f\n",poligonos[selectPoligon][n].x, poligonos[selectPoligon][n].y );
        printf("ponto destino: %.2f, %.2f\n", transX, transY);
        printf("OffX: %.2f, offy: %.2f\n", offX, offY);

        float MatrizT[3][3] = {
           {1,0,offX},
           {0,1,offY},
           {0,0,   1}
           };

        float MatrizP[3][1] = {
           {  (poligonos[selectPoligon][n].x)  },
           {  (poligonos[selectPoligon][n].y)  },
           {     1    }
           };

        float MatrizR[3][1];

        for(int i = 0; i < 3; i++) {
                for (int j = 0; j < 1; j++) {
                    MatrizR[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizR[i][j] += (MatrizT[i][k]) * (MatrizP[k][j]);
                    }
                }
            }

            for (int i = 0; i < 3; i++) {
                printf("%.2f\n", MatrizR[i][0]);
            }

            float newX = MatrizR[0][0];
            float newY = MatrizR[1][0];

            printf("X normal: %.2f\n", newX);
            printf("Y normal: %.2f\n", newY);

            poligonos[selectPoligon][n].x = newX;
            poligonos[selectPoligon][n].y = newY;

            printf("###\n");
            glutPostRedisplay();
    }
}

// FUNCAO DE ESCALA DA RETA
void Escalreta() {
    float centroideX = 0;
    float centroideY = 0;
    int window_width = glutGet(GLUT_WINDOW_WIDTH);
    int window_height = glutGet(GLUT_WINDOW_HEIGHT);
    centroideX = centroideX + retas[selecReta].inicio.x + retas[selecReta].fim.x;
    centroideY = centroideY + retas[selecReta].inicio.y + retas[selecReta].fim.y;

    centroideX = (centroideX/2);
    centroideY = (centroideY/2);

    for (int i = 0; i < qtd_retas; i++){

        if (i == selecReta){
            float offX = centroideX;
            float offY = centroideY;

           float MatrizT[3][3] = {
           {1,0,offX},
           {0,1,offY},
           {0,0,   1}
           };
           float MatrizV[3][3] = {
           {1,0,-offX},
           {0,1,-offY},
           {0,0,    1}
           };
           float MatrizE[3][3] = {
           {fatE  ,0   ,   0},
           {  0   ,fatE,   0},
           {0     ,0   ,   1}
           };
           float MatrizP[3][1] = {
           {retas[selecReta].inicio.x},
           {retas[selecReta].inicio.y},
           {     1    }
           };
           float MatrizP2[3][1] = {
           {retas[selecReta].fim.x},
           {retas[selecReta].fim.y},
           {     1    }
           };

           float MatrizRI[3][1];
           float MatrizRI2[3][3];
           float MatrizRI3[3][3];

           float MatrizRF[3][1];
           float MatrizRF2[3][3];
           float MatrizRF3[3][3];
            //para o primeiro ponto da reta
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    MatrizRI2[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizRI2[i][j] += MatrizT[i][k] * MatrizE[k][j];
                    }
                }
            }

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    MatrizRI3[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizRI3[i][j] += MatrizRI2[i][k] * MatrizV[k][j];
                    }
                }
            }

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 1; j++) {
                    MatrizRI[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizRI[i][j] += MatrizRI3[i][k] * MatrizP[k][j];
                    }
                }
            }
            //para o segundo ponto da reta
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    MatrizRF2[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizRF2[i][j] += MatrizT[i][k] * MatrizE[k][j];
                    }
                }
            }

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    MatrizRF3[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizRF3[i][j] += MatrizRF2[i][k] * MatrizV[k][j];
                    }
                }
            }

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 1; j++) {
                    MatrizRF[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizRF[i][j] += MatrizRF3[i][k] * MatrizP2[k][j];
                    }
                }
            }

            retas[selecReta].inicio.x = (MatrizRI[0][0]);
            retas[selecReta].inicio.y = (MatrizRI[1][0]);

            retas[selecReta].fim.x = (MatrizRF[0][0]);
            retas[selecReta].fim.y = (MatrizRF[1][0]);
            glutPostRedisplay();
        }
    }

}



// FUNCAO DE ESCALA DO POLIGONO
void Escalpoli(){
    float centroideX = 0;
    float centroideY = 0;

    for(int i =0; i < qtd_pontos_poligonos[selectPoligon]; i++){

        centroideX = centroideX + poligonos[selectPoligon][i].x;
        centroideY = centroideY + poligonos[selectPoligon][i].y;
    }

    centroideX = centroideX/(float)qtd_pontos_poligonos[selectPoligon];
    centroideY = centroideY/(float)qtd_pontos_poligonos[selectPoligon];

    for(int n =0; n < qtd_pontos_poligonos[selectPoligon]; n++){

        float offX = centroideX;
        float offY = centroideY;

        float MatrizT[3][3] = {
           {1,0,offX},
           {0,1,offY},
           {0,0,   1}
           };

        float MatrizV[3][3] = {
           {1,0,-offX},
           {0,1,-offY},
           {0,0,    1}
           };

        float MatrizE[3][3] = {
           {fatE  ,0   ,   0},
           {  0   ,fatE,   0},
           {0     ,0   ,   1}
           };

        float MatrizP[3][1] = {
           {  (poligonos[selectPoligon][n].x)},
           {  (poligonos[selectPoligon][n].y)},
           {     1    }
           };

        float MatrizR[3][1];
        float MatrizR2[3][3];
        float MatrizR3[3][3];

        for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    MatrizR2[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizR2[i][j] += MatrizT[i][k] * MatrizE[k][j];
                    }
                }
            }

        for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    MatrizR3[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizR3[i][j] += MatrizR2[i][k] * MatrizV[k][j];
                    }
                }
            }

        for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 1; j++) {
                    MatrizR[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizR[i][j] += MatrizR3[i][k] * MatrizP[k][j];
                    }
                }
            }

            poligonos[selectPoligon][n].x = (MatrizR[0][0]);
            poligonos[selectPoligon][n].y = (MatrizR[1][0]);
            glutPostRedisplay();
    }
}


void Rotreta(){
    float centroideX = 0;
    float centroideY = 0;
    int window_width = glutGet(GLUT_WINDOW_WIDTH);
    int window_height = glutGet(GLUT_WINDOW_HEIGHT);
    centroideX = centroideX + retas[selecReta].inicio.x + retas[selecReta].fim.x;
    centroideY = centroideY + retas[selecReta].inicio.y + retas[selecReta].fim.y;

    centroideX = (centroideX/2);
    centroideY = (centroideY/2);

    for (int i = 0; i < qtd_retas; i++){

        if (i == selecReta){
            float offX = centroideX;
            float offY = centroideY;

           float MatrizT[3][3] = {
           {1,0,offX},
           {0,1,offY},
           {0,0,   1}
           };

           float MatrizV[3][3] = {
           {1,0,-offX},
           {0,1,-offY},
           {0,0,    1}
           };

           float MatrizE[3][3] = {
           {cos(fatR),-sin(fatR),   0},
           {sin(fatR), cos(fatR),   0},
           {0        ,0         ,   1}
           };

           float MatrizP[3][1] = {
           {retas[selecReta].inicio.x},
           {retas[selecReta].inicio.y},
           {     1    }
           };

           float MatrizP2[3][1] = {
           {retas[selecReta].fim.x},
           {retas[selecReta].fim.y},
           {     1    }
           };

           float MatrizRI[3][1];
           float MatrizRI2[3][3];
           float MatrizRI3[3][3];

           float MatrizRF[3][1];
           float MatrizRF2[3][3];
           float MatrizRF3[3][3];

            //para o primeiro ponto da reta
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    MatrizRI2[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizRI2[i][j] += MatrizT[i][k] * MatrizE[k][j];
                    }
                }
            }

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    MatrizRI3[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizRI3[i][j] += MatrizRI2[i][k] * MatrizV[k][j];
                    }
                }
            }

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 1; j++) {
                    MatrizRI[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizRI[i][j] += MatrizRI3[i][k] * MatrizP[k][j];
                    }
                }
            }

            //para o segundo ponto da reta
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    MatrizRF2[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizRF2[i][j] += MatrizT[i][k] * MatrizE[k][j];
                    }
                }
            }

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    MatrizRF3[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizRF3[i][j] += MatrizRF2[i][k] * MatrizV[k][j];
                    }
                }
            }

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 1; j++) {
                    MatrizRF[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizRF[i][j] += MatrizRF3[i][k] * MatrizP2[k][j];
                    }
                }
            }

            retas[selecReta].inicio.x = (MatrizRI[0][0]);
            retas[selecReta].inicio.y = (MatrizRI[1][0]);

            retas[selecReta].fim.x = (MatrizRF[0][0]);
            retas[selecReta].fim.y = (MatrizRF[1][0]);
            glutPostRedisplay();
        }
    }



}


// FUNCAO DE ROTACAO DO POLIGONO
void Rotpoli(){
    float centroideX = 0;
    float centroideY = 0;

    for(int i =0; i < qtd_pontos_poligonos[selectPoligon]; i++){

        centroideX = centroideX + poligonos[selectPoligon][i].x;
        centroideY = centroideY + poligonos[selectPoligon][i].y;
    }

    centroideX = centroideX/(float)qtd_pontos_poligonos[selectPoligon];
    centroideY = centroideY/(float)qtd_pontos_poligonos[selectPoligon];

     for(int n =0; n < qtd_pontos_poligonos[selectPoligon]; n++){

        float offX = centroideX;
        float offY = centroideY;

        float MatrizT[3][3] = {
           {1,0,offX},
           {0,1,offY},
           {0,0,   1}
           };

        float MatrizV[3][3] = {
           {1,0,-offX},
           {0,1,-offY},
           {0,0,    1}
           };

        float MatrizRT[3][3] = {
           {cos(fatR)  ,-sin(fatR),   0},
           {sin(fatR)  ,cos(fatR),    0},
           {0        ,0      ,    1}
           };

        float MatrizP[3][1] = {
           {  (poligonos[selectPoligon][n].x)},
           {  (poligonos[selectPoligon][n].y)},
           {     1    }
           };

        float MatrizR[3][1];
        float MatrizR2[3][3];
        float MatrizR3[3][3];

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                MatrizR2[i][j] = 0;
                for (int k = 0; k < 3; k++) {
                    MatrizR2[i][j] += MatrizT[i][k] * MatrizRT[k][j];
                }
            }
        }

        for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    MatrizR3[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizR3[i][j] += MatrizR2[i][k] * MatrizV[k][j];
                    }
                }
            }

        for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 1; j++) {
                    MatrizR[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        MatrizR[i][j] += MatrizR3[i][k] * MatrizP[k][j];
                    }
                }
            }

        poligonos[selectPoligon][n].x = (MatrizR[0][0]);
        poligonos[selectPoligon][n].y = (MatrizR[1][0]);
        glutPostRedisplay();


     }

}
*/


