#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glaux.h>
#include <bits/stdc++.h>
#include "group.h"
#include "point.h"
#include "model.h"
#include "loadtexture.h"
using namespace std;
Model::Model(string fileName)
{
	this->fileName=fileName;
	this->v.clear();
	this->vt.clear();
	this->vn.clear();
	this->g.clear();
}
void Model::decode(string s,Point &v,Texture &vt,Normal &vn)
{
	for (int i=0;i<s.length();i++)
		if (s[i]=='/') s[i]=' ';
	stringstream ss(s);
	int vid,vtid,vnid;
	ss>>vid>>vtid>>vnid;
	v=this->v[vid];
	vt=this->vt[vtid];
	vn=this->vn[vnid];
}
void Model::loadModel()
{
	Model::load();
	Model::loadg();
}
void Model::drawModel()
{
	for (int i=0;i<this->g.size();i++)
		drawGroup(g[i]);
	glFlush();
}
void Model::drawGroup(Group g)
{
	if (g.hasTexture==false)
	{
		for (int i=0;i<g.s.size();i++)
		{
			glBegin(GL_TRIANGLES);
			for (int j=0;j<3;j++)
			{
				glColor3f(1,0,0);
				glVertex3f(g.s[i].v[j].x,g.s[i].v[j].y,g.s[i].v[j].z);
			}
			glEnd();
		}
	}
	else
	{
		LoadTexture temp=LoadTexture(g.textureName);
		temp.load();
		temp.init();
		temp.enable();
		for (int i=0;i<g.s.size();i++)
		{
			glBegin(GL_TRIANGLES);
			for (int j=0;j<3;j++)
			{
				glTexCoord2f(g.s[i].vt[j].x,g.s[i].vt[j].y);
				glVertex3f(g.s[i].v[j].x,g.s[i].v[j].y,g.s[i].v[j].z);
			}
			glEnd();
		}
	}
}
void Model::load()
{
	this->v.push_back(Point(0,0,0));    //for simplify
	this->vt.push_back(Texture(0,0,0));
	this->vn.push_back(Normal(0,0,0));
	fstream input(fileName.c_str());
	string s;
	while (getline(input,s))
	{
		stringstream ss(s);
		string op;
		GLfloat x,y,z;
		ss>>op;
		if (op!="v" && op!="vt" && op!="vn") continue;
		ss>>x>>y>>z;
		if (op=="v")
        {
            x=(x-75)/75;   //change size
            y=(y-20)/20;   //change size
            z=(z-50)/50;   //change size
        }
		if (op=="v") this->v.push_back(Point(x,y,z));
		if (op=="vt") this->vt.push_back(Texture(x,y,z));
		if (op=="vn") this->vn.push_back(Normal(x,y,z));
	}
	input.close();
}
void Model::loadg()
{
	fstream input(fileName.c_str());
	string s;
	while (getline(input,s))
	{
		stringstream ss(s);
		string op;
		ss>>op;
		if (op!="g") continue;
		getline(input,s);
		Group temp("NeHe.bmp");
		while (getline(input,s))
		{
			string op;
			stringstream tt(s);
			tt>>op;
			if (op!="f") break;
			string x,y,z;
			tt>>x>>y>>z;
			Surface cur;
			Model::decode(x,cur.v[0],cur.vt[0],cur.vn[0]);
			Model::decode(y,cur.v[1],cur.vt[1],cur.vn[1]);
			Model::decode(z,cur.v[2],cur.vt[2],cur.vn[2]);
			temp.s.push_back(cur);
		}
		this->g.push_back(temp);
	}
}
