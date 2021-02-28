#include "Menu.h"

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

	Menu madmin;
	madmin.add("Agregar curso");
	madmin.add("Agregar profesor");
	madmin.add("Agregar estudiante");
	madmin.add("Regresar");

	madmin.center(false, true);
	madmin.y = 5;
	madmin.title = "Menu administrador";
	madmin.width = 30;
	madmin.hide = true;

	while(true)
	{
		int index = m.start();

		switch(index){
			case 0: madmin.start(); break;
		}
			
		if(index == 3)
			break;
	}
	endwin();
	return 0;
}

