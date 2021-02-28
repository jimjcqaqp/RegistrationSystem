#include "menu_teacher.h"

void menu_teacher()
{
	std::vector<Teacher> ts = Teacher::all();
	Menu m;

	for(int i = 0; i < ts.size(); ++i)
		m.add(ts[i].name);
	m.add("Salir");

	m.width = 30;
	m.center(false, true);
	m.y = 5;
	m.title = "Login";
	m.hide = true;

	int indice = m.start();

	while(true){
		int indice = m.start();

			

		if(indice == ts.size())
			break;
	}
}

