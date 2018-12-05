//
// Created by Alex_Li on 2018/11/27.
//

#ifndef OPENGL_MODEL_H
#define OPENGL_MODEL_H

#include <iostream>
#include <vector>
#include <fstream>
#include "point.h"
#include "surface.h"

class Model
{
private:
	std::vector<Point> point = {Point()};
	std::vector<Surface> surface;

public:
	Model() = default;
	explicit Model(std::istream &is);
	Model(std::istream &pointFile, std::istream &surfaceFile);

public:
	void glDrawModel();
	void getModel(std::istream &pointFile, std::istream &surfaceFile);
};


#endif //OPENGL_MODEL_H
