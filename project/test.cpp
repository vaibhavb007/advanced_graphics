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



int main(){
	Fl_Window *window = new Fl_Window(800,800, "System");
	window->color(0);
	Board *b = new Board();

	Fl::add_timeout(0.1, timeractions,b);
	return(Fl::run());
}