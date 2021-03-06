
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   line1 - разделение классов точек на плоскости.
 *   4-й курс, 2-й семестр.
 *   Лабораторная работа по курсу "Искусственный интеллект".
 *   01.02.2008 - 31.03.2008.
 *   Автор: Антон Гончаров
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

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
