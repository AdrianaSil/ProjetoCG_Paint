#include <stdlib.h>
#include <windows.h>
#include <GL/glut.h>

#include "ponto.cpp"
#include "reta.cpp"
#include "poligono.cpp"

#define largura 500
#define altura 500

//variaveis globais
Lp *listaPontos = NULL;
Lr *listaRetas = NULL;
Lpol *listaPoligonos = NULL;

GLfloat mx, my;             //armazenar valor em float da posição do mouse
GLint op;                   //armazenar opção escolhida do menu
Ponto aux[MAX_P_POLYGON];   //vetor para auxiliar a criação de retas e poligonos
int qtd_p = 0;              //auxilia no controle da qtd de pontos na criação dos objetos
int indice;                 //armmazena indice do objeto selecionado

void criarMenu();
void menu(int opcao);
void cliqueMouse(int botao, int estado, int x, int y);

void init(){

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, largura, 0.0, altura);
}

void display(){

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    desenhaPontos(listaPontos);
    desenhaRetas(listaRetas);
    desenhaPoligono(listaPoligonos);

    glFlush();
}

int main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(largura, altura);
    glutInitWindowPosition(400, 200);
    glutCreateWindow("Projeto CG - Paint com OpenGL");

    criarMenu();
    glutMouseFunc(cliqueMouse);

    listaPontos = criarLp();
    listaRetas = criarLr();
    listaPoligonos = criarLpol();

    init();

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

void criarMenu() {

    int menu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Ponto", 1);
    glutAddMenuEntry("Reta", 2);
    glutAddMenuEntry("Poligono", 3);
    glutAddMenuEntry("Transladar ponto", 4);
    glutAddMenuEntry("Transladar reta", 5);
    glutAddMenuEntry("Transladar poligono", 6);
    glutAddMenuEntry("Rotacionar ponto", 7);
    glutAddMenuEntry("Rotacionar reta", 8);
    glutAddMenuEntry("Rotacionar poligono", 9);
    glutAddMenuEntry("Escalar reta", 10);
    glutAddMenuEntry("Escalar poligono", 11);
    glutAddMenuEntry("Deletar ponto", 12);
    glutAddMenuEntry("Deletar reta", 13);
    glutAddMenuEntry("Deletar poligono", 14);
    glutAddMenuEntry("Selecionar ponto", 15);
    glutAddMenuEntry("Selecionar reta", 16);
    glutAddMenuEntry("Selecionar poligono", 17);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

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
                addPonto(listaPontos,mx, my);
            }
            break;
        case 2: //criar reta
            if(botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN){
                aux[qtd_p].x = mx;
                aux[qtd_p].y = my;
                qtd_p++;
                if(qtd_p == 2){
                    addReta(listaRetas,aux[0], aux[1]);
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
                addPoligono(listaPoligonos, aux, qtd_p);
                qtd_p = 0;
            }
            break;
        case 4: //Transladar ponto
            if(botao ==  GLUT_LEFT_BUTTON && estado == GLUT_DOWN)
                indice = selecionarPonto(listaPontos, mx, my);
            else if(botao == GLUT_MIDDLE_BUTTON && estado == GLUT_DOWN)
                transladarPonto(listaPontos, indice, mx, my);
            break;
        case 5: //Transladar reta
            if(botao ==  GLUT_LEFT_BUTTON && estado == GLUT_DOWN)
                indice = selecionarReta(listaRetas, mx, my);
            else if(botao == GLUT_MIDDLE_BUTTON && estado == GLUT_DOWN && indice != -1)
                transladarReta(listaRetas, indice, mx, my);
            break;
        case 6: //Transladar poligono
            if(botao ==  GLUT_LEFT_BUTTON && estado == GLUT_DOWN)
                indice = selecionarPoligono(listaPoligonos, mx, my);
            else if(botao == GLUT_MIDDLE_BUTTON && estado == GLUT_DOWN && indice != -1)
                transladarPoligono(listaPoligonos, indice, mx, my);
            break;
        case 7: //Rotacionar ponto
            if(botao ==  GLUT_LEFT_BUTTON && estado == GLUT_DOWN){
                rotacionarPonto(listaPontos, selecionarPonto(listaPontos, mx, my));
            }
            break;
        case 8: //Rotacionar reta
            if(botao ==  GLUT_LEFT_BUTTON && estado == GLUT_DOWN){
                indice = selecionarReta(listaRetas, mx, my);
                if(indice != -1)
                    rotacionarReta(listaRetas, indice);
            }
            break;
        case 9: //Rotacionar poligono
            if(botao ==  GLUT_LEFT_BUTTON && estado == GLUT_DOWN){
                indice = selecionarPoligono(listaPoligonos, mx, my);
                if(indice != -1)
                    rotacionarPoligono(listaPoligonos, indice);
            }
            break;
        case 10: //Escalar reta
            if(botao ==  GLUT_LEFT_BUTTON && estado == GLUT_DOWN){
                indice = selecionarReta(listaRetas, mx, my);
                if(indice != -1)
                    escalarReta(listaRetas, indice);
            }
            break;
        case 11: //Escalar poligono
            if(botao ==  GLUT_LEFT_BUTTON && estado == GLUT_DOWN){
                indice = selecionarPoligono(listaPoligonos, mx, my);
                if(indice != -1)
                    escalarPoligono(listaPoligonos, indice);
            }
            break;
        case 12: //Deletar ponto
            if(botao ==  GLUT_LEFT_BUTTON && estado == GLUT_DOWN){
                removerPonto(listaPontos,selecionarPonto(listaPontos,mx, my));
            }
            break;
        case 13: //Deletar reta
            if(botao ==  GLUT_LEFT_BUTTON && estado == GLUT_DOWN){
                indice = selecionarReta(listaRetas, mx, my);
                if(indice != -1)
                    removerReta(listaRetas,indice);
            }
            break;
        case 14: //Deletar poligono
            if(botao ==  GLUT_LEFT_BUTTON && estado == GLUT_DOWN){
                indice = selecionarPoligono(listaPoligonos, mx, my);
                if(indice != -1)
                    removerPoligono(listaPoligonos,indice);
            }
            break;
        case 15: //selecionar ponto
            if(botao ==  GLUT_LEFT_BUTTON && estado == GLUT_DOWN){
                selecionarPonto(listaPontos,mx, my);
            }
            break;
        case 16: //selecionar reta
            if(botao ==  GLUT_LEFT_BUTTON && estado == GLUT_DOWN){
                selecionarReta(listaRetas, mx, my);
            }
            break;
        case 17: //selecionar poligono
            if(botao ==  GLUT_LEFT_BUTTON && estado == GLUT_DOWN){
                selecionarPoligono(listaPoligonos, mx, my);
            }
            break;
    glutPostRedisplay();
    }
}
