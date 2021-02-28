#pragma once

#include <menu.h>
#include <vector>
#include <string>

class Menu{
	public:
		Menu();
		~Menu();	
		int start();
		void add(std::string option);
		void center(bool vertical, bool horizontal);
		void clear();

		std::vector<std::string> options;
		int x;
		int y;
		int width;
		int height;

		bool hide;
		std::string mark;
		std::string title;

		WINDOW *win;
};

