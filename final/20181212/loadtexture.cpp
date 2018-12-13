#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glaux.h>
#include "loadtexture.h"
LoadTexture::LoadTexture()
{
    this->textureID=0;
}
LoadTexture::LoadTexture(string textureName)
{
	this->textureName=textureName;
}
void LoadTexture::setTextureName(string textureName)
{
    this->textureName=textureName;
}
void LoadTexture::load()
{
//    cout<<"Load: "<<this->textureName<<endl;
    if (texturePool.count(this->textureName))
        this->textureID=texturePool[textureName];
	const int BMP_Header_Length=54;
	GLint width,height,total_bytes;
	GLubyte* pixels=0;
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
	texturePool[this->textureName]=this->textureID;
}
bool LoadTexture::hasLoad()
{
    return this->textureID!=0;
}
void LoadTexture::init()
{
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
}
void LoadTexture::enable()
{
//    cout<<"ID: "<<this->textureID<<endl;
	glBindTexture(GL_TEXTURE_2D,this->textureID);
}
