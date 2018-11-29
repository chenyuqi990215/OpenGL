//
// Created by Alex_Li on 2018/11/27.
//

#include "surface.h"

Surface::Surface(Point A, Point B, Point C)
{
	/*point.push_back(A);
	point.push_back(B);
	point.push_back(C);
	shape = TRIANGLE;*/

	setSurface(A, B, C);
}

Surface::Surface(Point A, Point B, Point C, Point D)
{
	/*point.push_back(A);
	point.push_back(B);
	point.push_back(C);
	point.push_back(D);
	shape = RECTANGLE;*/

	setSurface(A, B, C, D);
}

Shape Surface::getShape() const
{
	return shape;
}

void Surface::glDrawSurface()
{
	if(shape == TRIANGLE)
		glBegin(GL_TRIANGLES);
	else if(shape == RECTANGLE)
		glBegin(GL_QUADS);
	else
		return;

	//std::cout << "---------------------------\n";

	for(Point &p : point)
	{
		glVertex3d(p.x, p.y, p.z);
		/*std::cout << "x: " << p.x
				  << "\ty: " << p.y
				  << "\tz: " << p.z
				  << std::endl;*/
	}

	//std::cout << "---------------------------\n";

	glEnd();
}

void Surface::setSurface(Point A, Point B, Point C)
{
	point.push_back(A);
	point.push_back(B);
	point.push_back(C);
	shape = TRIANGLE;
}

void Surface::setSurface(Point A, Point B, Point C, Point D)
{
	point.push_back(A);
	point.push_back(B);
	point.push_back(C);
	point.push_back(D);
	shape = RECTANGLE;
}
