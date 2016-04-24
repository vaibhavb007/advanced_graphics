#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
using namespace std;

class Board;

class spatial{
	double x;
	double y;
public:
	spatial();
	spatial(double x, double y);
	void setposition(double x, double y);
	double getx();
	double gety();
};

class motion{
	double rot[2][2];
	double trans[2];
public:
	motion();
};

class appearance{
	int color;
public:
	appearance();
};

class temporal{
	int timestamp;
	int id;
public:
	temporal();
	temporal(int timestamp, int id);
};

class sample{
		bool prev;
		spatial p;
		motion m;
		appearance a;
		temporal t;
	public:
		sample(double x, double y, int timestamp, int id, bool prev);
		double getx();
		double gety();
		bool get_prev();
};

class drawing{
	int id;
	vector<sample> samples;
	public:
	drawing();
	void add_sample(sample s);
	int get_samples_size();
	double distance_from_last_sample(double x, double y);
	double get_x_at_index(int i);
	double get_y_at_index(int i);
	bool get_prev_at_index(int i);
};

class Board : public Fl_Widget{
	vector<drawing> drawings;
	public:

	Board();
	int periodic();	
	void draw();
	int handle(int e);
};

void timeractions(void *p);