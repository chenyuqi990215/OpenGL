#ifndef GROUP_H_INCLUDED
#define GROUP_H_INCLUDED
#include <GL/gl.h>
#include <GL/glaux.h>
#include <bits/stdc++.h>
#include "point.h"
#include "loadtexture.h"
using namespace std;
class Group
{
	public:
		vector <Surface> s;
		string textureName;
		bool hasTexture;
		LoadTexture texture;
	public:
		Group();
		void drawGroup();
		void updateTexture(string textureName);
};

#endif // GROUP_H_INCLUDED
