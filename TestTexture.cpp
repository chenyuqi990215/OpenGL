#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glaux.h>
#include <bits/stdc++.h>
#define WIDTH 1000
#define HEIGHT 500
#define maxn 1500
#define BMP_Header_Length 54
using namespace std;
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
void init(void)
{
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
    texGround=load_texture("NeHe.bmp");
	
}
void display()
{
    glClearColor(0.0,0.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, texGround);
    glBegin(GL_POLYGON);
    	glTexCoord2f(0,0); glVertex2f(0,0);
        glTexCoord2f(0,1); glVertex2f(0,1);
        glTexCoord2f(1,1); glVertex2f(1,1);
        glTexCoord2f(1,0); glVertex3f(1,0);
    glEnd();
    glFlush();
}
int main(int argc, char* argv[])
{
    glutInit(&argc,argv);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutCreateWindow("test");
    init();
    glutDisplayFunc(&display);
    glutMainLoop();
    return 0;
}
