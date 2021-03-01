#pragma once

#include <map>
#include <string>
#include <ncurses.h>

class Form{
	public:
		Form();
		~Form();	
		void start();
		void add(std::string name);

		void center(bool vertical, bool horizontal);
		void clear();

		std::map<std::string, std::string> inputs;
		
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

