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

bool drawing_ended = false;

spatial :: spatial(double x, double y){
	this->x = x;
	this->y = y;
}

spatial :: spatial(){
	
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
temporal :: temporal(){
}

sample :: sample(double x, double y, int timestamp, int id, bool prev){
	spatial z(x,y);
	this -> p = z;
	motion a;
	this->m = a;
	appearance b;
	this-> a = b;
	temporal c(timestamp, id);
	this -> t = c;
	this -> prev = prev;
}

double sample :: getx(){
	return p.getx();
}

double sample :: gety(){
	return p.gety();
}

bool sample :: get_prev(){
	return prev;
}

void drawing::add_sample(sample s){
	this->samples.push_back(s);
}

int drawing::get_samples_size(){
	return this->samples.size();
}

drawing::drawing(){
	
}

double drawing :: distance_from_last_sample(double x, double y){
	return pow((pow((this->samples[this->samples.size()-1].getx()-x),2) + pow((this->samples[this->samples.size()-1].gety()-y),2)), 0.5);
}

double drawing :: get_x_at_index(int i){
	return this->samples[i].getx();
}

double drawing :: get_y_at_index(int i){
	return this->samples[i].gety();
}

bool drawing :: get_prev_at_index(int i){
	return this->samples[i].get_prev();
}

void next_drawing(Fl_Widget *, void *) {
	drawing_ended = true;
}

Board::Board() : Fl_Widget (0,0,1600,700,"Tetris") {
	drawing *d = new drawing();
	button = new Fl_Button(0, 0, 50, 20, "label");
	button->callback(next_drawing, 0);
	this->drawings.push_back(*d);
}

void Board::draw(){
	int tmp = this->drawings.size();
	if(tmp >= 2){
		cout<<tmp<<"\n";
		for(int i = 0; i<this->drawings[tmp-2].get_samples_size()-1; i++){
			if(drawings[tmp-2].get_prev_at_index(i+1)){
				fl_color(63);
				fl_line(this->drawings[tmp-2].get_x_at_index(i), this->drawings[tmp-2].get_y_at_index(i), this->drawings[tmp-2].get_x_at_index(i+1), this->drawings[tmp-2].get_y_at_index(i+1));	
			}
		}
		for(int i = 0; i<this->drawings[tmp-1].get_samples_size()-1; i++){
			if(drawings[tmp-1].get_prev_at_index(i+1)){
				fl_color(0);
				fl_line(this->drawings[tmp-1].get_x_at_index(i), this->drawings[tmp-1].get_y_at_index(i), this->drawings[tmp-1].get_x_at_index(i+1), this->drawings[tmp-1].get_y_at_index(i+1));	
			}
		}
	}
	else if(tmp == 1){
		for(int i=0; i<this->drawings[0].get_samples_size()-1;i++){
			int x1 = this->drawings[0].get_x_at_index(i);
			int y1 = this->drawings[0].get_y_at_index(i);
			int x2 = this->drawings[0].get_x_at_index(i+1);
			int y2 = this->drawings[0].get_y_at_index(i+1);
			if(drawings[0].get_prev_at_index(i+1)){
				fl_color(0);
				fl_line(x1, y1, x2, y2); 	
			}
		}
	}
	
}

int Board::handle(int e) {

	switch (e){
		case FL_PUSH:
			{
				drawing_ended = false;
				int x_coord = Fl::event_x();
				int y_coord = Fl::event_y();
				drawing *dwg = &(this->drawings[this->drawings.size()-1]);
				// dwg.strokes.push_back(*l);
				int temp_id,temp_tstamp;
				temp_id=dwg->get_samples_size();
				temp_tstamp=this->drawings.size();
				sample *l = new sample(x_coord,y_coord,temp_id,temp_tstamp, false);
				dwg->add_sample(*l);
				break;
			}
		case FL_DRAG:
			{	int x_coord = Fl::event_x();
				int y_coord = Fl::event_y();
				int temp_id,temp_tstamp;
	
				drawing *dwg = &(this->drawings[this->drawings.size()-1]);
				// sample last_sample = dwg->samples[dwg->samples.size()-1];
				spatial *new_s = new spatial(x_coord,y_coord);
	
				if(dwg->distance_from_last_sample(x_coord, y_coord) > 0.2){
					temp_id=dwg->get_samples_size();
					temp_tstamp=this->drawings.size();
					sample *l = new sample(x_coord,y_coord,temp_id,temp_tstamp, true);
					dwg->add_sample(*l);
				}
				break;
			}
			

		case FL_RELEASE:
			{
				int x_coord = Fl::event_x();
				int y_coord = Fl::event_y();
				drawing *dwg = &(this->drawings[this->drawings.size()-1]);
				// dwg.strokes.push_back(*l);
				int temp_id,temp_tstamp;
				temp_id=dwg->get_samples_size();
				temp_tstamp=this->drawings.size();
				sample *l = new sample(x_coord,y_coord,temp_id,temp_tstamp, true);
				dwg->add_sample(*l);
				break;
			}
	}
	redraw();
}

void timeractions(void *p) {
	     ((Board *)p)->periodic ();
}

int Board::periodic(){
	if(drawing_ended){
		drawing *d = new drawing();
		this->drawings.push_back(*d);
		drawing_ended = false;
	}
	redraw();
	Fl::repeat_timeout (0.1,timeractions,this);
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