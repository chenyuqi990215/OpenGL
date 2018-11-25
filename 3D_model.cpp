#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/gl.h>
#include <GL/glut.h>
#include <bits/stdc++.h>
#define WIDTH 1000
#define HEIGHT 500
using namespace std;
struct Point
{
    double x,y,z;
    Point (){x=0,y=0,z=0;}
    Point (double x=0,double y=0,double z=0):x(x),y(y),z(z){}
};
GLfloat LightAmbient1[]={0,0,1,1};
GLfloat LightDiffuse1[]={0,0,1,1};
GLfloat LightPosition1[]={1,1,1,1};
GLfloat Mat_specular1[]={1,1,1,1};
GLfloat Mat_shininess1[]={50};
GLfloat LightAmbient2[]={0,1,0,1};
GLfloat LightDiffuse2[]={0,1,0,1};
GLfloat LightPosition2[]={1,1,-1,1};
GLfloat Mat_specular2[]={0,0,1,1};
GLfloat Mat_shininess2[]={50};
GLfloat LightAmbient3[]={1,0,0,1};
GLfloat LightDiffuse3[]={1,0,0,1};
GLfloat LightPosition3[]={-1,1,1,1};
GLfloat Mat_specular3[]={1,1,1,1};
GLfloat Mat_shininess3[]={50};
void init()
{
    glMaterialfv(GL_FRONT,GL_SPECULAR,Mat_specular1);
    glMaterialfv(GL_FRONT,GL_SHININESS,Mat_shininess1);
    glLightfv(GL_LIGHT0,GL_AMBIENT,LightAmbient1);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,LightDiffuse1);
    glLightfv(GL_LIGHT0,GL_POSITION,LightPosition1);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glColorMaterial(GL_FRONT,GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glMaterialfv(GL_FRONT,GL_SPECULAR,Mat_specular2);
    glMaterialfv(GL_FRONT,GL_SHININESS,Mat_shininess2);
    glLightfv(GL_LIGHT2,GL_AMBIENT,LightAmbient2);
    glLightfv(GL_LIGHT2,GL_DIFFUSE,LightDiffuse2);
    glLightfv(GL_LIGHT2,GL_POSITION,LightPosition2);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT2);
    glMaterialfv(GL_FRONT,GL_SPECULAR,Mat_specular3);
    glMaterialfv(GL_FRONT,GL_SHININESS,Mat_shininess3);
    glLightfv(GL_LIGHT1,GL_AMBIENT,LightAmbient3);
    glLightfv(GL_LIGHT1,GL_DIFFUSE,LightDiffuse3);
    glLightfv(GL_LIGHT1,GL_POSITION,LightPosition3);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);
}
double calf(double x)
{
    const double pi=acos(-1);
    const double theta=0.5;
    return 1.0/(sqrt(2*pi)*theta)*exp(-x*x*2/theta/theta);
}
void get_curve1(double stx,double enx,double dely,double posz)
{
    glBegin(GL_LINE_STRIP);
    glColor3f(1,1,1);
    for (double x=stx;x<enx;x+=0.005)
        glVertex3f(x,calf(x)+dely,posz);
    glEnd();
}
void get_curve2(double stz,double enz,double dely,double posx)
{
    glBegin(GL_LINE_STRIP);
    glColor3f(1,1,1);
    for (double z=stz;z<enz;z+=0.005)
        glVertex3f(posx,calf(z)+dely,z);
    glEnd();
}
static int anglex=0;
static int angley=0;
static int anglez=0;
static double movex=0;
static double movey=0;
void display()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(anglex,1,0,0);
    glRotatef(angley,0,1,0);
    glRotatef(anglez,0,0,1);
    glTranslatef(movex,movey,0);
    double x=-0.8,y=0,z=0;
    for (int i=0;i<16;i++)
    {
        get_curve1(x,-x,calf(y)-0.8,z);
        y-=0.05;
        x+=0.05;
        z-=0.05;
    }
    x=-0.8,z=0,y=0;
    for (int i=0;i<16;i++)
    {
        get_curve1(x,-x,calf(y)-0.8,z);
        y-=0.05;
        x+=0.05;
        z+=0.05;
    }
    z=-0.8,y=0,x=0;
    for (int i=0;i<16;i++)
    {
        get_curve2(z,-z,calf(y)-0.8,x);
        y-=0.05;
        z+=0.05;
        x-=0.05;
    }
    z=-0.8,y=0,x=0;
    for (int i=0;i<16;i++)
    {
        get_curve2(z,-z,calf(y)-0.8,x);
        y-=0.05;
        z+=0.05;
        x+=0.05;
    }
    glFlush();
}
void KeyBoards(unsigned char key,int x,int y)
{
    printf("Key: %c,x:%d y:%d\n",key,x,y);
    bool flag=false;
    if (key=='w')
    {
        movey+=0.01;
        flag=true;
    }
    if (key=='s')
    {
        movey-=0.01;
        flag=true;
    }
    if (key=='a')
    {
        movex-=0.01;
        flag=true;
    }
    if (key=='d')
    {
        movex+=0.01;
        flag=true;
    }
    if (key=='x')
    {
        anglex++;
        anglex%=360;
        flag=true;
    }
    if (key=='y')
    {
        angley++;
        angley%=360;
        flag=true;
    }
    if (key=='z')
    {
        anglez++;
        anglez%=360;
        flag=true;
    }
    if (flag) display();
}
int main(int argc, char* argv[])
{
    glutInit(&argc,argv);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutCreateWindow("test");
    init();
    glutDisplayFunc(&display);
    glutKeyboardFunc(&KeyBoards);
    glutMainLoop();
}

