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
#include <QThread>

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

	QTimer * timer = new QTimer(this);
	QObject::connect(timer, SIGNAL (timeout()), this, SLOT(update_count()));
	timer->start(250);

}

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

void Calc::do_work()
{
	calc_display->setText("Performing Calculation");
	qApp->processEvents();	// Force a redraw by asking the app to process its event queue.

	QThread * thread = new QThread;
	
	Calc_Data * data = new Calc_Data;
	
	data->moveToThread(thread);

	QObject::connect(thread, SIGNAL (started()),  data,   SLOT (calculation()));
	QObject::connect(  data, SIGNAL (finished()), thread, SLOT (quit()));
	QObject::connect(  data, SIGNAL (finished()), this,   SLOT (done()));
	QObject::connect(  data, SIGNAL (finished()), data,   SLOT (deleteLater()));
	QObject::connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));

	thread->start();

	// Retrieve calculation result through some sort of signal\slot combo.
	// Ex: connect( data, SIGNAL (send(calculated_data)), this, SLOT (receive(calculated_data))); 
	// Then delete the data object by connecting Calc_Data::finished() to Calc_Data::deleteLater()
}

void Calc::done()
{
	calc_display->setText("Done");
}

void Calc_Data::calculation()
{
	struct timespec req, rem; 	// Requested and remaining time to sleep. 
								// Upon success rem will = 0.0
	req.tv_sec  = 1;
	req.tv_nsec = 500000000; 
	
	nanosleep(&req, &rem);

	emit finished();
}
