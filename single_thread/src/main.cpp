#include <QApplication>
#include "window.h"

int main (int argc, char **argv) 
{
	QApplication app(argc, argv);

	Model * model = new Model;
	
	Counter * counter = new Counter(model);
	Calc * calc = new Calc(model);

	counter->show();
	calc->show();

	return app.exec();
}
