
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   line1 - разделение классов точек на плоскости.
 *   4-й курс, 2-й семестр.
 *   Лабораторная работа по курсу "Искусственный интеллект".
 *   01.02.2008 - 31.03.2008.
 *   Автор: Антон Гончаров
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef points_area_h
#define points_area_h

#include <QtGui>
#include <list>
#include <algorithm>
#include <functional>
#include <math.h>

#include "point.h"
#include "vector.h"
#include "line.h"

enum PointType {PointTypeRed, PointTypeBlue};

typedef std::vector<avg::Point> PointsVector;

struct PointCustomColor :  avg::Point {
	QColor color;
	int diam;
	PointCustomColor(avg::Point p0, QColor color__) : avg::Point(p0), color(color__) {}
};

struct LineCustom :  avg::Line {
	QColor color;
	int width;
	
	LineCustom(avg::Point p0, avg::Point p1, QColor color__) : avg::Line(p0, p1), color(color__) {}
	LineCustom(avg::Point p0, avg::Point p1, QColor color__, int width__) : avg::Line(p0, p1), color(color__), width(width__) {}
	LineCustom(avg::Vector a, avg::Point p0, QColor color__, int width__) : avg::Line(a, p0), color(color__), width(width__) {}
	LineCustom(avg::Line line__, QColor color__, int width__) : avg::Line(line__.p0, line__.p1), color(color__), width(width__) {}
};

typedef std::vector<PointCustomColor> PointsCustomColorVector;
typedef std::vector<LineCustom> LinesCustomVector;

class PointsArea: public QWidget {

    Q_OBJECT

protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    
public:
    struct sortbyangleCW: public std::binary_function<avg::Point, avg::Point, bool> {
        avg::Point p0;
        avg::Point p1;
        sortbyangleCW(){}
        bool operator()(avg::Point P1, avg::Point P2)
        {
            double angle1 = avg::angleCW(avg::Vector(p0, p1), avg::Vector(p0, P1));
            double angle2 = avg::angleCW(avg::Vector(p0, p1), avg::Vector(p0, P2));
            return angle1 < angle2;
        }
    } sortbyangleCW1;
	
	struct sort2: public std::binary_function<avg::Point, avg::Point, bool> {
		double angle;
		sort2(){}
		bool operator()(avg::Point P1, avg::Point P2)
		{
			avg::Vector V1(avg::Point(0, 0), P1);
			avg::Vector V2(avg::Point(0, 0), P2);
			V1.rotateCW(angle);
			V2.rotateCW(angle);
			return V1.y > V2.y;
		}
	} sort22;
	
    bool Lines1Visible;
    QString log;
    PointType CurrentPoint;
    PointsVector PointsRed;
    PointsVector PointsBlue;
    PointsCustomColorVector Points1;
    LinesCustomVector Lines1;
    LinesCustomVector Lines2;
    avg::Line FindLine(bool cw);
    void Clear();
    void DrawLine();
    PointsVector::iterator FindPoint(PointsVector::iterator p0, PointsVector &pv, bool cw);
    void InitPointsArea();
    void DrawLine1(avg::Point M0, avg::Vector a);
    inline void SetLines1Visible(bool visible__) { Lines1Visible = visible__; update(); }
    PointsArea();
    PointsArea(QWidget *pParentWidget);
};

//const double pii = 3.1415926535897932384626433832795;


#endif
