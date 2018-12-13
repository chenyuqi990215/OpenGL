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
#include "loadtexture.h"
#include "material.h"
using namespace std;
class Model : public Group
{
	private:
		vector <Point> v;
		vector <Texture> vt;
		vector <Normal> vn;
		vector <Group> g;
		string fileName;
		string MTLName;
		void load();
		void loadg();
		void drawGroup(Group &g);
		void decode(string s,Point &v,Texture &vt,Normal &vn);
		map <string,pair<Material,string> > MTLinfo;
	public:
		Model(string fileName);
		void loadModel();
		void drawModel();
		void loadMTL();
		//void moveModel();
		//void rotateModel();
};

#endif // MODEL_H_INCLUDED
