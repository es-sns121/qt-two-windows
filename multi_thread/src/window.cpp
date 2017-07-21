#include "window.h"

#include <iostream>
#include <ctime>

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
	counter_display = new QLabel("blah blah blah");
	counter_display->setFrameStyle(QFrame::VLine || QFrame::Raised);
	
	QVBoxLayout * layout = new QVBoxLayout;

	layout->addWidget(counter_display);

	setLayout(layout);

	QTimer * timer = new QTimer(this);
	QObject::connect(timer, SIGNAL (timeout()), this, SLOT(update_count()));
	timer->start(1000);

}

void Counter::update_count() 
{
	model->mutex->lock();
	
	if   (model->count == 10) model->count = 1;
	else model->count += 1;
	
	QString qStr;
	qStr.setNum(model->count);
	model->mutex->unlock();

	counter_display->setText(qStr);
}

Widgets::Widgets(Model * model) :
	widgets_added(false),
	model(model)
{
	layout = new QVBoxLayout;
	
	add_widgets_button = new QPushButton;
	add_widgets_button->setText("Add Widgets");
	
	del_widgets_button = new QPushButton;
	del_widgets_button->setText("Delete Widgets");

	QObject::connect(add_widgets_button, SIGNAL (clicked()), 
		this, SLOT (add_widgets()));
	
	QObject::connect(del_widgets_button, SIGNAL (clicked()), 
		this, SLOT (delete_widgets()));

	layout->addWidget(add_widgets_button);
	layout->addWidget(del_widgets_button);
	
	for (size_t i = 0; i < 10; ++i) {
		widgets.push_back(new QLineEdit);
		layout->addWidget(widgets[i]);
	}
	
	widgets_added = true;

	setLayout(layout);	
}

void Widgets::add_widgets()
{
	if (widgets_added == true)
		return;
	
	for (size_t i = 0; i < 10; ++i) {
		widgets[i] = new QLineEdit;
		layout->addWidget(widgets[i]);
	}
	
	setLayout(layout);

	widgets_added = true;
}

void Widgets::delete_widgets()
{
	if (widgets_added == false)
		return;

	struct timespec req; 		// requested sleep
	struct timespec rem; 		// remaining sleep. upon success, = 0
 	
	for (size_t i = 0; i < 10; ++i) {	
		
		delete widgets[i];

		req.tv_sec = 0;  			
		req.tv_nsec = 250000000;  	// .25 seconds
		nanosleep(&req, &rem);		
		setLayout(layout);
	}
	
	widgets_added = false;
}
