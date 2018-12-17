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
#include "Fmod.h"
#include "loadtexture.h"
#include "model.h"
#define WIDTH 1000
#define HEIGHT 500
#define maxn 1500
#pragma comment(lib, "opengl32.lib")							// 链接时查找OpenGL32.lib
#pragma comment(lib, "glu32.lib")								// 链接时查找glu32.lib
#pragma comment(lib, "glaux.lib")								// 链接时查找glaux.lib
#pragma comment(lib, "fmodvc.lib")										// 把音频库加入到链接器中
using namespace std;
int anglex=0,angley=0,anglez=0;
static Model model("model_table.obj");
/*            Load music.                     */
//FSOUND_STREAM *mp3back;													// 背景音乐 *.mp3格式
//GLvoid InitFMOD(void)
//{
//	// 载入音频文件
//	if (FSOUND_Init(44100, 32, 0))										// 把声音初始化为44khz
//	{
//		// 载入文件bgmusic.mp3
//		mp3back = FSOUND_Stream_OpenFile("bgmusic.mp3", FSOUND_LOOP_NORMAL, 0);
//	}
//
//}
//
//GLvoid FreeFMOD(void)
//{
//	// 释放音频文件
//	if (mp3back != NULL)
//	{
//		FSOUND_Stream_Close(mp3back);									// 释放文件bgmusic.mp3
//	}
//
//}
/*             Load music finish.             */
void init()
{
/*             Use music.                     */
//    InitFMOD();															// 初始化音频文件
//	FSOUND_Stream_Play(FSOUND_FREE,mp3back);
/*             Use music finish.              */
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


    glutInit(&argc,argv);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutCreateWindow("test");
    glutDisplayFunc(&display);
    init();
//    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    model.loadModel();

    glutKeyboardFunc(&keyboardfunc);
    glutMainLoop();
    return 0;
}
