#pragma once

#include "Teacher.h"
#include <iostream>
#include <sqlite3.h>
#include <vector>

class Course{
	public:
		Course();
		~Course();
		static Course find(int id);
		static std::vector<Course> all(); 
		bool save();
		// void remove();

		// Propiedades
		int id = 0;
		std::string name;
		std::string code;
		Teacher teacher;
};

