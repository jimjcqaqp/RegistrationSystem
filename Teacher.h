#pragma once

#include <iostream>
#include <sqlite3.h>
#include <vector>

class Teacher{
	public:
		Teacher();
		~Teacher();
		static Teacher find(int id);
		static std::vector<Teacher> all(); 
		bool save();
		// void remove();

		// Propiedades
		int id = 0;
		std::string name;
		std::string code;
};

