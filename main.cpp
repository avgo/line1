
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   line1 - разделение классов точек на плоскости.
 *   4-й курс, 2-й семестр.
 *   Лабораторная работа по курсу "Искусственный интеллект".
 *   01.02.2008 - 31.03.2008.
 *   Автор: Антон Гончаров
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <QtGui>
#include <QTextCodec>
#include "MainWindow.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
	MainWindow mainWnd;
	mainWnd.show();
	return app.exec();
}
