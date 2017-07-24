#ifndef WINDOW_H
#define WINDOW_H

#include <vector>
#include <QObject>
#include <QWidget>

class QLabel;
class QMutex;
class QLineEdit;
class QPushButton;
class QVBoxLayout;

// Data the two windows can share.
class Model : public QObject {
	Q_OBJECT

	public:
		Model();
		QMutex * mutex;
		int count;
};

// Counter to demonstrate application performing work.
class Counter : public QWidget {
	Q_OBJECT
	
	public:
		Counter(Model * model);
	
	public slots:
		void update_count();
	
	private:
		QLabel * counter_display;		
		Model * model;
};

// Sleep 1500 ms for each 'calculation'. 
// This will cause the other window to hitch. Downside of a 
// single thread.
class Calc: public QWidget {
	Q_OBJECT
	
	public:
		Calc(Model * model);
	
	public slots:
		void do_work();
		
	private:
		QVBoxLayout * layout;
		
		QLabel * calc_display;

		Model * model;
};

#endif // WINDOW_H
