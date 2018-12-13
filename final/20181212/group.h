#ifndef GROUP_H_INCLUDED
#define GROUP_H_INCLUDED
#include <GL/gl.h>
#include <GL/glaux.h>
#include <bits/stdc++.h>
#include "point.h"
#include "normal.h"
#include "surface.h"
#include "material.h"
#include "loadtexture.h"
using namespace std;
class Group
{
	public:
		vector <Surface> s;
		string textureName;
		bool hasTexture;
		LoadTexture texture;
		Material material;
	public:
		Group();
		void drawGroup();
		void updateTexture(string textureName);
};

#endif // GROUP_H_INCLUDED
