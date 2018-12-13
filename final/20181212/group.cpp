#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glaux.h>
#include "group.h"
#include "point.h"
#include "normal.h"
#include "surface.h"
#include "material.h"
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
			glBegin(GL_POLYGON);
			for (int j=0;j<this->s[i].v.size();j++)
			{
				glColor3f(1,1,0);
				glNormal3f(this->s[i].vn[j].x,this->s[i].vn[j].y,this->s[i].vn[j].z);
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
//        cout<<"drawGroup: "<<this->texture.textureID<<endl;
//	    cout<<"drawGroup: "<<this->texture.textureName<<endl;
		for (int i=0;i<this->s.size();i++)
		{
			glBegin(GL_POLYGON);
			for (int j=0;j<this->s[i].v.size();j++)
			{
				glTexCoord2f(this->s[i].vt[j].x,this->s[i].vt[j].y);
				glNormal3f(this->s[i].vn[j].x,this->s[i].vn[j].y,this->s[i].vn[j].z);
				glVertex3f(this->s[i].v[j].x,this->s[i].v[j].y,this->s[i].v[j].z);
			}
			glEnd();
		}
	}
}
