/*Author Vaibhav Bhosale, IIT Bombay*/
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>

using namespace std;


static const int tilesize = 30;

static const int xmaxtiles = 14;
static const int ymaxtiles = 20;

static const int bgcolor = 245;
static const int boardTiles = 1;

struct Tile{
	int x, y;
};

void ts_down(Tile ts[4]){
	for(int i=0; i<4; i++) ts[i].y++;
}

void ts_left(Tile ts[4]){
	for(int i=0; i<4; i++) ts[i].x--;
}

void ts_right(Tile ts[4]){
	for(int i=0; i<4; i++) ts[i].x++;
}

void ts_rotate(Tile ts[4], int midpointTile, int direction)//-1 for counterclock and +1 for clock
{
	if(midpointTile==1)
	{
		int a,b;
		for(int i=0; i<4; i++)
		{
			if(i!=1)
			{
				a=ts[i].x-ts[1].x; b=ts[i].y-ts[1].y;
			
				ts[i].x=ts[1].x-(direction*b);
				ts[i].y=ts[1].y+(direction*a);
			}
		}
	} 
}

void ts_copy(Tile in[4], Tile out[4])
{
	for(int i=0; i<4; i++)
	{
		out[i].x=in[i].x;
		out[i].y=in[i].y;
	}
}

class Board;

class ActivePiece{
	
	friend class Board;
	Tile tileSet[4];
	int color;
	int midpointTile;
	Board*b;
	
	public:
	ActivePiece(Board*container);
	bool moveDown ();
	bool moveLeft ();
	bool moveRight ();
	bool rotate(int direction);
	void fallDown();
};
//----------------------------------------------------------------------
class Board : public Fl_Widget{
	int occupancy [xmaxtiles] [ymaxtiles];
	int score;
	ActivePiece *p;
	ActivePiece *next;
		
	public :
	Board();
	Fl_Box *scoreBox;
	char* scoreLabel;
	void setScoreBox(Fl_Box** sb);
	bool isFree(Tile ts[4]); // before moving down
	bool inBoard(Tile ts[4]); // check boundaries
	void transferTiles(Tile ts[4]);// when the piece comes to rest
	void deleteRow(int row);
	bool rowDone(int row);
	int periodic();
	void draw();
	int handle(int e);
	bool termination();
	bool end;
};
//----------------------------------------------------------------------
ActivePiece :: ActivePiece(Board*container){
	int r = rand()%7; int a = rand()%247;
	int c = (int) (xmaxtiles/2); //xcenter
	b = container;
	color = a;
	if(color==0) color++;
	
	switch(r){
		case 0:
			tileSet[0].x=c-2; tileSet[0].y=0; // horizontal
			tileSet[1].x=c-1; tileSet[1].y=0;
			tileSet[2].x=c; tileSet[2].y=0;
			tileSet[3].x=c+1; tileSet[3].y=0;
			midpointTile = 1;
			break;
			
		case 1:
			tileSet[0].x=c; tileSet[0].y=0; // block
			tileSet[1].x=c-1; tileSet[1].y=0;
			tileSet[2].x=c; tileSet[2].y=1;
			tileSet[3].x=c-1; tileSet[3].y=1;
			midpointTile = -1;
			break;
			
		case 2:
			tileSet[0].x=c-1; tileSet[0].y=1; // L(horizontal)
			tileSet[1].x=c; tileSet[1].y=1;
			tileSet[2].x=c+1; tileSet[2].y=0;
			tileSet[3].x=c+1; tileSet[3].y=1;
			midpointTile = 1;
			break;
			
		case 3:
			tileSet[0].x=c-1; tileSet[0].y=1; // mirror image of L(horizontal)
			tileSet[1].x=c; tileSet[1].y=1;
			tileSet[2].x=c-1; tileSet[2].y=0;
			tileSet[3].x=c+1; tileSet[3].y=1;
			midpointTile = 1;
			break;
			
		case 4:
			tileSet[0].x=c-1; tileSet[0].y=0; // wedge
			tileSet[1].x=c; tileSet[1].y=1;
			tileSet[2].x=c; tileSet[2].y=0;
			tileSet[3].x=c+1; tileSet[3].y=1;
			midpointTile = 1;
			break;
			
		case 5:
			tileSet[0].x=c+1; tileSet[0].y=0; // horizontal wedge
			tileSet[1].x=c; tileSet[1].y=1;
			tileSet[2].x=c; tileSet[2].y=0;
			tileSet[3].x=c-1; tileSet[3].y=1;
			midpointTile = 1;
			break;
			
		case 6:
			tileSet[0].x=c-1; tileSet[0].y=1; // inverted T
			tileSet[1].x=c; tileSet[1].y=1;
			tileSet[2].x=c; tileSet[2].y=0;
			tileSet[3].x=c+1; tileSet[3].y=1;
			midpointTile = 1;
			break;
	}
}

bool ActivePiece :: moveDown(){
	Tile proposedSet[4];
	ts_copy(tileSet, proposedSet);
	ts_down(proposedSet);
	if( ( b->isFree(proposedSet) ) && ( b->inBoard(proposedSet) ) ) {
		//clear();
		ts_copy(proposedSet, tileSet);
		return true;
	}
	
	return false;
}

bool ActivePiece :: moveLeft(){
	Tile proposedSet[4];
	ts_copy(tileSet, proposedSet);
	ts_left(proposedSet);
	if( ( b->isFree(proposedSet) ) && ( b->inBoard(proposedSet) ) ) {
		//clear();
		ts_copy(proposedSet, tileSet);
		return true;
	}
	
	else return false;
}

bool ActivePiece :: moveRight(){
	Tile proposedSet[4];
	ts_copy(tileSet, proposedSet);
	ts_right(proposedSet);
	if( ( b->isFree(proposedSet) ) && ( b->inBoard(proposedSet) ) ) {
		//clear();
		ts_copy(proposedSet, tileSet);
		return true;
	}
	
	else return false;
}

bool ActivePiece :: rotate(int direction){
	Tile proposedSet[4];
	ts_copy(tileSet, proposedSet);
	ts_rotate(proposedSet, midpointTile, direction);
	if( ( b->isFree(proposedSet) ) && ( b->inBoard(proposedSet) ) ) {
		//clear();
		ts_copy(proposedSet, tileSet);
		return true;
	}
	
	else return false;
}

void ActivePiece :: fallDown(){
	Tile proposedSet[4];
	while(moveDown()); 
}
	
	
//----------------------------------------------------------------------


Board :: Board() : Fl_Widget (0, 0, 800, 700,"TETRIS"){
	score=0;
	for(int i=0; i<xmaxtiles; i++)
	{
		for(int j=0; j<ymaxtiles; j++)
		{
			occupancy [i] [j]=0;
		}
	}
	p=new ActivePiece(this);
	next=new ActivePiece(this);
	end=false;
}

void Board :: setScoreBox(Fl_Box** sb){
	scoreBox = *sb ;
	score=0;
	scoreLabel = (char*) malloc(sizeof(char)*10);
}

bool Board :: isFree(Tile ts[4]){
	 for(int z=0; z<4; z++)
	 {
		 if(occupancy [ts[z].x] [ts[z].y] != 0 ) return false;
	 }
	 
	 return true;
}
 
bool Board :: inBoard(Tile ts[4]){
	for(int i=0; i<4; i++)
	{
		if( !((ts[i].x>=0) && (ts[i].x<xmaxtiles) && (ts[i].y>=0) && (ts[i].y<ymaxtiles)) ) return false;
		
	}
	return true;
}

void Board :: transferTiles(Tile ts[4]){
	for(int i=0; i<4; i++)
	{
		occupancy [ts[i].x] [ts[i].y]=p->color;
	}
	p=next;
	next=new ActivePiece(this);
}

void Board :: deleteRow(int row){
	for(int i=row; i>=0; i--)
	{
		for(int j=0; j<xmaxtiles; j++)
		{
			occupancy [j] [i] = occupancy [j] [i-1];
		}
	}
	
	for(int i=0; i<xmaxtiles; i++)
	{
		occupancy [i] [0]=0;
	}
	
}

bool Board :: rowDone(int row){
	bool flag=true;
	for(int i=0; i<xmaxtiles; i++)
	{
		if(occupancy [i] [row] == 0){flag=false;}
	}
	return flag;
}

bool Board :: termination(){
	if ( (occupancy [xmaxtiles/2] [1]!=0) && (occupancy [(xmaxtiles/2)-1] [1]!=0) && (occupancy [(xmaxtiles/2)-1] [1]!=0) && (occupancy [xmaxtiles/2] [1]!=0) ) {end=true; return true; }
	else return false;
}

void timeractions(void *p) {
	((Board *)p)->periodic ();
}

int Board :: periodic(){
	if( !p->moveDown() ) {
		transferTiles(p->tileSet);
	}
	
	for(int i=0; i<ymaxtiles; i++)
	{
		if(rowDone(i)){
			score=score+5;
			stringstream strs;
			strs << score;
			string temp_str = strs.str();
			strcpy(scoreLabel,"Score: ");
			strcat(scoreLabel,(char*) temp_str.c_str() );
	
			scoreBox->label(scoreLabel);
			deleteRow(i);
		}
	}
	
	redraw();
	Fl::repeat_timeout (0.5,timeractions,this);
}

int Board :: handle(int e){
	if(e==8){
		switch (Fl::event_key()) {
			case 65361 : p->moveLeft(); break;
			case 65362 : p->rotate(-1); break;
			case 65363 : p->moveRight(); break;
			case 65364 : p->rotate(1); break;
			case 32 : p->fallDown(); break;
			case 65307 : if(end==true) exit(0); break;
		}
			
		redraw();
	}
}
			
void Board :: draw(){
	for(int i=0; i<xmaxtiles; i++)
	{
		for(int j=0; j<ymaxtiles; j++)
		{
			if(occupancy [i] [j]==0)
			{fl_draw_box(FL_FLAT_BOX, i*tilesize, j*tilesize, tilesize, tilesize, bgcolor);}
			
			else fl_draw_box(FL_BORDER_BOX, i*tilesize, j*tilesize, tilesize, tilesize, occupancy [i] [j]);
		}
	}
	
	for(int i=0; i<4; i++)
	{
		fl_draw_box(FL_BORDER_BOX, (p->tileSet[i].x)*tilesize, (p->tileSet[i].y)*tilesize, tilesize, tilesize, (p->color));
	}
	
	for(int i=xmaxtiles+1; i<xmaxtiles+7; i++)
	{
		for(int j=10; j<17; j++)
		{
			fl_draw_box(FL_FLAT_BOX, i*tilesize, j*tilesize, tilesize, tilesize, bgcolor);
		}
	}
	for(int i=0; i<4; i++)
	{
		fl_draw_box(FL_BORDER_BOX, ((next->tileSet[i].x)+xmaxtiles/2+3)*tilesize, ((next->tileSet[i].y)+11)*tilesize, tilesize, tilesize, next->color);
	}	
	
	if(termination())
	{
		for(int i=xmaxtiles; i>=0; i--)
		{
			for(int j=ymaxtiles-1; j>=0; j--)
			{
				fl_draw_box(FL_FLAT_BOX, i*tilesize, j*tilesize, tilesize, tilesize, 21);
			}
		}
		for(int i=xmaxtiles+1; i<xmaxtiles+7; i++)
		{
			for(int j=10; j<17; j++)
			{
				fl_draw_box(FL_FLAT_BOX, i*tilesize, j*tilesize, tilesize, tilesize, bgcolor);
			}
		}
		//G
		for(int i=3; i<8; i++){
			fl_draw_box(FL_BORDER_BOX, 0*tilesize/2, i*tilesize/2, tilesize/2, tilesize/2, 2);
		}
		for(int i=1; i<4; i++){
			fl_draw_box(FL_BORDER_BOX, i*tilesize/2, 3*tilesize/2, tilesize/2, tilesize/2, 2);
			fl_draw_box(FL_BORDER_BOX, i*tilesize/2, 7*tilesize/2, tilesize/2, tilesize/2, 2);
		}
		for(int i=2; i<4; i++){
			fl_draw_box(FL_BORDER_BOX, i*tilesize/2, 7*tilesize/2, tilesize/2, tilesize/2, 2);
			fl_draw_box(FL_BORDER_BOX, i*tilesize/2, 5*tilesize/2, tilesize/2, tilesize/2, 2);
		}
		fl_draw_box(FL_BORDER_BOX, 3*tilesize/2, 6*tilesize/2, tilesize/2, tilesize/2, 2);
		
		//A
		for(int i=3; i<8; i++)
		{
			fl_draw_box(FL_BORDER_BOX, 5*tilesize/2, i*tilesize/2, tilesize/2, tilesize/2, 2);
			fl_draw_box(FL_BORDER_BOX, 7*tilesize/2, i*tilesize/2, tilesize/2, tilesize/2, 2);
		}
		fl_draw_box(FL_BORDER_BOX, 6*tilesize/2, 3*tilesize/2, tilesize/2, tilesize/2, 2);
		fl_draw_box(FL_BORDER_BOX, 6*tilesize/2, 5*tilesize/2, tilesize/2, tilesize/2, 2);
		
		//M
		for(int i=3; i<8; i++)
		{
			fl_draw_box(FL_BORDER_BOX, 9*tilesize/2, i*tilesize/2, tilesize/2, tilesize/2, 2);
			fl_draw_box(FL_BORDER_BOX, 13*tilesize/2, i*tilesize/2, tilesize/2, tilesize/2, 2);
		}
		for(int i=3; i<6; i++)
		{
			fl_draw_box(FL_BORDER_BOX, 11*tilesize/2, i*tilesize/2, tilesize/2, tilesize/2, 2);
		}
		fl_draw_box(FL_BORDER_BOX, 10*tilesize/2, 3*tilesize/2, tilesize/2, tilesize/2, 2);
		fl_draw_box(FL_BORDER_BOX, 12*tilesize/2, 3*tilesize/2, tilesize/2, tilesize/2, 2);
		
		//E
		for(int i=3; i<8; i++)
		{
			fl_draw_box(FL_BORDER_BOX, 15*tilesize/2, i*tilesize/2, tilesize/2, tilesize/2, 2);
		}
		for(int i=3; i<8; i=i+2)
		{
			fl_draw_box(FL_BORDER_BOX, 16*tilesize/2, i*tilesize/2, tilesize/2, tilesize/2, 2);
			fl_draw_box(FL_BORDER_BOX, 17*tilesize/2, i*tilesize/2, tilesize/2, tilesize/2, 2);
		}
		
		//O
		for(int i=10; i<15; i++)
		{
			fl_draw_box(FL_BORDER_BOX, 3*tilesize/2, i*tilesize/2, tilesize/2, tilesize/2, 2);
			fl_draw_box(FL_BORDER_BOX, 5*tilesize/2, i*tilesize/2, tilesize/2, tilesize/2, 2);
		}
		fl_draw_box(FL_BORDER_BOX, 4*tilesize/2, 10*tilesize/2, tilesize/2, tilesize/2, 2);
		fl_draw_box(FL_BORDER_BOX, 4*tilesize/2, 14*tilesize/2, tilesize/2, tilesize/2, 2);
		
		//V
		for(int i=10; i<13; i++)
		{
			fl_draw_box(FL_BORDER_BOX, 7*tilesize/2, i*tilesize/2, tilesize/2, tilesize/2, 2);
			fl_draw_box(FL_BORDER_BOX, 9*tilesize/2, i*tilesize/2, tilesize/2, tilesize/2, 2);
		}
		fl_draw_box(FL_BORDER_BOX, 7.5*tilesize/2, 13*tilesize/2, tilesize/2, tilesize/2, 2);
		fl_draw_box(FL_BORDER_BOX, 8.5*tilesize/2, 13*tilesize/2, tilesize/2, tilesize/2, 2);
		fl_draw_box(FL_BORDER_BOX, 8*tilesize/2, 14*tilesize/2, tilesize/2, tilesize/2, 2);
		
		//E
		for(int i=10; i<15; i++)
		{
			fl_draw_box(FL_BORDER_BOX, 11*tilesize/2, i*tilesize/2, tilesize/2, tilesize/2, 2);
		}
		for(int i=10; i<15; i=i+2)
		{
			fl_draw_box(FL_BORDER_BOX, 12*tilesize/2, i*tilesize/2, tilesize/2, tilesize/2, 2);
			fl_draw_box(FL_BORDER_BOX, 13*tilesize/2, i*tilesize/2, tilesize/2, tilesize/2, 2);
		}
		
		//R
		for(int i=10; i<15; i++)
		{
			fl_draw_box(FL_BORDER_BOX, 15*tilesize/2, i*tilesize/2, tilesize/2, tilesize/2, 2);
			
		}
		fl_draw_box(FL_BORDER_BOX, 16*tilesize/2, 10*tilesize/2, tilesize/2, tilesize/2, 2);
		fl_draw_box(FL_BORDER_BOX, 16*tilesize/2, 12*tilesize/2, tilesize/2, tilesize/2, 2);
		fl_draw_box(FL_BORDER_BOX, 17*tilesize/2, 10*tilesize/2, tilesize/2, tilesize/2, 2);
		fl_draw_box(FL_BORDER_BOX, 17*tilesize/2, 11*tilesize/2, tilesize/2, tilesize/2, 2);
		fl_draw_box(FL_BORDER_BOX, 17*tilesize/2, 12*tilesize/2, tilesize/2, tilesize/2, 2);
		fl_draw_box(FL_BORDER_BOX, 17.5*tilesize/2, 13*tilesize/2, tilesize/2, tilesize/2, 2);
		fl_draw_box(FL_BORDER_BOX, 18*tilesize/2, 14*tilesize/2, tilesize/2, tilesize/2, 2);
	
		stringstream strs;
			string temp_str = strs.str();
			strcpy(scoreLabel,"Press Escape to Exit ");
			
			scoreBox->label(scoreLabel);
		
	}
	
	
}

int main(int argc, char *argv[]) {
    	Fl_Window *window = new Fl_Window (800,700,"TETRIS");
	window->color(56);
	Board *b = new Board();
	Fl_Box *scorebox = new Fl_Box(tilesize*xmaxtiles+10,50,300,200,"Score: 0\0");
	scorebox->box(FL_UP_BOX);
	scorebox->labelfont(FL_BOLD+FL_ITALIC);
    scorebox->labelsize(36);
    scorebox->labeltype(FL_ENGRAVED_LABEL);
	b->setScoreBox(&scorebox); 
	Fl_Box *exi = new Fl_Box(tilesize*2,ymaxtiles*15,300,200,"Press Escape to Exit");
	exi->box(FL_UP_BOX);
	exi->labelfont(FL_BOLD+FL_ITALIC);
	exi->labelsize(36);
	exi->labeltype(FL_ENGRAVED_LABEL);
	window->end(); 
   	window->show();
   	
	Fl::add_timeout(0.1, timeractions,b);
    	return(Fl::run());
}