#include "menu_admin.h"
#include "Teacher.h"
#include "Course.h"
#include "Student.h"
#include "Form.h"
#include <boost/format/format_fwd.hpp>
#include <string>
#include <boost/format.hpp>

void add_course();
void add_teacher();
void add_student();
void view_courses();
void view_teachers();
void view_students();
void add_course_requirement();

void menu_admin(){
	Menu m;
	m.add("Agregar curso");
	m.add("Agregar profesor");
	m.add("Agregar estudiante");
	m.add("Agregar requisito a curso");
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
			case 3: add_course_requirement(); break;

			case 5: view_courses() ;break;
			case 6: view_teachers();break;
			case 7: view_students();break;
		}
		if(index == 8)
			break;
	}
}

void add_course(){
	Form f;
	f.add("Codigo", 5);
	f.add("Nombre", 25);
	f.width = 40;
	f.center(false, true);
	f.y = 20;
	f.title = "Agregar Curso";
	f.hide = false;
	
	f.footer = "(q) para cancelar";
	f.start();

	for(std::map<std::string, std::string>::iterator it = f.inputs.begin();
			it != f.inputs.end(); it++)
		if(it->second.size() == 0){
			f.clear();
			return ;
		}

	Menu m;	
	std::vector<Teacher> ts = Teacher::all();
	for(int i = 0; i < ts.size(); ++i)
		m.add(ts[i].name);
	m.width = 40;
	m.center(false, true);
	m.height = 5;
	m.y = 33;			// Se puede modificar para la ubicación
	m.title = "Profesor encargado";
	m.mark = "";
	m.hide = false;
	int indice = m.start();
	
	Course course;
	course.code = f.inputs["Codigo"];
	course.name = f.inputs["Nombre"];
	course.teacher = ts[indice];

	course.save();

	m.clear();
	f.clear();
}
void add_teacher(){
	Form f;	
	f.add("Codigo", 11);
	f.add("Nombre", 25);
	f.width = 40;
	f.center(false, true);
	f.y = 20;
	f.title = "Agregar Profesor";
	f.hide = true;
	f.footer = "(q) para cancelar";

	f.start();

	Teacher t;
	t.code = f.inputs["Codigo"];	
	t.name = f.inputs["Nombre"];
	t.save();
}
void add_student(){
	Form f;
	f.add("Codigo", 11);
	f.add("Nombre", 25);
	f.width = 40;
	f.center(false, true);
	f.y = 20;
	f.title = "Agregar Estudiante";
	f.hide = true;
	f.footer = "(q) para cancelar";

	f.start();

	Student s;
	s.code = f.inputs["Codigo"];	
	s.name = f.inputs["Nombre"];
	s.save();
}
void view_courses(){
	Menu m;
	std::vector<Course> cs = Course::all();
	for(int i = 0; i < cs.size(); ++i)
		m.add((boost::format("%5s") % cs[i].code).str() + "  " + 
					(boost::format("%25s") % cs[i].name).str() + "  " + 
					(boost::format("%10s") % cs[i].teacher.code).str()
					);

	m.width = 50;
	m.center(false, true);
	m.height = 10;
	m.y = 20;
	m.title = "Todos los cursos";
	m.footer = std::to_string(cs.size()) + " cursos";
	m.mark = "";
	m.hide = true;

	m.start();
}
void view_teachers(){
	Menu m;
	std::vector<Teacher> ts = Teacher::all();
	for(int i = 0; i < ts.size(); ++i)
		m.add((boost::format("%15s    ") % ts[i].code).str() + "" + ts[i].name);

	m.width = 50;
	m.center(false, true);
	m.height = 10;
	m.y = 20;
	m.title = "Todos los docentes";
	m.footer = std::to_string(ts.size()) + " profesores";
	m.mark = "";
	m.hide = true;

	m.start();
}
void view_students(){
	Menu m;
	std::vector<Student> ss = Student::all();
	for(int i = 0; i < ss.size(); ++i)
		m.add((boost::format("%15s    ") % ss[i].code).str() + "" + ss[i].name);

	m.width = 50;
	m.center(false, true);
	m.height = 10;
	m.y = 20;
	m.title = "Todos los docentes";
	m.footer = std::to_string(ss.size()) + " estudiantes";
	m.mark = "";
	m.hide = true;

	m.start();
}

void add_course_requirement(){
	
}


