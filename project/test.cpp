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
#include "test.h"
using namespace std;

Board::Board() : Fl_Widget (0,0,1600,700,"Tetris") { 

}

void Board::add_sample(int x, int y){
	sample s;
	s.p
}
	int periodic();	
	void draw(){
		
	}

	int handle(int e) {
	    switch (e){
	    	case FL_DRAG:
	    		int x_coord = event_x();
	    		int y_coord = event_y();

	    		add_sample(x_coord,y_coord);

	    }
	}
};

void timeractions(void *p) {
	     ((Board *)p)->periodic ();
}

int Board::periodic() {    
	redraw();
	Fl::repeat_timeout (0.5,timeractions,this);
	return 1;
}


     
int main(){
	Fl_Window *window = new Fl_Window(800,800, "System");
	window->color(255);
	Board *b = new Board();
	window->end(); 
   	window->show();
	Fl::add_timeout(0.1, timeractions,b);
	return(Fl::run());
}