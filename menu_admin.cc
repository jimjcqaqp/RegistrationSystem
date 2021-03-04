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
	m.add("Agregar profesor");
	m.add("Agregar curso");
	m.add("Agregar estudiante");
	m.add("Agregar requisito a curso");
	m.add("Matricular alumno en un curso");
	m.add("Ver Profesores");
	m.add("Ver Cursos");
	m.add("Ver Estudiantes");
	m.add("Regresar");

	m.width = 40;
	m.center(false, true);
	m.y = 5;
	m.title = "Menu administrador";
	m.hide = false;

	while(true){
		int index = m.start();
		
		switch(index){
			case 0: add_teacher();break;
			case 1: add_course() ;break;
			case 2: add_student();break;
			case 3: add_course_requirement(); break;
			case 4: register_student(); break;	
			case 5: view_teachers();break;
			case 6: view_courses() ;break;
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
	f.y = 19;
	f.title = "Agregar Curso";
	f.hide = false;
	
	f.footer = "(q) para cancelar";
	if(f.start() == false)
	{
		active_message("", "La operacion ha sido cancelado");
		return;
	}


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
	m.y = 31;			// Se puede modificar para la ubicación
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

	if(f.start() == false)
	{
		active_message("", "La operacion ha sido cancelada");
		return;
	}


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
	f.hide = false;
	f.footer = "(q) para cancelar";	

	if(f.start() == false)
	{
		active_message("", "La operacion ha sido cancelada");
		return;
	}

	Student s;
	s.code = f.inputs["Codigo"];	
	s.name = f.inputs["Nombre"];

	if(s.save() == false)
		active_message("ERROR", "ERROR DB");
	else
		active_message("COMPLETADO", "El estudiante fue creado");

	f.clear();
}
void view_courses(){
	Menu m;
	std::vector<Course> cs = Course::all();
	for(int i = 0; i < cs.size(); ++i)
	{
		Course course_re = Course::find(cs[i].course_id);
		m.add((boost::format("%6s") % cs[i].code).str().substr(0, 6) + "  " + 
					(boost::format("%25s") % cs[i].name).str().substr(0, 25) + "  " + 
					// (boost::format("%10s") % cs[i].teacher.code).str().substr(0, 10) + "  " +
					(boost::format("%22s ") % course_re.name).str().substr(0, 23) 
					);
	}

	// m.width = 70;
	m.width = 60;
	m.center(false, true);
	m.height = 10;
	m.y = 20;
	m.title = "Todos los cursos";
	m.footer = std::to_string(cs.size()) + " cursos - (e) editar - (v) detalles";
	m.mark = "";
	m.hide = false;
	m.addkey('e');
	m.addkey('v');	

	int indice = 0;

	while(true)
	{
		indice = m.start();
		if(cs.size() == 0)
			return ;
		if(m.keyup == 'v')
		{
			Course dep = Course::find(cs[indice].course_id);
			Menu viewm;
			viewm.width = 40;
			viewm.center(false, true);
			viewm.y = 38;
			viewm.title = "Detalles";
			viewm.mark = "";	
			viewm.add((boost::format("%-12s: ") % "ID").str() + (boost::format("%-25s") % cs[indice].id).str());
			viewm.add((boost::format("%-12s: ") % "Codigo").str() + (boost::format("%-25s") % cs[indice].code).str());
			viewm.add((boost::format("%-12s: ") % "Nombre").str() + (boost::format("%-25s") % cs[indice].name).str());
			viewm.add((boost::format("%-12s: ") % "Profesor").str() + (boost::format("%-25s") % cs[indice].teacher.name).str());
			viewm.add((boost::format("%-12s: ") % "Dependencia").str() + (boost::format("%-25s") % dep.name).str());
					
			viewm.start();
			m.keyup = 10;
		}
		else
			break;
	}	
	if(m.keyup == 'e')	
	{
		m.clear();
		Form f;	
		f.add("Codigo", 5);
		f.add("Nombre", 25);
		f.width = 40;
		f.center(false, true);
		f.y = 20;
		f.title = "Editar " + cs[indice].name;
		f.hide = true;
		f.footer = "(q) para cancelar (d) default";

		if(f.start() == false)
		{
			active_message("", "La operacion ha sido cancelada");
			return;
		}
		
		Menu mt;	
		std::vector<Teacher> ts = Teacher::all();
		for(int i = 0; i < ts.size(); ++i)
			mt.add(ts[i].name);
		mt.width = 40;
		mt.center(false, true);
		mt.height = 5;
		mt.y = 31;			// Se puede modificar para la ubicación
		mt.title = "Profesor encargado";
		mt.mark = "";
		mt.hide = false;
		mt.footer = "(d) default";
		mt.addkey('d');
		int indice_edit = mt.start();

		if(ts.size() == 0)
			return ;

		Course c = Course::find(cs[indice].id);

		for(std::map<std::string, std::string>::iterator it = f.inputs.begin(); 
				it != f.inputs.end(); it++)
		{
			if(it->second != "d")
			{
				if(it->first == "Codigo")
					c.code = it->second;
				else if(it->first == "Nombre")
					c.name = it->second;
			}
		}
		if(mt.keyup != 'd')
			c.teacher = ts[indice_edit];	

		// t.code = f.inputs["Codigo"];	
		// t.name = f.inputs["Nombre"];
		
		if(c.save() == false)
			active_message("ERROR", "ERROR DB");
		else
			active_message("COMPLETADO", "Actualizacion completa");
	}

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
	m.footer = std::to_string(ts.size()) + " profesores - (e) editar";
	m.mark = "";
	m.hide = true;
	m.addkey('e');

	int indice = m.start();

	// Si es que no hay nada para seleccionar
	if(ts.size() == 0)
		return;

	if(m.keyup == 'e')	
	{
		Form f;	
		f.add("Codigo", 10);
		f.add("Nombre", 25);
		f.width = 40;
		f.center(false, true);
		f.y = 20;
		f.title = "Editar " + ts[indice].name;
		f.hide = true;
		f.footer = "(q) para cancelar (d) default";

		if(f.start() == false)
		{
			active_message("", "La operacion ha sido cancelada");
			return;
		}

		Teacher t = Teacher::find(ts[indice].id);

		for(std::map<std::string, std::string>::iterator it = f.inputs.begin(); 
				it != f.inputs.end(); it++)
		{
			if(it->second != "d")
			{
				if(it->first == "Codigo")
					t.code = it->second;
				else if(it->first == "Nombre")
					t.name = it->second;
			}
		}

		// t.code = f.inputs["Codigo"];	
		// t.name = f.inputs["Nombre"];
		
		if(t.save() == false)
			active_message("ERROR", "ERROR DB");
		else
			active_message("COMPLETADO", "Actualizacion completa");
	}	

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
	m.footer = std::to_string(ss.size()) + " estudiantes - (e) editar";
	m.mark = "";
	m.hide = true;
	m.addkey('e');

	int indice_student = m.start();
	if(ss.size() == 0)
		return;

	if(m.keyup == 'e')	
	{
		Form f;	
		f.add("Codigo", 10);
		f.add("Nombre", 25);
		f.width = 40;
		f.center(false, true);
		f.y = 20;
		f.title = "Editar " + ss[indice_student].name;
		f.hide = true;
		f.footer = "(q) para cancelar (d) default";

		if(f.start() == false)
		{
			active_message("", "La operacion ha sido cancelada");
			return;
		}

		Student student = Student::find(ss[indice_student].id);

		for(std::map<std::string, std::string>::iterator it = f.inputs.begin(); 
				it != f.inputs.end(); it++)
		{
			if(it->second != "d")
			{
				if(it->first == "Codigo")
					student.code = it->second;
				else if(it->first == "Nombre")
					student.name = it->second;
			}
		}

		// t.code = f.inputs["Codigo"];	
		// t.name = f.inputs["Nombre"];
		
		if(student.save() == false)
			active_message("ERROR", "ERROR DB");
		else
			active_message("COMPLETADO", "Actualizacion completa");
	}	


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
	m.hide = false;
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

	if(cs[indice_course].course_id < 0){	
		Grade grade_dep = Grade::findByStudentAndCourse(ss[indice_student].id, 
																										cs[indice_course].course_id);
		if(grade_dep.id == 0)
		{
			Course course_dep = Course::find(cs[indice_course].course_id);
			active_message("Para continuar se debe estar", "matriculado en " + course_dep.name.substr(0, 20));
			return ;
		}
	
		if(grade_dep.average == -1){
			// Aqui se debe de agregar la nota minima o maxima para matricularse 
			if(grade_dep.average < 10){
				Course course_dep = Course::find(cs[indice_course].course_id);
				active_message("Nota insuficiente, mejorar", "notas en " + course_dep.name.substr(0, 20));
				return ;
			}
		}
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

