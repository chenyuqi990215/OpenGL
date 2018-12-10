#ifndef LOADTEXTURE_H_INCLUDED
#define LOADTEXTURE_H_INCLUDED

#include <GL/gl.h>
#include <GL/glaux.h>
#include <bits/stdc++.h>
using namespace std;
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

#endif // LOADTEXTURE_H_INCLUDED
