#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glaux.h>
#include <bits/stdc++.h>
#include <stdarg.h>
#include "lodepng.h"
#define WIDTH 1000
#define HEIGHT 500
#define maxn 1500
#define BMP_Header_Length 54

#define PNG_BYTES_TO_CHECK 4
#pragma  comment(lib, "libpng.lib")
#pragma  comment(libm "zlib.lib")
using namespace std;
/* Texture id for the demo */
GLuint texGround;
void upsidedown32(unsigned char *pImage, unsigned width, unsigned height)  //Upside down the image
{
	unsigned i;
	unsigned char *pLine;
 
	pLine = (unsigned char *)malloc(4*width);
	if(pLine == NULL)
	{
		printf("No memory left!");
		exit(0);
	}
	for(i=0; i<height/2; i++)
	{
		memcpy(pLine, &pImage[i*4*width], 4*width);
		memcpy(&pImage[i*4*width], &pImage[(height-1-i)*4*width], 4*width);
		memcpy(&pImage[(height-1-i)*4*width], pLine, 4*width);
	}
	free(pLine);
}
GLuint CreateTextureFromPng(char *fileName)
{
    int i;
    GLuint texID;
	unsigned error;
	unsigned width, height;
	unsigned char *pImg;
	unsigned char img1D[16][3];
    error = lodepng_decode32_file(&pImg, &width, &height, fileName);
	if(error)
	{
		printf("error %u: %s\n", error, lodepng_error_text(error));
		exit(0);
	}
	upsidedown32(pImg, width, height); //Upside down the image
	glGenTextures(1, &texID); //生成纹理号
	glBindTexture(GL_TEXTURE_2D, texID);  //纹理绑定
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pImg); //定义纹理数据
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);  //设置纹理目标参数
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glEnable(GL_DEPTH_TEST);
	free(pImg);
}
void init(void)
{
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
    texGround=CreateTextureFromPng("NeHe.png");

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
        glTexCoord2f(1,0); glVertex2f(1,0);
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
