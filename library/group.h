#ifndef GROUP_H_INCLUDED
#define GROUP_H_INCLUDED
#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glaux.h>

class Group
{
	public:
		vector <Surface> s;
		string textureName;
		bool hasTexture;
	public:
		Group();
		Group(string textureName);
};


#endif // GROUP_H_INCLUDED
