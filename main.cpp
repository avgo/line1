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
