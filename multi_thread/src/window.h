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

class Calc_Data : public QObject {
	Q_OBJECT

	public slots:
		void calculation();
	
	signals:
		void send(QString);
		void finished();

	private:
		// Data would go here.
};

// Sleep 250ms for each 'calculation'. 
// This will cause the other window to hitch. Downside of a 
// single thread.
class Calc: public QWidget {
	Q_OBJECT
	
	public:
		Calc(Model * model);
	
	public slots:
		void do_work();
		void recieve(QString);	
	
	private:
		QVBoxLayout * layout;
		
		QLabel * calc_display;

		Model * model;
};

#endif // WINDOW_H
