#include <iostream>
#include <fstream>
#include <GL/glut.h>
#include "model.h"

using namespace std;

const int WIDTH = 1000;
const int HEIGHT = 500;

Model model;

void initLight()
{
	GLfloat LightAmbient1[] = {0, 0, 1, 1};
	GLfloat LightDiffuse1[] = {0, 0, 1, 1};
	GLfloat LightPosition1[] = {0, 0, 0, 1};
	GLfloat Mat_specular1[] = {1, 1, 1, 1};
	GLfloat Mat_shininess1[] = {50};
	GLfloat LightAmbient2[] = {0, 1, 0, 1};
	GLfloat LightDiffuse2[] = {0, 1, 0, 1};
	GLfloat LightPosition2[] = {1, 1, 1, 1};
	GLfloat Mat_specular2[] = {0, 0, 1, 1};
	GLfloat Mat_shininess2[] = {50};
	GLfloat LightAmbient3[] = {1, 0, 0, 1};
	GLfloat LightDiffuse3[] = {1, 0, 0, 1};
	GLfloat LightPosition3[] = {1, 0, 0, 1};
	GLfloat Mat_specular3[] = {-1, 1, 1, 1};
	GLfloat Mat_shininess3[] = {50};

	glMaterialfv(GL_FRONT, GL_SPECULAR, Mat_specular1);
	glMaterialfv(GL_FRONT, GL_SHININESS, Mat_shininess1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse1);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition1);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Mat_specular2);
	glMaterialfv(GL_FRONT, GL_SHININESS, Mat_shininess2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, LightAmbient2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiffuse2);
	glLightfv(GL_LIGHT2, GL_POSITION, LightPosition2);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT2);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Mat_specular3);
	glMaterialfv(GL_FRONT, GL_SHININESS, Mat_shininess3);
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient3);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse3);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition3);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
}

int initGL()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	return true;
}

void OnDraw()
{
	static double rtri = 0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glScaled(50, 50, 50);
	glTranslated(0, 0, -3);
	glRotated(rtri, 0, 1, 0);

	glColor3f(1, 1, 1);
	model.glDrawModel();

	rtri += 0.01;
	glFlush();
}

void reshape(int width, int height)
{
	if(height == 0)
		height = 1;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45, (double)width / height, 0.1, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char *argv[])
{
	fstream input1("1.dat");
	fstream input2("2.dat");
	model.getModel(input2, input1);
	input1.close();
	input2.close();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(-1, -1);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("OpenGL Windows Test");

	initGL();
	initLight();

	glutDisplayFunc(OnDraw);
	glutIdleFunc(OnDraw);
	glutReshapeFunc(reshape);
	//glutMouseFunc(OnMouse);
	//glutMotionFunc(OnMove);

	glutMainLoop();
	return 0;
}
