//
// Created by Alex_Li on 2018/11/27.
//

#ifndef OPENGL_SURFACE_H
#define OPENGL_SURFACE_H

#include <iostream>
#include <vector>
#include <GL/glut.h>
#include "point.h"

enum Shape
{
	UNKNOWN, TRIANGLE, RECTANGLE
};

class Surface
{
private:
	std::vector<Point> point;
	Shape shape = UNKNOWN;

public:
	Surface() = default;
	Surface(Point A, Point B, Point C);
	Surface(Point A, Point B, Point C, Point D);

public:
	Shape getShape() const;
	void glDrawSurface();
	void setSurface(Point A, Point B, Point C);
	void setSurface(Point A, Point B, Point C, Point D);
};


#endif //OPENGL_SURFACE_H
