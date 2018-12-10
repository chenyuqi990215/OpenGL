#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glaux.h>
#include <bits/stdc++.h>
using namespace std;
struct Point
{
	GLfloat x,y,z;
	Point(GLfloat x=0,GLfloat y=0,GLfloat z=0):x(x),y(y),z(z){}
};
struct Texture
{
	GLfloat x,y,z;
	Texture(GLfloat x=0,GLfloat y=0,GLfloat z=0):x(x),y(y),z(){}
};
struct Normal
{
	GLfloat x,y,z;
	Normal(GLfloat x=0,GLfloat y=0,GLfloat z=0):x(x),y(y),z(){}
};
struct Surface
{
	Point v[3];
	Texture vt[3];
	Normal vn[3];
};


#endif // POINT_H_INCLUDED
