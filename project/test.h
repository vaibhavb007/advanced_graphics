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
	spatial(int x, int y);
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
	temporal(int timestamp, int id);
};

class sample{
		spatial p;
		motion m;
		appearance a;
		temporal t;
	public:
		sample();
};

class Board : public Fl_Widget{
	vector<sample> samples;
	public:

	Board();
	void add_sample(int x, int y);
	int periodic();	
	void draw();
	int handle(int e);
};

void timeractions(void *p);