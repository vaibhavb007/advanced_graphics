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
bool stroke_started=false;
sample *last_sample;


Board::Board() : Fl_Widget (0,0,1600,700,"Tetris") { 

}

void Board::add_sample(sample s){
	this->samples.push_back(s);
}
	
void Board::draw(){
		
}

int Board::handle(int e) {

    switch (e){
    	case FL_DRAG:
    		int x_coord = event_x();
    		int y_coord = event_y();
    		sample l = new sample(x_coord,y_coord,);

    		if(!stroke_started){
    			last_sample= l;
    			add_sample(l);
    			stroke_started=true;
    		}
    	
    		if(spatial_dist(last_sample->p,l->p) > 2){
    			add_sample(l);
    		}


    }
}

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