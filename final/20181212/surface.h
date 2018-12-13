#ifndef SURFACE_H_INCLUDED
#define SURFACE_H_INCLUDED
#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glaux.h>
#include <bits/stdc++.h>
#include "point.h"
#include "texture.h"
class Surface
{
    public:
        vector<Point> v;
        vector<Texture> vt;
        vector<Normal> vn;
};

#endif // SURFACE_H_INCLUDED
