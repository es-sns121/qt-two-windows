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

// Data the two windows will share.
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

// Delete a bunch of widgets. Sleep 100ms after each deletion. 
// This will cause the other window to hitch. Downside of single
// thread.
class Widgets: public QWidget {
	Q_OBJECT
	
	public:
		Widgets(Model * model);
	
	public slots:
		void add_widgets();
		void delete_widgets();

	private:
		bool widgets_added;
		
		QVBoxLayout * layout;
		
		QPushButton * del_widgets_button; 
		QPushButton * add_widgets_button;
		
		std::vector<QLineEdit *> widgets;
		
		Model * model;
};

#endif // WINDOW_H
