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
#include "method.h"
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
    Method method;
    v=this->v[0];
    vt=this->vt[0];
    vn=this->vn[0];
    if (s.find("//")==string::npos)
    {
        for (int i=0;i<s.length();i++)
            if (s[i]=='/') s[i]=' ';
        int poss=0;
        string token;
        bool flag=method.stringtoken(s,poss,token,' ');
        if (flag) v=this->v[atoi(token.c_str())];
        flag=method.stringtoken(s,poss,token,' ');
        if (flag) vt=this->vt[atoi(token.c_str())];
        flag=method.stringtoken(s,poss,token,' ');
        if (flag) vn=this->vn[atoi(token.c_str())];
    }
    else
    {
        for (int i=0;i<s.length();i++)
            if (s[i]=='/') s[i]=' ';
        int poss=0;
        string token;
        bool flag=method.stringtoken(s,poss,token,' ');
        if (flag) v=this->v[atoi(token.c_str())];
        flag=method.stringtoken(s,poss,token,' ');
        if (flag) vn=this->vn[atoi(token.c_str())];
    }
}
void Model::loadModel()
{
	Model::load();
	Model::loadMTL();
	Model::loadg();
}
void Model::drawModel()
{
	for (int i=0;i<this->g.size();i++)
		this->g[i].drawGroup();
	glFlush();
}

void Model::load()
{
    Method method;
	this->v.push_back(Point(0,0,0));    //for simplify
	this->vt.push_back(Texture(0,0,0));
	this->vn.push_back(Normal(0,0,0));
	fstream input(fileName.c_str());
	string s;
	const GLfloat INF=10000;
	GLfloat minx=INF,maxx=-INF,miny=INF,maxy=-INF,minz=INF,maxz=-INF;
	while (getline(input,s))
	{
		int poss=0;
		string token;
		bool flag=method.stringtoken(s,poss,token,' ');
		if (flag && token=="mtllib")
        {
            bool flag=method.stringtoken(s,poss,token,' ');
            if (flag) this->MTLName=token;
        }
		GLfloat x=0,y=0,z=0;
		if (!flag || token!="v" && token!="vt" && token!="vn") continue;
		string op=token;
		flag=method.stringtoken(s,poss,token,' ');
		if (flag) x=atof(token.c_str());
		flag=method.stringtoken(s,poss,token,' ');
		if (flag) y=atof(token.c_str());
		flag=method.stringtoken(s,poss,token,' ');
		if (flag) z=atof(token.c_str());
		if (op=="v")
        {
            minx=min(minx,x);
            maxx=max(maxx,x);
            miny=min(miny,y);
            maxy=max(maxy,y);
            minz=min(minz,z);
            maxz=max(maxz,z);
        }
		if (op=="v") this->v.push_back(Point(x,y,z));
		if (op=="vt") this->vt.push_back(Texture(x,y,z));
		if (op=="vn") this->vn.push_back(Normal(x,y,z));

	}
	input.close();
	GLfloat maxp=max(maxx-minx,max(maxy-miny,maxz-minz));
	GLfloat centerx=(maxx+minx)/2,centery=(maxy+miny)/2,centerz=(maxz+minz)/2;
	for (int i=0;i<this->v.size();i++)
    {
        this->v[i].x=((this->v[i].x+centerx)/maxp)*0.6;
        this->v[i].y=((this->v[i].y+centery)/maxp)*0.6;
        this->v[i].z=((this->v[i].z+centerz)/maxp)*0.6;
    }
}
void Model::loadg()
{
    Method method;
	fstream input(fileName.c_str());
	Group temp;
	bool first=true;
	string curmtl;
	string s;
	while (getline(input,s))
    {
        int poss=0;
        string token;
        bool flag=method.stringtoken(s,poss,token,' ');
        if (flag && token=="f")
        {
			Point tempv;
			Normal tempvn;
			Texture tempvt;
			Surface cur;
			while (method.stringtoken(s,poss,token,' '))
            {
                if (token.find("//")!=string::npos) hasTexture=false;
                    else hasTexture=true;
                Model::decode(token,tempv,tempvt,tempvn);
                cur.v.push_back(tempv);
                cur.vn.push_back(tempvn);
                cur.vt.push_back(tempvt);
            }
			temp.s.push_back(cur);
        }
        else if (flag && token=="usemtl")
        {
            if (first)
            {
                first=false;
            }
            else
            {
                if (!MTLinfo.count(curmtl) || MTLinfo[curmtl].second=="") hasTexture=false;
                if (hasTexture) temp.updateTexture(MTLinfo[curmtl].second);
                this->g.push_back(temp);
                temp.init();
                hasTexture=0;
                curmtl="";
            }
            bool flag=method.stringtoken(s,poss,token,' ');
            if (flag) curmtl=token;
        }
    }
	input.close();
}
void Model::loadMTL()
{
    if (!MTLName.length()) return;
    fstream input(MTLName.c_str());
    if (!input)
    {
        cout<<"MTL not found"<<endl;
    }
    Method method;
    string s;
    string temp="";
    Material material;
    string texture="";
    bool first=true;
    string op;
    while (getline(input,s))
    {
        string token;
        int poss=0;
        bool flag=method.stringtoken(s,poss,token,' ');
        if (flag && token=="newmtl")
        {
            if (!first)
            {
                MTLinfo[temp]=make_pair(material,texture);
                texture="";
            }
            else
            {
                first=false;
            }
            bool flag=method.stringtoken(s,poss,token,' ');
            if (flag) temp=token;
        }
        if (flag && token=="Ns")
        {
            bool flag=method.stringtoken(s,poss,token,' ');
            if (flag) material.ns=atof(token.c_str());
        }
        if (flag && token=="Ka")
        {
            bool flag=method.stringtoken(s,poss,token,' ');
            if (flag) material.ka[0]=atof(token.c_str());
            flag=method.stringtoken(s,poss,token,' ');
            if (flag) material.ka[1]=atof(token.c_str());
            flag=method.stringtoken(s,poss,token,' ');
            if (flag) material.ka[2]=atof(token.c_str());
        }
        if (flag && token=="Kd")
        {
            bool flag=method.stringtoken(s,poss,token,' ');
            if (flag) material.kd[0]=atof(token.c_str());
            flag=method.stringtoken(s,poss,token,' ');
            if (flag) material.kd[1]=atof(token.c_str());
            flag=method.stringtoken(s,poss,token,' ');
            if (flag) material.kd[2]=atof(token.c_str());
        }
        if (flag && token=="Ks")
        {
            bool flag=method.stringtoken(s,poss,token,' ');
            if (flag) material.ks[0]=atof(token.c_str());
            flag=method.stringtoken(s,poss,token,' ');
            if (flag) material.ks[1]=atof(token.c_str());
            flag=method.stringtoken(s,poss,token,' ');
            if (flag) material.ks[2]=atof(token.c_str());
        }
        if (flag && token=="Ke")
        {
            bool flag=method.stringtoken(s,poss,token,' ');
            if (flag) material.ke[0]=atof(token.c_str());
            flag=method.stringtoken(s,poss,token,' ');
            if (flag) material.ke[1]=atof(token.c_str());
            flag=method.stringtoken(s,poss,token,' ');
            if (flag) material.ke[2]=atof(token.c_str());
        }
        if (flag && token=="Ni")
        {
            bool flag=method.stringtoken(s,poss,token,' ');
            if (flag) material.ni=atof(token.c_str());
        }
        if (flag && (token=="map_Kd" || token=="map_Bump"))
        {
            string tempTexture;
            while (method.stringtoken(s,poss,token,' '))
                tempTexture=token;
            for (int i=0;i<tempTexture.length();i++)
                if (tempTexture[i]=='\\')
                    tempTexture[i]=' ';
            int post=0;
            while (method.stringtoken(tempTexture,post,token,' '))
                texture=token;
        }
    }
}
