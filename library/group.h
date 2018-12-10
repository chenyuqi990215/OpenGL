#ifndef GROUP_H_INCLUDED
#define GROUP_H_INCLUDED
#include <GL/gl.h>
#include <GL/glaux.h>
#include <bits/stdc++.h>
#include "point.h"
using namespace std;
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

#endif // GROUP_H_INCLUDED
