#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED
#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glaux.h>
#include <bits/stdc++.h>
class Texture
{
    public:
        GLfloat x,y,z;
        Texture(GLfloat x=0,GLfloat y=0,GLfloat z=0):x(x),y(y),z(){}
};

#endif // TEXTURE_H_INCLUDED
