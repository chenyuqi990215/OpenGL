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
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glaux.lib")
#define WIDTH 1000
#define HEIGHT 500
#define maxn 1500
using namespace std;
struct Point
{
    double x,y,z;
    Point(){x=0,y=0,z=0;}
    Point(double x,double y,double z):x(x),y(y),z(z){};
}point[maxn];
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
struct Face
{
    int a,b,c,d;
    Face(){a=0,b=0,c=0,d=0;}
    Face(int a,int b,int c,int d):a(a),b(b),c(c),d(d){}
}face[maxn];
struct ImageFileDate
{
    unsigned long bWidth;
    unsigned long bHeight;
    unsigned char* fileData;
};
GLuint texture[1];
struct ImageFileDate *image = NULL;
void LoadImageFile(char* imageName)
{
    image = (struct ImageFileDate*)malloc(sizeof(struct ImageFileDate));
    image->bHeight = 0;
    image->bWidth = 0;
    image->fileData = NULL;
    FILE* imageFile = NULL;
    unsigned long size = 0;
    imageFile = fopen(imageName, "rb");
    fseek(imageFile,18,SEEK_SET);
    fread(&(image->bWidth), 4, 1, imageFile); 
    fread(&(image->bHeight), 4, 1, imageFile);
    fseek(imageFile, 0, SEEK_END);
    size = ftell(imageFile) - 54;
    image->fileData = (unsigned char*) malloc(size);
    memset(image->fileData, 0, size);
    fseek(imageFile, 54, SEEK_SET);
    fread(image->fileData, size, 1, imageFile);
    fclose(imageFile);
}
int LoadGLTextures()
{
	int Status=FALSE;
	AUX_RGBImageRec *TextureImage[1];
    memset(TextureImage,0,sizeof(void *)*1);
	LoadImageFile("NeHe.bmp");
	{
		Status=TRUE;
        glGenTextures(1, &texture[0]);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, (GLsizei)image->bWidth, (GLsizei)image->bHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image->fileData);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}
	if (TextureImage[0])
	{
		if (TextureImage[0]->data)
		{
			free(TextureImage[0]->data);
		}
		free(TextureImage[0]);
	}
	return Status;
}
int n,m;
void init()
{
    assert(LoadGLTextures());
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
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
void get_rotate_z(Point &p,double rad)
{
    const double tmp=p.x*cos(rad)+p.y*sin(rad);
    p.y=p.x*(-sin(rad))+p.y*cos(rad);
    p.x=tmp;
}
void get_rotate_y(Point &p,double rad)
{
    const double tmp=p.x*cos(rad)+p.z*sin(rad);
    p.z=p.x*(-sin(rad))+p.z*cos(rad);
    p.x=tmp;
}
void get_rotate_x(Point &p,double rad)
{
    const double tmp=p.y*cos(rad)+p.z*sin(rad);
    p.z=p.y*(-sin(rad))+p.z*cos(rad);
    p.y=tmp;
}
static int angle=0;
void display()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    for (int i=1;i<=n;i++)
    {
        if (face[i].d==0) glBegin(GL_TRIANGLES);
        else glBegin(GL_POLYGON);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(point[face[i].a].x,point[face[i].a].y,point[face[i].a].z);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(point[face[i].b].x,point[face[i].b].y,point[face[i].b].z);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(point[face[i].c].x,point[face[i].c].y,point[face[i].c].z);
        if (face[i].d)
        {
            glTexCoord2f(1.0f, 1.0f); glVertex3f(point[face[i].d].x,point[face[i].d].y,point[face[i].d].z);
        }

        glEnd();
    }
    glFlush();
}
void changePoint(int x,int y,double& vx,double& vy)
{
    vx=x,vy=HEIGHT-y;
    vx-=(double)WIDTH/2.0;
    vy-=(double)HEIGHT/2.0;
    vx/=(double)WIDTH/2.0;
    vy/=(double)HEIGHT/2.0;
}
void rotate_x(double rad)
{
    for (int i=1;i<=m;i++)
        get_rotate_x(point[i],rad);
}
void rotate_y(double rad)
{
    for (int i=1;i<=m;i++)
        get_rotate_y(point[i],rad);
}
void rotate_z(double rad)
{
    for (int i=1;i<=m;i++)
        get_rotate_z(point[i],rad);
}
void move_x(double del)
{
    for (int i=1;i<=m;i++)
        point[i].x+=del;
}
void move_y(double del)
{
    for (int i=1;i<=m;i++)
        point[i].y+=del;
}
void KeyBoards(unsigned char key,int x,int y)
{
    printf("Key: %c,x:%d y:%d\n",key,x,y);
    if (key=='w')
        move_y(0.01);
    if (key=='s')
        move_y(-0.01);
    if (key=='a')
        move_x(-0.01);
    if (key=='d')
        move_x(0.01);
    if (key=='x')
        rotate_x(acos(-1)/100);
    if (key=='y')
        rotate_y(acos(-1)/100);
    if (key=='z')
        rotate_z(acos(-1)/100);
    display();
}
int main(int argc, char* argv[])
{
    fstream input1("1.dat");
    input1>>n>>m;
    cout<<n<<m<<endl;
    for (int i=1,k;i<=n;i++)
    {
        input1>>k;
        input1>>face[i].a>>face[i].b>>face[i].c>>face[i].d;
    }
    input1.close();
    fstream input2("2.dat");
    for (int i=1,k;i<=m;i++)
    {
        input2>>k;
        input2>>point[i].x>>point[i].y>>point[i].z;
        point[i].x/=250;
        point[i].y/=100;
        point[i].z/=100;
    }
    input2.close();
    glutInit(&argc,argv);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutCreateWindow("test");
    init();
    glutDisplayFunc(&display);
    glutKeyboardFunc(&KeyBoards);
    glutMainLoop();
    return 0;
}
