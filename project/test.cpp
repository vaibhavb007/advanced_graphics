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

spatial :: spatial(double x, double y){
	this->x = x;
	this->y = y;
}

void spatial :: setposition(double x, double y){
	this->x = x;
	this->y = y;
}

double spatial :: getx(){
	return this->x;
}

double spatial :: gety(){
	return this->y;
}

motion :: motion(){
	rot[0][0] = 1;
	rot[0][1] = 0;
	rot[1][0] = 0;
	rot[1][1] = 1;
	trans[0] = 0;
	trans[1] = 0;
}

appearance :: appearance(){
	color = 1;
}

temporal :: temporal(int timestamp, int id){
	this -> timestamp = timestamp;
	this -> id = id;
}

sample :: sample(double x, double y, int timestamp, int id){
	this->p.setposition(x, y);
	motion a();
	this->m = a;
	appearance b();
	this-> a = b;
	temporal c(timestamp, id);
	this -> t = c;
}

Board::Board() : Fl_Widget (0,0,1600,700,"Tetris") { 

}

void Board::add_sample(int x, int y){
	sample s;
}

void Board::draw(){
		
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