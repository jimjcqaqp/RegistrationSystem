#include "menu_teacher.h"
#include "Grade.h"

void menu_teacher_postlogin(Teacher t);
void workload();

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

	
	int indice = m.start();
	if(indice == ts.size())
		return;
	menu_teacher_postlogin(ts[indice]);
	
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
		switch(indice){
			case 0: 
				workload();
				break;
			case 1:
				break;
		}
		if(indice == 2)
			break;
	}
}

void workload(){
/*	Menu m;
	std::vector<Grade> gs = Grade::allByCourseId();
	for(int i = 0; i < ts.size(); ++i)
		m.add("");

	m.width = 50;
	m.center(false, true);
	m.height = 10;
	m.y = 20;
	m.title = "Todos los docentes";
	m.footer = std::to_string(ts.size()) + " profesores";
	m.mark = "";
	m.hide = true;

	m.start();
*/
}


