#include "Menu.h"

void menu_admin();

int main(){
	initscr();

	Menu m;
	m.add("Administrador");
	m.add("Docente");
	m.add("Estudiante");
	m.add("Salir");

	m.center(false, true);
	m.y = 5;
	m.title = "Login";
	m.width = 25;
	m.hide = true;
	while(true)
	{
		int index = m.start();

		switch(index){
			case 0:  
				menu_admin();
				break;
		}
			
		if(index == 3)
			break;
	}
	endwin();
	return 0;
}

void menu_admin(){
	Menu madmin;
	madmin.add("Agregar curso");
	madmin.add("Agregar profesor");
	madmin.add("Agregar estudiante");
	madmin.add("Regresar");

	madmin.center(false, true);
	madmin.y = 5;
	madmin.title = "Menu administrador";
	madmin.width = 30;
	madmin.hide = false;

	madmin.start();
	madmin.clear();
}
