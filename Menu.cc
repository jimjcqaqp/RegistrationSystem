#include "Menu.h"
#include <curses.h>
#include <iterator>
#include <menu.h>

Menu::Menu(){
	x = 0;
	y = 0;
	width = 30;
	height = 0;
	hide = false;
	mark = "-> ";
	title = "";
	win = NULL;
}
Menu::~Menu(){
	this->clear();
}

void Menu::center(bool ly, bool lx){
	int lines, cols;
	getmaxyx(stdscr, lines, cols);

	if(ly){		
		y = (int)((lines - height) / 2) - 3;
	}
	if(lx){
		x = (int)(cols - width) / 2 + 3;
	}
}
void Menu::add(std::string option){
	options.push_back(option);
}
int Menu::start(){
	ITEM **items;	
	MENU *menu;
	// WINDOW *win;
	int i;

	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);

	items = (ITEM **) calloc(options.size() + 1, sizeof(ITEM *));
	for(i = 0; i < options.size(); ++i)	
		items[i] = new_item(options[i].c_str(), NULL);
	items[i] = new_item(NULL, NULL);

	menu = new_menu(items);

	int th = 0;
	if(height == 0)
		th = options.size();
	else
		th = height;
	win = newwin(th + 4, width, y, x);
	keypad(win, TRUE);

	set_menu_win(menu, win);
	set_menu_sub(menu, derwin(win, th , width - 2, 3, 2));
	set_menu_format(menu, th, 1);

	set_menu_mark(menu, mark.c_str());

	box(win, 0, 0);

	mvwaddch(win, 2, 0, ACS_LTEE);
	mvwhline(win, 2, 1, ACS_HLINE, width - 2);
	mvwaddch(win, 2, width - 1, ACS_RTEE);

	mvwprintw(win, 1, (width - title.size()) / 2, title.c_str());

	post_menu(menu);
	wrefresh(win);

	int c;
	while((c = wgetch(win)) != 10){
		switch(c){
			case KEY_DOWN: menu_driver(menu, REQ_DOWN_ITEM); break;
			case KEY_UP: menu_driver(menu, REQ_UP_ITEM); break;
			case KEY_NPAGE: menu_driver(menu, REQ_SCR_DPAGE); break;
			case KEY_PPAGE: menu_driver(menu, REQ_SCR_UPAGE); break;
		}
		wrefresh(win);
	}

	/* get */
 	ITEM *select_item = current_item(menu);	
	int index = item_index(select_item);

	unpost_menu(menu);
	free_menu(menu);
	for(i = 0; i < options.size(); ++i)
		free_item(items[i]);

	if(hide)
	{
		wclear(win);
		wrefresh(win);
		delwin(win);
		win = NULL;
	}
	curs_set(1);
	return index;
}
void Menu::clear(){
	if(win != NULL)
	{
		wclear(win);
		wrefresh(win);
		delwin(win);
		win = NULL;
	}
}
