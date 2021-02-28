#include "menu_admin.h"

void menu_admin(){
	Menu m;
	m.add("Agregar curso");
	m.add("Agregar profesor");
	m.add("Agregar estudiante");
	m.add("Encargar profesor a curso");
	m.add("Matricular alumno en un curso");
	m.add("Ver Cursos");
	m.add("Ver Profesores");
	m.add("Ver Alumnos");
	m.add("Regresar");

	m.width = 40;
	m.center(false, true);
	m.y = 5;
	m.title = "Menu administrador";
	m.hide = false;


	while(true){
		int index = m.start();
		
		if(index == 8)
			break;
	}

}

