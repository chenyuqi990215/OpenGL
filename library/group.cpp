#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glaux.h>
#include "group.h"
#include "point.h"
#include "loadtexture.h"
Group::Group()
{
	this->s.clear();
	this->textureName="";
	this->hasTexture=false;
}
void Group::updateTexture(string textureName)
{
	this->textureName=textureName;
	this->hasTexture=true;
	this->texture.LoadTexture::setTextureName(textureName);
}
void Group::drawGroup()
{
	if (this->hasTexture==false)
	{
		for (int i=0;i<this->s.size();i++)
		{
			glBegin(GL_TRIANGLES);
			for (int j=0;j<3;j++)
			{
				glColor3f(1,1,0);
				glVertex3f(this->s[i].v[j].x,this->s[i].v[j].y,this->s[i].v[j].z);
			}
			glEnd();
		}
	}
	else
	{
	    if (!this->texture.hasLoad())
        {
            this->texture.load();
            this->texture.init();
            this->texture.enable();
        }
        else
        {
            this->texture.enable();
        }
		for (int i=0;i<this->s.size();i++)
		{
			glBegin(GL_TRIANGLES);
			for (int j=0;j<3;j++)
			{
				glTexCoord2f(this->s[i].vt[j].x,this->s[i].vt[j].y);
				glVertex3f(this->s[i].v[j].x,this->s[i].v[j].y,this->s[i].v[j].z);
			}
			glEnd();
		}
	}
}
