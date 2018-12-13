#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glaux.h>
#include <bits/stdc++.h>

class Material
{
    public:
        GLfloat ns;
        GLfloat ka[3];
        GLfloat kd[3];
        GLfloat ks[3];
        GLfloat ke[3];
        GLfloat ni;
        GLfloat d;
};

#endif // MATERIAL_H_INCLUDED
