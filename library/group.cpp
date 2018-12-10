#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glaux.h>
#include "group.h"
Group::Group()
{
	this->s.clear();
	this->textureName="";
	this->hasTexture=false;
}
Group::Group(string textureName)
{
	this->s.clear();
	this->textureName=textureName;
	this->hasTexture=true;
}
