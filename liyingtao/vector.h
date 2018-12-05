//
// Created by Alex_Li on 2018/12/1.
//

#ifndef OPENGL_VECTOR_H
#define OPENGL_VECTOR_H

#include <cmath>

class Point;

class Vector
{
	friend class Point;

private:
	long double x = 0;
	long double y = 0;
	long double z = 0;

public:
	long double getX() const;
	void setX(double x);
	long double getY() const;
	void setY(double y);
	long double getZ() const;
	void setZ(double z);

public:
	Vector() = default;
	Vector(Point A, Point B);
	Vector(long double x, long double y, long double z);

public:
	friend Vector operator*(Vector left, double right);
	friend Vector operator*(double left, Vector right);
	friend Vector operator+(Vector left, Vector right);
	friend Vector operator-(Vector left, Vector right);

public:
	static Vector vectorProduct(const Vector &left, const Vector &right);
	static long double scalarProduct(const Vector &left, const Vector &right);
	static long double abs(const Vector &vector);
	static Vector unitVector(const Vector &vector);
	static Vector rotate(Vector vector, Vector axis, long double theta);
};


#endif //OPENGL_VECTOR_H
