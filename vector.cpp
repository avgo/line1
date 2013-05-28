
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   line1 - разделение классов точек на плоскости.
 *   4-й курс, 2-й семестр.
 *   Лабораторная работа по курсу "Искусственный интеллект".
 *   01.02.2008 - 31.03.2008.
 *   Автор: Антон Гончаров
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "vector.h"

namespace avg {

Vector average(Vector a, Vector b)
{
	Vector c;
	Vector d;
	
	double abs_a = sqrt(a.x*a.x + a.y*a.y);
	double abs_b = sqrt(b.x*b.x + b.y*b.y);
	
	if(abs_a < abs_b)
	{
		c.x = a.x*abs_b/abs_a;
		c.y = a.y*abs_b/abs_a;
		d = b + c;
	}
	else
	{
		c.x = b.x*abs_a/abs_b;
		c.y = b.y*abs_a/abs_b;
		d = a + c;
	}
	return d;
}

void Vector::rotateCW(double alpha)
{
	double beta;
	if(x == 0)
	{
		if(y > 0)
			beta = pii/2;
		else
		if(y < 0)
			beta = -pii/2;
		else
			return ;
	}
	else
		beta = atan(y/x);
	double gamma = beta - alpha;
	double abs_ = abs(); 
	x = abs_*cos(gamma);
	y = abs_*sin(gamma);
}

double angleCCW(Vector a, Vector b)
{
	double angle1 = angle(a, b);
	
	if(a.x == 0.
			&& ((a.y > 0 && b.x > 0)
			|| (a.y < 0 && b.x < 0)))
	{
		angle1 = 2*pii - angle1;
		return angle1;
	}
	
	double aa;
	aa = a.y*b.x/a.x;
	
	if((a.x > 0 && b.y < aa)
			|| (a.x < 0 && b.y > aa))
	{
		angle1 = 2*pii - angle1;
		return angle1;
	}
	
	return angle1;
}

double angleCW(Vector a, Vector b)
{
	double angle1 = angle(a, b);
	
	if(a.x == 0.
			&& ((a.y > 0 && b.x < 0)
			|| (a.y < 0 && b.x > 0)))
	{
		angle1 = 2*pii - angle1;
		return angle1;
	}
	
	double aa;
	aa = a.y*b.x/a.x;
	
	if((a.x > 0 && aa < b.y)
			|| (a.x < 0 && aa > b.y))
	{
		angle1 = 2*pii - angle1;
	}
	
	return angle1;
}

double angle(Vector a, Vector b)
{
	return acos((a.x*b.x + a.y*b.y)/(sqrt(a.x*a.x+a.y*a.y)*sqrt(b.x*b.x+b.y*b.y)));
}

double rad_to_grad(double angle)
{
	return angle*180/pii;
}

double grad_to_rad(double angle)
{
	return angle*pii/180;
}

bool intersection(Point M0, Vector a, Point M1, Vector b, Point *M2)
{
	Point M22;
	if(a.y*b.x - a.x*b.y == 0)
		return false;
	if(a.x == 0)
	{
		M22.x = M0.x;
		M22.y = (b.y*M0.x/b.x) - (b.y*M1.x/b.x) + M1.y;
	}
	else
	{
		M22.x = (a.x*b.y*M1.x - a.y*b.x*M0.x - a.x*b.x*M1.y + a.x*b.x*M0.y)
			/(a.x*b.y - b.x*a.y);
		M22.y = a.y*M22.x/a.x - a.y*M0.x/a.x + M0.y;
	}
	if(M2)
		*M2 = M22;
	return true;
}

}

