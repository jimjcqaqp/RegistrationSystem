#pragma once

#include <menu.h>
#include <vector>
#include <string>

class Message{
	public:
		Message();
		~Message();	
		void start();
		void center(bool vertical, bool horizontal);
		void clear();

		int x;
		int y;
		int width;
		int height;

		bool hide;

		std::string title;
		WINDOW *win;
		std::string footer;
		std::string message;
};

