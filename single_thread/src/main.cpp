#include <QApplication>
#include "window.h"

int main (int argc, char **argv) 
{
	QApplication app(argc, argv);

	Model * model = new Model;
	
	Counter * counter = new Counter(model);
	Widgets * widgets = new Widgets(model);

	counter->show();
	widgets->show();

	return app.exec();
}
