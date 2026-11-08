

#include <cstdlib>
#include <vector>
#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;
#define INACTIVE 0
#define TETRAEDO 1



// Globals.
static GLsizei width, height; // OpenGL window size.
static float pointSize = 3.0; // Size of point
static int primitive = INACTIVE; // Current drawing primitive.
static int pointCount = 0; // Number of specified points.
static int tempX, tempY; // Co-ordinates of clicked point.
static int isGrid = 1; // Is there grid?


static int MonitoramentoX, MonitoramentoY;
static int tetraSelecionado = -1;

class Tetraedro{
public:
    float x;
    float y;
    float angulo;
    float escala;

    Tetraedro(float xx, float yy) 
    {
        x = xx;
        y = yy;
        angulo = 0;
        escala = 1;
    }
    void draw();
};


void Tetraedro::draw(){
    glPushMatrix();
    glTranslatef(x, y, 0);
    glRotatef(angulo, 0, 0, 1);
    glScalef(escala, escala, 1);

    glBegin(GL_LINE_LOOP);
        glVertex2f(-20, -20);
        glVertex2f(20, -20);
        glVertex2f(0, 20);
    glEnd();

    glBegin(GL_LINES);
        glVertex2f(-20, -20);
        glVertex2f(0, 0);

        glVertex2f(20, -20);
        glVertex2f(0, 0);

        glVertex2f(0, 20);
        glVertex2f(0, 0);
    glEnd();

    glPopMatrix();
}



vector<Tetraedro> tetraedro;

void drawTetraedro(){
    for(auto &t : tetraedro)
        t.draw();
}




void Monitoramento(int x, int y){
    MonitoramentoX = x;
    MonitoramentoY = height - y;
    glutPostRedisplay();
}


void Tetraedro_Monitoramento(){
    glColor3f(1.0, 0.0, 0.0); 
    Tetraedro tempTetra(MonitoramentoX, MonitoramentoY);
    tempTetra.draw();
}


void DrawIconeTetraedro(){
    if (primitive == TETRAEDO) glColor3f(1.0, 1.0, 1.0);
    else glColor3f(0.8, 0.8, 0.8);
   
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glRectf(0.0, 0.9*height, 0.1*width, 1.0*height);

   glColor3f(0.0, 0.0, 0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glRectf(0.0, 0.9*height, 0.1*width, 1.0*height);

    glBegin(GL_LINE_LOOP);
        glVertex2f(0.05 * width, 0.97 * height);
        glVertex2f(0.03 * width, 0.93 * height);
        glVertex2f(0.07 * width, 0.93 * height);
    glEnd();

    glBegin(GL_LINES);
        glVertex2f(0.05 * width, 0.97 * height);
        glVertex2f(0.05 * width, 0.94 * height);
        glVertex2f(0.03 * width, 0.93 * height);
        glVertex2f(0.05 * width, 0.94 * height);

        glVertex2f(0.07 * width, 0.93 * height);
        glVertex2f(0.05 * width, 0.94 * height);
    glEnd();
}

void drawInactiveArea(void) {
    glColor3f(0.6, 0.6, 0.6);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glRectf(0.0, 0.0, 0.1*width, 0.9*height);

   glColor3f(0.0, 0.0, 0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glRectf(0.0, 0.0, 0.1*width, 0.9*height);
}


void drawGrid(void){
    int i;
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x5555); 
    glColor3f(0.75, 0.75, 0.75);

    glBegin(GL_LINES);
    for (i=2; i <=9; i++){
        glVertex3f(i*0.1*width, 0.0, 0.0);
        glVertex3f(i*0.1*width, height, 0.0);
    }
    
    for (i=1; i <=9; i++){
        glVertex3f(0.1*width, i*0.1*height, 0.0);
        glVertex3f(width, i*0.1*height, 0.0);
    }
    glEnd();
    glDisable(GL_LINE_STIPPLE);
}



void drawScene(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0); 

    if (isGrid) drawGrid();
    drawInactiveArea();
    DrawIconeTetraedro();
    drawTetraedro();

  
    if (MonitoramentoX > 0.1 * width){
        if (pointCount == 0 && primitive == TETRAEDO){
            Tetraedro_Monitoramento();
        }
    }

    glutSwapBuffers();
}

void pickPrimitive(int y) {
    
    if (y >= 0.9 * height && y <= height)
        primitive = TETRAEDO;
    else
        primitive = INACTIVE;
}


void mouseControl(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        y = height - y;

        if (x >= 0 && x <= width && y >= 0 && y <= height) {
            if (x < 0.1 * width) {
                pickPrimitive(y);
                pointCount = 0;
            } else {
                if (primitive == TETRAEDO) {
                    tetraedro.push_back(Tetraedro(x, y));
                    tetraSelecionado = static_cast<int>(tetraedro.size()) - 1; 
                }  
            }
        }
    }
    glutPostRedisplay();
}

 
void setup(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0); 
}


void resize(int w, int h){
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, (float)w, 0.0, (float)h, -1.0, 1.0);
   
    width = w; 
    height = h;  

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void keyInput(unsigned char key, int x, int y){
    if (tetraSelecionado >= 0 && tetraSelecionado < tetraedro.size()){
        switch (key){
            case 'a':
                tetraedro[tetraSelecionado].x -= 10;
            break;
            case 'd':
                tetraedro[tetraSelecionado].x += 10;
            break;
            case 'w':
                tetraedro[tetraSelecionado].y += 10;
            break;
            case 's':
                tetraedro[tetraSelecionado].y -= 10;
            break;
            case 'q':
                tetraedro[tetraSelecionado].angulo += 10;
            break;
            case 'e':
                tetraedro[tetraSelecionado].angulo -= 10;
            break;
            case '+':
                tetraedro[tetraSelecionado].escala += 0.1f;
            break;
            case '-':
                tetraedro[tetraSelecionado].escala -= 0.1f;
            break;
            case 27:
                exit(0);
            break;
        }
    }
    else if (key == 27)
    {
        exit(0);
    }

    glutPostRedisplay();
}


void clearAll(void){
   
   tetraedro.clear();
   pointCount = 0;
   tetraSelecionado = -1;
}


void rightMenu(int id){
   if (id == 1) {
     clearAll();
     glutPostRedisplay();
   }
   if (id == 2) exit(0);
}

void grid_menu(int id){
   if (id == 3) isGrid = 1;
   if (id == 4) isGrid = 0;
   glutPostRedisplay();
}

void makeMenu(void){
   int sub_menu;
   sub_menu = glutCreateMenu(grid_menu);
   glutAddMenuEntry("On", 3);
   glutAddMenuEntry("Off", 4);

   glutCreateMenu(rightMenu);
   glutAddSubMenu("Grid", sub_menu);
   glutAddMenuEntry("Clear", 1);
   glutAddMenuEntry("Quit", 2);
   glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void printInteraction(void){
   cout << "Interaction:" << endl;
   cout << "Left click on a box on the left to select a primitive." << endl
        << "Then left click on the drawing area: once for point, twice for line or rectangle." << endl
        << "Right click for menu options." <<  endl; 
}

int main(int argc, char **argv) {
   printInteraction();
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(100, 100); 
   glutCreateWindow("canvas.cpp");
   setup(); 
   glutDisplayFunc(drawScene); 
   glutReshapeFunc(resize);  
   glutKeyboardFunc(keyInput);
   glutMouseFunc(mouseControl); 
   glutPassiveMotionFunc(Monitoramento);

   makeMenu();

   glutMainLoop(); 

   return 0;  
}
