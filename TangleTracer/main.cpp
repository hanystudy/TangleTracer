#include "tangletracer.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TangleTracer w;
	w.show();
	return a.exec();
}
