
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   line1 - разделение классов точек на плоскости.
 *   4-й курс, 2-й семестр.
 *   Лабораторная работа по курсу "Искусственный интеллект".
 *   01.02.2008 - 31.03.2008.
 *   Автор: Антон Гончаров
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef avg_vector_h
#define avg_vector_h

#include "math.h"
#include "point.h"

namespace avg {

struct Vector {
	double x;
	double y;
	Vector(): x(0), y(0) {}
	Vector(double x_, double y_): x(x_), y(y_) {}
	Vector(Point p0, Point p1): x(p1.x - p0.x), y(p1.y - p0.y) {}
	Vector(double x1, double x0, double y1, double y0):
		x( x1 - x0 ), y( y1 - y0 )  {}
	Vector operator+(Vector b)
	{
		Vector c;
		c.x = x + b.x;
		c.y = y + b.y;
		return c;
	}
	Vector operator-(Vector b)
	{
		Vector c;
		c.x = x - b.x;
		c.y = y - b.y;
		return c;
	}
	inline double abs() { return sqrt(x*x + y*y); }
	inline bool zero() { return x == 0 && y == 0; }
	void rotateCW(double alpha);
};

const double pii = 3.1415926535897932384626433832795;

double angleCCW(avg::Vector a, avg::Vector b);
double angleCW(avg::Vector a, avg::Vector b);
double angle(avg::Vector a, avg::Vector b);
double rad_to_grad(double angle);
double grad_to_rad(double angle);
Vector average(Vector a, Vector b);
bool intersection(Point M0, Vector a, Point M1, Vector b, Point *M2);

}

#endif /*VECTOR_H_*/
