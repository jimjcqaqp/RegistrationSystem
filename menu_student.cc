#include "menu_student.h"

void menu_student_postlogin(Student &s);
void report(Student &s);
// void report_grade(Student &s);

void menu_student(){
	std::vector<Student> ss = Student::all();
	Menu m;

	for(int i = 0; i < ss.size(); ++i)
		m.add(ss[i].name);
	m.add("Salir");

	m.width = 40;
	m.center(false, true);
	m.y = 5;
	m.title = "Login";
	m.hide = true;
	
	int indice = m.start();
	if(indice == ss.size())
		return;
	menu_student_postlogin(ss[indice]);
}

void menu_student_postlogin(Student &s){
	Menu m;
	m.add("Ver constancia de matriculas");
	// m.add("Ver constancia de notas");
	m.add("Salir");	
	m.width = 40;
	m.center(false, true);
	m.y = 5;
	m.title = s.name;
	m.hide = true;

	while(true){
		int indice = m.start();
		switch(indice){
			case 0: 
				report(s);
				break;
			/*case 1:
				report_grade(s);
				break;*/
		}
		if(indice == 1)
			break;
	}
}

void report(Student &s){
	Menu m;

	std::vector<Grade> gs = Grade::allByStudentId(s.id);
	for(int i = 0; i < gs.size(); ++i)
	{
		Course course = Course::find(gs[i].course_id);
		m.add((boost::format("  %-36s  ") % course.name).str());
	}
	m.width = 40;
	m.center(false, true);
	m.y = 5;
	m.height = 5;
	m.title = s.name;
	m.footer = "(v) detalles";
	m.hide = false;
	m.mark = "";
	m.addkey('v');

	int indice_course = 0;
	while(true){
		indice_course = m.start();
		if(gs.size() == 0)
			return;
		if(m.keyup == 'v'){
			Course course = Course::find(gs[indice_course].course_id);
			Menu menu_grade;
			menu_grade.width = 40;
			menu_grade.center(false, true);
			menu_grade.y = 18;
			menu_grade.title = course.name;
			
			std::string grade1 = (gs[indice_course].grade1 == -1)? "" : std::to_string(gs[indice_course].grade1);
			std::string grade2 = (gs[indice_course].grade2 == -1)? "" : std::to_string(gs[indice_course].grade2);
			std::string grade3 = (gs[indice_course].grade3 == -1)? "" : std::to_string(gs[indice_course].grade3);
			std::string average = (gs[indice_course].average == -1)? "" : std::to_string(gs[indice_course].average);
			
			menu_grade.add( (boost::format("%-12s: %-25s") % "Encargado" % course.teacher.name).str() );	
			menu_grade.add( (boost::format("%-12s: %-25s") % "Nota 01" % grade1).str() );
			menu_grade.add( (boost::format("%-12s: %-25s") % "Nota 02" % grade2).str() );
			menu_grade.add( (boost::format("%-12s: %-25s") % "Nota 03" % grade3).str() );
			menu_grade.add( (boost::format("%-12s: %-25s") % "Promedio" % average).str() );

			menu_grade.start();
			m.resetkey();;
		}
		else
			break;
	}
		
}

