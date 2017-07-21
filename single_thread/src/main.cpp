#include <QApplication>
#include "window.h"

int main (int argc, char **argv) 
{
	// The main application.
	QApplication app(argc, argv);

	// Object for data encapsulation
	Model * model = new Model;
	
	// Two windows. One that operates a counter, the other
	// that performs a 'caculation'. In reality it sleeps
	// for 1.5 seconds.
	Counter * counter = new Counter(model);
	Calc * calc = new Calc(model);

	counter->show();
	calc->show();

	return app.exec();
}
