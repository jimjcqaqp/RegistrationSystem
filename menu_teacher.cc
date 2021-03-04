#include "menu_teacher.h"
#include "Course.h"
#include "Grade.h"
#include "Form.h"
#include <boost/format.hpp>
#include <string>
#include "Student.h"
#include "Message.h"

void menu_teacher_postlogin(Teacher t);
void workload(Teacher &t);
void add_note(Teacher &t);
static void active_message(std::string title, std::string msg);

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
		std::vector<Grade> gs = Grade::allByCourseId(cs[i].id);
		// m.add(cs[i].name);
		// std::vector<Grade> gs = Grade::findByStudentAndCourse
		std::string nstudent = std::to_string(gs.size()) + " Estudiantes";
		m.add((boost::format("%24s") % cs[i].name).str() + 
					(boost::format("%23s ") % nstudent).str());
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

	int indice_student, indice_course;

	Menu mc;
	std::vector<Course> cs = Course::allByTeacher(t.id);
	for(int i = 0; i < cs.size(); ++i)
		mc.add((boost::format("%27s ") % cs[i].name).str());
	mc.width = 30;
	mc.center(false, true);
	mc.height = 10;
	mc.y = 13;
	mc.x -= 15;
	mc.mark = "";
	mc.hide = false;
	mc.title = "Curso";

 	indice_course =  mc.start();
	if(cs.size() == 0){
		mc.clear();
		return;
	}	

	Menu ms;
	std::vector<Grade> gs = Grade::allByCourseId(cs[indice_course].id);
	for(int i = 0; i < gs.size(); ++i)
	{
		Student student = Student::find(gs[i].student_id);
		ms.add( (boost::format("%27s ") % student.name).str());
	}
	ms.width = 30;
	ms.center(false, true);
	ms.height = 10;
	ms.y = 13;
	ms.x += 15;
	ms.mark = "";
	ms.hide = false;
	ms.title = "Alumno";
	ms.footer = std::to_string(gs.size());

	indice_student = ms.start();
	mc.clear();
	ms.clear();
	if(gs.size() == 0)
		return ;
	
	Grade grade_s = Grade::findByStudentAndCourse(gs[indice_student].student_id, gs[indice_student].course_id);
	
	Form fg;
	fg.add("Nota 1", 2);
	fg.add("Nota 2", 2);
	fg.add("Nota 3", 2);

	Student student = Student::find(gs[indice_student].student_id);

	fg.width = 20;
	fg.center(false, true);
	fg.y = 13;
	fg.title = student.name;

	fg.start();

	for(std::map<std::string, std::string>::iterator it = fg.inputs.begin(); 
			it != fg.inputs.end(); it++)	
		if(it->second.size() == 0)
		{
			active_message("Operacion Cancelada", "Tienes que completar todos los campos");		
			return;
		}
	active_message(std::to_string(grade_s.id), " ");
	
	grade_s.grade1 = atoi(fg.inputs["Nota 1"].c_str());
	grade_s.grade2 = atoi(fg.inputs["Nota 2"].c_str());
	grade_s.grade3 = atoi(fg.inputs["Nota 3"].c_str());
	int average = grade_s.grade1 + grade_s.grade2 + grade_s.grade3;
	average /= 3;
	grade_s.average = average;

	if(grade_s.save() == false){
		active_message("ERROR", "ERROR DB");
		return ;
	}
	active_message("Se ha agregado las notas", 
			"Promedio " + std::to_string(average));
}
static void active_message(std::string title, std::string msg){
	Message m;
	m.title = title;
	m.message = msg;
	m.center(false, true);
	m.start();
}

