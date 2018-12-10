#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <wingdi.h>
#include <GL/glut.h>
#include <assert.h>
#include <GL/gl.h>
#include <GL/glaux.h>
#include <bits/stdc++.h>
#include "light.h"
#define WIDTH 1000
#define HEIGHT 500
#define maxn 1500
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

class LoadTexture
{
	private:
		string textureName;
		GLuint textureID;
	public:
		LoadTexture(string textureName);
		void load();
		void init();
		void enable();
};
LoadTexture::LoadTexture(string textureName)
{
	this->textureName=textureName;
}
void LoadTexture::load()
{
	const int BMP_Header_Length=54;
	GLint width,height,total_bytes;
	GLubyte* pixels=0;
	GLuint textureID=0;
	FILE* pFile=fopen(this->textureName.c_str(),"rb");
	fseek(pFile,0x0012,SEEK_SET);
	fread(&width,4,1,pFile);
	fread(&height,4,1,pFile);
	fseek(pFile,BMP_Header_Length,SEEK_SET);
	GLint line_bytes=width*3;
	while (line_bytes%4!=0)
		++line_bytes;
	total_bytes=line_bytes*height;
	pixels=(GLubyte*)malloc(total_bytes);
    fread(pixels,total_bytes,1,pFile);
	glGenTextures(1,&this->textureID);
	glBindTexture(GL_TEXTURE_2D,this->textureID);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_BGR_EXT,GL_UNSIGNED_BYTE,pixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	free(pixels);
	fclose(pFile);
}
void LoadTexture::init()
{
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
}
void LoadTexture::enable()
{
	glBindTexture(GL_TEXTURE_2D,this->textureID);
}
class Model : public Group
{
	private:
		vector <Point> v;
		vector <Texture> vt;
		vector <Normal> vn;
		vector <Group> g;
		string fileName;
		void load();
		void loadg();
		void drawGroup(Group g);
		void decode(string s,Point &v,Texture &vt,Normal &vn);
	public:
		Model(string fileName);
		void loadModel();
		void drawModel();
		//void moveModel();
		//void rotateModel();
};
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
    cout<<this->g.size()<<endl;
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
void display(void)
{
    glClearColor(0.0,0.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Model model("model.obj");
    model.loadModel();
    model.drawModel();
}

int main(int argc, char* argv[])
{
    glutInit(&argc,argv);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutCreateWindow("test");
    glutDisplayFunc(&display);
    glutMainLoop();
    return 0;
}
