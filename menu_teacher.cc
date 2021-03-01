#include "menu_teacher.h"

void menu_teacher_postlogin(Teacher t);

void menu_teacher()
{
	std::vector<Teacher> ts = Teacher::all();
	Menu m;

	for(int i = 0; i < ts.size(); ++i)
		m.add(ts[i].name);
	m.add("Salir");

	m.width = 40;
	m.center(false, true);
	m.y = 5;
	m.title = "Login";
	m.hide = true;

	while(true){
		int indice = m.start();
		if(indice == ts.size())
			break;
		menu_teacher_postlogin(ts[indice]);
	}
}

void menu_teacher_postlogin(Teacher t){
	Menu m;
	m.add("Ver carga lectiva asignada");
	m.add("Ingresar nota");
	m.add("Salir");	
	m.width = 40;
	m.center(false, true);
	m.y = 5;
	m.title = t.name;
	m.hide = false;

	while(true){
		int indice = m.start();
		if(indice == 2)
			break;
	}
}

