#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <wingdi.h>
#include <GL/glut.h>
#include <assert.h>
#include <GL/gl.h>
#include <GL/glaux.h>
#include <bits/stdc++.h>
#include "light.h"
#include "group.h"
#include "point.h"
#include "normal.h"
#include "surface.h"
#include "loadtexture.h"
#include "model.h"
#define WIDTH 1000
#define HEIGHT 500
#define maxn 1500
using namespace std;
int anglex=0,angley=0,anglez=0;
static Model model("model.dae(1).obj");
Light light(GL_LIGHT0,Light::DIRECTIONAL_LIGHT,Light::DEFAULT);
void init()
{
    light.setLightAmbient(1,0,0);
    light.setLightDiffuse(1,0,0);
    light.setLightModelAmbient(1,0,0);
    light.setLightPosition(1,1,1);
    light.init();
    light.enable();
}
void display(void)
{
    glClearColor(0.0,0.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(anglex,1,0,0);
    glRotatef(angley,0,1,0);
    glRotatef(anglez,0,0,1);

    model.drawModel();
}
void keyboardfunc(unsigned char key,int x,int y)
{
    if (key=='x')
    {
        anglex++;
        display();
    }
    if (key=='y')
    {
        angley++;
        display();
    }
    if (key=='z')
    {
        anglez++;
        display();
    }
    if (key==27)
        exit(0);
}
int main(int argc, char* argv[])
{
    model.loadModel();
    glutInit(&argc,argv);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(WIDTH,HEIGHT);
//    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("test");
    //init();
    glutDisplayFunc(&display);
    glutKeyboardFunc(&keyboardfunc);
    glutMainLoop();
    return 0;
}
