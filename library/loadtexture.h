#ifndef LOADTEXTURE_H_INCLUDED
#define LOADTEXTURE_H_INCLUDED

#include <GL/gl.h>
#include <GL/glaux.h>
#include <bits/stdc++.h>
using namespace std;
static map <string,GLuint> texturePool;
class LoadTexture
{
	private:
		string textureName;
		GLuint textureID;
	public:
	    LoadTexture();
		LoadTexture(string textureName);
		void setTextureName(string textureName);
		void load();
		void init();
		void enable();
		bool hasLoad();
};

#endif // LOADTEXTURE_H_INCLUDED
