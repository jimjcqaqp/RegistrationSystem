#include "Form.h"
#include <curses.h>
#include <iterator>
#include <menu.h>

Form::Form(){
	x = 0;
	y = 0;
	width = 30;
	height = 0;
	hide = false;
	title = "";
	win = NULL;
	footer = "";
}
Form::~Form(){
	this->clear();
}

void Form::center(bool ly, bool lx){
	int lines, cols;
	getmaxyx(stdscr, lines, cols);

	if(ly){		
		y = (int)((lines - height) / 2) - 3;
	}
	if(lx){
		x = (int)((cols - width) / 2) + 3;
	}
}
void Form::add(std::string name, int w){
	inputs[name] = "";
	winputs[name] = w;
}
void Form::start(){
	clear();
	echo();

	int th = 0;
	if(height == 0)
		th = inputs.size();
	else
		th = height;

	int thf = 0;
	if(footer.size() != 0)
		thf = 2;

	win = newwin((th * 3) + 3 + thf, width, y, x);

	box(win, 0, 0);
	
	mvwaddch(win, 2, 0, ACS_LTEE);
	mvwhline(win, 2, 1, ACS_HLINE, width - 2);
	mvwaddch(win, 2, width - 1, ACS_RTEE);
	mvwprintw(win, 1, (width - title.size()) / 2, title.c_str());
	
	// ******************* //
	if(footer.size() != 0)
	{
		mvwaddch(win, (th*3) + 2, 0, ACS_LTEE);
		mvwhline(win, (th*3) + 2, 1, ACS_HLINE, width - 2);
		mvwaddch(win, (th*3) + 2, width - 1, ACS_RTEE);
		mvwprintw(win,(th*3) + 3, (width - footer.size()) / 2, footer.c_str());	
	}

	int i = 3;
  for(std::map<std::string, std::string>::iterator it = inputs.begin();
      it != inputs.end(); it++)
  {
    mvwprintw(win, i, 1, it->first.c_str());
    ////////////////////////////////////
    mvwaddch(win, i - 1, 0, ACS_LTEE);
    mvwhline(win, i - 1, 1, ACS_HLINE, width - 2);
    mvwaddch(win, i - 1, width - 1, ACS_RTEE);
    ///////////////////////////////////
    i += 3;
  }
  wrefresh(win);	

  i = 4;
  for(std::map<std::string, std::string>::iterator it = inputs.begin();
      it != inputs.end(); it++)
  {
    char text[1024];

    while(true)
    {
      // WINDOW *wini = derwin(win, 1, width-2, i, 1);
      WINDOW *wini = derwin(win, 1, winputs[it->first] + 1, i, 1);
      wattron(wini, A_REVERSE);
      mvwgetstr(wini, 0, 0, text);
      wattroff(wini, A_REVERSE);
      it->second = text;
			delwin(wini);
			if(std::string(text) == "q")
			{
				it->second = "";
				this->clear();
				return; 
			}
      if(it->second.size() != 0)
        break;
    }
    i += 3;
  }
	if(hide)
	{
		wclear(win);
		wrefresh(win);
		delwin(win);
		win = NULL;
	}
}
void Form::clear(){
	if(win != NULL)
	{
		wclear(win);
		wrefresh(win);
		delwin(win);
		win = NULL;
	}
}
/* 
int main()
{
	initscr();

	Form form;
	form.add("Nombre");
	form.add("Apellidos");
	form.add("Edad");

	form.title = "Nuevo Usuario";
	form.width = 40;
	form.center(false, true);
	//form.footer = "Complete los campos";
	
	form.start();
	endwin();

  for(std::map<std::string, std::string>::iterator it = form.inputs.begin();
      it != form.inputs.end(); it++)
  {
    std::cout << it->first << "   " << it->second << "   " << it->second.size() << std::endl;
  }


	return 0;	
}
*/
