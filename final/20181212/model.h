#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

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
#include "material.h"
#include "loadtexture.h"
using namespace std;
class Model : public Group
{
	private:
		vector <Point> v;
		vector <Texture> vt;
		vector <Normal> vn;
		vector <Group> g;
		map < string,pair<Material,string> > MTLinfo;
		string fileName;
		string MTLName;
		void load();
		void loadg();
		void loadMTL();
		void drawGroup(Group &g);
		void decode(string s,Point &v,Texture &vt,Normal &vn);
	public:
		Model(string fileName);
		void loadModel();
		void drawModel();
		//void moveModel();
		//void rotateModel();
};

#endif // MODEL_H_INCLUDED
