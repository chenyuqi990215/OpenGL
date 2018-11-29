//
// Created by Alex_Li on 2018/11/27.
//

#ifndef OPENGL_POINT_H
#define OPENGL_POINT_H


class Point
{
public:
	double x = 0;
	double y = 0;
	double z = 0;

	Point() = default;
	Point(double x, double y, double z);
};


#endif //OPENGL_POINT_H
