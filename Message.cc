#include "Message.h"
#include <curses.h>
#include <iterator>
#include <menu.h>

Message::Message(){
	x = 0;
	y = 0;
	width = 40;
	height = 0;
	hide = true;
	title = "";
	win = NULL;
	footer = "";
	message = "";
}
Message::~Message(){
	this->clear();
}

void Message::center(bool ly, bool lx){
	int lines, cols;
	getmaxyx(stdscr, lines, cols);

	if(ly){		
		y = (int)((lines - height) / 2) - 3;
	}
	if(lx){
		x = (int)((cols - width) / 2) + 3;
	}
}

void Message::start(){
	clear();

	// WINDOW *win;
	int i;

	cbreak();
	noecho();
	curs_set(0);

	win = newwin(5, width, y, x);
	keypad(win, TRUE);

	box(win, 0, 0);

	mvwaddch(win, 2, 0, ACS_LTEE);
	mvwhline(win, 2, 1, ACS_HLINE, width - 2);
	mvwaddch(win, 2, width - 1, ACS_RTEE);
	mvwprintw(win, 1, (width - title.size()) / 2, title.c_str());
	
	mvwprintw(win, 3, (width - message.size()) / 2, message.c_str());
	wrefresh(win);

	wgetch(win);
	
	if(hide)
	{
		wclear(win);
		wrefresh(win);
		delwin(win);
		win = NULL;
	}
	curs_set(1);
}
void Message::clear(){
	if(win != NULL)
	{
		wclear(win);
		wrefresh(win);
		delwin(win);
		win = NULL;
	}
}
