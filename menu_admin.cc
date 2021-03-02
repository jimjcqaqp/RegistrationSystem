#include "Message.h"
#include "menu_admin.h"
#include "Teacher.h"
#include "Course.h"
#include "Student.h"
#include "Grade.h"
#include "Form.h"
#include <string>
#include <boost/format.hpp>

static void active_message(std::string title, std::string msg);

void add_course();
void add_teacher();
void add_student();
void register_student();
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
			case 4: register_student(); break;	
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

	if(ts.size() == 0)
		return ;
		
	Course course;
	course.code = f.inputs["Codigo"];
	course.name = f.inputs["Nombre"];
	course.teacher = ts[indice];

	if(course.save() == false)
		active_message("ERROR", "ERROR DB");
	else
		active_message("COMPLETADO", "El curso fue agregado");

	m.clear();
	f.clear();
}
void add_teacher(){
	Form f;	
	f.add("Codigo", 10);
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
	if(t.save() == false)
		active_message("ERROR", "ERROR DB");
	else
		active_message("COMPLETADO", "El profesor fue creado");
}
void add_student(){
	Form f;
	f.add("Codigo", 10);
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

	if(s.save() == false)
		active_message("ERROR", "ERROR DB");
	else
		active_message("COMPLETADO", "El estudiante fue creado");
}
void view_courses(){
	Menu m;
	std::vector<Course> cs = Course::all();
	for(int i = 0; i < cs.size(); ++i)
	{
		Course course_re = Course::find(cs[i].course_id);
		m.add((boost::format("%5s") % cs[i].code).str().substr(0, 5) + "  " + 
					(boost::format("%25s") % cs[i].name).str().substr(0, 25) + "  " + 
					(boost::format("%10s") % cs[i].teacher.code).str().substr(0, 10) + "  " +
					(boost::format("%22s") % course_re.name).str().substr(0, 22)
					);
	}

	m.width = 70;
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
		m.add((boost::format("%15s") % ts[i].code).str().substr(0, 15) + 
					(boost::format("%32s ") % ts[i].name).str().substr(0, 33));

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
		m.add((boost::format("%15s") % ss[i].code).str() + 
					(boost::format("%32s ") % ss[i].name).str().substr(0, 33));

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
	Menu m;
	std::vector<Course> cs = Course::all();
	for(int i = 0; i < cs.size(); ++i)
	{
		Course course_re = Course::find(cs[i].course_id);
		m.add((boost::format("%5s") % cs[i].code).str().substr(0, 5) + "  " + 
					(boost::format("%25s") % cs[i].name).str().substr(0, 25) + "  " + 
					(boost::format("%10s") % cs[i].teacher.code).str().substr(0, 10) + "  " +
					(boost::format("%22s") % course_re.name).str().substr(0, 22)
					);
	}
	m.width = 70;
	m.center(false, true);
	m.height = 10;
	m.y = 20;
	// m.footer = std::to_string(cs.size()) + " cursos";
	m.mark = "";
	m.hide = true;

	m.title = "Curso";
	m.footer = "";
	int indice_course = m.start();

	if(cs.size() == 0)
		return;

	m.title = "Curso de requirimiento";
	m.footer = cs[indice_course].name;
	int indice_course_r = m.start();
	
	if(cs[indice_course].id != cs[indice_course_r].id){
		cs[indice_course].course_id = cs[indice_course_r].id;

		if(cs[indice_course].save() == false)
			active_message("ERROR", "ERROR DB");
		else
			active_message("COMPLETADO", "Requerimiento agregado");
	}
}

void register_student(){
	int indice_student, indice_course;

	Menu ms;
	std::vector<Student> ss = Student::all();
	for(int i = 0; i < ss.size(); ++i)
		ms.add( (boost::format("%27s ") % ss[i].name).str());
	ms.width = 30;
	ms.center(false, true);
	ms.height = 10;
	ms.y = 20;
	ms.x -= 15;
	ms.mark = "";
	ms.hide = false;
	ms.title = "Alumno";

	indice_student = ms.start();
	if(ss.size() == 0)
	{
		ms.clear();
		return ;
	}

	Menu mc;
	std::vector<Course> cs = Course::all();
	for(int i = 0; i < cs.size(); ++i)
		mc.add((boost::format("%27s ") % cs[i].name).str());
	mc.width = 30;
	mc.center(false, true);
	mc.height = 10;
	mc.y = 20;
	mc.x += 15;
	mc.mark = "";
	mc.hide = false;
	mc.title = "Curso";

 	indice_course =  mc.start();
	if(cs.size() == 0){
		ms.clear();
		mc.clear();
		return;
	}
	
	Grade grade = Grade::findByStudentAndCourse(ss[indice_student].id,
																							cs[indice_course].id);

	if(grade.id == 0){
		grade.student_id = ss[indice_student].id;	
		grade.course_id = cs[indice_course].id;
		if(grade.save() == false)
			active_message("ERROR", "DATABASE ERROR");
		else 
			active_message("COMPLETADO", "El usuario ha sido matriculado");
	}
	else{
		active_message("ERROR", "El estudiante ya matriculado");
	}
	ms.clear();
	mc.clear();
}

static void active_message(std::string title, std::string msg){
	Message m;
	m.title = title;
	m.message = msg;
	m.center(false, true);
	m.start();
}

