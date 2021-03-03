#include "menu_teacher.h"
#include "Course.h"
#include "Grade.h"
#include <boost/format.hpp>

void menu_teacher_postlogin(Teacher t);
void workload(Teacher &t);
void add_note(Teacher &t);

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
				workload(t);
				break;
			case 1:
				add_note(t);
				break;
		}
		if(indice == 2)
			break;
	}
}

void workload(Teacher &t){
	Menu m;
	std::vector<Course> cs = Course::allByTeacher(t.id);
	for(int i = 0; i < cs.size(); ++i)
	{
		// m.add(cs[i].name);
		// std::vector<Grade> gs = Grade::findByStudentAndCourse
		m.add((boost::format("%25s") % cs[i].name).str());
	}
	m.width = 50;
	m.center(false, true);
	m.height = 10;
	m.y = 13;
	m.title = "Todos los cursos";
	m.footer = std::to_string(cs.size()) + " cursos";
	m.mark = "";
	m.hide = true;

	m.start();
}
void add_note(Teacher &t){
	Menu m;
	std::vector<Course> cs = Course::allByTeacher(t.id);
	for(int i = 0; i < cs.size(); ++i)
		m.add((boost::format("%25s") % cs[i].name).str());
	m.width = 50;
	m.center(false, true);
	m.height = 10;
	m.y = 13;
	m.title = "Todos los cursos";
	m.footer = std::to_string(cs.size()) + " cursos";
	m.mark = "";
	m.hide = true;

	m.start();

}


