//
// Created by Alex_Li on 2018/11/27.
//

#include "model.h"

Model::Model(std::istream &is)
{

}

Model::Model(std::istream &pointFile, std::istream &surfaceFile)
{
	getModel(pointFile, surfaceFile);
}

void Model::glDrawModel()
{
	for(Surface &s : surface)
	{
		s.glDrawSurface();
	}
}

void Model::getModel(std::istream &pointFile, std::istream &surfaceFile)
{
	unsigned int pointNum = 0;
	unsigned int surfaceNum = 0;

	surfaceFile >> surfaceNum >> pointNum;

	for(int i = 0; i < pointNum; ++i)
	{
		unsigned int num;
		double x = 0;
		double y = 0;
		double z = 0;
		Point temp;
		pointFile >> num;
		pointFile >> x >> y >> z;
		x /= 100;
		y /= 100;
		z /= 100;
		temp.setPoint(x, y, z);
		point.push_back(temp);
	}
	for(int i = 0; i < surfaceNum; ++i)
	{
		unsigned int num;
		unsigned int A = 0;
		unsigned int B = 0;
		unsigned int C = 0;
		unsigned int D = 0;
		Surface temp;
		surfaceFile >> num >> A >> B >> C >> D;
		if(!D)
			temp.setSurface(point[A], point[B], point[C]);
		else
			temp.setSurface(point[A], point[B], point[C], point[D]);
		surface.push_back(temp);
	}
}
