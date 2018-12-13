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

#include "loadtexture.h"
#include "model.h"
#define WIDTH 1000
#define HEIGHT 500
#define maxn 1500
using namespace std;
int anglex=0,angley=0,anglez=0;
static Model model("mech_f_432.obj");
GLfloat LightAmbient1[]={0,0,1,1};
GLfloat LightDiffuse1[]={0,0,1,1};
GLfloat LightPosition1[]={1,1,1,1};
GLfloat Mat_specular1[]={1,1,1,1};
GLfloat Mat_shininess1[]={50};
GLfloat LightAmbient2[]={0,1,0,1};
GLfloat LightDiffuse2[]={0,1,0,1};
GLfloat LightPosition2[]={-1,-1,1,1};
GLfloat Mat_specular2[]={0,0,1,1};
GLfloat Mat_shininess2[]={50};
GLfloat LightAmbient3[]={1,0,0,1};
GLfloat LightDiffuse3[]={1,0,0,1};
GLfloat LightPosition3[]={1,-1,1,1};
GLfloat Mat_specular3[]={-1,1,1,1};
GLfloat Mat_shininess3[]={50};
void init()
{
    Light light1(GL_LIGHT1,Light::DIRECTIONAL_LIGHT,Light::DEFAULT);
    light1.setLightAmbient(0,0,1);
    light1.setLightDiffuse(0,0,1);
    light1.setLightPosition(1,1,1);
    light1.setMatSpecular(1,1,1);
    light1.setMatShininess(50);
    light1.init();
    light1.enable();
    Light light2(GL_LIGHT2,Light::DIRECTIONAL_LIGHT,Light::DEFAULT);
    light2.setLightAmbient(0,1,0);
    light2.setLightDiffuse(0,1,0);
    light2.setLightPosition(-1,-1,1);
    light2.setMatSpecular(0,0,1);
    light2.setMatShininess(50);
    light2.init();
    light2.enable();
    Light light3(GL_LIGHT3,Light::DIRECTIONAL_LIGHT,Light::DEFAULT);
    light3.setLightAmbient(1,0,0);
    light3.setLightDiffuse(1,0,0);
    light3.setLightPosition(1,-1,1);
    light3.setMatSpecular(1,1,1);
    light3.setMatShininess(50);
    light3.init();
    light3.enable();
}
void display(void)
{
    glClearColor(0.0,0.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
    init();
    glutDisplayFunc(&display);
    glutKeyboardFunc(&keyboardfunc);
    glutMainLoop();
    return 0;
}
