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
#include "normal.h"
#include "surface.h"
#include "model.h"
#include "loadtexture.h"
#include "material.h"
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
    if (s.find("//")==string::npos)
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
    else
    {
        for (int i=0;i<s.length();i++)
            if (s[i]=='/') s[i]=' ';
        stringstream ss(s);
        int vid,vnid;
        ss>>vid>>vnid;
        v=this->v[vid];
        vt=this->vt[0];
        vn=this->vn[vnid];
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
		if (op=="mtllib") ss>>this->MTLName;
		if (op!="v" && op!="vt" && op!="vn") continue;
		ss>>x>>y;
		if (op=="v")
        {
            x=x/20;   //change size
            y=y/20;   //change size
            z=z/20;   //change size
        }
        z=0;
        if (op!="vt") ss>>z;
		if (op=="v") this->v.push_back(Point(x,y,z));
		if (op=="vt") this->vt.push_back(Texture(x,y,z));
		if (op=="vn") this->vn.push_back(Normal(x,y,z));
	}
	input.close();
	cout<<this->MTLName<<endl;
}
void Model::loadg()
{
	fstream input(fileName.c_str());
	string s;
	while (getline(input,s))
	{
		stringstream ss(s);
		string op;
		string mtlname;
		ss>>op;
		if (op!="usemtl") continue;
		getline(input,s);
		ss>>mtlname;
		Group temp;
		bool hasTexture;
		while (getline(input,s))
		{
			string op;
			stringstream tt(s);
			tt>>op;
			if (op!="f") break;
			Surface cur;
			Point tempv;
			Normal tempvn;
			Texture tempvt;
            string tmp;
			while (tt>>tmp)
            {
                if (tmp.find("//")!=string::npos) hasTexture=false;
                    else hasTexture=true;
                decode(tmp,tempv,tempvt,tempvn);
                cur.v.push_back(tempv);
                cur.vt.push_back(tempvt);
                cur.vn.push_back(tempvn);
            }
			temp.s.push_back(cur);
		}
		cout<<"count: "<<MTLinfo.count(mtlname)<<endl;
		cout<<"mtlname: "<<mtlname<<endl;
		cout<<"second: "<<MTLinfo[mtlname].second<<endl;
		temp.material=MTLinfo[mtlname].first;
		//if (MTLinfo[mtlname].second=="") hasTexture=false;
		if (hasTexture) temp.updateTexture("NeHe.bmp");
		//if (hasTexture) temp.updateTexture(MTLinfo[mtlname].second);
		this->g.push_back(temp);
	}
	input.close();
}
void Model::loadMTL()
{
    fstream input(MTLName.c_str());
    string s;
    string temp="";
    Material material;
    string texture="";
    bool first;
    string op;
    while (getline(input,s))
    {
        stringstream ss(s);
        ss>>op;
        if (op=="newmtl")
        {
            if (!first)
            {
                cout<<"temp->texture: "<<temp<<' '<<texture<<endl;
                MTLinfo[temp]=make_pair(material,texture);
                texture="";
            }
            else
            {
                first=false;
            }
            ss>>temp;
        }
        if (op=="Ns")
            ss>>material.ns;
        if (op=="Ka")
            ss>>material.ka[0]>>material.ka[1]>>material.ka[2];
        if (op=="Kd")
            ss>>material.kd[0]>>material.kd[1]>>material.kd[2];
        if (op=="Ks")
            ss>>material.ks[0]>>material.ks[1]>>material.ks[2];
        if (op=="Ke")
            ss>>material.ke[0]>>material.ke[1]>>material.ke[2];
        if (op=="Ni")
            ss>>material.ni;
        if (op=="map_Kd" || op=="map_Bump")
        {
            string tempTexture;

            while (ss>>tempTexture);
            cout<<tempTexture<<endl;
            for (int i=0;i<tempTexture.length();i++)
                if (tempTexture[i]=='\\')
                    tempTexture[i]=' ';    //adjust to relative path
            stringstream tt(tempTexture);
            while (tt>>texture);
            cout<<"URL: "<<texture<<endl;
        }
    }
}
