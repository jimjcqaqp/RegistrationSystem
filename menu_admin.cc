#include "menu_admin.h"
#include "Teacher.h"

void add_course();
void add_teacher();
void add_student();
void view_courses();
void view_teachers();
void view_students();

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
		
		switch(index){
			case 0: add_course() ;break;
			case 1: add_teacher();break;
			case 2: add_student();break;

			case 5: view_courses() ;break;
			case 6: view_teachers();break;
			case 7: view_students();break;
		}
		if(index == 8)
			break;
	}
}

void add_course(){}
void add_teacher(){
	
}
void add_student(){}
void view_courses(){}
void view_teachers(){
	Menu m;
	std::vector<Teacher> ts = Teacher::all();
	for(int i = 0; i < ts.size(); ++i)
		m.add(ts[i].name);

	m.width = 50;
	m.center(false, true);
	m.y = 20;
	m.title = "Todos los docentes";
	m.hide = true;

	m.start();
}
void view_students(){}

