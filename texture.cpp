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
#define WIDTH 1000
#define HEIGHT 500
#define maxn 1500
#define BMP_Header_Length 54
using namespace std;
/* Initialize material property, light source, lighting model,
 * and depth buffer.
 */
static double angle = 40;
struct Point
{
    double x,y,z;
    Point(){x=0,y=0,z=0;}
    Point(double x,double y,double z):x(x),y(y),z(z){};
}point[maxn];
struct Face
{
    int a,b,c,d;
    Face(){a=0,b=0,c=0,d=0;}
    Face(int a,int b,int c,int d):a(a),b(b),c(c),d(d){}
}face[maxn];
GLuint texGround;
GLuint load_texture(const char* file_name)
{
	GLint width, height, total_bytes;
	GLubyte* pixels = 0;
	GLuint last_texture_ID=0, texture_ID = 0;

	// 打开文件，如果失败，返回
	FILE* pFile = fopen(file_name, "rb");
	if( pFile == 0 )
		return 0;

	// 读取文件中图象的宽度和高度
	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, 4, 1, pFile);
	fread(&height, 4, 1, pFile);
	fseek(pFile, BMP_Header_Length, SEEK_SET);

	// 计算每行像素所占字节数，并根据此数据计算总像素字节数
	{
		GLint line_bytes = width * 3;
		while( line_bytes % 4 != 0 )
			++line_bytes;
		total_bytes = line_bytes * height;
	}

	// 根据总像素字节数分配内存
	pixels = (GLubyte*)malloc(total_bytes);
    fread(pixels, total_bytes, 1, pFile);
	// 读取像素数据
	// 分配一个新的纹理编号
	glGenTextures(1, &texture_ID);

	// 绑定新的纹理，载入纹理并设置纹理参数
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	free(pixels);
	fclose(pFile);
	return texture_ID;
}

int n,m;
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
void init(void)
{
    texGround=load_texture("NeHe.bmp");
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
    Light light0=Light(GL_LIGHT0,Light::SPOT_LIGHT,Light::DEFAULT);
    light0.setAngle(angle);
    light0.setLightAmbient(1,1,1);
    light0.setLightDiffuse(1,1,1);
    light0.setLightPosition(1,1,1);
    light0.setSpotDirection(-1,-1,0);
    light0.setLightSpecular(0,1,1);
    light0.init();
    light0.enable();
}
void display()
{
    glClearColor(0.0,0.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, texGround);
    init();
    for (int i=1;i<=n;i++)
    {
        glColor3b(0,0,0);
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
    if (key==27)
        exit(0);
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
