#ifndef avg_line_h
#define avg_line_h

#include "point.h"
#include "vector.h"

namespace avg {
	
struct Line {
	avg::Point p0;
	avg::Point p1;
	Line(){}
	Line(avg::Point p0__, avg::Point p1__) :  p0(p0__), p1(p1__) {}
	Line(Vector a, Point p){
		p0 = p;
		p1.x = p0.x + a.x;
		p1.y = p0.y + a.y; 
	}
	Vector DirectingVector() {
		return Vector(p0, p1);
	}
};
	
}

#endif
