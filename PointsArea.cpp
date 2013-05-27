#include "PointsArea.h"

PointsArea::PointsArea()
: QWidget(),
  PointsRed(),
  PointsBlue(),
  Points1(),
  Lines1(),
  CurrentPoint(PointTypeRed)
{
	InitPointsArea();
}

PointsArea::PointsArea(QWidget *pParentWidget)
: QWidget(pParentWidget),
  PointsRed(),
  PointsBlue(),
  Points1(),
  Lines1(),
  CurrentPoint(PointTypeRed)
{
	InitPointsArea();
}

void PointsArea::InitPointsArea()
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    resize(400, 300);
    
    PointsRed.reserve(1000);
    PointsBlue.reserve(1000);
    Points1.reserve(50);
    Lines1.reserve(50);
    Lines2.reserve(50);
}

void PointsArea::mousePressEvent(QMouseEvent *event)
{
    if(CurrentPoint == PointTypeRed)
        PointsRed.push_back(avg::Point(event->x(), event->y()));
    else
        PointsBlue.push_back(avg::Point(event->x(), event->y()));
    update();
}

void PointsArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.begin(this);

	QPen Pen1;
	if(Lines1Visible)
	{
		LinesCustomVector::iterator i = Lines1.begin();
		while(i != Lines1.end())
		{
			Pen1.setColor(i->color);
			Pen1.setWidth(i->width);
			painter.setPen(Pen1);
			QLine Line1(i->p0.x, i->p0.y, i->p1.x, i->p1.y);
			painter.drawLine(Line1);
			i++;
		}
	}
	
	LinesCustomVector::iterator Lines2element = Lines2.begin();
	while(Lines2element != Lines2.end())
	{
		Pen1.setColor(Lines2element->color);
		Pen1.setWidth(Lines2element->width);
		painter.setPen(Pen1);
		QLine Line1(Lines2element->p0.x, Lines2element->p0.y, Lines2element->p1.x, Lines2element->p1.y);
		painter.drawLine(Line1);
		Lines2element++;
	}
	
	if(Lines1Visible)
	{
		PointsCustomColorVector::iterator i = Points1.begin();
		while(i != Points1.end())
		{
			Pen1.setColor(i->color);
			painter.setPen(Pen1);
			painter.drawEllipse(i->x - 4, i->y - 4, 8, 8);
			i++;
		}
	}
	
	Pen1.setWidth(3);
	Pen1.setColor(Qt::red);
	painter.setPen(Pen1);
	painter.setFont(QFont("Arial", 6.5));
	
	PointsVector::iterator i = PointsRed.begin();
	while(i != PointsRed.end())
	{
		painter.drawEllipse(i->x - 2, i->y - 2, 4, 4);
		QString str = "(" + QString::number(i->x) + "; " + QString::number(i->y) +"; " + QString::number(avg::rad_to_grad(i->angle)) + ")";
        painter.drawText(i->x + 2, i->y + 8, str);
        i++;
    }

    Pen1.setColor(Qt::blue);
    painter.setPen(Pen1);

    i = PointsBlue.begin();
    while(i != PointsBlue.end())
    {
        painter.drawEllipse(i->x - 2, i->y - 2, 4, 4);
        QString str = "(" + QString::number(i->x) + "; " + QString::number(i->y) +"; " + QString::number(avg::rad_to_grad(i->angle)) + ")";
        painter.drawText(i->x + 2, i->y + 8, str);
        i++;
    }
	
	painter.end();
}

void PointsArea::Clear()
{
	PointsRed.erase(PointsRed.begin(), PointsRed.end());
	PointsBlue.erase(PointsBlue.begin(), PointsBlue.end());
	Points1.erase(Points1.begin(), Points1.end());
	Lines1.erase(Lines1.begin(), Lines1.end());
	Lines2.erase(Lines2.begin(), Lines2.end());
	update();
}

void PointsArea::DrawLine()
{
	try
	{
		log = "";
		Points1.erase(Points1.begin(), Points1.end());
		Lines1.erase(Lines1.begin(), Lines1.end());
		Lines2.erase(Lines2.begin(), Lines2.end());
		if(PointsRed.begin() == PointsRed.end() 
			|| PointsBlue.begin() == PointsBlue.end())
		{
			throw QString(tr("Не заданы точки !"));
		}
		
		avg::Line LineCW = FindLine(true);
		avg::Line LineCCW = FindLine(false);
		
		Points1.push_back(PointCustomColor(LineCW.p1, Qt::magenta));
		Points1.push_back(PointCustomColor(LineCW.p0, Qt::magenta));
		
		Points1.push_back(PointCustomColor(LineCCW.p1, Qt::green));
		Points1.push_back(PointCustomColor(LineCCW.p0, Qt::green));
		
		Lines1.push_back(LineCustom(LineCW, Qt::magenta, 3));
		Lines1.push_back(LineCustom(LineCCW, Qt::green, 3));
		
// Точка пересечения LineCW и LineCCW
		avg::Point P0;
		avg::intersection(LineCW.p0, LineCW.DirectingVector(), LineCCW.p0, LineCCW.DirectingVector(), &P0);
		
// Направляющи вектор разделительной линии (НВРЛ)
		avg::Vector a = avg::average(LineCW.DirectingVector(), LineCCW.DirectingVector());
		
// Угол от НВРЛ до вектора, лежащего на Ox, отсчитанный по часовой стрелке
		sort22.angle = avg::angleCW(a, avg::Vector(255, 0));
		
// Нахождение ближайших точек
		std::sort(PointsRed.begin(), PointsRed.end(), sort22);
		std::sort(PointsBlue.begin(), PointsBlue.end(), sort22);
		avg::Point Pr = *PointsRed.rbegin();
		avg::Point Pb = *PointsBlue.begin();
		Points1.push_back(PointCustomColor(Pr, Qt::blue));
		Points1.push_back(PointCustomColor(Pb, Qt::red));
		
		avg::Vector b(a.y, -a.x);
		avg::Point P1;
		avg::intersection(Pr, b, Pb, a, &P1);
		
		avg::Point P2((Pr.x + P1.x)/2, (Pr.y + P1.y)/2);
		Points1.push_back(PointCustomColor(P1, Qt::magenta));
		Points1.push_back(PointCustomColor(P2, Qt::magenta));
		
		
		DrawLine1(P0, a);
		
		update();
	}
	catch(QString str)
	{
		QMessageBox::critical(0, tr("ошибка !"), str);
	}
}

avg::Line PointsArea::FindLine(bool cw)
{
	PointsVector::iterator LastPointRed = PointsRed.end();
	PointsVector::iterator LastPointBlue = PointsBlue.end();
	
	PointsVector::iterator CurPointRed = PointsRed.begin();
	PointsVector::iterator CurPointBlue = PointsBlue.begin();
	
	while(CurPointRed != LastPointRed && CurPointBlue != LastPointBlue)
	{
		LastPointBlue = CurPointBlue;
		CurPointBlue = FindPoint(CurPointRed, PointsBlue, cw);
		if(CurPointBlue == PointsBlue.end())
			throw QString(tr("Классы линейно неразделимы (пересекаются)."));
		LastPointRed = CurPointRed;
		CurPointRed = FindPoint(CurPointBlue, PointsRed, cw);
		if(CurPointRed == PointsRed.end())
			throw QString(tr("Классы линейно неразделимы (пересекаются)."));
	}
	
	avg::Line line;
	QColor color;
	
	if(cw)
	{
		line.p0 = *CurPointBlue;
		line.p1 = *CurPointRed;
	}
	else
	{
		line.p0 = *CurPointRed;
		line.p1 = *CurPointBlue;
	}
		
	return line;
}

PointsVector::iterator PointsArea::FindPoint(PointsVector::iterator p0, PointsVector &pv, bool cw)
{
	PointsVector::iterator first__ = pv.begin();
	if(pv.size() == 1)
		return first__;
	PointsVector::iterator last__ = first__;
	last__++;
	
	first__ = pv.begin();
	log += tr("точки до: \n");
	while(first__ != pv.end())
	{
		log += tr("  p0 (");
		log += QString::number(p0->x);
		log += tr("; ");
		log += QString::number(p0->y);
		log += tr("), first__ (");
		log += QString::number(first__->x);
		log += tr("; ");
		log += QString::number(first__->y);
		log += tr("; ");
		log += QString::number(avg::rad_to_grad(first__->angle));
		log += tr(").\n");
		first__++;
	}
	log += "\n\n";
	
	sortbyangleCW1.p0 = *p0;
	sortbyangleCW1.p1 = *pv.begin();
	std::sort(pv.begin(), pv.end(), sortbyangleCW1);
	
	first__ = pv.begin();
	log += tr("точки после: \n");
	while(first__ != pv.end())
	{
		log += tr("  p0 (");
		log += QString::number(p0->x);
		log += tr("; ");
		log += QString::number(p0->y);
		log += tr("), first__ (");
		log += QString::number(first__->x);
		log += tr("; ");
		log += QString::number(first__->y);
		log += tr("; ");
		log += QString::number(avg::rad_to_grad(first__->angle));
		log += tr(").\n");
		first__++;
	}
	log += "\n\n";

	first__ = pv.begin();
	last__ = first__;
	last__++;
	
	double angle1 = 0;
	log += tr("Углы между соседями:\n");
	while(last__ != pv.end())
	{
		angle1 = avg::angleCW(avg::Vector(*p0, *first__), avg::Vector(*p0, *last__));
		
		log += tr("p0 (");
		log += QString::number(p0->x);
		log += tr("; ");
		log += QString::number(p0->y);
		log += tr("), first__ (");
		log += QString::number(first__->x);
		log += tr("; ");
		log += QString::number(first__->y);
		log += tr("), last__ (");
		log += QString::number(last__->x);
		log += tr("; ");
		log += QString::number(last__->y);
		log += tr("),  angle = ");
		log += QString::number(avg::rad_to_grad(angle1));
		log += "\n";
		
		if(angle1 > avg::pii)
		{
			log += "finded !\n";
			break;
		}
		
		first__++;
		last__++;
	}
	if(angle1 < avg::pii)
	{
		first__ = pv.end();
		first__--;
		last__ = pv.begin();
		angle1 = avg::angleCW(avg::Vector(*p0, *first__), avg::Vector(*p0, *last__));
		log += tr("p0 (");
		log += QString::number(p0->x);
		log += tr("; ");
		log += QString::number(p0->y);
		log += tr("), first__ (");
		log += QString::number(first__->x);
		log += tr("; ");
		log += QString::number(first__->y);
		log += tr("), last__ (");
		log += QString::number(last__->x);
		log += tr("; ");
		log += QString::number(last__->y);
		log += tr("),  angle = ");
		log += QString::number(avg::rad_to_grad(angle1));
		log += "\n";
	}
	log += "\n\n";
	if(angle1 < avg::pii)
		return pv.end();
	else
	if(cw)
		return first__;
	else
		return last__;
	
}

void PointsArea::DrawLine1(avg::Point M0, avg::Vector a)
{
	avg::Point P0;
	avg::Point P1;
	
	if(a.x == 0)
	{
		P0.x = M0.x;
		P0.y = 0;
		P1.y = height()*2;
		P1.x = M0.x;
		Lines2.push_back(LineCustom(P0, P1, Qt::black, 3));
		return ;
	}
	
	P0.x = 0;
	P0.y = M0.y - a.y*M0.x/a.x;
	
	P1.x = height()*2;
	P1.y = a.y*P1.x/a.x - a.y*M0.x/a.x + M0.y;
	Lines2.push_back(LineCustom(P0, P1, Qt::black, 3));
}
