#include "Menu.h"
#include "menu_teacher.h"
#include "menu_admin.h"

void menu_admin();
void menu_teacher();

int main(){
	initscr();

	Menu m;
	m.add("Administrador");
	m.add("Docente");
	m.add("Estudiante");
	m.add("Salir");

	m.width = 25;
	m.center(false, true);
	m.y = 5;
	m.title = "Login";
	m.hide = true;
	while(true)
	{
		int index = m.start();

		switch(index){
			case 0:
				m.clear();
				menu_admin();
				break;
			case 1: 
				m.clear();
				menu_teacher();
		}
			
		if(index == 3)
			break;
	}
	endwin();
	return 0;
}

	
