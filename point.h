#ifndef avg_point_h
#define avg_point_h

namespace avg {

struct Point {
    int x;
    int y;
    double angle;
    Point(): x(0), y(0), angle(0) {}
    Point(int x_, int y_):
        x(x_), y(y_), angle(0) {}
};

}

#endif
