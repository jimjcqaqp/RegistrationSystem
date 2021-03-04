#pragma once

#include <map>
#include <string>
#include <ncurses.h>
#include <menu.h>

class Form{
	public:
		Form();
		~Form();	
		bool start();
		void add(std::string name, int w);

		void center(bool vertical, bool horizontal);
		void clear();

		std::map<std::string, std::string> inputs;
		std::map<std::string, int> winputs; 
		
		int x;
		int y;
		int width;
		int height;

		bool hide;

		std::string mark;
		std::string title;

		WINDOW *win;
		std::string footer;
};

