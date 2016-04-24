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
	int periodic();	
	void draw(){
		// draw
	}

	int handle(int e) {

	     if (e==8) {
          
	     switch(Fl::event_key()) {
				// case 65307: exit (1);  // Esc key
				// case 65361: moveallleft(tilesize);break;  // left arrow
			}
	      
      redraw();
	}
};

void timeractions(void *p) {
	     ((Board *)p)->periodic ();
}
     
int Board::periodic() {    
	redraw();
	Fl::repeat_timeout (0.5,timeractions,this);
}




int main(){
	Fl_Window *window = new Fl_Window(800,800, "System");
	window->color(0);
	Board *b = new Board();

	Fl::add_timeout(0.1, timeractions,b);
	return(Fl::run());
}