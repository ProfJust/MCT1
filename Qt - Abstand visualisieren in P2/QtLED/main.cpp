#include "QtLED.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtLED w;
	w.show();
	return a.exec();
}
