#include "window.h"

#include <iostream>
#include <ctime>

#include <QApplication>
#include <QLabel>
#include <QMutex>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QTimer>
#include <QPushButton>

using namespace std;

Model::Model()
{
	mutex = new QMutex;
	count = 0;
}

Counter::Counter(Model * model) :
	model(model)
{
	counter_display = new QLabel;
	counter_display->setFrameStyle(QFrame::VLine || QFrame::Raised);
	counter_display->setFixedSize(200, 40);
	
	counter_display->setAlignment(Qt::AlignCenter);
	
	QVBoxLayout * layout = new QVBoxLayout;

	layout->addWidget(counter_display);

	setLayout(layout);

	// Timer will emit signal every 250 ms. 
	QTimer * timer = new QTimer(this);
	QObject::connect(timer, SIGNAL (timeout()), this, SLOT(update_count()));
	timer->start(250);

}

// Increments count by 1, resets to 1 when 100 is reached.
void Counter::update_count() 
{
	model->mutex->lock();
	
	if   (model->count == 100) model->count = 1;
	else model->count += 1;
	
	QString qStr;
	qStr.setNum(model->count);
	model->mutex->unlock();

	counter_display->setText(qStr);
}

Calc::Calc(Model * model) :
	model(model)
{
	layout = new QVBoxLayout;
	
	calc_display = new QLabel("Done");
	calc_display->setFrameStyle(QFrame::VLine || QFrame::Raised);
	calc_display->setFixedSize(200, 40);
	
	calc_display->setAlignment(Qt::AlignCenter);

	layout->addWidget(calc_display);

	setLayout(layout);	
	
	QTimer * timer = new QTimer(this);
	QObject::connect(timer, SIGNAL (timeout()), this, SLOT(do_work()));
	timer->start(5000);
}

// Performs a 'calculation'
void Calc::do_work()
{
	calc_display->setText("Performing Calculation");
	qApp->processEvents();	// Force a redraw by asking the app to process its event queue.

	struct timespec req, rem; 	// Requested and remaining time to sleep. 
								// Upon success rem will = 0.0
	req.tv_sec  = 1;
	req.tv_nsec = 500000000; 
	
	nanosleep(&req, &rem);
	
	calc_display->setText("Done");
}
